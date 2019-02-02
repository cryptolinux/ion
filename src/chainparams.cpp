// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The Ion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <arith_uint256.h>

#include <assert.h>
#include <memory>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTxTime, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.nTime = nTxTime;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 1486045800 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateDevNetGenesisBlock(const uint256 &prevBlockHash, const std::string& devNetName, uint32_t nTxTime, uint32_t nTime, uint32_t nNonce, uint32_t nBits, const CAmount& genesisReward)
{
    assert(!devNetName.empty());

    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.nTime = nTxTime;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    // put height (BIP34) and devnet name into coinbase
    txNew.vin[0].scriptSig = CScript() << 1 << std::vector<unsigned char>(devNetName.begin(), devNetName.end());
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = CScript() << OP_RETURN;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = 4;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock = prevBlockHash;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nTime=0, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTxTime, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "The Guardian: [2nd Feb 2017] Finsbury Park mosque wins apology and damages from Thomson Reuters";
    const CScript genesisOutputScript = CScript() << ParseHex("045622582bdfad9366cdff9652d35a562af17ea4e3462d32cd988b32919ba2ff4bc806485be5228185ad3f75445039b6e744819c4a63304277ca8d20c99a6acec8") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTxTime, nTime, nNonce, nBits, nVersion, genesisReward);
}


void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout, int64_t nWindowSize, int64_t nThresholdStart, int64_t nThresholdMin, int64_t nFalloffCoeff)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
    if (nWindowSize != -1) {
            consensus.vDeployments[d].nWindowSize = nWindowSize;
    }
    if (nThresholdStart != -1) {
        consensus.vDeployments[d].nThresholdStart = nThresholdStart;
    }
    if (nThresholdMin != -1) {
        consensus.vDeployments[d].nThresholdMin = nThresholdMin;
    }
    if (nFalloffCoeff != -1) {
        consensus.vDeployments[d].nFalloffCoeff = nFalloffCoeff;
    }
}

void CChainParams::UpdateDIP3Parameters(int nActivationHeight, int nEnforcementHeight)
{
    consensus.DIP0003Height = nActivationHeight;
    consensus.DIP0003EnforcementHeight = nEnforcementHeight;
}

void CChainParams::UpdateBudgetParameters(int nMasternodePaymentsStartBlock, int nBudgetPaymentsStartBlock, int nSuperblockStartBlock)
{
    consensus.nMasternodePaymentsStartBlock = nMasternodePaymentsStartBlock;
    consensus.nBudgetPaymentsStartBlock = nBudgetPaymentsStartBlock;
    consensus.nSuperblockStartBlock = nSuperblockStartBlock;
}

void CChainParams::UpdateSubsidyAndDiffParams(int nMinimumDifficultyBlocks, int nHighSubsidyBlocks, int nHighSubsidyFactor)
{
    consensus.nMinimumDifficultyBlocks = nMinimumDifficultyBlocks;
    consensus.nHighSubsidyBlocks = nHighSubsidyBlocks;
    consensus.nHighSubsidyFactor = nHighSubsidyFactor;
}

void CChainParams::UpdateLLMQChainLocks(Consensus::LLMQType llmqType) {
    consensus.llmqTypeChainLocks = llmqType;
}

void CChainParams::UpdateLLMQTestParams(int size, int threshold) {
    auto& params = consensus.llmqs.at(Consensus::LLMQ_TEST);
    params.size = size;
    params.minSize = threshold;
    params.threshold = threshold;
    params.dkgBadVotesThreshold = threshold;
}

void CChainParams::UpdateLLMQDevnetParams(int size, int threshold)
{
    auto& params = consensus.llmqs.at(Consensus::LLMQ_DEVNET);
    params.size = size;
    params.minSize = threshold;
    params.threshold = threshold;
    params.dkgBadVotesThreshold = threshold;
}

static CBlock FindDevNetGenesisBlock(const CBlock &prevBlock, const CAmount& reward)
{
    std::string devNetName = gArgs.GetDevNetName();
    assert(!devNetName.empty());

    CBlock block = CreateDevNetGenesisBlock(prevBlock.GetHash(), devNetName.c_str(), prevBlock.nTime + 1, prevBlock.nTime + 2, 0, prevBlock.nBits, reward);

    arith_uint256 bnTarget;
    bnTarget.SetCompact(block.nBits);

    for (uint32_t nNonce = 0; nNonce < UINT32_MAX; nNonce++) {
        block.nNonce = nNonce;

        uint256 hash = block.GetHash();
        if (UintToArith256(hash) <= bnTarget)
            return block;
    }

    // This is very unlikely to happen as we start the devnet with a very low difficulty. In many cases even the first
    // iteration of the above loop will give a result already
    error("FindDevNetGenesisBlock: could not find devnet genesis block for %s", devNetName);
    assert(false);
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
        (       0,	uint256("0000004cf5ffbf2e31a9aa07c86298efb01a30b8911b80af7473d1114715084b") ) // Genesis block
        (    1000,  uint256("0000000144b22b0af9bced65256d5eccc4e3f112a89bdb0f08ab8dc2a6145b56") ) // Last PoW block
        (    1001,  uint256("a66b31f9841cc86f85a89142641b4c02f43065dda1818002595d2cef6b0b7cc2") ) // First PoS startheight block
        (  100000,  uint256("a5a4e8f2554cda59955e0117fd71245e1f6d73a30ab420a3d3731384dcbcfffc") )
        (  200000,  uint256("e6f984e3fe6bf992d640f30ad3c28777b303b4b3b59bd7bf3f696566abe08c13") )
        (  300000,  uint256("d6b6250ec6bedf74663a10babf5774562736fa99f7dd0a53841a4c95b1b8ec11") )
        (  400000,  uint256("507851828598daf03711e6eaed1709f17837a105dd62209ff68d2cf1dc6ddf7a") )
        (  550001,  uint256("aa063547717c4e9f1f1593a580143491896cde85a0b369442d629cd364a1b78d") ) // Zerocoin Start (v8)            1521903907   1464462
        (  550142,  uint256("4a9e4ee53bc441e0aadf788b5daa9b8d01a3a6debed01b5c599d6f7e22f4f7d0") ) //                                1521912217   1464746
        (  552317,  uint256("654cf4e6d0e9d8249075c674a54859849b2648cfe35ea71e25bd6394f24331b2") ) // Last block                     1522095098   1469475
        (  853104,  uint256("9623e2c68f6eab9f91ac9ca4b65a2049a05f223f970ca2d3cf8280ad1ead5efc") ) // v3.1.0                         1540360964   2232434
        (  860817,  uint256("b78531efc5d878f8afc5aa9fd349d0181e8cc213853251aad63839d59781a716") ) //                                1540827763   2251929
        (  886654,  uint256("c816d0e907ab44f43ec6bef321ac2c9b4e4a578c9ee4e7946e4a74c3073edf66") ) //                                1542390128   2316854
        (  908698,  uint256("aa44b1eebd7ad5d4bc7b428dcdacd527677fa639557b58666a68dc2fdba3f133") ) // Last active zerocoin v1 block  1543722397   2371470 (zerocoin v1 disabled: 1543722400)
        (  936756,  uint256("873aa1d52ca79dc77d67f8162a2a60b9c936f50449b58b5464b91e412d351c29") ) //                                1543729708   2371718
        (  956579,  uint256("bac382323420c9c8e89024b66a3cab28d6133ca7450eae07de63364f74f087f6") ) //                                1546631813   2492172
        (  980729,  uint256("a12927283f8396a65bf45cf516f5d8a2c618ac6b2a9cc530cdd962c9263b3398") ) //                                1548101941   2552465
        (  997048,  uint256("5fcdcf658a5b20a8c8e2c583a68122e9c0b66804f6c2941384c53cf90490d210") );//                                1549093695   2592520
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1548101941, // * UNIX timestamp of last checkpoint block
    2592520,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3490        // * estimated number of transactions per day after checkp
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
	(       1,      uint256("000000b86fdd7f2ae9e9973e73790492989113075a2d5c581495ab7bb2ad5711") ) // First block 
	(      10,      uint256("0000008c29a7d680710d1cc821d79f33ba0159bc26d9e233bccfabd668b0430e") ) // Confirmation of first block
	(      73,      uint256("0000000000414be74794bb2e455e24c0e446ad36df162c69a81742dc07f51d0d") ) // 
	(      74,      uint256("1881b795f7531232ba90ade14c16b7f0cf9392b6c9fe76a3d5bfeab9150b7dca") ) // ERROR: AcceptBlock : prev block 1881b795f7531232ba90ade14c16b7f0cf9392b6c9fe76a3d5bfeab9150b7dca is invalid, unable to add block c54904618b734eeb3f098b442934586806f869e80656eacfba65ca91a091cf31
	(      75,      uint256("c54904618b734eeb3f098b442934586806f869e80656eacfba65ca91a091cf31") ) // ERROR: AcceptBlock : prev block 1881b795f7531232ba90ade14c16b7f0cf9392b6c9fe76a3d5bfeab9150b7dca is invalid, unable to add block c54904618b734eeb3f098b442934586806f869e80656eacfba65ca91a091cf31
	(     300,      uint256("000000125e3e3d005aa72281e02b4ebaabc2fa9aed817b9365a8d29bb7901c10") ) // Last POW Block
	(   75000,      uint256("20faec3994dac57fb88748e29139974522c91036e1bf8ff204c769a90fab5a12") ) // Fork June 2017
	(   85000,      uint256("43ee28cd1f804dafe05ef120569726e50e9e6f2b634746925742cbd9f738c201") ) // Fork June 2017
	(   88800,      uint256("2807b46cbfa28a2d4854215b40f4db64b62fc71a1d010844d67d7c03888ce692") ) // Fork June 2017
	(  331099,      uint256("1ba565ae5336eeb1cbdc4c8804f229f685391d6b9a8568f7baf5c70b80bed17e") ) // Testnet Fork June 2018
	(  331100,      uint256("ffa0eaa61e9b2291dd497338235d071b0e9eb71d4fda723ce778f52b38e349fe") ) // Testnet Fork June 2018
	(  443601,      uint256("c5e9467f24b1d149a9716776be2fdc806af2db54d11330df33bb931f8ebf6254") ) // Testnet Fork June 2018
	(  472999,      uint256("5d55f229074b930f4dd42a0f4e0e2f1d855dcd1d87cb86553ea21c797825482c") ) // Testnet Fork June 2018
	(  473000,      uint256("237bc8d1e7cb02af8cd3e6affe1fa134c1a29a4852f3fa177ebcd50014463152") ) // Testnet Fork December 2018; timestamp=1545338100  txcount=947151
    (  500535,      uint256("d6a5202217fcbdbe34592e78038937cb89541cb41051492bde6d061188285086") ) // timestamp=1547025824 txcount=1003348
    (  516559,      uint256("8b91cc91179419e72777e51b3c298fd29df8827256b361c48cf61bab0b1e1bb5") ) // timestamp=1548102045 txcount=1035503
    (  532875,      uint256("483a77879f686a3e04076776ef82409ff17c4955d04c5b221ace7bfd4c3b5086") );// timestamp=1549094295 txcount=1070146
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1549094295,
    1070146,
    3017};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210240; // Note: actual number of blocks per calendar year with DGW v3 is ~200700 (for example 449750 - 249050)
        consensus.nMasternodePaymentsStartBlock = 100000; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 158000; // actual historical value
        consensus.nMasternodePaymentsIncreasePeriod = 576*30; // 17280 - actual historical value
        consensus.nInstantSendConfirmationsRequired = 6;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 99999999; // currently not activated
        consensus.nBudgetPaymentsCycleBlocks = 16616; // ~(60*24*30)/2.6, actual number of blocks per month is 200700 / 12 = 16725
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nSuperblockStartBlock = 99999999; // The block at which 12.1 goes live (end of final 12.0 budget cycle)
        consensus.nSuperblockStartHash = uint256S("0000000000020cb27c7ef164d21003d5d20cdca2f54dd9a9ca6d45f4d47f8aa3");
        consensus.nSuperblockCycle = 16616; // ~(60*24*30)/2.6, actual number of blocks per month is 200700 / 12 = 16725
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.BIP34Height = 951;
        consensus.BIP34Hash = uint256S("603066b255ac410e0a488dcad007a74917257ad6dbdade34938f6a17e522722b");
        consensus.BIP65Height = 619382; // 00000000000076d8fcea02ec0963de4abfd01e771fec0863f960c2c64fe6f357
        consensus.BIP66Height = 245817; // 00000000000b1fa2dfa312863570e13fae9ca7b5566cb27e55422620b469aefa
        consensus.DIP0001Height = 99999999;
        consensus.DIP0003Height = 99999999;
        consensus.DIP0003EnforcementHeight = 99999999;
        consensus.DIP0003EnforcementHash = uint256S("000000000000002d1734087b4c5afc3133e4e1c3e1a89218f62bcd9bb3d17f81");
        consensus.IIP0006Height = 1510000;
        consensus.POSStartHeight = 1001;
        consensus.MidasStartHeight = 176500;
        consensus.DGWStartHeight = 550000;
        consensus.DGWStartTime = 1521851265;
        consensus.ATPStartHeight = 1320000; // Start enforcing the Atomic Token Protocol (ATP) for blocks with version 11 and higher
        consensus.powLimit = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint256(0) >> 24
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Ion: 1 day
        consensus.nPowTargetSpacing = 2.5 * 60; // Ion: 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 99999999;
        consensus.nPowDGWHeight = 99999999;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.posLimit = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint256(0) >> 24
        consensus.nPosTargetTimespanMidas = 7 * 24 * 60 * 60; // 1 week
        consensus.nPosTargetSpacingMidas = 64;
        consensus.nPosTargetSpacing = 1 * 60; // 1 minute
        consensus.nStakeMinDepth = 600;
        consensus.nZerocoinRequiredStakeDepth = 200;
        consensus.nZerocoinStartHeight = 550001;
        consensus.nZerocoinStartTime = 1521851265; // GMT: Saturday, March 24, 2018 12:27:45 AM
        consensus.nBlockZerocoinV2 = 1012710;
        consensus.nPublicZCSpends = 1320000;
        consensus.nBlockStakeModifierV2 = 1320000;
        consensus.nFakeSerialBlockheightEnd = -1;
        consensus.nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        consensus.nRequiredAccumulation = 1;
        consensus.zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";

        // ATP
        consensus.strTokenManagementKey = "inqaYuaES1cmRBXHodp25UceeVPbWQG5wY";
        consensus.nOpGroupNewRequiredConfirmations = 1;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1486252800; // Feb 5th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517788800; // Feb 5th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1508025600; // Oct 15th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1539561600; // Oct 15th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThresholdStart = 3226; // 80% of 4032

        // Deployment of BIP147
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].nStartTime = 1524477600; // Apr 23th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].nTimeout = 1556013600; // Apr 23th, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].nThresholdStart = 3226; // 80% of 4032

        // Deployment of DIP0003
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].bit = 3;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].nStartTime = 1546300800; // Jan 1st, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].nTimeout = 1577836800; // Jan 1st, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].nThresholdStart = 3226; // 80% of 4032

        // Deployment of DIP0008
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].nStartTime = 1557878400; // May 15th, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].nTimeout = 1589500800; // May 15th, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].nThresholdStart = 3226; // 80% of 4032

        // Deployment of Block Reward Reallocation
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].bit = 5;
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nStartTime = 1601510400; // Oct 1st, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nTimeout = 1633046400; // Oct 1st, 2021
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nThresholdStart = 3226; // 80% of 4032
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nThresholdMin = 2420; // 60% of 4032
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nFalloffCoeff = 5; // this corresponds to 10 periods

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000a64ab529ced4bacca2"); // 1381790
        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00000000000000022f355c52417fca9b73306958f7c0832b3a7bce006ca369ef"); // 1364585

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xc4;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xd8;
        pchMessageStart[3] = 0xec;
        vAlertPubKey = ParseHex("04ab1a302b40c65c08281974e4ccbe6df987d8a87cbc490ace9a261d8a57b809a5dad39f53bdc85e392c61c3c5a3f990d53430bb40a731ff28fa2255fecef70da3");
        nDefaultPort = 12700;
        bnProofOfWorkLimit  = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        bnProofOfStakeLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetTimespanMidas = 7 * 24 * 60 * 60;    // 1 week
        nTargetTimespanDGW = 1 * 60; // ION: 1 day
        nTargetSpacing = 1 * 60;  // ION: 1 minute
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 38600000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1000;
        nModifierUpdateBlock = 615800;
        nZerocoinStartHeight = 550001;
        nZerocoinStartTime = 1521851265;            // GMT: Saturday, March 24, 2018 12:27:45 AM,
        nBlockEnforceSerialRange = 550137;          //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 550137;     //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 99999999;           //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 550137;          //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 550137;          //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0*COIN;            //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 1012710;                 //!> The block that zerocoin v2 becomes active - roughly GMT: Thursday, February 7, 2019 12:00:01 AM
        nEnforceNewSporkKey = 1548979201;           //!> Sporks signed after, GMT: Friday, February 1, 2019 12:00:01 AM must use the new spork key
        nRejectOldSporkKey = 1549497601;            //!> Reject old spork key afters, GMT: Thursday, February 7, 2019 12:00:01 AM

        nMidasStartHeight = 176500;                 // MIDAS startheight, first big attack
        nMidasStartTime = 1497541280;               // Time when MIDAS started and old algorithm stopped
        nDGWStartHeight = 550000;                   // Startheight of DGW
        nDGWStartTime = 1521851265;                 // GMT: Saturday, March 24, 2018 12:27:45 AM - Exact time when DGW algorithm starts and old MIDAS stops

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "The Guardian: [2nd Feb 2017] Finsbury Park mosque wins apology and damages from Thomson Reuters";
        genesis.nTime = 1486045800; // GMT: Thursday, February 2, 2017 14:30:00
        CMutableTransaction txNew;
        txNew.nTime = genesis.nTime;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 1486045800 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("045622582bdfad9366cdff9652d35a562af17ea4e3462d32cd988b32919ba2ff4bc806485be5228185ad3f75445039b6e744819c4a63304277ca8d20c99a6acec8") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nBits = 0x1e00ffff;
        genesis.nNonce = 28884498;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000004cf5ffbf2e31a9aa07c86298efb01a30b8911b80af7473d1114715084b"));
        assert(genesis.hashMerkleRoot == uint256("0x7af2e961c5262cb0411edcb7414ab7178133fc06257ceb47d349e4e5e35e2d40"));

        vSeeds.push_back(CDNSSeedData("1", "main.seeder.baseserv.com")); // Ionomy official seed 1
        vSeeds.push_back(CDNSSeedData("2", "main.seeder.uksafedns.net")); // Ionomy official seed 2

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 103);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 88);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x73)(0x79)(0x78).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "ion";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fRequireRoutableExternalIP = true;
        fMineBlocksOnDemand = false;
        fAllowMultipleAddressesFromGroup = false;
        fAllowMultiplePorts = false;
        nLLMQConnectionRetryTimeout = 60;

        nPoolMaxTransactions = 3;
        strSporkKey = "04e892d181f083856991c4e68f82b935dad9ca5dee2fb912ceb0247c3670725f879bfdb718be019f7a0bc53f77105f60a8ed750b16e55c220b4b6c47279d7dce17";
        strSporkKeyOld = "04f8c457bd279e667228d38faf2032958ee80ead5ec3d04ab92eeab54ac078ea2a79a2a03dee10634123cc47ea795699bd02b6370e040b622b2f15bcc56dafc2b7";
        strObfuscationPoolDummyAddress = "ijeSPVizJAFuKx4E3rEAcadQR5tZF9cjC8";
        nStartMasternodePayments = 1558696182; // GMT: Thursday, 15. February 2018 12:03:02

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 8; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a xion to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

        chainTxData = ChainTxData{
            1601017518, // * UNIX timestamp of last known number of transactions (Block 1344000)
            28914483,   // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.3         // * estimated number of transactions per second after that timestamp
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210240;
        consensus.nMasternodePaymentsStartBlock = 4010; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 4030;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendConfirmationsRequired = 2;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 80000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nSuperblockStartBlock = 4200; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockStartHash = uint256(); // do not check this on testnet
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.BIP34Height = 76;
        consensus.BIP34Hash = uint256S("0x000008ebb1db2598e897d17275285767717c6acfeac4c73def49fbea1ddcbcb6");
        consensus.BIP65Height = 2431; // 0000039cf01242c7f921dcb4806a5994bc003b48c1973ae0c89b67809c2bb2ab
        consensus.BIP66Height = 2075; // 0000002acdd29a14583540cb72e1c5cc83783560e38fa7081495d474fe1671f7
        consensus.DIP0001Height = 2;
        consensus.DIP0003Height = 7000;
        consensus.DIP0003EnforcementHeight = 7300;
        consensus.DIP0003EnforcementHash = uint256S("00000055ebc0e974ba3a3fb785c5ad4365a39637d4df168169ee80d313612f8f");
        consensus.IIP0006Height = 90000;
        consensus.POSStartHeight = 250;
        consensus.MidasStartHeight = 999999999;
        consensus.DGWStartHeight = 300;
        consensus.DGWStartTime = 1554332940;
        consensus.ATPStartHeight = 5530; // Start enforcing the Atomic Token Protocol (ATP) for blocks with version 11 and higher
        consensus.powLimit = uint256S("3fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint256(0) >> 2
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Ion: 1 day
        consensus.nPowTargetSpacing = 2.5 * 60; // Ion: 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 4002; // nPowKGWHeight >= nPowDGWHeight means "no KGW"
        consensus.nPowDGWHeight = 4002;
        consensus.nStakeMinDepth = 100;
        consensus.nZerocoinRequiredStakeDepth = 200;
        consensus.nZerocoinStartHeight = 300;
        consensus.nZerocoinStartTime = 1501776000;
        consensus.nBlockZerocoinV2 = 301;
        consensus.nPublicZCSpends = 5500;
        consensus.nBlockStakeModifierV2 = 1214000;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // ATP
        consensus.strTokenManagementKey = "gBi3gDLnGfw8HA2rN4HmNxHk9hMC4GLFbh";
        consensus.nOpGroupNewRequiredConfirmations = 1;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1544655600; // Dec 13th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1576191600; // Dec 13th, 2019

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1544655600; // Dec 13th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1576191600; // Dec 13th, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThresholdStart = 50; // 50% of 100

        // Deployment of BIP147
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].nStartTime = 1544655600; // Dec 13th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].nTimeout = 1576191600; // Dec 13th, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_BIP147].nThresholdStart = 50; // 50% of 100

        // Deployment of DIP0003
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].bit = 3;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].nStartTime = 1544655600; // Dec 13th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].nTimeout = 1576191600; // Dec 13th, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0003].nThresholdStart = 50; // 50% of 100

        // Deployment of DIP0008
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].nStartTime = 1553126400; // Mar 21st, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].nTimeout = 1584748800; // Mar 21st, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0008].nThresholdStart = 50; // 50% of 100

        // Deployment of Block Reward Reallocation
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].bit = 5;
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nStartTime = 1598918400; // Sep 1st, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nTimeout = 1630454400; // Sep 1st, 2021
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nThresholdStart = 80; // 80% of 100
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nThresholdMin = 60; // 60% of 100
        consensus.vDeployments[Consensus::DEPLOYMENT_REALLOC].nFalloffCoeff = 5; // this corresponds to 10 periods

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000022f13324cfe06a3"); // 395750

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000008b78b6aef3fd05ab78db8b76c02163e885305545144420cb08704dce538"); // 395750

        pchMessageStart[0] = 0xdb;
        pchMessageStart[1] = 0x86;
        pchMessageStart[2] = 0xfc;
        pchMessageStart[3] = 0x69;
        nDefaultPort = 27170;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nTargetTimespanMidas = 7 * 24 * 60 * 60;   // 1 week
        nTargetTimespanDGW = 1 * 60; // ion: 1 day
        nTargetSpacing = 1 * 60;  // ION: 1 minute
        nLastPOWBlock = 300;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 38600000 * COIN;
        nZerocoinStartHeight = 331100;
        nZerocoinStartTime = 1521414629;
        nBlockEnforceSerialRange = 10000000; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 10000000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 99999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 10000000; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 10000000; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 474100; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1545361200; //!> Sporks signed after 12/21/2018 @ 3:00am (UTC) must use the new spork key
        nRejectOldSporkKey = 1545620400; //!> Reject old spork key after 12/24/2018 @ 3:00am (UTC)

        nMidasStartHeight = 75000;
        nMidasStartTime = 1497209344;
        nDGWStartHeight = nZerocoinStartHeight;
        nDGWStartTime = nZerocoinStartTime;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        const char* pszTimestamp = "The Guardian: [2nd Feb 2017] Finsbury Park mosque wins apology and damages from Thomson Reuters";
        genesis.nTime = 1491737471; // GMT: Thursday, February 2, 2017 14:30:00
        genesis.vtx.clear();
        CMutableTransaction txNew;
        txNew.nTime = genesis.nTime;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 1491737471 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("045622582bdfad9366cdff9652d35a562af17ea4e3462d32cd988b32919ba2ff4bc806485be5228185ad3f75445039b6e744819c4a63304277ca8d20c99a6acec8") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);

        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nNonce = 1603027;
        genesis.nBits = 0x1e00ffff;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000002bed128b6b2a62bd8edd4e6f8a414eac38e256aa0194adb8c93fe18132"));

        vFixedSeeds.clear();
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("1", "testnet.seeder.baseserv.com"));
        vSeeds.push_back(CDNSSeedData("2", "testnet.seeder.uksafedns.net")); // Ionomy official testseed 2"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 97); // Testnet ion addresses start with 'g'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);  // Testnet ion script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239); 
        // Testnet ion BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xcf).convert_to_container<std::vector<unsigned char> >();
        // Testnet ion BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x91).convert_to_container<std::vector<unsigned char> >();
        // Testnet ion BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "tion";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fRequireRoutableExternalIP = true;
        fMineBlocksOnDemand = false;
        fAllowMultipleAddressesFromGroup = false;
        fAllowMultiplePorts = true;
        nLLMQConnectionRetryTimeout = 60;

        nPoolMinParticipants = 3;
        nPoolNewMinParticipants = 2;
        nPoolMaxParticipants = 5;
        nPoolNewMaxParticipants = 20;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        nPoolMaxTransactions = 2;
        strSporkKey = "0430b1f83d3acb90cde0b7e0e1d9365c00bfaf04ab8614457cfa0766a787239dd47ad6ca478659dd5e401fccb7fea6fa83acad23a2c7b451aafe6fa2ae4cfd4a58";
        strSporkKeyOld = "0470e14fc60a25e0eb4f6b1fe280e4c3f9427f7bb8b38f14a0c310c2e56402bdce0f25049bf22351dc3d07f389d4d433b339d8e1b991784f11df68f50340185c1d";
        strObfuscationPoolDummyAddress = "g9gvvemz52aDkRn4iiGrzTbBRS1HiqcY9r";
        nStartMasternodePayments = 1558696183; // GMT: Thursday, 15. February 2018 12:03:03
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0x9a;
        pchMessageStart[2] = 0x39;
        pchMessageStart[3] = 0x9e;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 1;
        nTargetTimespanMidas = 7 * 24 * 60 * 60;    // 1 week
        nTargetTimespanDGW = 24 * 60 * 60;          // ION: 1 day
        nTargetSpacing = 1 * 60;                    // ION: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 850;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 38600000 * COIN;
        nZerocoinStartHeight = 1;
        nZerocoinStartTime = 1521414629;
        nBlockEnforceSerialRange = 10000000; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 10000000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 99999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 10000000; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 10000000; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 1000; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1545361200; //!> Sporks signed after 12/21/2018 @ 3:00am (UTC) must use the new spork key
        nRejectOldSporkKey = 1545620400; //!> Reject old spork key after 12/24/2018 @ 3:00am (UTC)

        nMidasStartHeight = 99999999;
        nMidasStartTime = 9997209344;
        nDGWStartHeight = nZerocoinStartHeight;
        nDGWStartTime = nZerocoinStartTime;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        const char* pszTimestamp = "The Guardian: [2nd Feb 2017] Finsbury Park mosque wins apology and damages from Thomson Reuters";
        genesis.nTime = 1491737471;                 // GMT: Thursday, February 2, 2017 14:30:00
        genesis.vtx.clear();
        CMutableTransaction txNew;
        txNew.nTime = genesis.nTime;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 1491737471 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("045622582bdfad9366cdff9652d35a562af17ea4e3462d32cd988b32919ba2ff4bc806485be5228185ad3f75445039b6e744819c4a63304277ca8d20c99a6acec8") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);

        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nNonce = 574752;                  // hex 57 47 52 in text = ION
        genesis.nBits = 0x207ffff;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 34567;
        assert(hashGenesisBlock == uint256("0x47c7c6267ccd4a73c21c696d4bc004f74edc172a470c9c5a4201aa8d3196f99e"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fRequireRoutableExternalIP = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 2;
        strSporkKey = "0430b1f83d3acb90cde0b7e0e1d9365c00bfaf04ab8614457cfa0766a787239dd47ad6ca478659dd5e401fccb7fea6fa83acad23a2c7b451aafe6fa2ae4cfd4a58";
        strSporkKeyOld = "0470e14fc60a25e0eb4f6b1fe280e4c3f9427f7bb8b38f14a0c310c2e56402bdce0f25049bf22351dc3d07f389d4d433b339d8e1b991784f11df68f50340185c1d";
        strObfuscationPoolDummyAddress = "TMPUBzcsHZawA32XYYDF9FHQp6icv492CV";
        nStartMasternodePayments = 1558696183; // GMT: Thursday, 15. February 2018 12:03:03
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
        bech32_hrp = "ionrt";

    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 27770;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;

        bech32_hrp = "ionut";
    }

        bech32_hrp = "ionut";
    }

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::DEVNET) {
        return std::unique_ptr<CChainParams>(new CDevNetParams());
    } else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout, int64_t nWindowSize, int64_t nThresholdStart, int64_t nThresholdMin, int64_t nFalloffCoeff)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout, nWindowSize, nThresholdStart, nThresholdMin, nFalloffCoeff);
}

void UpdateDIP3Parameters(int nActivationHeight, int nEnforcementHeight)
{
    globalChainParams->UpdateDIP3Parameters(nActivationHeight, nEnforcementHeight);
}

void UpdateBudgetParameters(int nMasternodePaymentsStartBlock, int nBudgetPaymentsStartBlock, int nSuperblockStartBlock)
{
    globalChainParams->UpdateBudgetParameters(nMasternodePaymentsStartBlock, nBudgetPaymentsStartBlock, nSuperblockStartBlock);
}

void UpdateDevnetSubsidyAndDiffParams(int nMinimumDifficultyBlocks, int nHighSubsidyBlocks, int nHighSubsidyFactor)
{
    globalChainParams->UpdateSubsidyAndDiffParams(nMinimumDifficultyBlocks, nHighSubsidyBlocks, nHighSubsidyFactor);
}

void UpdateDevnetLLMQChainLocks(Consensus::LLMQType llmqType)
{
    globalChainParams->UpdateLLMQChainLocks(llmqType);
}

void UpdateLLMQTestParams(int size, int threshold)
{
    globalChainParams->UpdateLLMQTestParams(size, threshold);
}

void UpdateLLMQDevnetParams(int size, int threshold)
{
    globalChainParams->UpdateLLMQDevnetParams(size, threshold);
}
