// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The Ion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/transactionrecord.h>

#include "base58.h"
#include "obfuscation.h"
#include "swifttx.h"
#include "timedata.h"
#include "wallet.h"
#include "xionchain.h"

#include <stdint.h>


/* Return positive answer if transaction should be shown in list.
 */
bool TransactionRecord::showTransaction(const CWalletTx &wtx)
{
    // There are currently no cases where we hide transactions, but
    // we may want to use this in the future for things like RBF.
    return true;
}

/*
 * Decompose CWallet transaction to model transaction records.
 */
std::vector<TransactionRecord> TransactionRecord::decomposeTransaction(const CWallet* wallet, const CWalletTx& wtx)
{
    std::vector<TransactionRecord> parts;
    int64_t nTime = wtx.GetComputedTxTime();
    CAmount nCredit = wtx.GetCredit(ISMINE_ALL);
    CAmount nDebit = wtx.GetDebit(ISMINE_ALL);
    CAmount nNet = nCredit - nDebit;
    uint256 hash = wtx.GetHash();
    std::map<std::string, std::string> mapValue = wtx.mapValue;
    bool fZSpendFromMe = false;

    if (wtx.IsZerocoinSpend()) {
        // a zerocoin spend that was created by this wallet
        libzerocoin::CoinSpend zcspend = TxInToZerocoinSpend(wtx.vin[0]);
        fZSpendFromMe = wallet->IsMyZerocoinSpend(zcspend.getCoinSerialNumber());
    }

    if (wtx.IsCoinStake()) {
        TransactionRecord sub(hash, nTime);
        CTxDestination address;
        if (!wtx.IsZerocoinSpend() && !ExtractDestination(wtx.vout[1].scriptPubKey, address))
            return parts;

        if (wtx.IsZerocoinSpend() && (fZSpendFromMe || wallet->xionTracker->HasMintTx(hash))) {
            //xION stake reward
            sub.involvesWatchAddress = false;
            sub.type = TransactionRecord::StakeXION;
            sub.address = mapValue["zerocoinmint"];
            sub.credit = 0;
            for (const CTxOut& out : wtx.vout) {
                if (out.IsZerocoinMint())
                    sub.credit += out.nValue;
            }
            sub.debit -= wtx.vin[0].nSequence * COIN;
        } else if (isminetype mine = wallet->IsMine(wtx.vout[1])) {
            // ION stake reward
            sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
            sub.type = TransactionRecord::StakeMint;
            sub.address = EncodeDestination(address);
            sub.credit = nNet;
        } else {
            //Masternode reward
            CTxDestination destMN;
            int nIndexMN = wtx.vout.size() - 1;
            if (ExtractDestination(wtx.vout[nIndexMN].scriptPubKey, destMN) && IsMine(*wallet, destMN)) {
                isminetype mine = wallet->IsMine(wtx.vout[nIndexMN]);
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                sub.type = TransactionRecord::MNReward;
                sub.address = EncodeDestination(destMN);
                sub.credit = wtx.vout[nIndexMN].nValue;
            }
        }

        parts.push_back(sub);
    } else if (wtx.IsZerocoinSpend()) {
        //zerocoin spend outputs
        bool fFeeAssigned = false;
        for (const CTxOut& txout : wtx.vout) {
            // change that was reminted as zerocoins
            if (txout.IsZerocoinMint()) {
                // do not display record if this isn't from our wallet
                if (!fZSpendFromMe)
                    continue;

                isminetype mine = wallet->IsMine(txout);
                TransactionRecord sub(hash, nTime);
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                sub.type = TransactionRecord::ZerocoinSpend_Change_xIon;
                sub.address = mapValue["zerocoinmint"];
                if (!fFeeAssigned) {
                    sub.debit -= (wtx.GetZerocoinSpent() - wtx.GetValueOut());
                    fFeeAssigned = true;
                }
                sub.idx = parts.size();
                parts.push_back(sub);
                continue;
            }

            string strAddress = "";
            CTxDestination address;
            if (ExtractDestination(txout.scriptPubKey, address))
                strAddress = EncodeDestination(address);

            // a zerocoinspend that was sent to an address held by this wallet
            isminetype mine = wallet->IsMine(txout);
            if (mine) {
                TransactionRecord sub(hash, nTime);
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                if (fZSpendFromMe) {
                    sub.type = TransactionRecord::ZerocoinSpend_FromMe;
                } else {
                    sub.type = TransactionRecord::RecvFromZerocoinSpend;
                    sub.credit = txout.nValue;
                }
                sub.address = mapValue["recvzerocoinspend"];
                if (strAddress != "")
                    sub.address = strAddress;
                sub.idx = parts.size();
                parts.push_back(sub);
                continue;
            }

            // spend is not from us, so do not display the spend side of the record
            if (!fZSpendFromMe)
                continue;

            // zerocoin spend that was sent to someone else
            TransactionRecord sub(hash, nTime);
            sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
            sub.debit = -txout.nValue;
            sub.type = TransactionRecord::ZerocoinSpend;
            sub.address = mapValue["zerocoinspend"];
            if (strAddress != "")
                sub.address = strAddress;
            sub.idx = parts.size();
            parts.push_back(sub);
        }
    } else if (nNet > 0 || wtx.IsCoinBase()) {
        //
        // Credit
        //
        for(unsigned int i = 0; i < wtx.tx->vout.size(); i++)
        {
            const CTxOut& txout = wtx.tx->vout[i];
            isminetype mine = wallet->IsMine(txout);
            if(mine)
            {
                TransactionRecord sub(hash, nTime);
                CTxDestination address;
                sub.idx = i; // vout index
                sub.credit = txout.nValue;
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                if (ExtractDestination(txout.scriptPubKey, address) && IsMine(*wallet, address)) {
                    // Received by ION Address
                    sub.type = TransactionRecord::RecvWithAddress;
                    sub.address = EncodeDestination(address);
                } else {
                    // Received by IP connection (deprecated features), or a multisignature or other non-simple transaction
                    sub.type = TransactionRecord::RecvFromOther;
                    sub.strAddress = mapValue["from"];
                    sub.txDest = DecodeDestination(sub.strAddress);
                }
                if (wtx.IsCoinBase())
                {
                    // Generated
                    sub.type = TransactionRecord::Generated;
                }

                parts.push_back(sub);
            }
        }
    }
    else
    {
        bool fAllFromMeDenom = true;
        int nFromMe = 0;
        bool involvesWatchAddress = false;
        isminetype fAllFromMe = ISMINE_SPENDABLE;
        for (const CTxIn& txin : wtx.tx->vin)
        {
            if(wallet->IsMine(txin)) {
                fAllFromMeDenom = fAllFromMeDenom && wallet->IsDenominated(txin.prevout);
                nFromMe++;
            }
            isminetype mine = wallet->IsMine(txin);
            if(mine & ISMINE_WATCH_ONLY) involvesWatchAddress = true;
            if(fAllFromMe > mine) fAllFromMe = mine;
        }

        isminetype fAllToMe = ISMINE_SPENDABLE;
        bool fAllToMeDenom = true;
        int nToMe = 0;
        for (const CTxOut& txout : wtx.tx->vout) {
            if(wallet->IsMine(txout)) {
                fAllToMeDenom = fAllToMeDenom && CPrivateSend::IsDenominatedAmount(txout.nValue);
                nToMe++;
            }
            isminetype mine = wallet->IsMine(txout);
            if(mine & ISMINE_WATCH_ONLY) involvesWatchAddress = true;
            if(fAllToMe > mine) fAllToMe = mine;
        }

        if (fAllFromMeDenom && fAllToMeDenom && nFromMe * nToMe) {
            parts.push_back(TransactionRecord(hash, nTime, TransactionRecord::ObfuscationDenominate, "", -nDebit, nCredit));
            parts.back().involvesWatchAddress = false; // maybe pass to TransactionRecord as constructor argument
        } else if (fAllFromMe && fAllToMe) {
            // Payment to self
            // TODO: this section still not accurate but covers most cases,
            // might need some additional work however

            TransactionRecord sub(hash, nTime);
            // Payment to self by default
            sub.type = TransactionRecord::SendToSelf;
            sub.strAddress = "";

            if(mapValue["DS"] == "1")
            {
                sub.type = TransactionRecord::PrivateSend;
                CTxDestination address;
                if (ExtractDestination(wtx.vout[0].scriptPubKey, address)) {
                    // Sent to ION Address
                    sub.address = EncodeDestination(address);
                } else {
                    // Sent to IP, or other non-address transaction like OP_EVAL
                    sub.strAddress = mapValue["to"];
                    sub.txDest = DecodeDestination(sub.strAddress);
                }
            }
            else
            {
                sub.idx = parts.size();
                if(wtx.tx->vin.size() == 1 && wtx.tx->vout.size() == 1
                    && CPrivateSend::IsCollateralAmount(nDebit)
                    && CPrivateSend::IsCollateralAmount(nCredit)
                    && CPrivateSend::IsCollateralAmount(-nNet))
                {
                    sub.type = TransactionRecord::PrivateSendCollateralPayment;
                } else {
                    bool fMakeCollateral{false};
                    if (wtx.tx->vout.size() == 2) {
                        CAmount nAmount0 = wtx.tx->vout[0].nValue;
                        CAmount nAmount1 = wtx.tx->vout[1].nValue;
                        // <case1>, see CPrivateSendClientSession::MakeCollateralAmounts
                        fMakeCollateral = (nAmount0 == CPrivateSend::GetMaxCollateralAmount() && !CPrivateSend::IsDenominatedAmount(nAmount1) && nAmount1 >= CPrivateSend::GetCollateralAmount()) ||
                                          (nAmount1 == CPrivateSend::GetMaxCollateralAmount() && !CPrivateSend::IsDenominatedAmount(nAmount0) && nAmount0 >= CPrivateSend::GetCollateralAmount()) ||
                        // <case2>, see CPrivateSendClientSession::MakeCollateralAmounts
                                          (nAmount0 == nAmount1 && CPrivateSend::IsCollateralAmount(nAmount0));
                    } else if (wtx.tx->vout.size() == 1) {
                        // <case3>, see CPrivateSendClientSession::MakeCollateralAmounts
                        fMakeCollateral = CPrivateSend::IsCollateralAmount(wtx.tx->vout[0].nValue);
                    }
                    if (fMakeCollateral) {
                        sub.type = TransactionRecord::PrivateSendMakeCollaterals;
                    } else {
                        for (const auto& txout : wtx.tx->vout) {
                            if (CPrivateSend::IsDenominatedAmount(txout.nValue)) {
                                sub.type = TransactionRecord::PrivateSendCreateDenominations;
                                break; // Done, it's definitely a tx creating mixing denoms, no need to look any further
                            }
                        }
                    }
                }
            }

            CAmount nChange = wtx.GetChange();

            sub.debit = -(nDebit - nChange);
            sub.credit = nCredit - nChange;
            parts.push_back(sub);
            parts.back().involvesWatchAddress = involvesWatchAddress; // maybe pass to TransactionRecord as constructor argument
        } else if (fAllFromMe || wtx.IsZerocoinMint()) {
            //
            // Debit
            //
            CAmount nTxFee = nDebit - wtx.tx->GetValueOut();

            bool fDone = false;
            if(wtx.tx->vin.size() == 1 && wtx.tx->vout.size() == 1
                && CPrivateSend::IsCollateralAmount(nDebit)
                && nCredit == 0 // OP_RETURN
                && CPrivateSend::IsCollateralAmount(-nNet))
            {
                TransactionRecord sub(hash, nTime);
                sub.idx = 0;
                sub.type = TransactionRecord::PrivateSendCollateralPayment;
                sub.debit = -nDebit;
                parts.append(sub);
                fDone = true;
            }

            for (unsigned int nOut = 0; nOut < wtx.tx->vout.size() && !fDone; nOut++)
            {
                const CTxOut& txout = wtx.tx->vout[nOut];
                TransactionRecord sub(hash, nTime);
                sub.idx = nOut;
                sub.involvesWatchAddress = involvesWatchAddress;

                if(wallet->IsMine(txout))
                {
                    // Ignore parts sent to self, as this is usually the change
                    // from a transaction sent back to our own address.
                    continue;
                }

                CTxDestination address;
                if (ExtractDestination(txout.scriptPubKey, address)) {
                    //This is most likely only going to happen when resyncing deterministic wallet without the knowledge of the
                    //private keys that the change was sent to. Do not display a "sent to" here.
                    if (wtx.IsZerocoinMint())
                        continue;
                    // Sent to ION Address
                    sub.type = TransactionRecord::SendToAddress;
                    sub.address = EncodeDestination(address);
                } else if (txout.IsZerocoinMint()){
                    sub.type = TransactionRecord::ZerocoinMint;
                    sub.address = mapValue["zerocoinmint"];
                    sub.credit += txout.nValue;
                } else {
                    // Sent to IP, or other non-address transaction like OP_EVAL
                    sub.type = TransactionRecord::SendToOther;
                    sub.strAddress = mapValue["to"];
                    sub.txDest = DecodeDestination(sub.strAddress);
                }

                if(mapValue["DS"] == "1")
                {
                    sub.type = TransactionRecord::PrivateSend;
                }

                CAmount nValue = txout.nValue;
                /* Add fee to first output */
                if (nTxFee > 0)
                {
                    nValue += nTxFee;
                    nTxFee = 0;
                }
                sub.debit = -nValue;

                parts.push_back(sub);
            }
        }
        else
        {
            //
            // Mixed debit transaction, can't break down payees
            //
            parts.push_back(TransactionRecord(hash, nTime, TransactionRecord::Other, "", nNet, 0));
            parts.back().involvesWatchAddress = involvesWatchAddress;
        }
    }

    return parts;
}

bool IsXIONType(TransactionRecord::Type type)
{
    switch (type) {
        case TransactionRecord::StakeXION:
        case TransactionRecord::ZerocoinMint:
        case TransactionRecord::ZerocoinSpend:
        case TransactionRecord::RecvFromZerocoinSpend:
        case TransactionRecord::ZerocoinSpend_Change_xIon:
        case TransactionRecord::ZerocoinSpend_FromMe:
            return true;
        default:
            return false;
    }
}

void TransactionRecord::updateStatus(const CWalletTx& wtx)
{
    AssertLockHeld(cs_main);
    AssertLockHeld(wtx.GetWallet()->cs_wallet);
    // Determine transaction status

    // Find the block the tx is in
    CBlockIndex* pindex = nullptr;
    BlockMap::iterator mi = mapBlockIndex.find(wtx.hashBlock);
    if (mi != mapBlockIndex.end())
        pindex = (*mi).second;

    // Sort order, unrecorded transactions sort to the top
    status.sortKey = strprintf("%010d-%01d-%010u-%03d",
        (pindex ? pindex->nHeight : std::numeric_limits<int>::max()),
        (wtx.IsCoinBase() ? 1 : 0),
        wtx.nTimeReceived,
        idx);
    //status.countsForBalance = wtx.IsTrusted() && !(wtx.GetBlocksToMaturity() > 0);
    status.depth = wtx.GetDepthInMainChain();

    //Determine the depth of the block
    int nBlocksToMaturity = wtx.GetBlocksToMaturity();

    status.countsForBalance = wtx.IsTrusted() && !(nBlocksToMaturity > 0);
    status.cur_num_blocks = chainActive.Height();
    status.cachedChainLockHeight = chainLockHeight;

    bool oldLockedByChainLocks = status.lockedByChainLocks;
    if (!status.lockedByChainLocks) {
        status.lockedByChainLocks = wtx.IsChainLocked();
    }

    auto addrBookIt = wtx.GetWallet()->mapAddressBook.find(this->txDest);
    if (addrBookIt == wtx.GetWallet()->mapAddressBook.end()) {
        status.label = "";
    } else {
        status.label = QString::fromStdString(addrBookIt->second.name);
    }

    if (!CheckFinalTx(*wtx.tx))
    {
        if (wtx.tx->nLockTime < LOCKTIME_THRESHOLD)
        {
            status.status = TransactionStatus::OpenUntilBlock;
            status.open_for = wtx.tx->nLockTime - chainActive.Height();
        }
        else
        {
            status.status = TransactionStatus::OpenUntilDate;
            status.open_for = wtx.tx->nLockTime;
        }
    }
    // For generated transactions, determine maturity
    else if (type == TransactionRecord::Generated || type == TransactionRecord::StakeMint || type == TransactionRecord::StakeXION || type == TransactionRecord::MNReward) {
        if (nBlocksToMaturity > 0) {
            status.status = TransactionStatus::Immature;
            status.matures_in = nBlocksToMaturity;

            if (pindex && chainActive.Contains(pindex)) {
                // Check if the block was requested by anyone
                if (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0)
                    status.status = TransactionStatus::MaturesWarning;
            } else {
                status.status = TransactionStatus::NotAccepted;
            }
        }
        else
        {
            status.status = TransactionStatus::Confirmed;
            status.matures_in = 0;
        }
    }
    else
    {
        // The IsLockedByInstantSend call is quite expensive, so we only do it when a state change is actually possible.
        if (status.lockedByChainLocks) {
            if (oldLockedByChainLocks != status.lockedByChainLocks) {
                status.lockedByInstantSend = wtx.IsLockedByInstantSend();
            } else {
                status.lockedByInstantSend = false;
            }
        } else if (!status.lockedByInstantSend) {
            status.lockedByInstantSend = wtx.IsLockedByInstantSend();
        }

        if (status.depth < 0)
        {
            status.status = TransactionStatus::Conflicted;
        }
        else if (status.depth == 0)
        {
            status.status = TransactionStatus::Unconfirmed;
            if (wtx.isAbandoned())
                status.status = TransactionStatus::Abandoned;
        }
        else if (status.depth < RecommendedNumConfirmations && !status.lockedByChainLocks)
        {
            status.status = TransactionStatus::Confirming;
        }
        else
        {
            status.status = TransactionStatus::Confirmed;
        }
    }
    status.needsUpdate = false;
}

bool TransactionRecord::statusUpdateNeeded(int chainLockHeight) const
{
    AssertLockHeld(cs_main);
    return status.cur_num_blocks != chainActive.Height() || status.needsUpdate
        || (!status.lockedByChainLocks && status.cachedChainLockHeight != chainLockHeight);
}

std::string TransactionRecord::getTxID() const
{
    //return QString::fromStdString(hash.ToString());
    return hash.ToString();
}

int TransactionRecord::getOutputIndex() const
{
    return idx;
}
