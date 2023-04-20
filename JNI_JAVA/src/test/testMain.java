package src.test;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import java.net.InetSocketAddress;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.sun.net.httpserver.HttpServer;



import src.envelop.Envelop;
import src.tx.Tx.get_invest_req;
import src.tx.Tx.get_stake_req;
import src.tx.Tx.get_stakeutxo_req;
import src.tx.Tx.get_unstake_req;
import src.tx.Tx.tx_req;
import src.tx.Tx.tx_req.TOADDR;
import src.tx.Tx.get_disinvest_req;
import src.tx.Tx.get_disinvestutxo_req;
import src.sig.sig;
import src.tx.Tx.get_bonus_req;
import src.tx.Tx.get_deloyutxo_req;
import src.tx.Tx.contract_info;
import src.tx.Tx.deploy_contract_req;

import src.tx.Tx.call_contract_req;

/* javac -sourcepath src/test src/test/*.java    */
/*javac -sourcepath src/test src/test/*.java src/tx/*.java -extdirs lib */
public class testMain {

    public static String readFile(String path) throws IOException {
        File file = new File(path);
        BufferedReader br = new BufferedReader(new FileReader(file));
        String len = null;
        String ret = "";
        while ((len = br.readLine()) != null) {
            ret = ret + len;
        }
        return ret;
    }

    public static void main(String[] arg) throws IOException {

        System.loadLibrary("libjni_cpp");
        // Envelop env_obj = new Envelop();
        // long envelop_p_1 = env_obj.GetEnvelopPoint();
        // long envelop_p_2 = env_obj.GetEnvelopPoint();

        // String testHello_to_encode = "hello,myName is Func";
        // String pubstr_2 = env_obj.GetPublicString(envelop_p_2);
        // System.out.println(pubstr_2);
 
        // String encoded = env_obj.Encode(envelop_p_1, pubstr_2, testHello_to_encode);

        // String decoded = env_obj.Decode(envelop_p_2, encoded);

        // System.out.println(decoded);

        // env_obj.FreeEnvelopPoint(envelop_p_2);
        // env_obj.FreeEnvelopPoint(envelop_p_1);

        // tx_req tx_obj=new tx_req();

        // tx_obj.fromAddr.add("12345");
        // tx_obj.toAddr.add(new TOADDR("kdfksadf","dkafsdf"));

        // System.out.println("what");
        // ObjectMapper

        // ObjectMapper mapper=new ObjectMapper();

        // try {
        // String debug_value=mapper.writeValueAsString(tx_obj);
        // System.out.println(debug_value);
        // } catch (JsonProcessingException e) {

        // e.printStackTrace();
        // }

        String NewPkey = "LS0tLS1CRUdJTiBQUklWQVRFIEtFWS0tLS0tCk1DNENBUUF3QlFZREsyVndCQ0lFSUJkaXE2cDFXbmZZVnRlSmdDdjRjMXRjbTBxK0FiQTFXR2R2a2ExRDc1QWYKLS0tLS1FTkQgUFJJVkFURSBLRVktLS0tLQo=";

        sig sig_obj = new sig();

        long pkey = sig_obj.importPkey(NewPkey);
        String base58addr = sig_obj.GetBase58(pkey);
        System.out.println(base58addr);

        String zzkey = "-----BEGIN PRIVATE KEY-----\nMC4CAQAwBQYDK2VwBCIEIKUKajl2raolMtoZ6qIW8rPgiiKfEB0pwfMQg12jDv2Q\n-----END PRIVATE KEY-----";

        String pkec = sig_obj.Base64Encode(zzkey);
        long lzpkey = sig_obj.importPkey(pkec);
        String base58_ = sig_obj.GetBase58(lzpkey);
        System.out.println(base58_);

        // tx_test(pkey);

        // sig_obj.newPkey();

        // stake(pkey);

        // unstake(pkey);

        // invest(pkey);

        // disinvest(pkey);

        //bonus(lzpkey);

        // deploy(pkey);

        // callDeploy(pkey);

        // String Mne=sig_obj.ExportMnemoic(pkey);
        // System.out.println(Mne);
        // String Hexstr=sig_obj.ExportPriHexStr(pkey);
        // System.out.println(Hexstr);

        printDeployutxo();
        printStakeUtxo();
        printInverstUtxo();
    }

    public static void printDeployutxo() throws IOException{
        get_deloyutxo_req req=new get_deloyutxo_req();
        req.addr="1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        String res = httpPost("http://192.168.1.141:11190/call_contract_req", body);
        System.out.println(res);
    }

    public static void printStakeUtxo() throws IOException {
        get_stakeutxo_req req=new get_stakeutxo_req();
        req.fromAddr="1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        String res = httpPost("http://192.168.1.141:11190/get_stakeutxo_req", body);
        System.out.println(res);

    }

    public static void printInverstUtxo() throws IOException{
        get_disinvestutxo_req req=new get_disinvestutxo_req();
        req.fromAddr="1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        req.toAddr="1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        String res = httpPost("http://192.168.1.141:11190/get_disinvestutxo_req", body);
        System.out.println(res);

    }

    public static void callDeploy(long pkey) throws IOException {
        sig acount = new sig();
        call_contract_req req = new call_contract_req();
        req.addr = "1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        req.deployer = "1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        req.args = "0x06fdde03";
        req.deployutxo = "d3a903fc0c38b95266cec2d210755390da2bce9d5a7b93ff283e2485475706f4";
        req.pubstr = acount.getPubStringBase64(pkey);

        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        System.out.println(body);
        String res = httpPost("http://192.168.1.141:11190/call_contract_req", body);

        body = acount.sigTx(pkey, res);
        System.out.println(body);
        res = httpPost("http://192.168.1.141:11190/send_message", body);
        System.out.println(res);

    }

    public static void deploy(long pkey) throws IOException {
        contract_info info = new contract_info();
        info.ABI = readFile("src/test/contract/abi.json");
        info.developerDoc = readFile("src/test/contract/devdoc.json");
        info.name = "blabal";
        info.metadata = readFile("src/test/contract/metadata.json");
        info.other = readFile("src/test/contract/otherdata.json");
        info.userDoc = readFile("src/test/contract/userdoc.json");
        info.source = readFile("src/test/contract/source.sol");
        info.srcMap = readFile("src/test/contract/srcmap.txt");
        info.srcMapRuntime = readFile("src/test/contract/srcmap_runtime.txt");

        ObjectMapper mapper = new ObjectMapper();
        String info_str = mapper.writeValueAsString(info);

        sig acount = new sig();
        deploy_contract_req req = new deploy_contract_req();
        req.addr = "1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        req.contract = readFile("src/test/contract/contract");
        req.nContractType = "0";
        req.pubstr = acount.getPubStringBase64(pkey);
        req.data = "";

        req.info = info_str;
       

        String body = mapper.writeValueAsString(req);
        System.out.println(body);
        String res = httpPost("http://192.168.1.141:11190/deploy_contract_req", body);

        body = acount.sigTx(pkey, res);
       
        res = httpPost("http://192.168.1.141:11190/send_message", body);
        System.out.println(res);

    }

    public static void bonus(long pkey) throws IOException {
        sig acount = new sig();
        get_bonus_req req = new get_bonus_req();
        req.Addr = "19QyLmm5sDMUsnAaBbW9sgQjKtRRJjf9mN";

        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        
        String res = httpPost("http://192.168.1.141:11190/get_bonus_req", body);

        body = acount.sigTx(pkey, res);
       
        res = httpPost("http://192.168.1.141:11190/send_message", body);
        System.out.println(res);

    }

    public static String httpPost(String address, String body) throws IOException {
        URL postUrl = new URL(address);

        HttpURLConnection connection = (HttpURLConnection) postUrl.openConnection();
        connection.setDoOutput(true);
        connection.setDoInput(true);
        connection.setRequestMethod("POST");
        connection.setUseCaches(false);
        connection.setInstanceFollowRedirects(true);

        connection.setRequestProperty("connection", "close");

        connection.setRequestProperty("Content-Type", "application/json");
        connection.connect();
        DataOutputStream out = new DataOutputStream(connection.getOutputStream());
        out.write(body.getBytes("UTF-8"));
        out.flush();
        out.close();
        ByteArrayOutputStream outStream = new ByteArrayOutputStream();
        InputStream input = null;
        if (connection.getResponseCode() == 200) {
            input = connection.getInputStream();
        } else {
            input = connection.getErrorStream();
        }
        byte[] buffer = new byte[1024];
        int len = 0;
        while ((len = input.read(buffer)) != -1) {
            outStream.write(buffer, 0, len);
        }
        byte[] data = outStream.toByteArray();
        String result = new String(data, "UTF-8");
        outStream.close();
        input.close();
        connection.disconnect();
        System.out.println(result);
        return result;
    }

    // trade
    public static void tx_test(long pkey) throws IOException {

        sig acount = new sig();
        tx_req req = new tx_req();
        req.fromAddr.add("1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk");
        req.toAddr.add(new TOADDR("1zzF8jNBAXFTPJzhvY45zLKgQmnPLBZ93", "10"));

        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        System.out.println(body);
        String res = httpPost("http://192.168.1.141:11190/get_transaction_req", body);

        body = acount.sigTx(pkey, res);
        System.out.println(body);
        res = httpPost("http://192.168.1.141:11190/send_message", body);
        System.out.println(res);

    }

    // impawn
    public static void stake(long pkey) throws IOException {
        sig account = new sig();
        get_stake_req req = new get_stake_req();
        req.fromAddr = "1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        req.stake_amount = "10000";
        req.PledgeType = "0";

        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        System.out.println(body);
        String res = httpPost("http://192.168.1.141:11190/get_stake_req", body);

        body = account.sigTx(pkey, res);
        System.out.println(body);
        res = httpPost("http://192.168.1.141:11190/send_message", body);
        System.out.println(res);
    }

    // Unstake
    public static void unstake(long pkey) throws IOException {
        sig account = new sig();
        get_unstake_req req = new get_unstake_req();
        req.fromAddr = "1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";

        req.utxo_hash = "6db09ae49b295448f14fc8c3f61c37ee52a5c6848ddd483535b128d95fae194d";
        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        System.out.println(body);
        String res = httpPost("http://192.168.1.141:11190/get_unstake_req", body);
       

        body = account.sigTx(pkey, res);
        System.out.println(body);
        res = httpPost("http://192.168.1.141:11190/send_message", body);
        System.out.println(res);

    }

    // investment
    public static void invest(long pkey) throws IOException {
        sig account = new sig();
        get_invest_req req = new get_invest_req();
        req.fromAddr = "1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        req.toAddr = "1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        req.investType = "0";
        req.invest_amount = "25000";

        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        System.out.println(body);
        String res = httpPost("http://192.168.1.141:11190/get_invest_req", body);

        body = account.sigTx(pkey, res);
        System.out.println(body);
        res = httpPost("http://192.168.1.141:11190/send_message", body);
        System.out.println(res);
    }

    // Solution investment
    public static void disinvest(long pkey) throws IOException {
        sig account = new sig();
        get_disinvest_req req = new get_disinvest_req();

        req.fromAddr = "1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        req.toAddr = "1H1o5Dt7d5A4zUTpSV4CRkAFed2qtgvtQk";
        req.utxo_hash = "148f21965662d9034295312b6dcdee82fc3a74df6fe8aea96023177a40a8e423";

        ObjectMapper mapper = new ObjectMapper();
        String body = mapper.writeValueAsString(req);
        System.out.println(body);
        String res = httpPost("http://192.168.1.141:11190/get_disinvest_req", body);

        body = account.sigTx(pkey, res);
        System.out.println(body);
        res = httpPost("http://192.168.1.141:11190/send_message", body);
        // res=httpPost("http://192.168.1.141:11190/send_message", body);
        System.out.println(res);
    }
}
