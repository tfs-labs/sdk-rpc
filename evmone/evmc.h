
#include <cstdint>
#include <string>
typedef struct evmc_address
{
    /** The 20 bytes of the hash. */
    uint8_t bytes[20];
} evmc_address;


struct address : evmc_address
{
    /// Default and converting constructor.
    ///
    /// Initializes bytes to zeros if not other @p init value provided.
    constexpr address(evmc_address init = {}) noexcept : evmc_address{init} {}

    /// Converting constructor from unsigned integer value.
    ///
    /// This constructor assigns the @p v value to the last 8 bytes [12:19]
    /// in big-endian order.
    constexpr explicit address(uint64_t v) noexcept
      : evmc_address{{0,
                      0,
                      0,
                      0,
                      0,
                      0,
                      0,
                      0,
                      0,
                      0,
                      0,
                      0,
                      static_cast<uint8_t>(v >> 56),
                      static_cast<uint8_t>(v >> 48),
                      static_cast<uint8_t>(v >> 40),
                      static_cast<uint8_t>(v >> 32),
                      static_cast<uint8_t>(v >> 24),
                      static_cast<uint8_t>(v >> 16),
                      static_cast<uint8_t>(v >> 8),
                      static_cast<uint8_t>(v >> 0)}}
    {}

    /// Explicit operator converting to bool.
    inline constexpr explicit operator bool() const noexcept;
};



namespace evm_utils{
    evmc_address stringToEvmAddr(const std::string& addr);
    std::string EvmAddrToBase58(const std::string& addr);
    evmc_address pubStrToEvmAddr(const std::string &pub) ;
    std::string EvmAddrToString(const evmc_address& addr);
}