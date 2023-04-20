package src.tx;

import java.util.Vector;

public class Tx {
    
    public static  class tx_base_req{
        public String type;
    }

    public static class tx_base_ack{
        public String type;
        public String ErrorCode;
        public String ErrorMessage;
    }


    //Normal transaction requests
    public static  class tx_req extends tx_base_req{
        public  static class TOADDR{
            public TOADDR(String addr_, String value_) {
                addr=addr_;
                value=value_;
            }
            public String addr;
            public String value;
        }
        public Vector<String> fromAddr;
        public Vector<TOADDR> toAddr;
        public tx_req(){
            type="tx_req";
            fromAddr=new Vector<String>();
            toAddr=new Vector<TOADDR>();
        }
    }


    //Request for staking
    public static class get_stake_req extends tx_base_req{
        public String fromAddr;
        public String stake_amount;
        public String PledgeType;
        public get_stake_req(){
            type="get_stake_req";
        }
    }

    //Get the staked UTXO
    public static class get_stakeutxo_req extends tx_base_req{
        public String fromAddr;
        public get_stakeutxo_req(){
            type="get_stakeutxo_req";
        }
    }

    //Unstaking request
    public static class get_unstake_req extends tx_base_req{
        public String fromAddr;
        public String utxo_hash;
        public get_unstake_req(){
            type="get_unstake_req";
        }
    }
    //Investment Requests
    public static class get_invest_req extends tx_base_req{
        public String fromAddr;
        public String toAddr;
        public String invest_amount;
        public String investType;
        public get_invest_req(){
            type="get_invest_req";
        }
    }

    //Solve investment requests
    public static class get_disinvest_req extends tx_base_req{
        public String fromAddr;
        public String toAddr;
        public String utxo_hash;
        public get_disinvest_req(){
            type="get_disinvest_req";
        }
    }

    //Claim Request
    public static class get_bonus_req extends tx_base_req{
        public String Addr;
        public get_bonus_req(){
            type="get_bonus_req";
        }
    }

    //Contract Information
    public static class contract_info extends tx_base_req{
        public String name;
        public String language;
        public String languageVersion;
        public String standard;
        public String logo;
        public String source;
        public String ABI;
        public String userDoc;
        public String developerDoc;
        public String compilerVersion;
        public String compilerOptions;
        public String srcMap;
        public String srcMapRuntime;
        public String metadata;
        public String other;
        public contract_info(){
            type="contract_info";
            name="";
            language="";
            languageVersion="";
            standard="";
            logo="";
            source="";
            ABI="";
            userDoc="";
            developerDoc="";
            compilerVersion="";
            compilerOptions="";
            srcMap="";
            srcMapRuntime="";
            metadata="";
            other="";
        }
    }

    //Deploy the contract request
    public static class deploy_contract_req extends tx_base_req{
        public String addr;
        public String nContractType;
        public String info;
        public String contract;
        public String data;
        public String pubstr;
        public deploy_contract_req(){
            type="deploy_contract_req";
        }
    }
    //Execute contract requests
    public static class call_contract_req extends tx_base_req{
        public String addr;
        public String deployer;
        public String deployutxo;
        public String args;
        public String pubstr;
        public call_contract_req(){
            type="call_contract_req";
        }
    }

    public static class get_deloyutxo_req extends tx_base_req{
        public String addr;
        public get_deloyutxo_req(){
            type="get_deloyutxo_req";
        }
    }

    public static class get_disinvestutxo_req extends tx_base_req{
        public String fromAddr;
        public String toAddr;
        public get_disinvestutxo_req(){
            type="get_disinvestutxo_req";
        }
     }

}


