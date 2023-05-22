package main

/*
#cgo CFLAGS: -I./lib
#cgo LDFLAGS: -L./ -ljni_cpp
#include "go_interface.h"
*/
import "C"
import (
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
	"solib/tx"
	"strings"
)

func main() {
	/*  base64*/
	pkeyStr := C.CString("LS0tLS1CRUdJTiBQUklWQVRFIEtFWS0tLS0tCk1DNENBUUF3QlFZREsyVndCQ0lFSUpabXI1S1ZlZVJPeS9EVjRTMmErZ3hqaENtSDh2dGl2T2Y1Y3gxREY5TXcKLS0tLS1FTkQgUFJJVkFURSBLRVktLS0tLQ=")
	//pkeyStr := C.CString("LS0tLS1CRUdJTiBQUklWQVRFIEtFWS0tLS0tCk1DNENBUUF3QlFZREsyVndCQ0lFSU5pdU9GdEFYTFovWDAyQmtRb2tBaGI0ZnQ1VWNDaW5UYWNPVnU5TXpNUkoKLS0tLS1FTkQgUFJJVkFURSBLRVktLS0tLQo=")
	res := C.GoString(pkeyStr)
	pkeyStr_size := C.int(len(res))

	/* */
	pkey := C.import_base64_prikey_handler(pkeyStr, pkeyStr_size)

	base58 := C.get_base58addr(pkey)

	base58_go_str := C.GoString(base58)

	fmt.Println(base58_go_str)

	pkey_t := int64(pkey)

	//tx_test(pkey_t)

	//stake_test(pkey_t)

	//printStakeUtxo()

	//ustake_test(pkey_t)

	//invest_test(pkey_t)

	//dinvest(pkey_t)

	//printInverst()

	//fmt.Println(readFile("contract/abi.json"))

	//deploy_contract_test(pkey_t)

	//printDeployer_and_DeployerUtxo()

	//call_contract_test(pkey_t)

	bounus_test(pkey_t)

}

func readFile(path string) string {

	file, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
		return ""
	}
	defer file.Close()

	fileinfo, err := file.Stat()
	if err != nil {
		fmt.Println(err)
		return ""
	}

	filesize := fileinfo.Size()
	buffer := make([]byte, filesize)

	bytesread, err := file.Read(buffer)
	if err != nil {
		fmt.Println(err)
		return ""
	}

	fmt.Println("bytes read: ", bytesread)
	//fmt.Println("bytestream to string: ", string(buffer))
	return string(buffer)
}

func bounus_test(pkey int64) {

	req := tx.Get_bonus_req{Type: "get_bonus_req", Addr: "1zzF8jNBAXFTPJzhvY45zLKgQmnPLBZ93"}
	res := httpPost("http://192.168.1.141:11190/get_bonus_req", tx.ToJson(req))
	toCstring := C.CString(res)
	toCstring_size := C.int(len(res))
	pkey_t := C.longlong(pkey)

	tx_msg := C.sig_tx(pkey_t, toCstring, toCstring_size)

	go_tx_msg := C.GoString(tx_msg)

	res = httpPost("http://192.168.1.141:11190/send_message", go_tx_msg)
	fmt.Println(res)
}

func printDeployer_and_DeployerUtxo() {
	res := httpPost("http://192.168.1.141:11190/deployers_req", "{}")
	fmt.Print("depolyer:")
	fmt.Println(res)

	req := tx.Deploy_utxo_req{Type: "Deploy_utxo_req", Addr: "1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x"}

	res = httpPost("http://192.168.1.141:11190/deploy_utxo_req", tx.ToJson(req))
	fmt.Print("utxo:")
	fmt.Println(res)
}

func call_contract_test(pkey int64) {
	pkeyt := C.longlong(pkey)
	pubbase64 := C.get_base58addr(pkeyt)
	pubbase64_go_str := C.GoString(pubbase64)
	req := tx.Call_contract("1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", "1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", "6d90997b1bfc384b13efb10577bf23040e6533513159d092ed336d9e42406b17", "0x06fdde03", pubbase64_go_str)
	res := httpPost("http://192.168.1.141:11190/call_contract_req", req)
	toCstring := C.CString(res)
	toCstring_size := C.int(len(res))

	pkey_t := C.longlong(pkey)

	tx_msg := C.sig_tx(pkey_t, toCstring, toCstring_size)

	go_tx_msg := C.GoString(tx_msg)

	res = httpPost("http://192.168.1.141:11190/send_message", go_tx_msg)

	fmt.Println(res)

}

func deploy_contract_test(pkey int64) {
	info := tx.Contract_info{}
	info.ABI = readFile("contract/abi.json")
	info.DeveloperDoc = readFile("contract/devdoc.json")
	info.Name = "blabla"
	info.Metadata = readFile("contract/metadata.json")
	info.Other = readFile("contract/otherdata.json")
	info.UserDoc = readFile("contract/userdoc.json")
	info.Source = readFile("contract/source.sol")
	info.SrcMap = readFile("contract/srcmap.txt")
	info.SrcMapRuntime = readFile("contract/srcmap_runtime.txt")

	req := tx.Deploy_contract("1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", "0", tx.ToJson(info), readFile("contract/contract"), "", "")

	res := httpPost("http://192.168.1.141:11190/deploy_contract_req", req)
	toCstring := C.CString(res)
	toCstring_size := C.int(len(res))

	pkey_t := C.longlong(pkey)

	tx_msg := C.sig_tx(pkey_t, toCstring, toCstring_size)

	go_tx_msg := C.GoString(tx_msg)

	res = httpPost("http://192.168.1.141:11190/send_message", go_tx_msg)

	fmt.Println(res)
}

func printInverst() {
	req := tx.DisinvestUtxo("1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", "1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x")
	res := httpPost("http://192.168.1.141:11190/get_disinvestutxo_req", req)
	fmt.Println(res)
}

func dinvest(pkey int64) {
	utxohash := "c5fb4a3ca5c480267f69e0321df335b25a6d758b9454ca4551984be101c23768"
	req := tx.Disinvest("1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", "1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", utxohash)
	res := httpPost("http://192.168.1.141:11190/get_disinvest_req", req)
	fmt.Println(res)
	toCstring := C.CString(res)
	toCstring_size := C.int(len(res))

	pkey_t := C.longlong(pkey)

	tx_msg := C.sig_tx(pkey_t, toCstring, toCstring_size)

	go_tx_msg := C.GoString(tx_msg)

	res = httpPost("http://192.168.1.141:11190/send_message", go_tx_msg)

	fmt.Println(res)
}

func invest_test(pkey int64) {
	req := tx.Invest("1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", "1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", "25000", "0")
	fmt.Println(req)
	res := httpPost("http://192.168.1.141:11190/get_invest_req", req)

	toCstring := C.CString(res)
	toCstring_size := C.int(len(res))

	pkey_t := C.longlong(pkey)

	tx_msg := C.sig_tx(pkey_t, toCstring, toCstring_size)

	go_tx_msg := C.GoString(tx_msg)

	res = httpPost("http://192.168.1.141:11190/send_message", go_tx_msg)

	fmt.Println(res)
}

func tx_test(pkey int64) {

	req := tx.Tx_req("tx_req", "1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", "1zzF8jNBAXFTPJzhvY45zLKgQmnPLBZ93", "10")
	fmt.Println(req)

	res := httpPost("http://192.168.1.141:11190/get_transaction_req", req)

	toCstring := C.CString(res)
	toCstring_size := C.int(len(res))

	pkey_t := C.longlong(pkey)

	tx_msg := C.sig_tx(pkey_t, toCstring, toCstring_size)

	go_tx_msg := C.GoString(tx_msg)

	res = httpPost("http://192.168.1.141:11190/send_message", go_tx_msg)

	fmt.Println(res)
}

func printStakeUtxo() {
	req := tx.Stakeutxo("1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x")
	res := httpPost("http://192.168.1.141:11190/get_stakeutxo_req", req)
	fmt.Println(res)
}

func stake_test(pkey int64) {
	req := tx.Stake("1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", "10000", "0")

	fmt.Println(req)

	res := httpPost("http://192.168.1.141:11190/get_stake_req", req)

	toCstring := C.CString(res)
	toCstring_size := C.int(len(res))

	pkey_t := C.longlong(pkey)

	tx_msg := C.sig_tx(pkey_t, toCstring, toCstring_size)

	go_tx_msg := C.GoString(tx_msg)

	res = httpPost("http://192.168.1.141:11190/send_message", go_tx_msg)

	fmt.Println(res)

}

func ustake_test(pkey int64) {
	utxohash := "e32fbce7161001e49c7b46679c8c4050b5a1c355f5d82c897b4316faa2e4db52" // by get_stakeutxo_req (printStakeUtxo)
	req := tx.Unstake("1F771mPzYKvYrxXPdrcRUWDKwrbjmuTA8x", utxohash)

	res := httpPost("http://192.168.1.141:11190/get_unstake_req", req)
	toCstring := C.CString(res)
	toCstring_size := C.int(len(res))

	pkey_t := C.longlong(pkey)

	tx_msg := C.sig_tx(pkey_t, toCstring, toCstring_size)

	go_tx_msg := C.GoString(tx_msg)

	//
	res = httpPost("http://192.168.1.141:11190/send_message", go_tx_msg)
	fmt.Println(res)
}

func httpPost(url string, msg string) string {
	_bodys := strings.NewReader(msg)

	response, err_t := http.Post(url, "application/json", _bodys)
	if err_t != nil {
		fmt.Printf(err_t.Error())
	}
	body, err := ioutil.ReadAll(response.Body)
	if err != nil {
		fmt.Println(err.Error())
	}
	return string(body)
}
