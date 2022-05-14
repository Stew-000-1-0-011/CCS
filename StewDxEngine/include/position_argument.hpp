#pragma once

#include <concepts>
#include <utility>

#include <StewLib/Math/vec2d.hpp>

#include "dxlib_types.hpp"

namespace StewDxEngine::Arg
{
    struct LeftUpper
    {
        const StewLib::Math::Vec2D<int> vec;
        
        template<class ... Args>
        constexpr LeftUpper(Args&& ... args) noexcept:
            vec{std::forward<Args>(args) ...}
        {}
        
        const auto& get_left_upper(const Vec2D<int>&) const
        {
            return vec;
        }

        const auto get_center(const Vec2D<int>& size) const
        {
            return vec + size / 2;
        }
    };

    struct Center
    {
        const StewLib::Math::Vec2D<int> vec;

        template<class ... Args>
        constexpr Center(Args&& ... args) noexcept :
            vec{ std::forward<Args>(args) ... }
        {}

        const auto get_left_upper(const Vec2D<int>& size) const
        {
            return vec - size / 2;
        }

        const auto& get_center(const Vec2D<int>&) const
        {
            return vec;
        }
    };

    template<class T>
    concept PositionArgmentC = std::same_as<T, LeftUpper> || std::same_as<T, Center>;
}