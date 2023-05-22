#ifdef __cplusplus
extern "C" {
#endif
/* base64 */
__declspec(dllexport) long long __stdcall import_base64_prikey_handler(
    const char *buf, int buf_size);

/* base64 */
__declspec(dllexport) char *__stdcall export_new_prikey_base64();

/* */
__declspec(dllexport) long long __stdcall import_prikey_handler_from_hex(
    const char *str);

/* */
__declspec(dllexport) char *__stdcall export_new_prikey_to_hex(long long pkey);

/* */
__declspec(dllexport) char *__stdcall export_mnemonic_from_prikey_handler(
    long long pkey);

/* */
__declspec(dllexport) long long __stdcall import_prikey_handler_from_mnemonic(
    const char *mnemonic);
/* base58*/
__declspec(dllexport) char *__stdcall get_base58addr(long long pkey);
/* base64 */
__declspec(dllexport) char *__stdcall get_pubstr_base64(long long pkey);
/* */
__declspec(dllexport) char *__stdcall sig_tx(long long pkey,
                                             const char *message, int msize);

#ifdef __cplusplus
}
#endif
