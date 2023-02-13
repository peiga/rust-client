#include "visuals.hpp"

#include "../../engine/engine.hpp"
#include "../../renderer/menu/config/config.hpp"

#include "../../renderer/renderer.hpp"

void modules::visuals::callback()
{
    std::unique_lock<std::mutex> initiate_thread_locker(engine::values::global_locker);

    const auto camera_copy = engine::values::camera;

    const auto entity_realm_copy = engine::values::entity_realm;

    initiate_thread_locker.unlock();

    if (!camera_copy.instance || !entity_realm_copy.instance)
        return;

    std::unique_lock<std::mutex> update_players_locker(engine::values::player_vector_locker);

    const auto players_copy = engine::values::players;

    const auto local_player_copy = entity_realm_copy.get_local_player(engine::values::client_entities);

    update_players_locker.unlock();

    for (auto player : players_copy)
    {
        if (!player.instance)
            continue;

        auto root_world_position = player.get_player_info().get_base_entity().get_bone_position( engine::structures::root ); auto root_postion = camera_copy.world_to_screen(root_world_position);

        auto head_world_position = player.get_player_info().get_base_entity().get_bone_position( engine::structures::head ); auto head_position = camera_copy.world_to_screen(head_world_position);

        auto eye_world_position = player.get_player_info().get_base_entity().get_bone_position(engine::structures::eyes); auto eye_position = camera_copy.world_to_screen(eye_world_position);

        auto draw_list = ImGui::GetBackgroundDrawList();

        if (root_postion.has_value() && head_position.has_value() && eye_position.has_value())
        {
            auto root_screen_position = root_postion.value();
            auto head_screen_position = head_position.value();

            auto eye_screen_position = eye_position.value();

            const float width = std::fabs(head_screen_position.y - root_screen_position.y) / 4.0f;
            const float height = std::fabs(head_screen_position.y - root_screen_position.y) * 1.2f;

            const auto line_len_width = width / 2.5f;

            auto [current_health, max_health] = player.get_player_info().get_base_entity().get_health();

            if (current_health <= 0)
                continue;

            const auto distance = static_cast<std::int32_t>(engine::values::local_player.get_player_info().get_base_entity().get_bone_position(engine::structures::bones::root).distance(root_world_position));

            if (distance > std::get< int >(menu::config::config_map[features::display_players_max_distance]))
                continue;

            const auto new_width_health = (width) / max_health * current_health;
            const auto new_height_health = (height) / max_health * current_health;

            if (std::get< bool >(menu::config::config_map[features::display_players_visibility_check]))       
                if (!player.get_player_model().is_visible())
                    continue;

            if(std::get< bool >(menu::config::config_map[features::display_players_ignore_sleepers]))
                if (player.get_player_flags().check_flag(engine::structures::player_flags::sleeping))
                    continue;

            if (std::get< bool >(menu::config::config_map[features::display_players_ignore_npcs]) && player.get_class_name(32).find(xs("NPC")))
                continue;
            
            if (std::get< bool >(menu::config::config_map[features::display_players_name]))
            {
                const auto player_name = player.get_player_name();

                const auto text_width = ImGui::CalcTextSize(player_name.c_str()).x;

                {
                    draw_list->AddOutlinedText(renderer::imgui::elements::fonts::bender_font_reg, 10.5f, { (root_screen_position.x - (width / 2) - (text_width / 2)), root_screen_position.y - height - 15.f }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::player_name_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::player_name_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::player_name_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::player_name_color]).color[3] }, player_name.c_str());
                }
            }

            if (std::get< bool >(menu::config::config_map[features::display_bounding_box]))
            {
                const auto col = std::get< engine::structures::vector4_t >(menu::config::config_map[features::bounding_box_color]);

                {
                    draw_list->AddRect({ root_screen_position.x - width, root_screen_position.y }, { root_screen_position.x + width, root_screen_position.y - height }, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] }, 0, 0, 1.8f);
                }
            }

            if (std::get< bool >(menu::config::config_map[features::display_filled_box]))
            {
                {
                    draw_list->AddRectFilled({ root_screen_position.x - width, root_screen_position.y }, { root_screen_position.x + width, root_screen_position.y - height }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::filled_box_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::filled_box_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::filled_box_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::filled_box_color]).color[3] });
                }
            }

            if (std::get< bool >(menu::config::config_map[features::display_corner_box]) && !std::get< bool >(menu::config::config_map[features::display_bounding_box]))
            {
                const auto col = std::get< engine::structures::vector4_t >(menu::config::config_map[features::corner_box_color]);

                {
                    draw_list->AddLine({ root_screen_position.x - width, root_screen_position.y - height }, { root_screen_position.x - width + line_len_width, root_screen_position.y - height }, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] }, 1.8f);
                    draw_list->AddLine({ root_screen_position.x - width, root_screen_position.y - height }, { root_screen_position.x - width, (root_screen_position.y - height) + line_len_width }, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] }, 1.8f);

                    draw_list->AddLine({ root_screen_position.x + width, root_screen_position.y - height }, { root_screen_position.x + width - line_len_width, root_screen_position.y - height }, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] }, 1.8f);
                    draw_list->AddLine({ root_screen_position.x + width, root_screen_position.y - height }, { root_screen_position.x + width, (root_screen_position.y - height) + line_len_width }, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] }, 1.8f);

                    draw_list->AddLine({ root_screen_position.x - width, root_screen_position.y }, { root_screen_position.x - width + line_len_width, root_screen_position.y }, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] }, 1.8f);
                    draw_list->AddLine({ root_screen_position.x - width, root_screen_position.y }, { root_screen_position.x - width, root_screen_position.y - line_len_width }, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] }, 1.8f);

                    draw_list->AddLine({ root_screen_position.x + width, root_screen_position.y }, { root_screen_position.x + width - line_len_width, root_screen_position.y }, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] }, 1.8f);
                    draw_list->AddLine({ root_screen_position.x + width, root_screen_position.y }, { root_screen_position.x + width, root_screen_position.y - line_len_width }, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] }, 1.8f);
                }
            }

            if (std::get< bool >(menu::config::config_map[features::display_players_head_hitbox]))
            {
                const auto col = std::get< engine::structures::vector4_t >(menu::config::config_map[features::hitbox_color]);

                {
                    draw_list->AddCircle({ head_screen_position.x, head_screen_position.y }, 5.f, ImColor{ col.color[0], col.color[1], col.color[2], col.color[3] });
                }
            }

            if (std::get< bool >(menu::config::config_map[features::display_players_chams]))
            {
                {
                    player.get_player_model().null_material();
                }
            }

            if (std::get< bool >(menu::config::config_map[features::display_players_skeleton]) && distance <= 100)
            {
                engine::types::transform_t bones[67];

                player.get_player_info().get_base_entity().get_parent().get_bone_transforms(bones);

                const auto r_finger_pos = bones[engine::structures::bones::r_finger].get_position(); const auto r_finger_spos = camera_copy.world_to_screen(r_finger_pos);
                const auto l_finger_pos = bones[engine::structures::bones::l_finger].get_position(); const auto l_finger_spos = camera_copy.world_to_screen(l_finger_pos);

                const auto r_hand_pos = bones[engine::structures::bones::r_hand].get_position(); const auto r_hand_spos = camera_copy.world_to_screen(r_hand_pos);
                const auto l_hand_pos = bones[engine::structures::bones::l_hand].get_position(); const auto l_hand_spos = camera_copy.world_to_screen(l_hand_pos);

                const auto r_forearm_pos = bones[engine::structures::bones::r_forearm].get_position(); const auto r_forearm_spos = camera_copy.world_to_screen(r_forearm_pos);
                const auto l_forearm_pos = bones[engine::structures::bones::l_forearm].get_position(); const auto l_forearm_spos = camera_copy.world_to_screen(l_forearm_pos);

                const auto r_upperarm_pos = bones[engine::structures::bones::r_upperarm].get_position(); const auto r_upperarm_spos = camera_copy.world_to_screen(r_upperarm_pos);
                const auto l_upperarm_pos = bones[engine::structures::bones::l_upperarm].get_position(); const auto l_upperarm_spos = camera_copy.world_to_screen(l_upperarm_pos);

                const auto spine3_pos = bones[engine::structures::bones::spine3].get_position(); const auto spine3_spos = camera_copy.world_to_screen(spine3_pos);
                const auto spine1_pos = bones[engine::structures::bones::spine1].get_position(); const auto spine1_spos = camera_copy.world_to_screen(spine1_pos);

                const auto neck_pos = bones[engine::structures::bones::neck].get_position(); const auto neck_spos = camera_copy.world_to_screen(neck_pos);

                const auto pelvis_pos = bones[engine::structures::bones::pelvis].get_position(); const auto pelvis_spos = camera_copy.world_to_screen(pelvis_pos);

                const auto r_hip_pos = bones[engine::structures::bones::r_hip].get_position(); const auto r_hip_spos = camera_copy.world_to_screen(r_hip_pos);
                const auto l_hip_pos = bones[engine::structures::bones::l_hip].get_position(); const auto l_hip_spos = camera_copy.world_to_screen(l_hip_pos);

                const auto r_knee_pos = bones[engine::structures::bones::r_knee].get_position(); const auto r_knee_spos = camera_copy.world_to_screen(r_knee_pos);
                const auto l_knee_pos = bones[engine::structures::bones::l_knee].get_position(); const auto l_knee_spos = camera_copy.world_to_screen(l_knee_pos);

                const auto r_foot_pos = bones[engine::structures::bones::r_foot].get_position(); const auto r_foot_spos = camera_copy.world_to_screen(r_foot_pos);
                const auto l_foot_pos = bones[engine::structures::bones::l_foot].get_position(); const auto l_foot_spos = camera_copy.world_to_screen(l_foot_pos);

                const auto r_toe_pos = bones[engine::structures::bones::r_toe].get_position(); const auto r_toe_spos = camera_copy.world_to_screen(r_toe_pos);
                const auto l_toe_pos = bones[engine::structures::bones::l_toe].get_position(); const auto l_toe_spos = camera_copy.world_to_screen(l_toe_pos);

                const auto color = ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::skeleton_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::skeleton_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::skeleton_color]).color[2] };

                if (
                    r_finger_spos.has_value() && l_finger_spos.has_value() &&
                    r_hand_spos.has_value() && l_hand_spos.has_value() &&
                    r_forearm_spos.has_value() && l_forearm_spos.has_value() &&
                    r_upperarm_spos.has_value() && l_upperarm_spos.has_value() &&
                    spine3_spos.has_value() && spine1_spos.has_value() &&
                    neck_spos.has_value() && pelvis_spos.has_value() &&
                    r_hip_spos.has_value() && l_hip_spos.has_value() &&
                    r_knee_spos.has_value() && l_knee_spos.has_value() &&
                    r_foot_spos.has_value() && l_foot_spos.has_value() &&
                    r_toe_spos.has_value() && l_toe_spos.has_value()
                    )
                {
                    draw_list->AddLine({ r_finger_spos.value().x, r_finger_spos.value().y }, { r_hand_spos.value().x, r_hand_spos.value().y }, color);
                    draw_list->AddLine({ l_finger_spos.value().x, l_finger_spos.value().y }, { l_hand_spos.value().x, l_hand_spos.value().y }, color);

                    draw_list->AddLine({ r_hand_spos.value().x, r_hand_spos.value().y }, { r_forearm_spos.value().x, r_forearm_spos.value().y }, color);
                    draw_list->AddLine({ l_hand_spos.value().x, l_hand_spos.value().y }, { l_forearm_spos.value().x, l_forearm_spos.value().y }, color);

                    draw_list->AddLine({ r_forearm_spos.value().x, r_forearm_spos.value().y }, { r_upperarm_spos.value().x, r_upperarm_spos.value().y }, color);
                    draw_list->AddLine({ l_forearm_spos.value().x, l_forearm_spos.value().y }, { l_upperarm_spos.value().x, l_upperarm_spos.value().y }, color);

                    draw_list->AddLine({ r_upperarm_spos.value().x, r_upperarm_spos.value().y }, { spine3_spos.value().x, spine3_spos.value().y }, color);
                    draw_list->AddLine({ l_upperarm_spos.value().x, l_upperarm_spos.value().y }, { spine3_spos.value().x, spine3_spos.value().y }, color);

                    draw_list->AddLine({ spine3_spos.value().x, spine3_spos.value().y }, { spine1_spos.value().x, spine1_spos.value().y }, color);

                    draw_list->AddLine({ spine1_spos.value().x, spine1_spos.value().y }, { r_hip_spos.value().x, r_hip_spos.value().y }, color);
                    draw_list->AddLine({ spine1_spos.value().x, spine1_spos.value().y }, { l_hip_spos.value().x, l_hip_spos.value().y }, color);

                    draw_list->AddLine({ spine1_spos.value().x, spine1_spos.value().y }, { pelvis_spos.value().x, pelvis_spos.value().y }, color);

                    draw_list->AddLine({ r_hip_spos.value().x, r_hip_spos.value().y }, { r_knee_spos.value().x, r_knee_spos.value().y }, color);
                    draw_list->AddLine({ l_hip_spos.value().x, l_hip_spos.value().y }, { l_knee_spos.value().x, l_knee_spos.value().y }, color);

                    draw_list->AddLine({ r_knee_spos.value().x, r_knee_spos.value().y }, { r_foot_spos.value().x, r_foot_spos.value().y }, color);
                    draw_list->AddLine({ l_knee_spos.value().x, l_knee_spos.value().y }, { l_foot_spos.value().x, l_foot_spos.value().y }, color);

                    draw_list->AddLine({ r_foot_spos.value().x, r_foot_spos.value().y }, { r_toe_spos.value().x, r_toe_spos.value().y }, color);
                    draw_list->AddLine({ l_foot_spos.value().x, l_foot_spos.value().y }, { l_toe_spos.value().x, l_toe_spos.value().y }, color);
                }
            }

            if (std::get< bool >(menu::config::config_map[features::display_players_distance]))
            {
                std::string to_draw; to_draw.append(std::to_string(distance)); to_draw.append("M");

                {
                    draw_list->AddOutlinedText(renderer::imgui::elements::fonts::bender_font_reg, 10.5f, { root_screen_position.x + width + 5.f, root_screen_position.y - height + 7.f }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::distance_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::distance_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::distance_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::distance_color]).color[3] }, to_draw.c_str());
                }
            }

            if (std::get< bool >(menu::config::config_map[features::display_players_health]))
            {
                std::string to_draw = "["; to_draw.append(std::to_string(static_cast<int>(current_health))); to_draw.append("] HP");

                const auto col = std::get< engine::structures::vector4_t >(menu::config::config_map[features::health_color]);

                {
                    draw_list->AddRectFilled({ root_screen_position.x - width - (width / 10.f) / 4.0f - 5, root_screen_position.y - 2 }, { root_screen_position.x - width - (width / 10.f) - 7, root_screen_position.y - new_height_health }, ImColor{ (255.f - 2.55f * current_health) / 255.0f, (2.55f * current_health) / 255.0f, 0.f });
                }

                {
                    draw_list->AddRectFilled({ root_screen_position.x - width - (width / 10.f) / 4.0f - 5, root_screen_position.y - 2 }, { root_screen_position.x - width - (width / 10.f) - 7, root_screen_position.y - height - 1 }, ImColor{ 0.f, 0.f, 0.f, 0.2f });
                }

                draw_list->AddOutlinedText(renderer::imgui::elements::fonts::bender_font_reg, 10.5f, { (root_screen_position.x - width - (width / 10.f) / 4.5f - 5 - 1) - 35.5f, root_screen_position.y - new_height_health }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::health_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::health_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::health_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::health_color]).color[3] }, to_draw.c_str());
            }
        }
    }

    update_players_locker.lock();
}