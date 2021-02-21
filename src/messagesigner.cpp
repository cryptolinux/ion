// Copyright (c) 2014-2020 The Dash Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <base58.h>
#include <hash.h>
#include <validation.h> // For strMessageMagic
#include <messagesigner.h>
#include <tinyformat.h>
#include <utilstrencodings.h>

bool CMessageSigner::GetKeysFromSecret(const std::string& strSecret, CKey& keyRet, CPubKey& pubkeyRet)
{
    CBitcoinSecret vchSecret;

    if(!vchSecret.SetString(strSecret)) return false;

    keyRet = vchSecret.GetKey();
    pubkeyRet = keyRet.GetPubKey();

    return true;
}

bool CMessageSigner::SignMessage(const std::string& strMessage, std::vector<unsigned char>& vchSigRet, const CKey& key)
{
    CHashWriter ss(SER_GETHASH, 0);
    ss << strMessageMagic;
    ss << strMessage;

    return CHashSigner::SignHash(ss.GetHash(), key, vchSigRet);
}

bool CMessageSigner::VerifyMessage(const CPubKey& pubkey, const std::vector<unsigned char>& vchSig, const std::string& strMessage, std::string& strErrorRet)
{
    return VerifyMessage(pubkey.GetID(), vchSig, strMessage, strErrorRet);
}

bool CMessageSigner::VerifyMessage(const CKeyID& keyID, const std::vector<unsigned char>& vchSig, const std::string& strMessage, std::string& strErrorRet)
{
    CHashWriter ss(SER_GETHASH, 0);
    ss << strMessageMagic;
    ss << strMessage;

    return CHashSigner::VerifyHash(ss.GetHash(), keyID, vchSig, strErrorRet);
}

bool CHashSigner::SignHash(const uint256& hash, const CKey& key, std::vector<unsigned char>& vchSigRet)
{
    return key.SignCompact(hash, vchSigRet);
}

bool CHashSigner::VerifyHash(const uint256& hash, const CPubKey& pubkey, const std::vector<unsigned char>& vchSig, std::string& strErrorRet)
{
    return VerifyHash(hash, pubkey.GetID(), vchSig, strErrorRet);
}

bool CHashSigner::VerifyHash(const uint256& hash, const CKeyID& keyID, const std::vector<unsigned char>& vchSig, std::string& strErrorRet)
{
    CPubKey pubkeyFromSig;
    if(!pubkeyFromSig.RecoverCompact(hash, vchSig)) {
        strErrorRet = "Error recovering public key.";
        return false;
    }

    // TODO - reenable
    //ConnectBlock(ION): ProcessSpecialTxsInBlock for block 601c4a3f8961a9c837871e7c8d4afd37c73fb91e4f63b95e28700b09c28a3b2a failed with bad-protx-sig, Keys don't match: pubkey=cdd48dd899cd05e6be5f22da630fcc84f9f13b99, pubkeyFromSig=893dba3bad81be161f6465fa9d0104873736f1ce, hash=55b75ed27a954805ac5fc57ed59dac9bf46c6389238d5997464d6df5c05fd7e3, vchSig=IOXMux6pGe0VpSHEOiVpeO7k5HSxHf4Us9yOp51cK7ljBGFvg+iTL/xOry9CDeEV9iPYiZ67SCvxxxNBUTm6MHQ= (code 16))
    if(pubkeyFromSig.GetID() != keyID) {
        strErrorRet = strprintf("Keys don't match: pubkey=%s, pubkeyFromSig=%s, hash=%s, vchSig=%s",
                    keyID.ToString(), pubkeyFromSig.GetID().ToString(), hash.ToString(),
                    EncodeBase64(vchSig.data(), vchSig.size()));
        return false;
    }
    return true;
}
