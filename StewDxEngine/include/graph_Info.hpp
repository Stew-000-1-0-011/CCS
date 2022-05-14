#include "DxLibrary/DxLib.h"

#include "dxlib_types.hpp"


namespace StewDxEngine
{
    struct GraphInfo
    {
        ColorBitDepth bit_depth{ColorBitDepth::depth32};
        bool is_alpha_multiplied{};

        virtual ~GraphInfo() = default;

        void apply() const noexcept
        {
            /// CPPVERSION: C++23以降は<utility>のto_underlyingを使うのが望ましい。
            DxLib::SetCreateGraphColorBitDepth(static_cast<int>(bit_depth));
            DxLib::SetUsePremulAlphaConvertLoad(is_alpha_multiplied);
        }
    };

    struct ScreenInfo : GraphInfo
    {
        ScreenChannelNum channel_num{ScreenChannelNum::channel4};
        bool is_floating{};
        bool has_alpha{};
        
        virtual ~ScreenInfo() override = default;
    };
}