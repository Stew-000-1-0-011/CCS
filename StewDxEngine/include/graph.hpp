#pragma once

#include <memory>

#include <DxLibrary/DxLib.h>

#include <StewLib/Math/vec2d.hpp>

#include "position_argument.hpp"
#include "color.hpp"
#include "dxlib_types.hpp"
#include "graph_handle.hpp"
#include "graph_info.hpp"

namespace StewDxEngine
{
    class Graph
    {
    protected:
        std::shared_ptr<Implement::Graph::GraphHandle> handle_sp{};
        // covariant型を返す仮想関数よりこちらのほうが最適化されやすく、またcovariantとか知らなくてもわかるのでこっちを使う。
        // 継承先でDerivedGraphInfo * derived_graph_info_dpみたいな変数を作らないこと！Graph::graph_info_dpをキャストして使うように。
        GraphInfo * graph_info_dp{};  // operator =をdefault指定で済ませたいので非constなポインタだが、それ以外では変更しないように。

    public:
        Graph(const TCHAR *const file_name, const GraphInfo& graph_info = GraphInfo()) noexcept:
            graph_info_dp{new GraphInfo(graph_info)}
        {
            graph_info.apply();
            handle_sp = std::make_shared<Implement::Graph::GraphHandle>(DxLib::LoadGraph(file_name));
        }

        Graph(const Vec2D<int> diagonal, const GraphInfo& graph_info = GraphInfo()) noexcept:
            graph_info_dp{new GraphInfo(graph_info)}
        {
            graph_info.apply();
            handle_sp = std::make_shared<Implement::Graph::GraphHandle>(DxLib::MakeGraph(diagonal.x, diagonal.y));
        }

    protected:
        Graph(GraphInfo *const graph_info_dp) noexcept:
            graph_info_dp{graph_info_dp}
        {}

    public:
        Graph() = default;
        Graph(const Graph&) = default;
        Graph(Graph&&) = default;
        Graph& operator =(const Graph&) = default;
        Graph& operator =(Graph&&) = default;
        virtual ~Graph() noexcept
        {
            delete graph_info_dp;
        }

        explicit operator bool() const noexcept
        {
            return static_cast<bool>(handle_sp);
        }

        GraphInfo& getr_graph_info() noexcept  // 非constのが良いだろう
        {
            return *graph_info_dp;
        }

        const GraphInfo& getcr_graph_info() const noexcept
        {
            return *graph_info_dp;
        }

        Vec2D<int> get_size(const Vec2D<double>& extend_rate = {1.0, 1.0}) const noexcept
        {
            Vec2D<int> ret{};
            if(handle_sp)
            {
                DxLib::GetGraphSize(*handle_sp, &ret.x, &ret.y);
            }

            const Vec2D<int> ret2 = {ret.x * extend_rate.x, ret.y * extend_rate.y};

            return ret2;
        }

    private:
        template<Arg::PositionArgmentC Pos>
        struct DrawArgs
        {
            Pos pos;
            Vec2D<double> extend_rate{1.0, 1.0};
            Vec2D<int> rotation_center{};
            double angle{0};
            Vec2D<bool> turn{false, false};
            RGB<int> rgb{255, 255, 255};
            DrawMode draw_mode{DrawMode::nearest};
        };

    public:
        template<Arg::PositionArgmentC Pos>
        void draw(const DrawArgs<Pos>& args) const noexcept
        {
            const auto vec = args.pos.get_left_upper(get_size(args.extend_rate));
            if(handle_sp)
            {
                DxLib::DrawRotaGraph3(
                    vec.x, vec.y,
                    args.rotation_center.x, args.rotation_center.y,
                    args.extend_rate.x, args.extend_rate.y,
                    args.angle, *handle_sp, false,
                    args.turn.x, args.turn.y
                );
            }
        }

    private:
        template <Arg::PositionArgmentC Pos>
        struct DrawModifyArgs
        {
            Pos pos;
            Vec2D<int> axis_x;
            Vec2D<int> axis_y;
            RGB<int> rgb{255, 255, 255};
            DrawMode draw_mode{DrawMode::nearest};
        };

    public:
        template<Arg::PositionArgmentC Pos>
        void draw_modify(const DrawModifyArgs<Pos>& args) noexcept
        {
            const auto& vec = args.pos.get_left_upper();
            const auto right_upper = vec + args.axis_x;
            const auto right_lower = right_upper + args.axis_y;
            const auto left_lower = vec + args.axis_y;

            if(handle_sp)
            {
                DxLib::DrawModiGraph(
                    vec.x, vec.y,
                    right_upper.x, right_upper.y,
                    right_lower.x, right_lower.y,
                    left_lower.x, left_lower.y,
                    *handle_sp, false
                );
            }
        }

        friend bool operator==(const Graph& l, const Graph& r) noexcept
        {
            if(l.handle_sp || r.handle_sp)
            {
                return *l.handle_sp == *r.handle_sp;
            }
            else return false;
        }

        friend bool operator!=(const Graph& l, const Graph& r) noexcept
        {
            if(l.handle_sp || r.handle_sp)
            {
                return *l.handle_sp != *r.handle_sp;
            }
            else return false;
        }
    };

    // 未完成
    class BlendGraph : public Graph
    {
    public:
        BlendGraph(const TCHAR *const filename, const GraphInfo& graph_info = GraphInfo()) noexcept:
            Graph{new GraphInfo(graph_info)}
        {
            graph_info.apply();
            handle_sp = std::make_shared<Implement::Graph::GraphHandle>(DxLib::LoadBlendGraph(filename));
        }

        // MakeBlendGraph相当の関数は存在しなさそうだから。
        BlendGraph(const Vec2D<int> diagonal, const GraphInfo& graph_info = GraphInfo()) noexcept = delete;

    protected:
        BlendGraph(GraphInfo *const graph_info_dp) noexcept:
            Graph{graph_info_dp}
        {}
    
    public:
        BlendGraph() = default;
        BlendGraph(const BlendGraph&) = default;
        BlendGraph(BlendGraph&&) = default;
        BlendGraph& operator =(const BlendGraph&) = default;
        BlendGraph& operator =(BlendGraph&&) = default;
        virtual ~BlendGraph() override = default;
    };

    class Screen : public Graph
    {
        friend class Thumbtack;
    public:
        Screen(const Vec2D<int> diagonal, const ScreenInfo& screen_info = ScreenInfo()) noexcept:
            Graph{new ScreenInfo(screen_info)}
        {
            screen_info.apply();
            handle_sp = std::make_shared<Implement::Graph::GraphHandle>(DxLib::MakeScreen(diagonal.x, diagonal.y, screen_info.has_alpha));
        }

        Screen(const TCHAR *const filename, const ScreenInfo& screen_info = ScreenInfo()) noexcept = delete;

    protected:
        Screen(ScreenInfo *const screen_info_dp) noexcept:
            Graph{screen_info_dp}
        {}

    public:
        Screen() = default;
        Screen(const Screen&) = default;
        Screen(Screen&&) = default;
        Screen& operator =(const Screen&) = default;
        Screen& operator =(Screen&&) = default;
        virtual ~Screen() override = default;
    };

    class Thumbtack final
    {
        Implement::Graph::GraphHandle before_screen;
        Thumbtack(const Screen& screen) noexcept:
            before_screen{DxLib::GetDrawScreen()}
        {
            if(screen.handle_sp)
            {
                DxLib::SetDrawScreen(*screen.handle_sp);
            }
        }

        ~Thumbtack()
        {
            DxLib::SetDrawScreen(before_screen);
        }
    };
}