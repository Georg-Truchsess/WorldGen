

#include<cstdint>
#include<string_view>





  // 64 bit hashing function
    constexpr uint64_t FNV1A::hash64(std::string_view str) noexcept
    {
        uint64_t Hash = 0xcbf29ce484222325;

        for (char c : str)
        {
            Hash ^= static_cast<uint8_t>(c);
            Hash *= 0x100000001b3;
        }

        return Hash;
    }


