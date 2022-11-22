#include "kasumi-legacy/platform/platform.h"
#include "kasumi-legacy/util/rand.h"
#include "kasumi-legacy/scene/particles.h"

#include "cloth_api.h"

using namespace HinaPE;

auto main(int argc, char **argv) -> int
{
    // Init Render Engine
    RNG::seed();
    Launch_Settings set;
    Platform platform;
    App app(set, &platform);

    // Register Cloth Engine
    Logging::mute();
    app.register_physics_API(std::make_shared<ClothAPI>());
    platform.loop(app);
    return 0;
}