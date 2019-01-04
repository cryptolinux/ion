// Copyright (c) 2014-2016 The Dash developers
// Copyright (c) 2016-2018 The PIVX developers
// Copyright (c) 2018 The Ion developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPORK_H
#define SPORK_H

#include <hash.h>
#include <net.h>
#include <utilstrencodings.h>
#include <key.h>

#include "obfuscation.h"
#include "protocol.h"

class CSporkMessage;
class CSporkManager;

/*
    Don't ever reuse these IDs for other sporks
    - This would result in old clients getting confused about which spork is for what
*/
#define SPORK_START 10001
#define SPORK_END 10009

#define SPORK_1_SWIFTTX 10001
#define SPORK_2_SWIFTTX_BLOCK_FILTERING 10002
#define SPORK_3_SWIFTTX_MAX_VALUE 10003
#define SPORK_4_MASTERNODE_PAYMENT_ENFORCEMENT 10004
#define SPORK_5_MASTERNODE_BUDGET_ENFORCEMENT 10005
#define SPORK_6_MASTERNODE_ENABLE_SUPERBLOCKS 10006
#define SPORK_7_MASTERNODE_PAY_UPDATED_NODES 10007
#define SPORK_8_NEW_PROTOCOL_ENFORCEMENT 10008
#define SPORK_9_ZEROCOIN_MAINTENANCE_MODE 10009

#define SPORK_1_SWIFTTX_DEFAULT 978307200                         //2001-1-1
#define SPORK_2_SWIFTTX_BLOCK_FILTERING_DEFAULT 1424217600        //2015-2-18
#define SPORK_3_SWIFTTX_MAX_VALUE_DEFAULT 1000                            //1000 ION
#define SPORK_4_MASTERNODE_PAYMENT_ENFORCEMENT_DEFAULT 1521851265 //OFF
#define SPORK_5_MASTERNODE_BUDGET_ENFORCEMENT_DEFAULT 4070908800  //OFF
#define SPORK_6_MASTERNODE_ENABLE_SUPERBLOCKS_DEFAULT 4070908800  //OFF
#define SPORK_7_MASTERNODE_PAY_UPDATED_NODES_DEFAULT 1521851265   //GMT: Saturday, March 24, 2018 12:27:45 AM (OFF 4070908800)
#define SPORK_8_NEW_PROTOCOL_ENFORCEMENT_DEFAULT 1521851265       //GMT: Saturday, March 24, 2018 12:27:45 AM (OFF 4070908800)
#define SPORK_9_ZEROCOIN_MAINTENANCE_MODE_DEFAULT 4070908800      //OFF

namespace std
{
    template<> struct hash<SporkId>
    {
        std::size_t operator()(SporkId const& id) const noexcept
        {
            return std::hash<int>{}(id);
        }
    };
}

struct CSporkDef
{
    SporkId sporkId{SPORK_INVALID};
    int64_t defaultValue{0};
    std::string name;
};

extern std::vector<CSporkDef> sporkDefs;
extern CSporkManager sporkManager;

/**
 * Sporks are network parameters used primarily to prevent forking and turn
 * on/off certain features. They are a soft consensus mechanism.
 *
 * We use 2 main classes to manage the spork system.
 *
 * SporkMessages - low-level constructs which contain the sporkID, value,
 *                 signature and a signature timestamp
 * SporkManager  - a higher-level construct which manages the naming, use of
 *                 sporks, signatures and verification, and which sporks are active according
 *                 to this node
 */

/**
 * CSporkMessage is a low-level class used to encapsulate Spork messages and
 * serialize them for transmission to other peers. This includes the internal
 * spork ID, value, spork signature and timestamp for the signature.
 */
class CSporkMessage
{
private:
    std::vector<unsigned char> vchSig;

public:
    SporkId nSporkID;
    int64_t nValue;
    int64_t nTimeSigned;

    CSporkMessage(SporkId nSporkID, int64_t nValue, int64_t nTimeSigned) :
        nSporkID(nSporkID),
        nValue(nValue),
        nTimeSigned(nTimeSigned)
        {}

    CSporkMessage() :
        nSporkID((SporkId)0),
        nValue(0),
        nTimeSigned(0)
        {}


    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(nSporkID);
        READWRITE(nValue);
        READWRITE(nTimeSigned);
        READWRITE(vchSig);
    }

    /**
     * GetHash returns the double-sha256 hash of the serialized spork message.
     */
    uint256 GetHash() const;

    /**
     * GetSignatureHash returns the hash of the serialized spork message
     * without the signature included. The intent of this method is to get the
     * hash to be signed.
     */
    uint256 GetSignatureHash() const;

    /**
     * Sign will sign the spork message with the given key.
     */
    bool Sign(const CKey& key);

    /**
     * CheckSignature will ensure the spork signature matches the provided public
     * key hash.
     */
    bool CheckSignature(const CKeyID& pubKeyId) const;

    /**
     * GetSignerKeyID is used to recover the spork address of the key used to
     * sign this spork message.
     *
     * This method was introduced along with the multi-signer sporks feature,
     * in order to identify which spork key signed this message.
     */
    bool GetSignerKeyID(CKeyID& retKeyidSporkSigner);

    /**
     * Relay is used to send this spork message to other peers.
     */
    void Relay(CConnman& connman);
};

/**
 * CSporkManager is a higher-level class which manages the node's spork
 * messages, rules for which sporks should be considered active/inactive, and
 * processing for certain sporks (e.g. spork 12).
 */
class CSporkManager
{
private:
    static const std::string SERIALIZATION_VERSION_STRING;

    std::unordered_map<SporkId, CSporkDef*> sporkDefsById;
    std::unordered_map<std::string, CSporkDef*> sporkDefsByName;

    mutable CCriticalSection cs;
    std::unordered_map<uint256, CSporkMessage> mapSporksByHash;
    std::unordered_map<SporkId, std::map<CKeyID, CSporkMessage> > mapSporksActive;

    std::set<CKeyID> setSporkPubKeyIDs;
    int nMinSporkKeys;
    CKey sporkPrivKey;

    /**
     * SporkValueIsActive is used to get the value agreed upon by the majority
     * of signed spork messages for a given Spork ID.
     */
    bool SporkValueIsActive(SporkId nSporkID, int64_t& nActiveValueRet) const;

public:

    CSporkManager();

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        std::string strVersion;
        if(ser_action.ForRead()) {
            READWRITE(strVersion);
            if (strVersion != SERIALIZATION_VERSION_STRING) {
                return;
            }
        } else {
            strVersion = SERIALIZATION_VERSION_STRING;
            READWRITE(strVersion);
        }
        // we don't serialize pubkey ids because pubkeys should be
        // hardcoded or be setted with cmdline or options, should
        // not reuse pubkeys from previous iond run
        READWRITE(mapSporksByHash);
        READWRITE(mapSporksActive);
        // we don't serialize private key to prevent its leakage
    }

    std::string GetSporkNameByID(int id);
    int GetSporkIDByName(std::string strName);
    bool UpdateSpork(int nSporkID, int64_t nValue);
    bool SetPrivKey(std::string strPrivKey);
    bool CheckSignature(CSporkMessage& spork, bool fCheckSigner = false);
    bool Sign(CSporkMessage& spork);
    void Relay(CSporkMessage& msg);
};

#endif
