// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2018 The Dash Core developers 
// Copyright (c) 2018-2021 The Veco Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Decentralised Economy += VECO; 9 October 2018";
    const CScript genesisOutputScript = CScript() << ParseHex("0431d9e740dfaa5e7f4c230bcd6ced7e8cdc5bf9f54acbc0f53c10e27a4e661b787a28be070def9b68ef679206cbe4590305ddb8f1bfd1865e20db9cc03ae09819") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 262800;
        consensus.nMasternodePaymentsStartBlock = 1080;
        consensus.nMasternodePaymentsIncreaseBlock = 10081;
        consensus.nMasternodePaymentsIncreasePeriod = 262800;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 99999999;
        consensus.nBudgetPaymentsCycleBlocks = 21600;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 99999999;
        consensus.nSuperblockCycle = 21600;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x000003fd1dff397d1be86183efd9e13f0316b5f5a3082bac91975a421bc43021");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 86400; // Veco: 1 day
        consensus.nPowTargetSpacing = 110; // Veco: 2.0 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 0;
        consensus.nPowDGWHeight = 0;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
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
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 3226; // 80% of 4032

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000003fd1dff397d1be86183efd9e13f0316b5f5a3082bac91975a421bc43021");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x76; //v
        pchMessageStart[1] = 0x65; //e
        pchMessageStart[2] = 0x63; //c
        pchMessageStart[3] = 0x6F; //o
        vAlertPubKey = ParseHex("047738e763b45593b3bc080cfd2ec07ce725d2c39b18e4bccced4ed75856afa15e88399cc894bbe9f10d98dd715081a27d3c45e5e7382f07c4c6bd32a9acda5c7d");
        nDefaultPort = 26919;
        
        nMaxTipAge = 21600;
        nDelayGetHeadersTime = 86400;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1539043200, 1599202, 0x1e0ffff0, 1, 20 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000003fd1dff397d1be86183efd9e13f0316b5f5a3082bac91975a421bc43021"));
        assert(genesis.hashMerkleRoot == uint256S("0xde4fe11d6d0c735a192d4e6eed593ad575ccd671ff4ff0d9188e347e067d028d"));

        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("veco.to", "block.veco.to"));
		vSeeds.push_back(CDNSSeedData("veco.to", "dns.veco.to"));
		vSeeds.push_back(CDNSSeedData("veco.to", "seed.veco.to"));
		vSeeds.push_back(CDNSSeedData("veco.to", "masi.veco.to"));


        // Veco addresses start with 'V'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,70);
        // Veco script addresses start with '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,20);
        // Veco private keys start with 'X'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,75);
        // Veco BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Veco BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // Veco BIP44 coin type is '5'
        nExtCoinType = 5;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "04825df8a146091cd7527a55a648cf1c23efb3cc25bed2029eaa17a606918be747b9afa29e08da4df312f8cfc9823fb3707635e8744000390574b40f28c0d509a9";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (    0, uint256S("0x000003fd1dff397d1be86183efd9e13f0316b5f5a3082bac91975a421bc43021"))
            (40000, uint256S("0x000001304558b69f7c952a4c8ad020ba3078ab6de3bf073c895171862f3885fd")),
                1544969061, // * UNIX timestamp of last checkpoint block
                83263,      // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
                500         // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210240;
        consensus.nMasternodePaymentsStartBlock = 4010;
        consensus.nMasternodePaymentsIncreaseBlock = 4030;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 4100;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 4200;
        consensus.nSuperblockCycle = 24; 
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00000997e30aad936446ab7226cecd21875e867a57aca1a46d17be4316bab391");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Veco: 1 day
        consensus.nPowTargetSpacing = 2.0 * 60; // Veco: 2.0 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 0;
        consensus.nPowDGWHeight = 0;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1506556800; // September 28th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1538092800; // September 28th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1505692800; // Sep 18th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1537228800; // Sep 18th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 50; // 50% of 100

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00000997e30aad936446ab7226cecd21875e867a57aca1a46d17be4316bab391");

        pchMessageStart[0] = 0x76; //v
        pchMessageStart[1] = 0x65; //e
        pchMessageStart[2] = 0x63; //c
        pchMessageStart[3] = 0x74; //testnet
        vAlertPubKey = ParseHex("04a6df8bb80ab3113dcae21d2a9ced9b2f48811ce079e44a19a53d0aae223388b79f5dfec3abe9dccfe250edd0caf243168ce4f0965fd8f0857c390c76da1a1db1");
        nDefaultPort = 16919;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1533168000, 189394, 0x1e0ffff0, 1, 20 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000997e30aad936446ab7226cecd21875e867a57aca1a46d17be4316bab391"));
        assert(genesis.hashMerkleRoot == uint256S("0xde4fe11d6d0c735a192d4e6eed593ad575ccd671ff4ff0d9188e347e067d028d"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("veco.info", "test01.veco.info"));
		vSeeds.push_back(CDNSSeedData("veco.info", "test02.veco.info"));
		vSeeds.push_back(CDNSSeedData("veco.info", "test03.veco.info"));
		vSeeds.push_back(CDNSSeedData("veco.info", "test04.veco.info"));
		vSeeds.push_back(CDNSSeedData("veco.info", "test05.veco.info"));
		vSeeds.push_back(CDNSSeedData("veco.info", "test06.veco.info"));
		vSeeds.push_back(CDNSSeedData("veco.info", "test07.veco.info"));
		vSeeds.push_back(CDNSSeedData("veco.info", "test08.veco.info"));
		vSeeds.push_back(CDNSSeedData("veco.info", "test09.veco.info"));
		vSeeds.push_back(CDNSSeedData("veco.info", "test10.veco.info"));

        // Testnet Veco addresses start with 'y'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,140);
        // Testnet Veco script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet Veco BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Veco BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Testnet Veco BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04ee3e3feb1e780b98327ece9579ff24991b6b6294f4bf53435e5feeb40ba166cbf71dc2b074c2703fd757b54befbe363b18bf56ec5a51be08ea6e912301afd1f2";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x00000997e30aad936446ab7226cecd21875e867a57aca1a46d17be4316bab391")),
                1533168000, //1519569150 * UNIX timestamp of last checkpoint block
                0,          // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
                10          // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Veco: 1 day
        consensus.nPowTargetSpacing = 2.0 * 60; // Veco: 2.0 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nPowKGWHeight = 0;
        consensus.nPowDGWHeight = 0;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x76; //v
        pchMessageStart[1] = 0x65; //e
        pchMessageStart[2] = 0x63; //c
        pchMessageStart[3] = 0x72; //reg
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 0; // never delay GETHEADERS in regtests
        nDefaultPort = 8334;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1531958400, 1, 0x207fffff, 1, 20 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x7f6c3cd530b97a2f646ff8311e5ff79a5ebaec359dacea13d67a7169b3f4e897"));
        assert(genesis.hashMerkleRoot == uint256S("0xde4fe11d6d0c735a192d4e6eed593ad575ccd671ff4ff0d9188e347e067d028d"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x7f6c3cd530b97a2f646ff8311e5ff79a5ebaec359dacea13d67a7169b3f4e897")),
            0,
            0,
            0
        };
        // Regtest Veco addresses start with 'y'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 140);
        // Regtest Veco script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);
        // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 239);
        // Regtest Veco BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Veco BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Regtest Veco BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
