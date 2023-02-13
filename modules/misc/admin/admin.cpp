#include "admin.hpp"

#include "../../../engine/engine.hpp"
#include "../../../renderer/menu/config/config.hpp"

bool toggled = false;

void modules::misc::admin::callback()
{
    std::unique_lock<std::mutex> initiate_thread_locker(engine::values::global_locker);

    const auto camera_copy = engine::values::camera;

    const auto entity_realm_copy = engine::values::entity_realm;

    if (!camera_copy.instance || !entity_realm_copy.instance || !engine::values::client_entities)
        return;

    const auto local_player_copy = entity_realm_copy.get_local_player(engine::values::client_entities);

    initiate_thread_locker.unlock();

    if (std::get< bool >(menu::config::config_map[features::enable_fake_admin]))
    {    
        if (GetAsyncKeyState(std::get< int >(menu::config::config_map[features::fake_admin_hotkey])) & 1)
            toggled = !toggled;

        if (toggled)
        {
            local_player_copy.get_player_flags().give_flag(local_player_copy.instance, engine::structures::player_flags::isadmin);
        }
        else
            local_player_copy.get_player_flags().remove_flag(local_player_copy.instance, engine::structures::player_flags::isadmin);
    }
    else
        local_player_copy.get_player_flags().remove_flag(local_player_copy.instance, engine::structures::player_flags::isadmin);
}