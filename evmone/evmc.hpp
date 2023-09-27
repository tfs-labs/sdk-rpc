#include <cstddef>
#include <cstdint>
#include <system_error>
#include "evmc.h"
#include "ripemd160.h"
#include "util2.h"

using bytes = std::basic_string<uint8_t>;
using bytes_view = std::basic_string_view<uint8_t>;


namespace evm_utils{


template <typename T>
T from_hex(const char*) noexcept;

constexpr int from_hex(char c) noexcept
{
    return (c >= 'a' && c <= 'f') ? c - ('a' - 10) :
           (c >= 'A' && c <= 'F') ? c - ('A' - 10) :
                                    c - '0';
}

constexpr uint8_t byte(const char* s, size_t i) noexcept
{
    return static_cast<uint8_t>((from_hex(s[2 * i]) << 4) | from_hex(s[2 * i + 1]));
}



template <>
constexpr address from_hex<address>(const char* s) noexcept
{
    return {
        {{byte(s, 0),  byte(s, 1),  byte(s, 2),  byte(s, 3),  byte(s, 4),  byte(s, 5),  byte(s, 6),
          byte(s, 7),  byte(s, 8),  byte(s, 9),  byte(s, 10), byte(s, 11), byte(s, 12), byte(s, 13),
          byte(s, 14), byte(s, 15), byte(s, 16), byte(s, 17), byte(s, 18), byte(s, 19)}}};
}


enum class hex_errc
{
    /// Invalid hex digit encountered during decoding.
    invalid_hex_digit = 1,

    /// Input contains incomplete hex byte (length is odd).
    incomplete_hex_byte_pair = 2,
};
struct hex_error : std::system_error
{
    using system_error::system_error;
};

class NotUse:public std::error_category{
    public:
    std::basic_string<char> message(int a) const override{
        return std::basic_string<char>();
    }
    const char*
    name() const noexcept override{
        static const char * n="not";
        return n;
    }

    
};


inline const std::error_category& hex_category() {
    static NotUse v;
    return v;
}

/// Creates error_code object out of a hex error code value.
static std::error_code make_error_code(hex_errc errc) noexcept
{
    return {static_cast<int>(errc), hex_category()};
}

static  int from_hex_digit(char h)
{
    if (h >= '0' && h <= '9')
        return h - '0';
    else if (h >= 'a' && h <= 'f')
        return h - 'a' + 10;
    else if (h >= 'A' && h <= 'F')
        return h - 'A' + 10;
    else
        throw hex_error{make_error_code(hex_errc::invalid_hex_digit)};
}




template <typename OutputIt>
inline void from_hex(std::string_view hex, OutputIt result)
{
    // TODO: This can be implemented with hex_decode_iterator and std::copy.

    // Omit the optional 0x prefix.
    const auto hex_begin =
        (hex.size() >= 2 && hex[0] == '0' && hex[1] == 'x') ? hex.begin() + 2 : hex.begin();

    constexpr int empty_byte_mark = -1;
    int b = empty_byte_mark;
    for (auto it = hex_begin; it != hex.end(); ++it)
    {
        const auto h = *it;
        if (std::isspace(h))
            continue;

        const int v = from_hex_digit(h);
        if (b == empty_byte_mark)
        {
            b = v << 4;
        }
        else
        {
            *result++ = static_cast<uint8_t>(b | v);
            b = empty_byte_mark;
        }
    }

    if (b != empty_byte_mark)
        throw hex_error{make_error_code(hex_errc::incomplete_hex_byte_pair)};
}


static std::string hex(uint8_t b) noexcept
{
    static constexpr auto hex_chars = "0123456789abcdef";
    return {hex_chars[b >> 4], hex_chars[b & 0xf]};
}

static std::string hex(bytes_view bs)
{
    std::string str;
    str.reserve(bs.size() * 2);
    for (const auto b : bs)
        str += hex(b);
    return str;
}


static bytes from_hex(std::string_view hex)
{
    bytes bs;
    bs.reserve(hex.size() / 2);
    from_hex(hex, std::back_inserter(bs));
    return bs;
}
static std::string GetMd160(std::string key)
{
	unsigned char md160[RIPEMD160_DIGEST_LENGTH];
	bu_Hash160(md160, key.data(),key.size());
	std::string str = hex({md160,20});
	return str;
}

static std::string generateEvmAddr(const std::string& pub)
{
    std::string md160 = GetMd160(pub);
    return md160;
}
}