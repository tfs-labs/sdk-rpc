# # SDK version

SDK Version: v0.0.1
Corresponding to the version of the support node program: V1.0.1

# # introduction

This SDK is a tool kit for the implementation of transaction functions, it provides a set of API interfaces, is a third-party generation transactions SDK library. It sends HTTP requests to a node via a fixed protocol in the JSON format. It makes it easy for developers to use the functionality it provides. This document is intended to provide developers with instructions on how to use this SDK so that they can quickly get started and use it.

# # environment and requirements

This SDK is applicable to a variety of environments, including:

- Windows (librpc.dll) 
- Centos 7(librpc.so) 

Software Requirements:

- operating system: Windows 10 or later, or CentOs 7
- development language: C + + , Go

Hardware Requirements:

Processor: 8-Core 64-bit processor, such as Intel Core I 5 or later
- memory: 8GB RAM or higher
- storage: at least 128GB of free space

Prerequisites

A private key needs to be prepared to be imported for the transaction signature, and an interface to import the private key is also provided in the library.

”'c' 
/* Export Base64 private key */
(DLLEXPORT) char * export () ;
/* import Base64 private key handle */
(DLLEXPORT) long long import (const char * buf, int buf) ;
/* import the hexadecimal private key */
(DLLEXPORT) long long import (const char * str) ;
```

# # transaction flow

Note: Various protocols are defined in this SDK

1. Get the parameters: before starting a transaction, you need to specify the protocol to get the parameters necessary for some transactions (such as UTXO, transaction hash, etc.) 
For example:

# # # Get Pledge Utxo

”'json
{
“Type”: “Get”,
“FromAddr”:”//Base58 where the account needs to be fetched
}

{
“Type”: “Get”,
“Utxos”: [{ 
“UTXO”:””,//The pledged UTXO returned
“Value”: the amount of the pledge returned by”//
}]
}

```

Get Investment Utxo

”'json
{
“Type”: “Get”,
“From Addr”:””,//Base58 needed to be fetched for the account
“TOADDR”:””//The Base58 in which the account is invested
}
{
“Type”: “Get”
“Utxos”: [”]//returns an investment in TOADDR's UTXO
}

```

# # # Get Deployer

”'json
{
“Type”: “Deployers”
}

{
“Type”: “Deployers”,
“Deployers”: [”]//deployer
}

```

Get Utxo for contract deployment

”'json
{
“Type”: “Deploy”,
“Addr”:”//deploy the contractor's Base58
}
{
“Type”: “Deploy”
“Utxos”: Utxo for the contract deployment returned by the [””]//interface
}

```

2. Populate Protocol: the protocol is then populated with the corresponding parameters, and the protocol is composed of JSON and sent over HTTP to the distribution node (described in the trade introduction title) 
3. Node processing: the node generates the transaction, which is then returned via the HTTP interface
4. Transaction signature: after receiving the transaction body returned by the node, the user will return the content via librpc. DLL/librpc.so.
5. Transaction Linked: At this point the transaction has been generated, and then broadcast through the HTTP interface, and then the success of the transaction will be returned through the HTTP interface.

# # description of the transaction

The following are the various JSON bodies that need to be populated:

# # # normal transaction
' JSON
{
“Type”: “TX”,//protocol name
“FromAddr”: “”,//Base58 of the initiator
“TOADDR”: [{//Base58 of the receiver
“Addr”:””,//receiver address
“Value”:””//the amount to be transferred
}]
}

```

Pledge transaction

' JSON
{
“Type”: “Get”,//protocol name
“From Addr”:”,//initiator base58
“Stake”: “”,//The amount pledged
“PledgeType”:”//PledgeType (defaults to 0) 
}

```
Release the pledge
”'json
{
“Type”: “Get”,
“FromAddr”: “”,//the originator of the pledge
“UTXO”:”//UTXO to be unpledged (this UTXO is utxo to be pledged for the account returned through the get interface) 
}

```

Invest
”'json
{
“Type”: “Get”,
“FromAddr”: “”,//transaction initiation
“ToAddr”: “”,//The investee
“Invest”:”,//amount invested
“InvestType”:”//investType (defaults to 0) 
}

```

Invest
”'json
{
“Type”: “Get”,
“FromAddr”: “”,//explain the originator of the investment transaction
“ToAddr”:””,”//investment transaction when the investor
“UTXO”:””//Utxo of the original investment transaction (this UTXO is returned by get) 
}

```

Claim
”'json
{
“Type”: “Get”,
“Addr”: the address where the claim transaction is initiated
}

```

# # # # deployment contract

”'json
{
“Type”: “Contract”,//contract information, defined by the user
“Name”: “Name”,
Language:
Languageversion,
Standard,
logo,
Source: source,
abi,
userDoc:””,
developerDoc,
Compilerversion:
Compileroptions,
SRCMAP: srcMap,
srcmap runtime,
Metadata:
Other

}
{
“Type”: “Deploy”,//deploy contract
“Addr”: “”,//The address to deploy
“NContractType”:””,//deployment type (default is 0) 
“Info”: “”,//
“Contract”:””,//generated contract
“Data”: “”,//constructor arguments
“Pubstr”: public key after”//Base64
}

```

Execute the contract

”'json
{
“Type”: “Call”,
“Addr”: “”,//The address to execute the contract
“Deployer”: “”,//deployer
“Deployutxo”:””,//deploy utxo for the contract
“Args”:””,//contract parameters
“Pubstr”: public key after”//Base64
}

```
Get started quickly

Below is sample code for various languages

”'go
//Go
{
/* Private Key Base64 */
PKEYSTR: = C. CString (“Ls0tls1crudjtibquklwqvrfietfws0tls0tck1dnenbuuf3qlfzresyvndcq0lfsu5pdu9gdefytfovwdayqmtrb2tbagi0znq1vwndaw5uywnpvnu5txpnukokls0tls1ftkqgufjjvkfursblrvktls0tlqo =”) 
Res: = C. Gostring (PKEYSTR) 
PKEYSTR: = C.int (Len (Res)) 

/* import private key produce private key handle */
Pkey: = C. Import (PKEYSTR, PKEYSTR) 

Base58: = C. Get (pkey) 

Base58: = C. Gostring (Base58) 

Fmt. Println (Base58) 

Pkey: = Int64(pkey) 

//TX (pkey) 

//stake (pkey) 

//Printstakeutxo () 

//Ustake (pkey) 

//Invest (pkey) 

//dinvest (pkey) 

//Printinverst () 

//fmt. Println (readFile (“Contract/Abi.json”)) 

//deploy (pkey) 

//Printdeployer () 

Call (PKEY) 

}
```

Note: The above code as an example code, please adjust and develop according to your actual situation.

