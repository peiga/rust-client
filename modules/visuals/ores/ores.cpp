#include "ores.hpp"

#include "../../../engine/engine.hpp"
#include "../../../renderer/menu/config/config.hpp"

#include "../../../renderer/renderer.hpp"

void modules::visuals::ores::callback()
{
    std::unique_lock<std::mutex> initiate_thread_locker(engine::values::global_locker);

    const auto camera_copy = engine::values::camera;

    const auto entity_realm_copy = engine::values::entity_realm;

    initiate_thread_locker.unlock();

    if (!camera_copy.instance || !entity_realm_copy.instance)
        return;

    std::unique_lock<std::mutex> update_ores_locker(engine::values::ore_vector_locker);

    const auto ores_copy = engine::values::ores;

    const auto local_player_copy = entity_realm_copy.get_local_player(engine::values::client_entities);

    update_ores_locker.unlock();

    for (auto ore : ores_copy)
    {
        if (!ore.second.instance)
            continue;

        auto ore_world_position = ore.second.get_position(ore.second.mono_object().get_class_object());  auto ore_position = engine::values::camera.world_to_screen(ore_world_position);

        auto draw_list = ImGui::GetBackgroundDrawList();

        if (ore_position.has_value())
        {
            auto ore_screen_position = ore_position.value();

            const float width = std::fabs(ore_screen_position.x - ore_screen_position.y) / 4.0f;
            const float height = std::fabs(ore_screen_position.y - ore_screen_position.x) * 1.2f;

            const auto distance = static_cast<std::int32_t>(local_player_copy.get_player_info().get_base_entity().get_bone_position(engine::structures::bones::root).distance(ore_world_position));

            if (distance > std::get< int >(menu::config::config_map[features::display_ores_max_distance]))
                continue;

            if (std::get< bool >(menu::config::config_map[features::display_ores_stone]) && ore.first == xs("stone"))
            {
                std::string to_draw = ore.first + "\n ["; to_draw.append(std::to_string(distance)); to_draw.append("M]");

                draw_list->AddOutlinedText(renderer::imgui::elements::fonts::bender_font_reg, 10.5f, { ore_screen_position.x, ore_screen_position.y }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::stone_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::stone_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::stone_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::stone_color]).color[3] }, to_draw.c_str());
            }

            if (std::get< bool >(menu::config::config_map[features::display_ores_sulfur]) && ore.first == xs("sulfur"))
            {
                std::string to_draw = ore.first + "\n ["; to_draw.append(std::to_string(distance)); to_draw.append("M]");

                draw_list->AddOutlinedText(renderer::imgui::elements::fonts::bender_font_reg, 10.5f, { ore_screen_position.x, ore_screen_position.y }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::sulfur_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::sulfur_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::sulfur_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::sulfur_color]).color[3] }, to_draw.c_str());
            }

            if (std::get< bool >(menu::config::config_map[features::display_ores_metal]) && ore.first == xs("metal"))
            {
                std::string to_draw = ore.first + "\n ["; to_draw.append(std::to_string(distance)); to_draw.append("M]");

                draw_list->AddOutlinedText(renderer::imgui::elements::fonts::bender_font_reg, 10.5f, { ore_screen_position.x, ore_screen_position.y }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::metal_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::metal_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::metal_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::metal_color]).color[3] }, to_draw.c_str());
            }
        }
    }

    update_ores_locker.lock();
}