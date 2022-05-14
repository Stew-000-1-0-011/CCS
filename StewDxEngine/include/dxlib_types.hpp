#pragma once

#include <cstdint>

#include "Dxlibrary/Dxlib.h"

namespace StewDxEngine
{
    enum class ColorBitDepth : int
    {
        depth16 = 16,
        depth32 = 32
    };

    enum class DrawMode : int
    {
        nearest = DX_DRAWMODE_NEAREST,
        bilinear = DX_DRAWMODE_BILINEAR
    };

    enum class DrawBlendMode : int
    {
        noblend = DX_BLENDMODE_NOBLEND,
        alpha = DX_BLENDMODE_ALPHA,
        add = DX_BLENDMODE_ADD,
        sub = DX_BLENDMODE_SUB,
        mula = DX_BLENDMODE_MULA,
        invsrc = DX_BLENDMODE_INVSRC,
        pmr_alpha = DX_BLENDMODE_PMA_ALPHA,
        pmr_add = DX_BLENDMODE_PMA_ADD,
        pmr_sub = DX_BLENDMODE_PMA_SUB,
        pmr_invsrc = DX_BLENDMODE_PMA_INVSRC
    };

    struct DrawBlendModeArg
    {
        DrawBlendMode mode{DrawBlendMode::noblend};
        std::uint8_t pal{};
    };

    enum class ScreenChannelNum : int
    {
        channel1 = 1,
        channel2 = 2,
        channel4 = 4
    };

    template<class T>
    using Vec2D = StewLib::Math::Vec2D<T>;
}