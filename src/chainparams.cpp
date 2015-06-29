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

        pchMessageStart[0] = 0x63;
        pchMessageStart[1] = 0xd7;
        pchMessageStart[2] = 0x1d;
        pchMessageStart[3] = 0x0a;

        vAlertPubKey = ParseHex("04f262f100bd6128131e41be3205dca5ee39a80ec99f66b3bad938d153e08d9de3882f8de75a85171873fdc600b2c543be1c7e04c63828707bf977050eb4ddec22");

        nDefaultPort = 76007;
        nRPCPort = 76008;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "MasterDoge";
        CTransaction txNew;
        txNew.nTime = 1435512297;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1435512297;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 515;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000ab95286e17cb32eee82992ec3699e90a7ebd1c5085b295c5a4ebcd9fe18"));
        assert(genesis.hashMerkleRoot == uint256("0x0adf5a0fcf460e8fb294aa4924194aa2d22b0e4bba129409169138b8bffb1ab2"));
		
        vSeeds.push_back(CDNSSeedData("104.238.152.99", "104.238.152.99"));
		
        base58Prefixes[PUBKEY_ADDRESS] = list_of(51);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(97);
        base58Prefixes[SECRET_KEY] =     list_of(139);

        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 60; // seconds

        nLastPOWBlock  = 20050; 
        nPremineAmount = 1000000 * COIN;
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

        vAlertPubKey = ParseHex("04f262f100bd6128131e41be3205dca5ee39a80ec99f66b3bad938d153e08d9de3882f8de75a85171873fdc600b2c543be1c7e04c63828707bf977050eb4ddec22");

        nDefaultPort = 55007;
        nRPCPort = 55008;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 259; //;

        hashGenesisBlock = genesis.GetHash(); 
        assert(hashGenesisBlock == uint256("0x0000dd87b6fcbc211a8a356c6964d85f3d380c3ee064e77157e36144dfc15379"));

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
