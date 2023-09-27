#include "evmc.hpp"
#include "base58.h"
#include <ripemd160.h>
namespace evm_utils {
evmc_address stringToEvmAddr(const std::string &addr) {
    const char *s = addr.data();
    evmc_address evm_addr = from_hex<address>(s);
    return evm_addr;
}

std::string EvmAddrToBase58(const evmc_address &addr) {
    using bytes = std::basic_string<uint8_t>;
    bytes str2 = bytes(addr.bytes, sizeof(addr.bytes));
    char buf[2048] = {0};
    size_t buf_len = sizeof(buf);
    b58check_enc(buf, &buf_len, 0x00, from_hex(hex(str2).data()).data(),
                 RIPEMD160_DIGEST_LENGTH);
    std::string Bs58Addr;
    Bs58Addr.append(buf, buf_len - 1);
    return Bs58Addr;
}

std::string EvmAddrToBase58(const std::string& addr)
{
    evmc_address evm_addr = stringToEvmAddr(addr);
    return EvmAddrToBase58(evm_addr);
}

evmc_address pubStrToEvmAddr(const std::string &pub) {
    std::string EvmAddress = generateEvmAddr(pub);
    const char *s = EvmAddress.data();
    evmc_address evmaddr = from_hex<address>(s);
    return evmaddr;
}

std::string EvmAddrToString(const evmc_address& addr)
{
    return hex({addr.bytes,sizeof(addr.bytes)});
}
} // namespace evm_utils