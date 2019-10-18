#pragma once

#include <bitset>

using u8  = unsigned char;
using s8  = char;
using u16 = unsigned short;
using s16 = short;
using u32 = unsigned int;
using s32 = int;
using u64 = unsigned long long;
using s64 = long long;
using f32 = float;
using f64 = double;

using bit_mask_t = std::bitset<32>;

#define BIT(bit) (1 << bit)

