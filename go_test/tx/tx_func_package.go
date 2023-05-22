package tx

import (
	"encoding/json"
	"fmt"
)

type toAddr struct {
	Addr  string `json:"addr"`  //base58 （ ）
	Value string `json:"value"` //
}
type tx_req struct {
	Type     string   `json:"type"`     //rpc
	FromAddr []string `json:"fromAddr"` //
	ToAddr   []toAddr `json:"toAddr"`   //toAddr
}

type get_stake_req struct {
	Type         string `json:"type"`
	FromAddr     string `json:"fromAddr"`
	Stake_amount string `json:"stake_amount"`
	PledgeType   string `json:"PledgeType"`
}

type get_unstake_req struct {
	Type      string `json:"type"`
	FromAddr  string `json:"fromAddr"`
	Utxo_hash string `json:"utxo_hash"`
}

type get_stakeutxo_req struct {
	Type     string `json:"type"`
	FromAddr string `json:"fromAddr"`
}

type get_invest_req struct {
	Type          string `json:"type"`
	FromAddr      string `json:"fromAddr"`
	ToAddr        string `json:"toAddr"`
	Invest_amount string `json:"invest_amount"`
	InvestType    string `json:"investType"`
}

type get_disinvest_req struct {
	Type      string `json:"type"`
	FromAddr  string `json:"fromAddr"`
	ToAddr    string `json:"toAddr"`
	Utxo_hash string `json:"utxo_hash"`
}
type get_disinvestutxo_req struct {
	Type     string `json:"type"`
	FromAddr string `json:"fromAddr"`
	ToAddr   string `json:"toAddr"`
}

type deploy_contract_req struct {
	Type          string `json:"type"`
	Addr          string `json:"addr"`
	NContractType string `json:"nContractType"`
	Info          string `json:"info"`
	Contract      string `json:"contract"`
	Data          string `json:"data"`
	Pubstr        string `json:"pubstr"`
}

type call_contract_req struct {
	Type       string `json:"type"`
	Addr       string `json:"addr"`
	Deployer   string `json:"deployer"`
	Deployutxo string `json:"deployutxo"`
	Drgs       string `json:"args"`
	Pubstr     string `json:"pubstr"`
}

type Contract_info struct {
	Type            string `json:"type"`
	Name            string `json:"name"`
	Language        string `json:"language"`
	LanguageVersion string `json:"languageVersion"`
	Standard        string `json:"standard"`
	Logo            string `json:"logo"`
	Source          string `json:"source"`
	ABI             string `json:"ABI"`
	UserDoc         string `json:"userDoc"`
	DeveloperDoc    string `json:"developerDoc"`
	CompilerVersion string `json:"compilerVersion"`
	CompilerOptions string `json:"compilerOptions"`
	SrcMap          string `json:"srcMap"`
	SrcMapRuntime   string `json:"srcMapRuntime"`
	Metadata        string `json:"metadata"`
	Other           string `json:"other"`
}

type Deploy_utxo_req struct {
	Type string `json:"type"`
	Addr string `json:"addr"`
}

type Get_bonus_req struct {
	Type string `json:"type"`
	Addr string `json:"Addr"`
}

func Call_contract(addr_str string, deployer_str string, deployutxo string, args_str string, pubstr string) string {
	tx_body := call_contract_req{"call_contract_req", addr_str, deployer_str, deployutxo, args_str, pubstr}
	js, err := json.Marshal(tx_body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)
}

func ToJson(info interface{}) string {
	js, err := json.Marshal(info)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)
}

func Deploy_contract(addr_str string, ntype_str string, info_str string, contract string, data string, pubstr string) string {
	tx_body := deploy_contract_req{"deploy_contract_req", addr_str, ntype_str, info_str, contract, data, pubstr}
	js, err := json.Marshal(tx_body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)
}

func DisinvestUtxo(fromadd_str string, toaddr_str string) string {
	tx_body := get_disinvestutxo_req{"get_disinvestutxo_req", fromadd_str, toaddr_str}
	js, err := json.Marshal(tx_body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)

}

func Disinvest(fromaddr_str string, toaddr_str string, utxo_hash string) string {
	tx_body := get_disinvest_req{"get_disinvest_req", fromaddr_str, toaddr_str, utxo_hash}
	js, err := json.Marshal(tx_body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)
}

func Invest(fromaddr_str string, toaddr_str string, amount string, itype string) string {
	tx_body := get_invest_req{"get_invest_req", fromaddr_str, toaddr_str, amount, itype}
	js, err := json.Marshal(tx_body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)
}

func Stakeutxo(fromAddr_str string) string {
	tx_body := get_stakeutxo_req{"get_stake_req", fromAddr_str}
	js, err := json.Marshal(tx_body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)

}

// json
func Tx_req(type_str string, fromAddr_str string, toAddr_str string, value string) string {
	toaddr_t := []toAddr{{toAddr_str, value}}
	fromaddr_t := []string{fromAddr_str}
	tx_body := tx_req{type_str, fromaddr_t, toaddr_t}
	js, err := json.Marshal(tx_body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)
}

func Stake(fromAddr_str string, amount string, ptype string) string {
	tx_body := get_stake_req{"get_stake_req", fromAddr_str, amount, ptype}
	js, err := json.Marshal(tx_body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)
}

func Unstake(fromaddr_str string, utxo_hash_str string) string {
	tx_body := get_unstake_req{"get_unstake_req", fromaddr_str, utxo_hash_str}
	js, err := json.Marshal(tx_body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(js)
}
