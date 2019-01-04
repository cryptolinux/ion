// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The Ion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/transaction.h>

#include "chain.h"
#include "hash.h"
#include "main.h"
#include "tinyformat.h"
#include "utilstrencodings.h"
#include "transaction.h"

#include <boost/foreach.hpp>

std::string COutPoint::ToString() const
{
    return strprintf("COutPoint(%s, %u)", hash.ToString()/*.substr(0,10)*/, n);
}

std::string COutPoint::ToStringShort() const
{
    return strprintf("%s-%u", hash.ToString().substr(0,64), n);
}

CTxIn::CTxIn(COutPoint prevoutIn, CScript scriptSigIn, uint32_t nSequenceIn)
{
    prevout = prevoutIn;
    scriptSig = scriptSigIn;
    nSequence = nSequenceIn;
}

CTxIn::CTxIn(uint256 hashPrevTx, uint32_t nOut, CScript scriptSigIn, uint32_t nSequenceIn)
{
    prevout = COutPoint(hashPrevTx, nOut);
    scriptSig = scriptSigIn;
    nSequence = nSequenceIn;
}

std::string CTxIn::ToString() const
{
    std::string str;
    str += "CTxIn(";
    str += prevout.ToString();
    if (prevout.IsNull())
        if(scriptSig.IsZerocoinSpend())
            str += strprintf(", zerocoinspend %s...", HexStr(scriptSig).substr(0, 25));
        else
            str += strprintf(", coinbase %s", HexStr(scriptSig));
    else
        str += strprintf(", scriptSig=%s", HexStr(scriptSig).substr(0, 24));
    if (nSequence != SEQUENCE_FINAL)
        str += strprintf(", nSequence=%u", nSequence);
    str += ")";
    return str;
}

CTxOut::CTxOut(const CAmount& nValueIn, CScript scriptPubKeyIn, int nRoundsIn)
{
    nValue = nValueIn;
    scriptPubKey = scriptPubKeyIn;
    nRounds = nRoundsIn;
}

bool CTxOut::IsZerocoinMint() const
{
    return scriptPubKey.IsZerocoinMint();
}

std::string CTxOut::ToString() const
{
    return strprintf("CTxOut(nValue=%d.%08d, scriptPubKey=%s)", nValue / COIN, nValue % COIN, HexStr(scriptPubKey).substr(0, 30));
}

CMutableTransaction::CMutableTransaction() : nVersion(CTransaction::CURRENT_VERSION), nType(TRANSACTION_NORMAL), nTime(0), nLockTime(0) {}
CMutableTransaction::CMutableTransaction(const CTransaction& tx) : nVersion(tx.nVersion), nType(tx.nType), nTime(tx.nTime), vin(tx.vin), vout(tx.vout), nLockTime(tx.nLockTime), vExtraPayload(tx.vExtraPayload) {}

uint256 CMutableTransaction::GetHash() const
{
    return SerializeHash(*this);
}

std::string CMutableTransaction::ToString() const
{
    std::string str;
    str += strprintf("CMutableTransaction(ver=%d, ",
        nVersion);
        if (nVersion == 1)
            str += strprintf("nTime=%d, ", nTime);
        str += strprintf("vin.size=%u, vout.size=%u, nLockTime=%u)\n",
        vin.size(),
        vout.size(),
        nLockTime,
        vExtraPayload.size());
    for (unsigned int i = 0; i < vin.size(); i++)
        str += "    " + vin[i].ToString() + "\n";
    for (unsigned int i = 0; i < vout.size(); i++)
        str += "    " + vout[i].ToString() + "\n";
    return str;
}

uint256 CTransaction::ComputeHash() const
{
    return SerializeHash(*this);
}

CTransaction& CTransaction::operator=(const CTransaction &tx) {
    *const_cast<int*>(&nVersion) = tx.nVersion;
    *const_cast<std::vector<CTxIn>*>(&vin) = tx.vin;
    *const_cast<std::vector<CTxOut>*>(&vout) = tx.vout;
    *const_cast<unsigned int*>(&nLockTime) = tx.nLockTime;
    *const_cast<uint256*>(&hash) = tx.hash;
    return *this;
}

bool CTransaction::IsCoinStake() const
{
    if (vin.empty())
        return false;

    // ppcoin: the coin stake transaction is marked with the first output empty
    bool fAllowNull = vin[0].scriptSig.IsZerocoinSpend();
    if (vin[0].prevout.IsNull() && !fAllowNull)
        return false;

    return (vin.size() > 0 && vout.size() >= 2 && vout[0].IsEmpty());
}

CAmount CTransaction::GetValueOut() const
{
    if (vin.empty())
        return false;

    // ppcoin: the coin stake transaction is marked with the first output empty
    bool fAllowNull = vin[0].scriptSig.IsZerocoinSpend();
    if (vin[0].prevout.IsNull() && !fAllowNull)
        return false;

    return (vin.size() > 0 && vout.size() >= 2 && vout[0].IsEmpty());
}

CAmount CTransaction::GetValueOut() const
{
    CAmount nValueOut = 0;
    for (const auto& tx_out : vout) {
        nValueOut += tx_out.nValue;
        if (!MoneyRange(tx_out.nValue) || !MoneyRange(nValueOut))
            throw std::runtime_error(std::string(__func__) + ": value out of range");
    }
    return nValueOut;
}

unsigned int CTransaction::GetTotalSize() const
{
    for (const CTxOut& txOut : vout) {
        if(!txOut.scriptPubKey.IsZerocoinMint())
            continue;

        return txOut.nValue;
    }

std::string CTransaction::ToString() const
{
    std::string str;
    str += strprintf("CTransaction(hash=%s, ver=%d, type=%d, vin.size=%u, vout.size=%u, nTime=%u, nLockTime=%u, vExtraPayload.size=%d)\n",
        GetHash().ToString().substr(0,10),
        nVersion,
        nType,
        nTime,
        vin.size(),
        vout.size(),
        nLockTime,
        vExtraPayload.size());
    for (const auto& tx_in : vin)
        str += "    " + tx_in.ToString() + "\n";
    for (const auto& tx_out : vout)
        str += "    " + tx_out.ToString() + "\n";
    return str;
}

bool CTransaction::HasZerocoinSpendInputs() const
{
    for (const CTxIn& in : vin) {
        if (in.prevout == out)
            return true;
    }
    return false;
}

bool CTransaction::HasZerocoinMintOutputs() const
{
    if(!IsZerocoinSpend())
        return 0;

    CAmount nValueOut = 0;
    for (const CTxIn& txin : vin) {
        if(!txin.scriptSig.IsZerocoinSpend())
            continue;

        nValueOut += txin.nSequence * COIN;
    }
    return false;
}

bool CTransaction::HasZerocoinPublicSpendInputs() const
{
    int nCount = 0;
    for (const CTxOut& out : vout) {
        if (out.scriptPubKey.IsZerocoinMint())
            nCount++;
    }
    return false;
}

bool CTransaction::IsCoinStake() const
{
    if (vin.empty())
        return false;

    // ppcoin: the coin stake transaction is marked with the first output empty
    bool fAllowNull = vin[0].IsZerocoinSpend();
    if (vin[0].prevout.IsNull() && !fAllowNull)
        return false;

    return (vout.size() >= 2 && vout[0].IsEmpty());
}

bool CTxIn::IsZerocoinSpend() const
{
    return prevout.hash == uint256() && scriptSig.IsZerocoinSpend();
}

bool CTxIn::IsZerocoinPublicSpend() const
{
    std::string str;
    str += strprintf("CTransaction(hash=%s, ver=%d, vin.size=%u, vout.size=%u, nLockTime=%u)\n",
        GetHash().ToString().substr(0,10),
        nVersion,
        vin.size(),
        vout.size(),
        nLockTime);
    for (unsigned int i = 0; i < vin.size(); i++)
        str += "    " + vin[i].ToString() + "\n";
    for (unsigned int i = 0; i < vout.size(); i++)
        str += "    " + vout[i].ToString() + "\n";
    return str;
}
