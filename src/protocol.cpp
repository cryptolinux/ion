// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018-2019 The Ion developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <protocol.h>

#include <util.h>
#include <utilstrencodings.h>

#ifndef WIN32
# include <arpa/inet.h>
#endif

static const char* ppszTypeName[] =
    {
        "ERROR",
        "tx",
        "block",
        "filtered block",
        "tx lock request",
        "tx lock vote",
        "spork",
        "mn winner",
        "mn scan error",
        "mn budget vote",
        "mn budget proposal",
        "mn budget finalized",
        "mn budget finalized vote",
        "mn quorum",
        "mn announce",
        "mn ping",
        "dstx",
        "pubcoins",
        "genwit",
        "accvalue"
    };

CMessageHeader::CMessageHeader()
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    nMessageSize = -1;
    memset(pchChecksum, 0, CHECKSUM_SIZE);
}

CMessageHeader::CMessageHeader(const MessageStartChars& pchMessageStartIn, const char* pszCommand, unsigned int nMessageSizeIn)
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    strncpy(pchCommand, pszCommand, COMMAND_SIZE);
    nMessageSize = nMessageSizeIn;
    memset(pchChecksum, 0, CHECKSUM_SIZE);
}

std::string CMessageHeader::GetCommand() const
{
    return std::string(pchCommand, pchCommand + strnlen(pchCommand, COMMAND_SIZE));
}

bool CMessageHeader::IsValid(const MessageStartChars& pchMessageStartIn) const
{
    // Check start string
    if (memcmp(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE) != 0)
        return false;

    // Check the command string for errors
    for (const char* p1 = pchCommand; p1 < pchCommand + COMMAND_SIZE; p1++)
    {
        if (*p1 == 0)
        {
            // Must be all zeros after the first zero
            for (; p1 < pchCommand + COMMAND_SIZE; p1++)
                if (*p1 != 0)
                    return false;
        }
        else if (*p1 < ' ' || *p1 > 0x7E)
            return false;
    }

    // Message size
    if (nMessageSize > MAX_SIZE)
    {
        LogPrintf("CMessageHeader::IsValid(): (%s, %u bytes) nMessageSize > MAX_SIZE\n", GetCommand(), nMessageSize);
        return false;
    }

    return true;
}


ServiceFlags GetDesirableServiceFlags(ServiceFlags services) {
    if ((services & NODE_NETWORK_LIMITED) && g_initial_block_download_completed) {
        return ServiceFlags(NODE_NETWORK_LIMITED);
    }
    return ServiceFlags(NODE_NETWORK);
}

void SetServiceFlagsIBDCache(bool state) {
    g_initial_block_download_completed = state;
}


CAddress::CAddress() : CService()
{
    Init();
}

CAddress::CAddress(CService ipIn, ServiceFlags nServicesIn) : CService(ipIn)
{
    Init();
    nServices = nServicesIn;
}

void CAddress::Init()
{
    nServices = NODE_NONE;
    nTime = 100000000;
}

CInv::CInv()
{
    type = 0;
    hash.SetNull();
}

CInv::CInv(int typeIn, const uint256& hashIn) : type(typeIn), hash(hashIn) {}

bool operator<(const CInv& a, const CInv& b)
{
    return (a.type < b.type || (a.type == b.type && a.hash < b.hash));
}

bool CInv::IsKnownType() const
{
    return GetCommandInternal() != nullptr;
}

const char* CInv::GetCommandInternal() const
{
    switch (type)
    {
        case MSG_TX:                            return NetMsgType::TX;
        case MSG_BLOCK:                         return NetMsgType::BLOCK;
        case MSG_FILTERED_BLOCK:                return NetMsgType::MERKLEBLOCK;
        case MSG_LEGACY_TXLOCK_REQUEST:         return NetMsgType::LEGACYTXLOCKREQUEST;
        case MSG_CMPCT_BLOCK:                   return NetMsgType::CMPCTBLOCK;
        case MSG_SPORK:                         return NetMsgType::SPORK;
        case MSG_DSTX:                          return NetMsgType::DSTX;
        case MSG_GOVERNANCE_OBJECT:             return NetMsgType::MNGOVERNANCEOBJECT;
        case MSG_GOVERNANCE_OBJECT_VOTE:        return NetMsgType::MNGOVERNANCEOBJECTVOTE;
        case MSG_QUORUM_FINAL_COMMITMENT:       return NetMsgType::QFCOMMITMENT;
        case MSG_QUORUM_CONTRIB:                return NetMsgType::QCONTRIB;
        case MSG_QUORUM_COMPLAINT:              return NetMsgType::QCOMPLAINT;
        case MSG_QUORUM_JUSTIFICATION:          return NetMsgType::QJUSTIFICATION;
        case MSG_QUORUM_PREMATURE_COMMITMENT:   return NetMsgType::QPCOMMITMENT;
        case MSG_QUORUM_RECOVERED_SIG:          return NetMsgType::QSIGREC;
        case MSG_CLSIG:                         return NetMsgType::CLSIG;
        case MSG_ISLOCK:                        return NetMsgType::ISLOCK;
        default:
            return nullptr;
    }
}

std::string CInv::GetCommand() const
{
    if (!IsKnownType()) {
        LogPrint("net", "CInv::GetCommand() : type=%d unknown type", type);
        return "UNKNOWN";
    }

    return ppszTypeName[type];
}

std::string CInv::ToString() const
{
    auto cmd = GetCommandInternal();
    if (!cmd) {
        return strprintf("0x%08x %s", type, hash.ToString());
    } else {
        return strprintf("%s %s", cmd, hash.ToString());
    }
}

const std::vector<std::string> &getAllNetMessageTypes()
{
    return allNetMessageTypesVec;
}
