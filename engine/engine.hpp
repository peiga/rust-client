#pragma once

#include <mutex>

#include "types/types.hpp"
#include "offsets/offsets.hpp"
#include "../settings/settings.hpp"

namespace engine::values
{
    extern std::uintptr_t unity_player;
    extern std::uintptr_t game_assembly;

    extern std::uintptr_t client_entities;

    extern types::realm_t entity_realm;

    extern types::game_object_manager_t game_object_manager;
    extern types::base_networkable_t base_networkable;
    extern types::camera_t camera;

    extern types::player_t local_player;

    extern std::mutex global_locker;
    extern std::mutex player_vector_locker;

    extern std::mutex ore_vector_locker;

    extern std::vector< types::player_t > players;

    extern std::vector< std::pair< std::string, types::ore_t > > ores;
}

namespace engine::functions
{
    void initiate();

    void update_players_vector(); void update_ores_vector();
}