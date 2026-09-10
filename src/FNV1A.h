#pragma once

#include<cstdint>
#include<string_view>


struct FNV1A
{
    static constexpr uint64_t hash64(std::string_view str) noexcept;

};