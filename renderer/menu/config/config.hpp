#pragma once

#include <windows.h>
#include <string_view>
#include <unordered_map>

#include <variant>
#include <fstream>

#include "../../../engine/structures/structures.hpp"

enum features : int32_t
{
	aimbot_enable,
	aimbot_smoothness,
	aimbot_bone,
	aimbot_max_distance,
	aimbot_show_fov,
	aimbot_snap_lines,
	aimbot_fov,
	aimbot_fov_segments,
	aimbot_hotkey,

	silent_aimbot_enable,
	silent_aimbot_bone,
	silent_aimbot_max_distance,
	silent_aimbot_show_fov,
	silent_aimbot_snap_lines,
	silent_aimbot_fov,
	silent_aimbot_fov_segments,

	enable_fake_admin,
	fake_admin_hotkey,

	enable_spiderman,
	enable_force_auto,
	enable_instant_eoka,
	enable_long_hand,
	enable_no_recoil,
	enable_no_spread,
	enable_run_on_hit,
	enable_thick_bullet,

	thick_bullet_size,

	recoil_yaw_min,
	recoil_yaw_max,

	recoil_pitch_min,
	recoil_pitch_max,

	display_players_max_distance,
	display_ores_max_distance,

	display_players_visibility_check,
	display_players_ignore_sleepers,

	display_players_ignore_npcs,
	display_players_name,

	display_bounding_box,
	display_filled_box,
	display_corner_box,
	display_players_head_hitbox,
	display_players_chams,
	display_players_skeleton,
	display_players_distance,
	display_players_health,
	display_players_tracers,

	display_ores_stone,
	display_ores_sulfur,
	display_ores_metal,

	display_crosshair,

	player_name_color,

	bounding_box_color,
	filled_box_color,
	corner_box_color,
	hitbox_color,
	skeleton_color,
	distance_color,
	health_color,
	fov_color,
	tracers_color,

	stone_color,
	sulfur_color,
	metal_color,

	crosshair_color
};

namespace menu::config
{
	extern std::variant< bool, int, float, engine::structures::vector4_t > config_map[];
}