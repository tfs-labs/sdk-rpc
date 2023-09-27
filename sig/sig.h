
#ifndef __SIG_H_
#define __SIG_H_
#include <string>
extern "C" {

/**
 * @brief Import the private key
 *
 * @param buf  Private key memory address
 * @param buf_size  The length of the private key
 * @return void* EVP_PKEY 
 */
void *ImportEVP_PKEY(const unsigned char *buf, int buf_size);

/**
 * @brief Generate a private key
 *
 * @param buf Private key secondary pointer
 * @param size  The length of the private key
 * @return true
 * @return false
 */

bool ExportEVP_PKEY(unsigned char **buf, int *size);

/**
 * @brief signature
 *
 * @param pkey ImportEVP_PKEY return value
 * @param message  The information to sign
 * @param size_message Information length
 * @param signature  Sign the result
 * @param size_signature Signature length
 * @return true
 * @return false
 */

bool sig_(const void *pkey, const unsigned char *message, int size_message,
          unsigned char **signature, int *size_signature);

/**
 * @brief Signature verification
 *
 * @param pkey ImportEVP_PKEY return value
 * @param message Information to be verified
 * @param size_message Information length
 * @param signature signature
 * @param size_signature Signature length
 * @return true
 * @return false
 */
bool verf_(const void *pkey, const unsigned char *message, int size_message,
           unsigned char *signature, int size_signature);


/**
 * @brief Import the private key from HexStr
 * 
 * @param str 
 * @return void* 
 */
void *ImportFromHexStr(const char *str);

/**
 * @brief The private key is exported to HexStr
 * 
 * @param pkey 
 * @param buf 
 * @param size 
 * @return true 
 * @return false 
 */
bool ExportToHexStr(const void *pkey, char **buf, int *size);

/**
 * @brief Export mnemonics
 * 
 * @param pkey 
 * @param buf 
 * @param size 
 * @return true 
 * @return false 
 */
bool ExportMnemonic(const void *pkey,char ** buf,int *size);

/**
 * @brief Import mnemonics
 * 
 * @param mnemonic 
 * @return void* 
 */
void *ImportFromMnemonic(const char * mnemonic);

void getBase58addr_c(const void * pkey,char **buf,int *size);

void getPriStr_c(const void * pkey,char **buf,int *size);

void getPubStr_c(const void *pkey,char ** buf,int *size);

void free_pkey(const void *pkey);

}


#endif