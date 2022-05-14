#include "DxLibrary/DxLib.h"

namespace StewDxEngine
{
    namespace Implement::Graph
    {
        // 非null
        class GraphHandle final
        {
            int graph_handle;

        public:
            GraphHandle(const int graph_handle) noexcept:
                graph_handle{graph_handle}
            {}

            GraphHandle(const GraphHandle&) = default;
            GraphHandle& operator=(const GraphHandle& obj) = default;

            ~GraphHandle() noexcept
            {
                DxLib::DeleteGraph(graph_handle);
            }

            operator int() const noexcept
            {
                return graph_handle;
            }

            friend bool operator==(const GraphHandle& l, const GraphHandle& r) noexcept
            {
                return l.graph_handle == r.graph_handle;
            }

            friend bool operator!=(const GraphHandle& l, const GraphHandle& r) noexcept
            {
                return l.graph_handle != r.graph_handle;
            }
        };
    }
}