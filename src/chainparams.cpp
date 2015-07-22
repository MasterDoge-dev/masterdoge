// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.

        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0xd7;
        pchMessageStart[2] = 0x2d;
        pchMessageStart[3] = 0x0a;

        vAlertPubKey = ParseHex("04bd92e9f7ec8b3c48ebb27b743ff19cc131b06b18dcac8663d75ee0cc55878057ce9989dd1c82ba13b5277c0d058dd3241ebdeefab91f38300bda1cf8fabf3ad2");

        nDefaultPort = 2589;
        nRPCPort = 2588;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "MasterDoge FIXED";
        CTransaction txNew;
        txNew.nTime = 1435774855;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1435774855;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1476223;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000cf795158c6e102d3bf2c91ba14bf4a9932e8b759214341892782d5e4904"));
        assert(genesis.hashMerkleRoot == uint256("0xd3414c5a81b461dfe3066b11f4265da48cfc851f02b6933c0ae0a4a4f7d475d8"));
		
        vSeeds.push_back(CDNSSeedData("104.238.152.99", "104.238.152.99"));
		
        base58Prefixes[PUBKEY_ADDRESS] = list_of(51);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(97);
        base58Prefixes[SECRET_KEY] =     list_of(139);

        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 60; // seconds

        nLastPOWBlock  = 19130; 
        nPremineAmount = 4350000 * COIN;
        nPremineBlock = 1;
        nRegularPoWReward = 5000 * COIN; 

        nFirstPoSBlock = nLastPOWBlock - 50;
        nCoinbaseMaturity = 100;
        nLaunchTime = txNew.nTime;
        nStakeMinAge = 6 * 60 * 60;
        nModifierInterval = 1 * 60;
        nPoSCoinReward = 10; // percents
        nAdvisablePoSTxOut = 5000 * COIN;

        nMasternodeFixReward = 1000 * COIN;
        nMasternodeProportionalReward = 5; // percents
        nMasternodeValue = 20000 * COIN;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.

        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x07;
        pchMessageStart[2] = 0x19;
        pchMessageStart[3] = 0x6d;

        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        vAlertPubKey = ParseHex("04d66d222f3552e2405ffd3604c9f17a6642d04ea031199197ab32bedb0134bafd38c5b85464465e3434303a54c7f481f478e699efd35a47c14deaa30b1eb0dfee");

        nDefaultPort = 55007;
        nRPCPort = 55008;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 45234; //;

        hashGenesisBlock = genesis.GetHash(); 
        assert(hashGenesisBlock == uint256("0x0000ed00fec7d19aa0614f1fc2f4cf8fa143d71187b1395614e38edc2afbfb5e"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(117);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(164);
        base58Prefixes[SECRET_KEY]     = list_of(219);

        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 10; // seconds

        nLastPOWBlock = 0x7fffffff;
        nPremineAmount = 1000000 * COIN;
        nPremineBlock = 1;
        nRegularPoWReward = 10000 * COIN;

        nFirstPoSBlock = 7000;
        nCoinbaseMaturity = 200;
        nLaunchTime = 1433538000;
        nStakeMinAge = 1 * 60 * 60;
        nModifierInterval = 1 * 60;
        nPoSCoinReward = 15; // percents
        nAdvisablePoSTxOut = 10000 * COIN;

        nMasternodeFixReward = 50 * COIN;
        nMasternodeProportionalReward = 20; // percents
        nMasternodeValue = 5000 * COIN;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
