#include "menu.hpp"

#include <array>
#include <functional>

#include "../renderer.hpp"

#include "../../engine/engine.hpp"

#include "../../dependencies/rawdata/person.hpp"
#include "../../dependencies/rawdata/skeleton.hpp"
#include "../../dependencies/libs/imgui_tricks.hpp"

#include "../../modules/visuals/visuals.hpp"
#include "../../modules/visuals/ores/ores.hpp"

#include "../../dependencies/xorstring/xorstring.hpp"

#include "config/config.hpp"

static auto current_tab = 0;

void Draw_Crosshair()
{
    if (std::get< bool >(menu::config::config_map[features::display_crosshair])) 
    {
        {      
            auto draw_list = ImGui::GetBackgroundDrawList();

            const float w = GetSystemMetrics(SM_CXSCREEN) / 2, h = GetSystemMetrics(SM_CYSCREEN) / 2;

            draw_list->AddLine({ w - 13.f, h }, { w - 5.f, h }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[3] }, 1.f);
            draw_list->AddLine({ w, h - 13.f }, { w, h - 5.f }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[3] }, 1.f);
            draw_list->AddLine({ w + 13.f, h }, { w + 5.f, h }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[3] }, 1.f);
            draw_list->AddLine({ w, h + 13.f }, { w, h + 5.f }, ImColor{ std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[0], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[1], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[2], std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color[3] }, 1.f);
        }
    }
}

void Draw_Main()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0,0 });

    ImGui::SetCursorPos({ 24, 235 });
    ImGui::BeginChild(xs("Main"), { 337, 530 }, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
    {
        switch (current_tab)
        {
        case 0:
            renderer::imgui::elements::functions::checkbox(xs("Force Auto"), xs("makes every weapon automatic"), std::get< bool >(menu::config::config_map[features::enable_force_auto]));

            renderer::imgui::elements::functions::checkbox(xs("Instant Eoka"), xs("removes delay of the eoka strike"), std::get< bool >(menu::config::config_map[features::enable_instant_eoka]));

            renderer::imgui::elements::functions::checkbox(xs("No Recoil"), xs("removes recoil from the weapon equipped"), std::get< bool >(menu::config::config_map[features::enable_no_recoil]));

            if (std::get< bool >(menu::config::config_map[features::enable_no_recoil]))
            {
                renderer::imgui::elements::functions::information(xs("Recoil Yaw Minimum"), xs("sets the minimum yaw value"), std::get< float >(menu::config::config_map[features::recoil_yaw_min]), "%.3f");
                renderer::imgui::elements::functions::slider_float("##3", &std::get< float >(menu::config::config_map[features::recoil_yaw_min]), 0, 10.f, "%.3f", 0.01f);

                renderer::imgui::elements::functions::information(xs("Recoil Yaw Max"), xs("sets the maximum yaw value"), std::get< float >(menu::config::config_map[features::recoil_yaw_max]), "%.3f");
                renderer::imgui::elements::functions::slider_float("##4", &std::get< float >(menu::config::config_map[features::recoil_yaw_max]), 0, 10.f, "%.3f", 0.01f);

                renderer::imgui::elements::functions::information(xs("Recoil Pitch Minimum"), xs("sets the minimum pitch value"), std::get< float >(menu::config::config_map[features::recoil_pitch_min]), "%.3f");
                renderer::imgui::elements::functions::slider_float("##7", &std::get< float >(menu::config::config_map[features::recoil_pitch_min]), 0, 10.f, "%.3f", 0.01f);

                renderer::imgui::elements::functions::information(xs("Recoil Pitch Maximum"), xs("sets the maximum pitch value"), std::get< float >(menu::config::config_map[features::recoil_pitch_max]), "%.3f");
                renderer::imgui::elements::functions::slider_float("##8", &std::get< float >(menu::config::config_map[features::recoil_pitch_max]), 0, 10.f, "%.3f", 0.01f);
            }

            renderer::imgui::elements::functions::checkbox(xs("No Spread"), xs("removes spread from the weapon equipped"), std::get< bool >(menu::config::config_map[features::enable_no_spread]));

            renderer::imgui::elements::functions::checkbox(xs("Thick Bullet"), xs("increases size of projectiles"), std::get< bool >(menu::config::config_map[features::enable_thick_bullet]));

            if (std::get< bool >(menu::config::config_map[features::enable_thick_bullet]))
            {
                renderer::imgui::elements::functions::information(xs("Bullet Size"), xs("sets the bullet size"), std::get< float >(menu::config::config_map[features::thick_bullet_size]), "%.3f");
                renderer::imgui::elements::functions::slider_float("##9", &std::get< float >(menu::config::config_map[features::thick_bullet_size]), 0, 1.5f, "%.3f", 0.01f);
            }
            break;
        case 1:
            renderer::imgui::elements::functions::checkbox(xs("Spoof Admin"), xs("debug/admin commands usable in console"), std::get< bool >(menu::config::config_map[features::enable_fake_admin]));

            renderer::imgui::elements::functions::hotkey("##1", &std::get< int >(menu::config::config_map[features::fake_admin_hotkey]));

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Spiderman"), xs("climb walls like spiderman"), std::get< bool >(menu::config::config_map[features::enable_spiderman]));

            renderer::imgui::elements::functions::checkbox(xs("Long Hand"), xs("extends your arm"), std::get< bool >(menu::config::config_map[features::enable_long_hand]));

            renderer::imgui::elements::functions::checkbox(xs("Run on Hit"), xs("melee while running"), std::get< bool >(menu::config::config_map[features::enable_run_on_hit]));
            break;
        case 2:
            renderer::imgui::elements::functions::information(xs("Player Max Distance"), xs("sets the max player visual distance"), std::get< int >(menu::config::config_map[features::display_players_max_distance]), "%i");

            renderer::imgui::elements::functions::slider_int("##1", &std::get< int >(menu::config::config_map[features::display_players_max_distance]), 0, 1000, "%i");

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::information(xs("Ore Max Distance"), xs("sets the max ore visual distance"), std::get< int >(menu::config::config_map[features::display_ores_max_distance]), "%i");

            renderer::imgui::elements::functions::slider_int("##2", &std::get< int >(menu::config::config_map[features::display_ores_max_distance]), 0, 1000, "%i");

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Visibility Check"), xs("ignores visible entities"), std::get< bool >(menu::config::config_map[features::display_players_visibility_check]));

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Ignore Sleepers"), xs("ignores sleeping entities"), std::get< bool >(menu::config::config_map[features::display_players_ignore_sleepers]));

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Ignore NPCs"), xs("ignores npc entities"), std::get< bool >(menu::config::config_map[features::display_players_ignore_npcs]));

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Stone"), xs("draws stone esp"), std::get< bool >(menu::config::config_map[features::display_ores_stone]));

            renderer::imgui::elements::functions::color_picker("##3", std::get< engine::structures::vector4_t >(menu::config::config_map[features::stone_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Sulfur"), xs("draws sulfur esp"), std::get< bool >(menu::config::config_map[features::display_ores_sulfur]));

            renderer::imgui::elements::functions::color_picker("##4", std::get< engine::structures::vector4_t >(menu::config::config_map[features::sulfur_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Metal"), xs("draws metal"), std::get< bool >(menu::config::config_map[features::display_ores_metal]));

            renderer::imgui::elements::functions::color_picker("##5", std::get< engine::structures::vector4_t >(menu::config::config_map[features::metal_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Player Name"), xs("draws player names"), std::get< bool >(menu::config::config_map[features::display_players_name]));

            renderer::imgui::elements::functions::color_picker("##6", std::get< engine::structures::vector4_t >(menu::config::config_map[features::player_name_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Bounding Box"), xs("draws a rectangular box on entities"), std::get< bool >(menu::config::config_map[features::display_bounding_box]));

            renderer::imgui::elements::functions::color_picker("##7", std::get< engine::structures::vector4_t >(menu::config::config_map[features::bounding_box_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Filled Box"), xs("draws a filled rectangular box on entities"), std::get< bool >(menu::config::config_map[features::display_filled_box]));

            renderer::imgui::elements::functions::color_picker("##8", std::get< engine::structures::vector4_t >(menu::config::config_map[features::filled_box_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Corner Box"), xs("draws a cornered box on entities"), std::get< bool >(menu::config::config_map[features::display_corner_box]));

            renderer::imgui::elements::functions::color_picker("##9", std::get< engine::structures::vector4_t >(menu::config::config_map[features::corner_box_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Head Hitbox"), xs("draws a head square on entities"), std::get< bool >(menu::config::config_map[features::display_players_head_hitbox]));

            renderer::imgui::elements::functions::color_picker("##10", std::get< engine::structures::vector4_t >(menu::config::config_map[features::hitbox_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Chams"), xs("brightly colors entities"), std::get< bool >(menu::config::config_map[features::display_players_chams]));

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Skeleton"), xs("expiremental"), std::get< bool >(menu::config::config_map[features::display_players_skeleton]));

            renderer::imgui::elements::functions::color_picker("##11", std::get< engine::structures::vector4_t >(menu::config::config_map[features::skeleton_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Distance"), xs("draws distance of entity"), std::get< bool >(menu::config::config_map[features::display_players_distance]));

            renderer::imgui::elements::functions::color_picker("##12", std::get< engine::structures::vector4_t >(menu::config::config_map[features::distance_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Health"), xs("draws health of entity"), std::get< bool >(menu::config::config_map[features::display_players_health]));

            renderer::imgui::elements::functions::color_picker("##13", std::get< engine::structures::vector4_t >(menu::config::config_map[features::health_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Tracers"), xs("draws a line to entities"), std::get< bool >(menu::config::config_map[features::display_players_tracers]));

            renderer::imgui::elements::functions::color_picker("##14", std::get< engine::structures::vector4_t >(menu::config::config_map[features::tracers_color]).color);
            break;
        case 3:
            renderer::imgui::elements::functions::checkbox(xs("Crosshair"), xs("draws a crosshair, disappears when aimed"), std::get< bool >(menu::config::config_map[features::display_crosshair]));

            renderer::imgui::elements::functions::color_picker("##1", std::get< engine::structures::vector4_t >(menu::config::config_map[features::crosshair_color]).color);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::checkbox(xs("Watermark"), xs("show/hide the watermark"), renderer::values::renderer->is_watermark_shown);

            renderer::imgui::elements::functions::separator();

            renderer::imgui::elements::functions::button(xs("Save Config"), { 328, 35 }, renderer::imgui::elements::button_flags::BUTTON_BLUE);

            ImGui::NewLine();

            renderer::imgui::elements::functions::button(xs("Load Config"), { 328, 35 }, renderer::imgui::elements::button_flags::BUTTON_GRAY);
            break;
        default:
            break;
        }
    }
    ImGui::EndChild();

    ImGui::PopStyleVar();
}

void renderer::menu::draw()
{
    {
        modules::visuals::ores::callback();
        modules::visuals::callback();
    }

    if (renderer::values::renderer->is_menu_open)
    {
        ImGui::SetNextWindowSize({ 375, 770 });

        ImGui::Begin(xs("Rust"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
        {
            auto DrawList = ImGui::GetWindowDrawList();
            auto Position = ImGui::GetWindowPos();

            DrawList->AddText(renderer::imgui::elements::fonts::druk_wide_bold, 30, { Position.x + 24, Position.y + 36 }, ImColor{ 255, 255, 255 }, xs("Rust"));
            DrawList->AddText(renderer::imgui::elements::fonts::druk_wide_bold, 30, { Position.x + 109, Position.y + 36 }, ImColor{ 255, 255, 255 }, xs("LITE"));

            DrawList->AddRectFilled({ Position.x + 24, Position.y + 73 }, { Position.x + 24 + 187, Position.y + 73 + 2 }, ImColor{ 255, 255, 255, 10 });
            DrawList->AddRectFilled({ Position.x + 24, Position.y + 73 }, { Position.x + 24 + 88, Position.y + 73 + 2 }, ImColor{ 138, 194, 227 });

            ImGui::SetCursorPos({ 24, 107 });

            ImGui::BeginGroup();
            {
                renderer::imgui::elements::functions::tab(xs("WEAPON"), (const char*)ICON_FA_RAYGUN, current_tab, 0);

                ImGui::SameLine();

                renderer::imgui::elements::functions::tab(xs("MISC"), (const char*)ICON_FA_FILE_ALT, current_tab, 1);

                ImGui::SameLine();

                renderer::imgui::elements::functions::tab(xs("VISUALS"), (const char*)ICON_FA_EYE, current_tab, 2);

                ImGui::SameLine();

                renderer::imgui::elements::functions::tab(xs("CFG"), (const char*)ICON_FA_ARCHIVE, current_tab, 3);

            }
            ImGui::EndGroup();

            Draw_Main();
        }
        ImGui::End();
    }
    else if (renderer::values::renderer->is_watermark_shown)
    {
        ImGui::Begin(xs("Watermark"), nullptr, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove);
        {
            auto DrawList = ImGui::GetWindowDrawList();

            ImGui::SetWindowSize({ 220, 40 });

            ImGui::SetWindowPos({ 0, 0 });

            DrawList->AddText(renderer::imgui::elements::fonts::druk_wide_bold, 25, { 15, 5 }, ImColor{ 255, 255, 255, 70 }, xs("loaded")); Draw_Crosshair();
        }
        ImGui::End();
    }
}