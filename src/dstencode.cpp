// Copyright (c) 2017 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <dstencode.h>
#include <base58.h>
#include <ionaddrenc.h>
#include <chainparams.h>
#include <script/standard.h>

std::string EncodeDestination(const CTxDestination &dst, const CChainParams &params)
{
    return EncodeLegacyAddr(dst, params);
}

CTxDestination DecodeDestination(const std::string &addr, const CChainParams &params)
{
    CTxDestination dst = DecodeIONAddr(addr, params);
    if (IsValidDestination(dst))
    {
        return dst;
    }
    return DecodeLegacyAddr(addr, params);
}

std::string EncodeDestination(const CTxDestination &dst) { return EncodeDestination(dst, Params()); }
CTxDestination DecodeDestination(const std::string &addr) { return DecodeDestination(addr, Params()); }
