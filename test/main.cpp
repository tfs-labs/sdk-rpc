#include "base64.h"
#include "debug.h"
#include "sig.h"
#include "tx.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <json.hpp>
#include <sstream>
#include <fstream>
#include <httplib.h>
#include <interface.h>
#include <string>
#include <tuple>
#include "Mac.h"
std::string readAllFile(const std::string & path){
   std::ifstream fin(path);   // filename: xly2016I.txt
    std::stringstream buffer;            // stringstream object
    buffer << fin.rdbuf();          // read file content in stringstream object
    std::string str(buffer.str());       // store file content in a string
    return str;

}


std::string RpcGet(const std::string & req,const std::string & rpc_api){

     httplib::Headers headers = {
	{ "content-type", "application/json" }
	};

    httplib::Client cli("192.168.1.141", 11190);
    httplib::Result res = cli.Post(rpc_api, headers,req, "application/json");

    if(res.error()!=httplib::Error::Success){
       return   Sutil::Format("error:%s",(int)res.error());
    }

    return res->body;

}
std::string DoNext(const std::string & req,long long pkey,const std::string & rpc_api){

     httplib::Headers headers = {
	{ "content-type", "application/json" }
	};

    httplib::Client cli("192.168.1.141", 11190);
    httplib::Result res = cli.Post(rpc_api, headers,req, "application/json");

    if(res.error()!=httplib::Error::Success){
       return   Sutil::Format("error:%s",(int)res.error());
        
    }

    //tx_ack ack;
   // ack.paseFromJson(res->body);
    std::string m_boy=res->body;
    tx_ack ack;
    if(!ack.paseFromJson(res->body)){
        return "pase faile";
    }

    debugL("body:%s",res->body);
    char *tx_body=sig_tx((long long)pkey,m_boy.c_str(),m_boy.size());
    std::string tx_t(tx_body);

    debugL(tx_body);
    auto retv= cli.Post("/send_message",headers,tx_t,"application/json");
    delete[] tx_body;
    if(retv.error()!=httplib::Error::Success){
        return Sutil::Format("error:%s",(int)retv.error());
    }
    
   return res->body;
}

void transtion(long long pkey){
    tx_req req;
    req.fromAddr={"139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1"};
    req.toAddr={{"16fUBxFbTYtCfhRCb5GSyMACbuZuxfvdos","13.5"}};
    auto res=DoNext(req.paseToString(), pkey, "/get_transaction_req");
    debugL(res);
}


void stake(long long pkey)
{
    get_stake_req req;
    req.stake_amount="10000";
    req.fromAddr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    req.PledgeType="0";
    auto res=DoNext(req.paseToString(), pkey, "/get_stake_req");
    debugL(res);
    
}
void unstake(long long pkey){
    get_unstake_req req;
    req.fromAddr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    req.utxo_hash="836d3f0d921653d62657bd1949fabc889989e691722bd59264b2605d9c2c1272";
    auto res=DoNext(req.paseToString(), pkey, "/get_unstake_req");
    debugL(res);
}

void invest(long long pkey){
    get_invest_req req;
    req.invest_amount="20000";
    req.fromAddr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    req.toAddr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    
    auto res=DoNext(req.paseToString(), pkey, "/get_invest_req");
    debugL(res);
}


void uninvest(long long pkey){
    get_disinvest_req req;
    req.fromAddr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    req.toAddr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    req.utxo_hash="c72b2e7e4b98d41dee37113b55692dc9457181364802cc0bd1d5511738aabac3";
    auto res=DoNext(req.paseToString(), pkey, "/get_disinvest_req");
    debugL(res);
}
void deploy(long long pkey){
    deploy_contract_req req;
    req.contract=readAllFile("/home/wbl/Desktop/rpc_lib/test/contract.txt");
    req.nContractType="0";
    req.addr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    req.info="[]";
    req.data="";
    char * pubs=get_pubstr_base64(pkey);
    req.pubstr=std::string(pubs);
    auto res=DoNext(req.paseToString(), pkey, "/deploy_contract_req");
    debugL(res);
    
}

void call(long long pkey){
    call_contract_req req;
    req.addr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    req.args="0xa0712d680000000000000000000000000000000000000000000000000000000000002710";
    req.deployer="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    req.deployutxo="dc13fd75970e5e20ea024928302888abb174cd67f373583061dbade27c0de76c";
    req.money="0";
    req.tip="0";
    req.istochain="true";
    char * pubs=get_pubstr_base64(pkey);
    req.pubstr=std::string(pubs);
    auto res=DoNext(req.paseToString(), pkey, "/call_contract_req");
    debugL(res);
}


void getDeployUxtoHash(){
    deploy_utxo_req req;
    req.addr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    auto res=RpcGet(req.paseToString(), "/deploy_utxo_req");
    debugL(res);
}

void getInvserUtxoHash(){
    get_disinvestutxo_req req;
    req.fromAddr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    req.toAddr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    auto res=RpcGet(req.paseToString(), "/get_disinvestutxo_req");
    debugL(res);
}

void GetStakeUtxoHash(){
    get_stakeutxo_req req;
    req.fromAddr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    auto res=RpcGet(req.paseToString(), "/get_stakeutxo_req");
    debugL(res);

}
void bonus(long long pkey){
    get_bonus_req req;
    req.Addr="139UHgLVLtsqZYR4ZyWma9EqvenZxtCTL1";
    auto res=DoNext(req.paseToString(), pkey, "/get_bonus_req");
    debugL(res);
}



int main(){
     const std::string pkey_str="LS0tLS1CRUdJTiBQUklWQVRFIEtFWS0tLS0tCk1DNENBUUF3QlFZREsyVndCQ0lFSUxkbGhpUkxkdDFiLy9oOUNLMm9XNnlEcENTMFNrNDBNaWYwckpHQWs2WDIKLS0tLS1FTkQgUFJJVkFURSBLRVktLS0tLQo=";
     long long pkey=import_base64_prikey_handler(pkey_str.c_str(),pkey_str.size());
     //stake(pkey);
     //invest(pkey);
     transtion(pkey);
     //deploy(pkey);
     //getDeployUxtoHash();
     //call(pkey);
     //getInvserUtxoHash();
     //uninvest(pkey);
     //GetStakeUtxoHash();
     //unstake(pkey);
     //bonus(pkey);
     return 0;
}