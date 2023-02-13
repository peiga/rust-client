#include "spiderman.hpp"

#include "../../../engine/engine.hpp"
#include "../../../renderer/menu/config/config.hpp"

void modules::misc::spiderman::callback( )
{
    std::unique_lock<std::mutex> initiate_thread_locker(engine::values::global_locker);

    const auto camera_copy = engine::values::camera;

    const auto entity_realm_copy = engine::values::entity_realm;

    if (!camera_copy.instance || !entity_realm_copy.instance || !engine::values::client_entities)
        return;

    const auto local_player_copy = entity_realm_copy.get_local_player(engine::values::client_entities);

    initiate_thread_locker.unlock();
    if (std::get< bool >(menu::config::config_map[features::enable_spiderman]))
    {
        auto base_movement = driver.read(local_player_copy.instance + engine::offsets::base_player::movement);

        if (base_movement)
        {
            driver.write<float>(base_movement + engine::offsets::player_walk_movement::ground_angle_new, 0.f);
        }
    }
}