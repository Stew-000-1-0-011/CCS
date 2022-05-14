#pragma once
#include <cstdint>
#include <bit>

namespace StewDxEngine
{
    namespace Implement::Color
    {
        // 同じ記述を何回もするのはだるいので継承させることに。最適化は同じくらいかかると信じたい。
        struct Color16Base
        {
            std::uint16_t value_in_u16;
            
            constexpr operator std::uint16_t() const noexcept
            {
                return value_in_u16;
            }

#define stew_DEFINE_OP_ASSIGN(op_assign)\
            constexpr std::uint16_t& operator op_assign(const std::uint16_t x) noexcept\
            {\
                value_in_u16 op_assign x;\
                return value_in_u16;\
            }

            stew_DEFINE_OP_ASSIGN(=)
            stew_DEFINE_OP_ASSIGN(|=)
            stew_DEFINE_OP_ASSIGN(&=)
            stew_DEFINE_OP_ASSIGN(^=)
            stew_DEFINE_OP_ASSIGN(<<=)
            stew_DEFINE_OP_ASSIGN(>>=)

#undef stew_DEFINE_OP_ASSIGN
        };
    }

    enum class Color16Format
    {
        R5G6B5,
    };

    template<Color16Format>
    struct Color16;

    enum class Color32Format
    {
        B8G8R8A8,
    };

    template<Color32Format>
    struct Color32;

    template<>
    struct Color16<Color16Format::R5G6B5> final : Implement::Color::Color16Base
    {
        static constexpr std::uint16_t r_bit = 0b11111'000000'00000;
        static constexpr std::uint16_t r_shift = 11;
        static constexpr std::uint16_t g_bit = 0b00000'111111'00000;
        static constexpr std::uint16_t g_shift = 5;
        static constexpr std::uint16_t b_bit = 0b00000'000000'11111;
        static constexpr std::uint16_t b_shift = 0;
    };

    template<>
    struct Color32<Color32Format::B8G8R8A8> final
    {
        std::uint8_t blue;
        std::uint8_t green;
        std::uint8_t red;
        std::uint8_t alpha;

        constexpr operator std::uint32_t() const noexcept
        {
            return std::bit_cast<std::uint32_t, Color32>(*this);
        }

        constexpr Color32& operator =(const std::uint32_t x) noexcept
        {
            operator =(std::bit_cast<Color32, std::uint32_t>(x));
            return *this;
        }
    };

    template<typename T>
    struct RGB final
    {
        T red;
        T green;
        T blue;
    };
}
