#include "engpch.h"
#include "RenderConfig.h"

namespace eng
{
    static RenderConfig cfg = 
    {
        "Game",
        700,
        600,
        144,
        true
    };

    const RenderConfig& GetRenderConfig()
    {
        return cfg;
    }
}