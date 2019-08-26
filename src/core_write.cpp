// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018-2019 The Ion developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <core_io.h>

#include "base58.h"
#include "primitives/transaction.h"
#include "script/script.h"
#include "script/standard.h"
#include "serialize.h"
#include "streams.h"
#include "tokens/tokengroupdescription.h"
#include "univalue.h"
#include "util.h"
#include "utilmoneystr.h"
#include "utilstrencodings.h"



std::string FormatScript(const CScript& script)
{
    std::string ret;
    CScript::const_iterator it = script.begin();
    opcodetype op;
    while (it != script.end()) {
        CScript::const_iterator it2 = it;
        std::vector<unsigned char> vch;
        if (script.GetOp2(it, op, &vch)) {
            if (op == OP_0) {
                ret += "0 ";
                continue;
            } else if ((op >= OP_1 && op <= OP_16) || op == OP_1NEGATE) {
                ret += strprintf("%i ", op - OP_1NEGATE - 1);
                continue;
            } else if (op >= OP_NOP && op <= OP_CHECKMULTISIGVERIFY) {
                std::string str(GetOpName(op));
                if (str.substr(0, 3) == std::string("OP_")) {
                    ret += str.substr(3, std::string::npos) + " ";
                    continue;
                }
            }
            if (vch.size() > 0) {
                ret += strprintf("0x%x 0x%x ", HexStr(it2, it - vch.size()), HexStr(it - vch.size(), it));
            } else {
                ret += strprintf("0x%x ", HexStr(it2, it));
            }
            continue;
        }
        ret += strprintf("0x%x ", HexStr(it2, script.end()));
        break;
    }
    return ret.substr(0, ret.size() - 1);
}

std::string EncodeHexTx(const CTransaction& tx)
{
    CDataStream ssTx(SER_NETWORK, PROTOCOL_VERSION);
    ssTx << tx;
    return HexStr(ssTx.begin(), ssTx.end());
}

void ScriptPubKeyToUniv(const CScript& scriptPubKey,
                        UniValue& out, bool fIncludeHex)
{
    txnouttype type;
    std::vector<CTxDestination> addresses;
    int nRequired;

    out.pushKV("asm", ScriptToAsmStr(scriptPubKey));
    if (fIncludeHex)
        out.pushKV("hex", HexStr(scriptPubKey.begin(), scriptPubKey.end()));

    if (!ExtractDestinations(scriptPubKey, type, addresses, nRequired)) {
        out.pushKV("type", GetTxnOutputType(type));
        return;
    }

    out.pushKV("reqSigs", nRequired);
    out.pushKV("type", GetTxnOutputType(type));

    UniValue a(UniValue::VARR);
    for (const CTxDestination& addr : addresses)
        a.push_back(CBitcoinAddress(addr).ToString());
    out.pushKV("addresses", a);
}

void TxToUniv(const CTransaction& tx, const uint256& hashBlock, UniValue& entry, bool include_hex, const CSpentIndexTxInfo* ptxSpentInfo)
{
    uint256 txid = tx.GetHash();
    entry.pushKV("txid", txid.GetHex());
    entry.pushKV("version", tx.nVersion);
    entry.pushKV("size", (int)::GetSerializeSize(tx, SER_NETWORK, PROTOCOL_VERSION));
    entry.pushKV("locktime", (int64_t)tx.nLockTime);

    UniValue vin(UniValue::VARR);
    for (const CTxIn& txin : tx.vin) {
        UniValue in(UniValue::VOBJ);
        if (tx.IsCoinBase())
            in.pushKV("coinbase", HexStr(txin.scriptSig.begin(), txin.scriptSig.end()));
        else {
            in.pushKV("txid", txin.prevout.hash.GetHex());
            in.pushKV("vout", (int64_t)txin.prevout.n);
            UniValue o(UniValue::VOBJ);
            o.pushKV("asm", ScriptToAsmStr(txin.scriptSig, true));
            o.pushKV("hex", HexStr(txin.scriptSig.begin(), txin.scriptSig.end()));
            in.pushKV("scriptSig", o);

            // Add address and value info if spentindex enabled
            if (ptxSpentInfo != nullptr) {
                CSpentIndexKey spentKey(txin.prevout.hash, txin.prevout.n);
                auto it = ptxSpentInfo->mSpentInfo.find(spentKey);
                if (it != ptxSpentInfo->mSpentInfo.end()) {
                    auto spentInfo = it->second;
                    in.push_back(Pair("value", ValueFromAmount(spentInfo.satoshis)));
                    in.push_back(Pair("valueSat", spentInfo.satoshis));
                    if (spentInfo.addressType == 1) {
                        in.push_back(Pair("address", EncodeDestination(CKeyID(spentInfo.addressHash))));
                    } else if (spentInfo.addressType == 2) {
                        in.push_back(Pair("address", EncodeDestination(CScriptID(spentInfo.addressHash))));
                    }
                }
            }
        }
        in.pushKV("sequence", (int64_t)txin.nSequence);
        vin.push_back(in);
    }
    entry.pushKV("vin", vin);

    UniValue vout(UniValue::VARR);
    for (unsigned int i = 0; i < tx.vout.size(); i++) {
        const CTxOut& txout = tx.vout[i];

        UniValue out(UniValue::VOBJ);

        out.pushKV("value", ValueFromAmount(txout.nValue));
        out.pushKV("valueSat", txout.nValue);
        out.pushKV("n", (int64_t)i);

        UniValue o(UniValue::VOBJ);
        ScriptPubKeyToUniv(txout.scriptPubKey, o, true);
        out.pushKV("scriptPubKey", o);

        // Add spent information if spentindex is enabled
        if (ptxSpentInfo != nullptr) {
            CSpentIndexKey spentKey(txid, i);
            auto it = ptxSpentInfo->mSpentInfo.find(spentKey);
            if (it != ptxSpentInfo->mSpentInfo.end()) {
                auto spentInfo = it->second;
                out.push_back(Pair("spentTxId", spentInfo.txid.GetHex()));
                out.push_back(Pair("spentIndex", (int)spentInfo.inputIndex));
                out.push_back(Pair("spentHeight", spentInfo.blockHeight));
            }
        }
        vout.push_back(out);
    }
    entry.pushKV("vout", vout);

    if (!tx.vExtraPayload.empty()) {
        entry.push_back(Pair("extraPayloadSize", (int)tx.vExtraPayload.size()));
        entry.push_back(Pair("extraPayload", HexStr(tx.vExtraPayload)));
    }

    if (tx.nType == TRANSACTION_PROVIDER_REGISTER) {
        CProRegTx proTx;
        if (GetTxPayload(tx, proTx)) {
            UniValue obj;
            proTx.ToJson(obj);
            entry.push_back(Pair("proRegTx", obj));
        }
    } else if (tx.nType == TRANSACTION_PROVIDER_UPDATE_SERVICE) {
        CProUpServTx proTx;
        if (GetTxPayload(tx, proTx)) {
            UniValue obj;
            proTx.ToJson(obj);
            entry.push_back(Pair("proUpServTx", obj));
        }
    } else if (tx.nType == TRANSACTION_PROVIDER_UPDATE_REGISTRAR) {
        CProUpRegTx proTx;
        if (GetTxPayload(tx, proTx)) {
            UniValue obj;
            proTx.ToJson(obj);
            entry.push_back(Pair("proUpRegTx", obj));
        }
    } else if (tx.nType == TRANSACTION_PROVIDER_UPDATE_REVOKE) {
        CProUpRevTx proTx;
        if (GetTxPayload(tx, proTx)) {
            UniValue obj;
            proTx.ToJson(obj);
            entry.push_back(Pair("proUpRevTx", obj));
        }
    } else if (tx.nType == TRANSACTION_COINBASE) {
        CCbTx cbTx;
        if (GetTxPayload(tx, cbTx)) {
            UniValue obj;
            cbTx.ToJson(obj);
            entry.push_back(Pair("cbTx", obj));
        }
    } else if (tx.nType == TRANSACTION_QUORUM_COMMITMENT) {
        llmq::CFinalCommitmentTxPayload qcTx;
        if (GetTxPayload(tx, qcTx)) {
            UniValue obj;
            qcTx.ToJson(obj);
            entry.push_back(Pair("qcTx", obj));
        }
    }

    if (!hashBlock.IsNull())
        entry.pushKV("blockhash", hashBlock.GetHex());

    if (include_hex) {
        entry.pushKV("hex", EncodeHexTx(tx)); // the hex-encoded transaction. used the name "hex" to be consistent with the verbose output of "getrawtransaction".
    }
}
