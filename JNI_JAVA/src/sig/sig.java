package src.sig;

public class sig {
 
    /**
     * Import the private key base64
     * @param str The base64 of the private key
     * @return The private key handle
     */
    public  native long importPkey(String str);
    /**
     *  Generate a new private key
     * @return
     */
    public  native String newPkey();
    /**
     * 
     * @param pkey The private key handle
     * @param message Information that requires a signature
     * @return The signed message
     */
    public  native String sigmessage(long pkey,String message);
    /**
     * 
     * @param pkey The private key handle
     * @param message The signed message
     * @param signature
     * @return
     */
    public  native boolean vefmessage(long pkey,String message,String signature);
    /**
     * Sign transactions
     * @param pkey The private key handle
     * @param tx transactions
     * @return Signed transactions
     */
    public  native String sigTx(long pkey,String tx);
    /**
     * Get base58 through the private key handle
     * @param pkey
     * @return 
     */
    public  native String GetBase58(long pkey);
    /**
     * Export the private key hex
     * @param pkey The private key handle
     * @return The private key is hex
     */
    public  native String ExportPriHexStr(long pkey);
    /**
     * Import the private key hex
     * @param hexstr The private key is hex
     * @return The private key handle
     */
    public  native long ImportPriHexStr(String hexstr);
    /**
     * Export the private key mnemonic phrase
     * @param pkey The private key handle
     * @return Private key mnemonic
     */
    public  native String ExportMnemoic(long pkey);
    /**
     * Import the private key mnemonic phrase
     * @param mnstr Mnemonic
     * @return The private key handle
     */
    public  native long ImportMnemoic(String mnstr);
    /**
     * Get the public key base64
     * @param pkey The private key handle
     * @return 
     */
    public native  String getPubStringBase64(long pkey);
    /**
     * 
     * @param str
     * @return
     */
    public native String Base64Encode(String str);
    /**
     * 
     * @param str
     * @return
     */
    public native String Base64Decode(String str);
}
