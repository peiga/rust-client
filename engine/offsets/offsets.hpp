#pragma once

namespace engine::offsets
{
    constexpr auto game_object_manager = 0x17C1F18;
    constexpr auto game_base_networkable = 0x3646888;
}

namespace engine::offsets::client_entities
{
    constexpr auto ent_realm = 0xa0;
}

namespace engine::offsets::object
{
    constexpr auto first_tagged_object = 0x0;
    constexpr auto last_tagged_object = 0x8;

    constexpr auto last_camera_tagged_object = 0x10;
    constexpr auto first_camera_tagged_object = 0x18;

    constexpr auto first_active_object = 0x18;
    constexpr auto last_active_object = 0x10;
}

namespace engine::offsets::base_object
{
    constexpr auto next_base_object = 0x8;
    constexpr auto game_object = 0x10;
}

namespace engine::offsets::game_object
{
    constexpr auto name = 0x54;

    constexpr auto class_object = 0x30;
    constexpr auto prefab_name = 0x60;
}

namespace engine::offsets::ore_object
{
    constexpr auto state = 0x8;
    constexpr auto visual = 0x38;
    constexpr auto position = 0x90;
}

namespace engine::offsets::class_object
{
    constexpr auto name = 0x10;
    constexpr auto transform = 0x8;
    constexpr auto object_reference = 0x18;
}

namespace engine::offsets::object_reference
{
    constexpr auto base_entity = 0x28;
}

namespace engine::offsets::generic_list
{
    constexpr auto elements = 0x20;
    constexpr auto size = 0x10;

    constexpr auto entry = 0x14;

    constexpr auto first_element = 0x20;
}

namespace engine::offsets::skin_component
{
    constexpr auto head = 0x68;
    constexpr auto body = 0x70;
    constexpr auto eyes = 0x78;
}

namespace engine::offsets::camera
{
    constexpr auto view_matrix = 0x2E4;
}

namespace engine::offsets::base_player
{
    constexpr auto __menu_option__climb = 0x240;
    constexpr auto __menu_option__drink = 0x298;
    constexpr auto __menu_option__invite_to_team = 0x2F0;
    constexpr auto __menu_option__menu__assist_player = 0x348;
    constexpr auto __menu_option__menu__loot_player = 0x3A0;
    constexpr auto __menu_option__promote = 0x3F8;
    constexpr auto __menu_option__salt_water = 0x450;
    constexpr auto loot_panel_override = 0x0;
    constexpr auto last_open_sound_play = 0x4A8;
    constexpr auto current_view_mode = 0x4AC;
    constexpr auto selected_view_mode = 0x4B0;
    constexpr auto last_revive_point = 0x4B4;
    constexpr auto last_revive_direction = 0x4C0;
    constexpr auto player_model = 0x4D0;
    constexpr auto frozen = 0x4D8;
    constexpr auto voice_recorder = 0x4E0;
    constexpr auto voice_speaker = 0x4E8;
    constexpr auto input = 0x4F0;
    constexpr auto movement = 0x4F8;
    constexpr auto collision = 0x500;
    constexpr auto empty_state = 0x8;
    constexpr auto _looking_at = 0x508;
    constexpr auto _looking_at_entity = 0x510;
    constexpr auto _looking_at_collider = 0x518;
    constexpr auto _looking_at_point_k___backing_field = 0x520;
    constexpr auto player_model_prefab = 0x0;
    constexpr auto player_collision_prefab = 0x0;
    constexpr auto wake_time = 0x52C;
    constexpr auto needs_clothes_rebuild = 0x530;
    constexpr auto was_sleeping = 0x531;
    constexpr auto woke_up_before = 0x532;
    constexpr auto was_dead = 0x533;
    constexpr auto last_clothes_hash = 0x534;
    constexpr auto visible_player_list = 0x10;
    constexpr auto craft_mode = 0x18;
    constexpr auto __is_wearing_dive_goggles_k___backing_field = 0x538;
    constexpr auto gesture_view_model = 0x540;
    constexpr auto i_nt_er_ac_ti_on__ti_ck__ra_te = 0x0;
    constexpr auto time_since_updated_looking_at = 0x548;
    constexpr auto next_topology_test_time = 0x54C;
    constexpr auto use_press_time = 0x550;
    constexpr auto use_held_time = 0x554;
    constexpr auto looking_at_test = 0x558;
    constexpr auto last_death_time_client = 0x1C;
    constexpr auto drink_range = 0x0;
    constexpr auto drink_movement_speed = 0x0;
    constexpr auto cached_water_drinking_point = 0x560;
    constexpr auto gesture_cancel_string = 0x0;
    constexpr auto gesture_list = 0x570;
    constexpr auto gesture_finished_time = 0x578;
    constexpr auto block_held_input_timer = 0x57C;
    constexpr auto current_gesture = 0x580;
    constexpr auto disabled_held_entity = 0x588;
    constexpr auto next_gesture_menu_open_time = 0x590;
    constexpr auto last_gesture_cancel = 0x594;
    constexpr auto client_last_hello_time = 0x598;
    constexpr auto current_team = 0x5A0;
    constexpr auto max_team_size_toast = 0x20;
    constexpr auto client_team = 0x5A8;
    constexpr auto last_received_team_time = 0x5B0;
    constexpr auto last_presence_team_id = 0x5B8;
    constexpr auto last_presence_team_size = 0x5C0;
    constexpr auto player_group_key = 0x5C8;
    constexpr auto player_group_size_key = 0x5D0;
    constexpr auto cl_active_item = 0x5D8;
    constexpr auto client_current_map_note = 0x5E0;
    constexpr auto client_current_death_note = 0x5E8;
    constexpr auto missions = 0x5F0;
    constexpr auto _active_mission = 0x5F8;
    constexpr auto model_state = 0x600;
    constexpr auto mounted = 0x608;
    constexpr auto next_seat_swap_time = 0x618;
    constexpr auto pet_entity = 0x620;
    constexpr auto last_pet_command_issued_time = 0x628;
    constexpr auto pet_prefab_id = 0x62C;
    constexpr auto pet_id = 0x630;
    constexpr auto pet_wheel_has_been_opened = 0x28;
    constexpr auto cached_building_privilege_time = 0x634;
    constexpr auto cached_building_privilege = 0x638;
    constexpr auto max_projectile_id = 0x640;
    constexpr auto w_il_de_rn_es_s = 0x0;
    constexpr auto m_on_um_en_t = 0x0;
    constexpr auto b_as_e = 0x0;
    constexpr auto f_ly_in_g = 0x0;
    constexpr auto b_oa_ti_ng = 0x0;
    constexpr auto s_wi_mm_in_g = 0x0;
    constexpr auto d_ri_vi_ng = 0x0;
    constexpr auto last_update_time = 0x644;
    constexpr auto cached_threat_level = 0x648;
    constexpr auto server_tick_rate_default = 0x0;
    constexpr auto client_tick_rate_default = 0x0;
    constexpr auto server_tick_rate = 0x64C;
    constexpr auto client_tick_rate = 0x650;
    constexpr auto server_tick_interval = 0x654;
    constexpr auto client_tick_interval = 0x658;
    constexpr auto last_sent_tick_time = 0x65C;
    constexpr auto last_tick_stopwatch = 0x660;
    constexpr auto last_sent_tick = 0x668;
    constexpr auto next_vis_think = 0x670;
    constexpr auto last_time_seen = 0x674;
    constexpr auto debug_prev_visible = 0x678;
    constexpr auto fall_damage_effect = 0x680;
    constexpr auto drown_effect = 0x688;
    constexpr auto player_flags = 0x690;
    constexpr auto eyes = 0x698;
    constexpr auto inventory = 0x6A0;
    constexpr auto blueprints = 0x6A8;
    constexpr auto metabolism = 0x6B0;
    constexpr auto modifiers = 0x6B8;
    constexpr auto player_collider = 0x6C0;
    constexpr auto belt = 0x6C8;
    constexpr auto player_rigidbody = 0x6D0;
    constexpr auto user_id = 0x6D8;
    constexpr auto user_id_string = 0x6E0;
    constexpr auto gamemodeteam = 0x6E8;
    constexpr auto reputation = 0x6EC;
    constexpr auto _display_name = 0x6F0;
    constexpr auto _last_set_name = 0x6F8;
    constexpr auto crouch_speed = 0x0;
    constexpr auto walk_speed = 0x0;
    constexpr auto run_speed = 0x0;
    constexpr auto crawl_speed = 0x0;
    constexpr auto player_collider_standing = 0x700;
    constexpr auto player_collider_ducked = 0x714;
    constexpr auto player_collider_crawling = 0x728;
    constexpr auto player_collider_lying_down = 0x73C;
    constexpr auto cached_protection = 0x750;
    constexpr auto old_camera_fix = 0x29;
    constexpr auto last_headshot_sound_time = 0x758;
    constexpr auto next_collider_refresh_time = 0x75C;
    constexpr auto clothing_blocks_aiming = 0x760;
    constexpr auto clothing_move_speed_reduction = 0x764;
    constexpr auto clothing_water_speed_bonus = 0x768;
    constexpr auto clothing_accuracy_bonus = 0x76C;
    constexpr auto equipping_blocked = 0x770;
    constexpr auto egg_vision = 0x774;
    constexpr auto active_telephone = 0x778;
    constexpr auto designing_ai_entity = 0x780;
}

namespace engine::offsets::base_entity
{
    constexpr auto ragdoll = 0x78;
    constexpr auto position_lerp = 0x80;
    constexpr auto menu_options = 0x88;
    constexpr auto global_broadcast_queue = 0x0;
    constexpr auto global_broadcast_protocol = 0x8;
    constexpr auto broadcast_protocol = 0x90;
    constexpr auto links = 0x98;
    constexpr auto linked_to_neighbours = 0xA0;
    constexpr auto max_file_requests_per_second = 0x0;
    constexpr auto queued_file_requests = 0x10;
    constexpr auto _file_request_counter = 0x18;
    constexpr auto _flush_queued_file_requests = 0x30;
    constexpr auto _pending_file_requests = 0xA8;
    constexpr auto update_parenting_action = 0xB0;
    constexpr auto added_to_parent_entity = 0xB8;
    constexpr auto item_skin = 0xC0;
    constexpr auto entity_slots = 0xC8;
    constexpr auto triggers = 0xD0;
    constexpr auto is_visible = 0xD8;
    constexpr auto is_animator_visible = 0xD9;
    constexpr auto is_shadow_visible = 0xDA;
    constexpr auto local_occludee = 0xE0;
    constexpr auto __weight_k___backing_field = 0x100;
    constexpr auto bounds = 0x104;
    constexpr auto impact_effect = 0x120;
    constexpr auto enable_saving = 0x128;
    constexpr auto sync_position = 0x129;
    constexpr auto model = 0x130;
    constexpr auto flags = 0x138;
    constexpr auto parent_bone = 0x13C;
    constexpr auto skin_id = 0x140;
    constexpr auto _components = 0x148;
    constexpr auto has_brain = 0x150;
    constexpr auto _name = 0x158;
    constexpr auto __owner_id_k___backing_field = 0x160;
}

namespace engine::offsets::base_combat_entity
{
    constexpr auto __menu_option__menu__pickup = 0x168;
    constexpr auto skeleton_properties = 0x1C0;
    constexpr auto base_protection = 0x1C8;
    constexpr auto start_health = 0x1D0;
    constexpr auto pickup = 0x1D8;
    constexpr auto repair = 0x1F8;
    constexpr auto show_health_info = 0x220;
    constexpr auto lifestate = 0x224;
    constexpr auto sends_hit_notification = 0x228;
    constexpr auto sends_melee_hit_notification = 0x229;
    constexpr auto mark_attacker_hostile = 0x22A;
    constexpr auto _health = 0x22C;
    constexpr auto _max_health = 0x230;
    constexpr auto faction = 0x234;
    constexpr auto death_time = 0x238;
    constexpr auto last_notify_frame = 0x23C;

    constexpr auto base_projectile = 0xa0; // heldEntity
}

namespace engine::offsets::base_networkable
{
    constexpr auto __just_created_k___backing_field = 0x18;
    constexpr auto entity_destroy = 0x20;
    constexpr auto post_network_update_components = 0x28;
    constexpr auto parent_entity = 0x30;
    constexpr auto children = 0x40;
    constexpr auto can_trigger_parent = 0x48;
    constexpr auto prefab_id = 0x4C;
    constexpr auto global_broadcast = 0x50;
    constexpr auto net = 0x58;
    constexpr auto __is_destroyed_k___backing_field = 0x60;
    constexpr auto _prefab_name = 0x68;
    constexpr auto _prefab_name_without_extension = 0x70;
    constexpr auto client_entities = 0x0;
    constexpr auto is_serverside_entity = 0x0;
}

namespace engine::offsets::base_movement
{
    constexpr auto admin_cheat = 0x18;
    constexpr auto admin_speed = 0x1C;
    constexpr auto __owner_k___backing_field = 0x20;
    constexpr auto __inherited_velocity_k___backing_field = 0x28;
    constexpr auto __target_movement_k___backing_field = 0x34;
    constexpr auto __running_k___backing_field = 0x40;
    constexpr auto __ducking_k___backing_field = 0x44;
    constexpr auto __crawling_k___backing_field = 0x48;
    constexpr auto __grounded_k___backing_field = 0x4C;
    constexpr auto r_ec_en_tl_y__te_le_po_rt_ed__ti_me = 0x0;
    constexpr auto last_teleported_time = 0x50;
}

namespace engine::offsets::projectile
{
    constexpr auto move_delta_time = 0x0;
    constexpr auto life_time = 0x0;
    constexpr auto initial_velocity = 0x18;
    constexpr auto drag = 0x24;
    constexpr auto gravity_modifier = 0x28;
    constexpr auto thickness = 0x2C;
    constexpr auto initial_distance = 0x30;
    constexpr auto remain_in_world = 0x34;
    constexpr auto stick_probability = 0x38;
    constexpr auto break_probability = 0x3C;
    constexpr auto condition_loss = 0x40;
    constexpr auto ricochet_chance = 0x44;
    constexpr auto penetration_power = 0x48;
    constexpr auto damage_properties = 0x50;
    constexpr auto damage_distances = 0x58;
    constexpr auto damage_multipliers = 0x60;
    constexpr auto damage_types = 0x68;
    constexpr auto renderer_to_scale = 0x70;
    constexpr auto first_person_renderer = 0x78;
    constexpr auto create_decals = 0x80;
    constexpr auto do_default_hit_effects = 0x81;
    constexpr auto flyby_sound = 0x88;
    constexpr auto flyby_sound_distance = 0x90;
    constexpr auto close_flyby_sound = 0x98;
    constexpr auto close_flyby_distance = 0xA0;
    constexpr auto tumble_speed = 0xA4;
    constexpr auto tumble_axis = 0xA8;
    constexpr auto swim_scale = 0xB4;
    constexpr auto swim_speed = 0xC0;
    constexpr auto owner = 0xD0;
    constexpr auto source_weapon_prefab = 0xD8;
    constexpr auto source_projectile_prefab = 0xE0;
    constexpr auto mod = 0xE8;
    constexpr auto projectile_id = 0xF0;
    constexpr auto seed = 0xF4;
    constexpr auto clientside_effect = 0xF8;
    constexpr auto clientside_attack = 0xF9;
    constexpr auto integrity = 0xFC;
    constexpr auto max_distance = 0x100;
    constexpr auto modifier = 0x104;
    constexpr auto invisible = 0x114;
    constexpr auto current_velocity = 0x118;
    constexpr auto current_position = 0x124;
    constexpr auto traveled_distance = 0x130;
    constexpr auto traveled_time = 0x134;
    constexpr auto launch_time = 0x138;
    constexpr auto sent_position = 0x13C;
    constexpr auto previous_position = 0x148;
    constexpr auto previous_velocity = 0x154;
    constexpr auto previous_traveled_time = 0x160;
    constexpr auto is_ricochet = 0x164;
    constexpr auto is_retiring = 0x165;
    constexpr auto flyby_played = 0x166;
    constexpr auto was_facing_player = 0x167;
    constexpr auto flyby_plane = 0x168;
    constexpr auto flyby_ray = 0x178;
    constexpr auto cleanup_action = 0x190;
    constexpr auto hit_test = 0x198;
    constexpr auto swim_random = 0x1A0;
    constexpr auto _flesh_material_id = 0x0;
    constexpr auto _water_material_id = 0x4;
    constexpr auto cached_water_string = 0x8;
}

namespace engine::offsets::base_projectile
{
    constexpr auto noise_radius = 0x280;
    constexpr auto damage_scale = 0x284;
    constexpr auto distance_scale = 0x288;
    constexpr auto projectile_velocity_scale = 0x28C;
    constexpr auto automatic = 0x290;
    constexpr auto usable_by_turret = 0x291;
    constexpr auto turret_damage_scale = 0x294;
    constexpr auto attack_fx = 0x298;
    constexpr auto silenced_attack = 0x2A0;
    constexpr auto muzzle_brake_attack = 0x2A8;
    constexpr auto muzzle_point = 0x2B0;
    constexpr auto reload_time = 0x2B8;
    constexpr auto can_unload_ammo = 0x2BC;
    constexpr auto primary_magazine = 0x2C0;
    constexpr auto fractional_reload = 0x2C8;
    constexpr auto reload_start_duration = 0x2CC;
    constexpr auto reload_fraction_duration = 0x2D0;
    constexpr auto reload_end_duration = 0x2D4;
    constexpr auto aim_sway = 0x2D8;
    constexpr auto aim_sway_speed = 0x2DC;
    constexpr auto recoil = 0x2E0;
    constexpr auto aimcone_curve = 0x2E8;
    constexpr auto aim_cone = 0x2F0;
    constexpr auto hip_aim_cone = 0x2F4;
    constexpr auto aimcone_penalty_per_shot = 0x2F8;
    constexpr auto aim_cone_penalty_max = 0x2FC;
    constexpr auto aimcone_penalty_recover_time = 0x300;
    constexpr auto aimcone_penalty_recover_delay = 0x304;
    constexpr auto stance_penalty_scale = 0x308;
    constexpr auto has_ad_s = 0x30C;
    constexpr auto no_aiming_while_cycling = 0x30D;
    constexpr auto manual_cycle = 0x30E;
    constexpr auto needs_cycle = 0x30F;
    constexpr auto is_cycling = 0x310;
    constexpr auto aiming = 0x311;
    constexpr auto is_burst_weapon = 0x312;
    constexpr auto can_change_fire_modes = 0x313;
    constexpr auto default_on = 0x314;
    constexpr auto internal_burst_recoil_scale = 0x318;
    constexpr auto internal_burst_fire_rate_scale = 0x31C;
    constexpr auto internal_burst_aim_cone_scale = 0x320;
    constexpr auto toast__burst_disabled = 0x328;
    constexpr auto toast__burst_enabled = 0x330;
    constexpr auto reset_duration = 0x338;
    constexpr auto num_shots_fired = 0x33C;
    constexpr auto next_reload_time = 0x340;
    constexpr auto start_reload_time = 0x344;
    constexpr auto stance_penalty = 0x348;
    constexpr auto aimcone_penalty = 0x34C;
    constexpr auto cached_mod_hash = 0x350;
    constexpr auto sight_aim_cone_scale = 0x354;
    constexpr auto sight_aim_cone_offset = 0x358;
    constexpr auto hip_aim_cone_scale = 0x35C;
    constexpr auto hip_aim_cone_offset = 0x360;
    constexpr auto is_reloading = 0x364;
    constexpr auto sway_sample_time = 0x368;
    constexpr auto last_shot_time = 0x36C;
    constexpr auto reload_press_time = 0x370;
    constexpr auto ammo_type_pre_reload = 0x378;
    constexpr auto fractional_reload_desired_count = 0x380;
    constexpr auto fractional_reload_num_added = 0x384;
    constexpr auto current_burst = 0x388;
    constexpr auto trigger_ready = 0x38C;
    constexpr auto next_height_check_time = 0x390;
    constexpr auto cached_underground = 0x394;
    constexpr auto created_projectiles = 0x398;
}

namespace engine::offsets::recoil_properties
{
    constexpr auto recoil_yaw_min = 0x18;
    constexpr auto recoil_yaw_max = 0x1C;
    constexpr auto recoil_pitch_min = 0x20;
    constexpr auto recoil_pitch_max = 0x24;
    constexpr auto time_to_take_min = 0x28;
    constexpr auto time_to_take_max = 0x2C;
    constexpr auto a_ds_scale = 0x30;
    constexpr auto movement_penalty = 0x34;
    constexpr auto clamp_pitch = 0x38;
    constexpr auto pitch_curve = 0x40;
    constexpr auto yaw_curve = 0x48;
    constexpr auto use_curves = 0x50;
    constexpr auto curves_as_scalar = 0x51;
    constexpr auto shots_until_max = 0x54;
    constexpr auto max_recoil_radius = 0x58;
    constexpr auto override_aimcone_with_curve = 0x5C;
    constexpr auto aimcone_curve_scale = 0x60;
    constexpr auto aimcone_curve = 0x68;
    constexpr auto aimcone_probability_curve = 0x70;
    constexpr auto new_recoil_override = 0x78;
}

namespace engine::offsets::player_inventory
{
    constexpr auto container_main = 0x20;
    constexpr auto container_belt = 0x28;
    constexpr auto container_wear = 0x30;
    constexpr auto crafting = 0x38;
    constexpr auto loot = 0x40;
}

namespace engine::offsets::player_walk_movement
{
    constexpr auto water_level_head = 0x0;
    constexpr auto water_level_neck = 0x0;
    constexpr auto zero_friction_material = 0x58;
    constexpr auto high_friction_material = 0x60;
    constexpr auto capsule_height = 0x68;
    constexpr auto capsule_center = 0x6C;
    constexpr auto capsule_height_ducked = 0x70;
    constexpr auto capsule_center_ducked = 0x74;
    constexpr auto capsule_height_crawling = 0x78;
    constexpr auto capsule_center_crawling = 0x7C;
    constexpr auto gravity_test_radius = 0x80;
    constexpr auto gravity_multiplier = 0x84;
    constexpr auto gravity_multiplier_swimming = 0x88;
    constexpr auto max_angle_walking = 0x8C;
    constexpr auto max_angle_climbing = 0x90;
    constexpr auto max_angle_sliding = 0x94;
    constexpr auto max_step_height = 0x98;
    constexpr auto body = 0xA0;
    constexpr auto initial_col_detection_mode = 0xA8;
    constexpr auto capsule = 0xB0;
    constexpr auto ladder = 0xB8;
    constexpr auto max_velocity = 0xC0;
    constexpr auto ground_angle = 0xC4;
    constexpr auto ground_angle_new = 0xC8;
    constexpr auto ground_time = 0xCC;
    constexpr auto jump_time = 0xD0;
    constexpr auto land_time = 0xD4;
    constexpr auto previous_position = 0xD8;
    constexpr auto previous_velocity = 0xE4;
    constexpr auto previous_inherited_velocity = 0xF0;
    constexpr auto ground_normal = 0xFC;
    constexpr auto ground_normal_new = 0x108;
    constexpr auto ground_velocity = 0x114;
    constexpr auto ground_velocity_new = 0x120;
    constexpr auto next_sprint_time = 0x12C;
    constexpr auto last_sprint_time = 0x130;
    constexpr auto sprint_forced = 0x134;
    constexpr auto attempted_mount_time = 0x138;
    constexpr auto modify = 0x13C;
    constexpr auto grounded = 0x140;
    constexpr auto climbing = 0x141;
    constexpr auto sliding = 0x142;
    constexpr auto swimming = 0x143;
    constexpr auto was_swimming = 0x144;
    constexpr auto jumping = 0x145;
    constexpr auto was_jumping = 0x146;
    constexpr auto falling = 0x147;
    constexpr auto was_falling = 0x148;
    constexpr auto flying = 0x149;
    constexpr auto was_flying = 0x14A;
    constexpr auto forced_duck_delta = 0x14C;
}

namespace engine::offsets::player_input
{
    constexpr auto state = 0x20;
    constexpr auto had_input_buffer = 0x28;
    constexpr auto body_rotation = 0x2C;
    constexpr auto body_angles = 0x3C;
    constexpr auto head_rotation = 0x48;
    constexpr auto head_angles = 0x58;
    constexpr auto recoil_angles = 0x64;
    constexpr auto view_delta = 0x70;
    constexpr auto head_lerp = 0x78;
    constexpr auto mouse_wheel_up = 0x7C;
    constexpr auto mouse_wheel_dn = 0x80;
    constexpr auto autorun = 0x84;
    constexpr auto toggle_duck = 0x85;
    constexpr auto toggle_ads = 0x86;
    constexpr auto last_ads_entity = 0x88;
    constexpr auto pending_mouse_delta = 0x8C;
    constexpr auto offset_angles = 0x98;
    constexpr auto ignored_buttons = 0xA4;
    constexpr auto has_key_focus = 0xA8;
}

namespace engine::offsets::player_model
{
    constexpr auto pm_uplimit = 0x0;
    constexpr auto pm_downlimit = 0x4;
    constexpr auto pm_upspine = 0x8;
    constexpr auto pm_downspine = 0xC;
    constexpr auto pm_lookoffset = 0x10;
    constexpr auto pm_anglesmoothspeed = 0x1C;
    constexpr auto pm_nohold = 0x20;
    constexpr auto pm_ladder = 0x24;
    constexpr auto pm_minweight = 0x28;
    constexpr auto _smooth_aim_weight = 0x18;
    constexpr auto _smooth_velocity = 0x1C;
    constexpr auto _smoothlook_angle = 0x20;
    constexpr auto allow_mounted_head_look = 0x2C;
    constexpr auto smooth_look_dir = 0x30;
    constexpr auto last_safe_look_dir = 0x3C;
    constexpr auto shoulders = 0x48;
    constexpr auto additional_spine_bones = 0x50;
    constexpr auto finished_leg_wearables = 0x30;
    constexpr auto leg_parts = 0x58;
    constexpr auto fake_spine_bones = 0x60;
    constexpr auto extra_lean_back = 0x68;
    constexpr auto draw_state = 0x6C;
    constexpr auto time_in_arms_mode = 0x70;
    constexpr auto speed = 0x38;
    constexpr auto acceleration = 0x3C;
    constexpr auto rotation_yaw = 0x40;
    constexpr auto forward = 0x44;
    constexpr auto right = 0x48;
    constexpr auto up = 0x4C;
    constexpr auto ducked = 0x50;
    constexpr auto grounded = 0x54;
    constexpr auto crawling = 0x58;
    constexpr auto waterlevel = 0x5C;
    constexpr auto attack = 0x60;
    constexpr auto attack_alt = 0x64;
    constexpr auto deploy = 0x68;
    constexpr auto reload = 0x6C;
    constexpr auto throw_weapon = 0x70;
    constexpr auto holster = 0x74;
    constexpr auto aiming = 0x78;
    constexpr auto on_ladder = 0x7C;
    constexpr auto posing = 0x80;
    constexpr auto pose_type = 0x84;
    constexpr auto relax_gun_pose = 0x88;
    constexpr auto vehicle_aim_yaw = 0x8C;
    constexpr auto vehicle_aim_speed = 0x90;
    constexpr auto on_phone = 0x94;
    constexpr auto use_pose_transition = 0x98;
    constexpr auto left_foot_ik = 0x9C;
    constexpr auto right_foot_ik = 0xA0;
    constexpr auto vehicle_steering = 0xA4;
    constexpr auto sit_reaction = 0xA8;
    constexpr auto forward_reaction = 0xAC;
    constexpr auto right_reaction = 0xB0;
    constexpr auto collision = 0x78;
    constexpr auto censorship_cube = 0x80;
    constexpr auto censorship_cube_breasts = 0x88;
    constexpr auto jaw_bone = 0x90;
    constexpr auto neck_bone = 0x98;
    constexpr auto head_bone = 0xA0;
    constexpr auto eye_controller = 0xA8;
    constexpr auto blink_controller = 0xB0;
    constexpr auto spine_bones = 0xB8;
    constexpr auto left_foot_bone = 0xC0;
    constexpr auto right_foot_bone = 0xC8;
    constexpr auto left_hand_prop_bone = 0xD0;
    constexpr auto right_hand_prop_bone = 0xD8;
    constexpr auto right_hand_target = 0xE0;
    constexpr auto left_hand_target_position = 0xEC;
    constexpr auto left_hand_target_rotation = 0xF8;
    constexpr auto right_hand_target_position = 0x108;
    constexpr auto right_hand_target_rotation = 0x114;
    constexpr auto steering_target_degrees = 0x124;
    constexpr auto right_foot_target_position = 0x128;
    constexpr auto right_foot_target_rotation = 0x134;
    constexpr auto left_foot_target_position = 0x144;
    constexpr auto left_foot_target_rotation = 0x150;
    constexpr auto cinematic_animation_controller = 0x160;
    constexpr auto default_avatar = 0x168;
    constexpr auto cinematic_avatar = 0x170;
    constexpr auto default_hold_type = 0x178;
    constexpr auto sleep_gesture = 0x180;
    constexpr auto crawl_to_incapacitated_gesture = 0x188;
    constexpr auto stand_to_incapacitated_gesture = 0x190;
    constexpr auto current_gesture = 0x198;
    constexpr auto male_skin = 0x1A0;
    constexpr auto female_skin = 0x1A8;
    constexpr auto subsurface_profile = 0x1B0;
    constexpr auto voice_volume = 0x1B8;
    constexpr auto skin_color = 0x1BC;
    constexpr auto skin_number = 0x1C0;
    constexpr auto mesh_number = 0x1C4;
    constexpr auto hair_number = 0x1C8;
    constexpr auto skin_type = 0x1CC;
    constexpr auto movement_sounds = 0x1D0;
    constexpr auto show_sash = 0x1D8;
    constexpr auto temp_pose_type = 0x1DC;
    constexpr auto underwear_skin = 0x1E0;
    constexpr auto _override_skin_seed_k___backing_field = 0x1E8;
    constexpr auto __aim_angles_k___backing_field = 0x1F0;
    constexpr auto __look_angles_k___backing_field = 0x200;
    constexpr auto layer_hands = 0x0;
    constexpr auto layer_gestures = 0x0;
    constexpr auto layer_player_gestures_upper_body = 0x0;
    constexpr auto layer_player_gestures_full_body = 0x0;
    constexpr auto layer_reactions = 0x0;
    constexpr auto model_state = 0x210;
    constexpr auto position = 0x218;
    constexpr auto velocity = 0x224;
    constexpr auto speed_override = 0x230;
    constexpr auto new_velocity = 0x23C;
    constexpr auto rotation = 0x248;
    constexpr auto mounted_rotation = 0x258;
    constexpr auto smooth_left_foot_ik = 0x268;
    constexpr auto smooth_right_foot_ik = 0x274;
    constexpr auto draw_shadow_only = 0x280;
    constexpr auto is_incapacitated = 0x281;
    constexpr auto flinch_location = 0x284;
    constexpr auto visible = 0x288;
    constexpr auto name_tag = 0x290;
    constexpr auto animator_needs_warmup = 0x298;
    constexpr auto is_local_player = 0x299;
    constexpr auto aim_sound_def = 0x2A0;
    constexpr auto aim_end_sound_def = 0x2A8;
    constexpr auto in_gesture = 0x2B0;
    constexpr auto current_gesture_config = 0x2B8;
    constexpr auto in_cinematic = 0x2C0;
    constexpr auto default_animator_controller = 0x2C8;
    constexpr auto _multi_mesh = 0x2D0;
    constexpr auto _animator = 0x2D8;
    constexpr auto _lod_group = 0x2E0;
    constexpr auto _current_gesture = 0x2E8;
    constexpr auto hold_type_lock = 0x2F0;
    constexpr auto has_held_entity = 0x2F4;
    constexpr auto was_mounted_right_aim = 0x2F5;
    constexpr auto cached_mask = 0x2F8;
    constexpr auto cached_construction_mask = 0x2FC;
    constexpr auto workshop_held_entity = 0x300;
    constexpr auto was_crawling = 0x308;
    constexpr auto mounted_spine_look_weight = 0x30C;
    constexpr auto mounted_anim_speed = 0x310;
    constexpr auto preserve_bones = 0x314;
    constexpr auto down_limit_override = 0x318;
    constexpr auto __is_npc_k___backing_field = 0x320;
    constexpr auto time_since_reaction_start = 0x324;
    constexpr auto time_since_left_foot_test = 0x328;
    constexpr auto cached_left_foot_pos = 0x32C;
    constexpr auto cached_left_foot_normal = 0x338;
    constexpr auto time_since_right_foot_test = 0x344;
    constexpr auto cached_right_foot_pos = 0x348;
    constexpr auto cached_right_foot_normal = 0x354;
}

namespace engine::offsets::model
{
    constexpr auto collision = 0x18;
    constexpr auto root_bone = 0x20;
    constexpr auto head_bone = 0x28;
    constexpr auto eye_bone = 0x30;
    constexpr auto animator = 0x38;
    constexpr auto skeleton = 0x40;
    constexpr auto bone_transforms = 0x48;
    constexpr auto bone_names = 0x50;
    constexpr auto bone_dict = 0x58;
    constexpr auto skin = 0x60;
    constexpr auto _lod_group = 0x68;
}

namespace engine::offsets::model_state
{
    constexpr auto should_pool = 0x10;
    constexpr auto _disposed = 0x11;
    constexpr auto water_level = 0x14;
    constexpr auto look_dir = 0x18;
    constexpr auto flags = 0x24;
    constexpr auto pose_type = 0x28;
    constexpr auto inherited_velocity = 0x2C;
}

namespace engine::offsets::item_container
{
    constexpr auto flags = 0x10;
    constexpr auto allowed_contents = 0x14;
    constexpr auto only_allowed_items = 0x18;
    constexpr auto available_slots = 0x20;
    constexpr auto capacity = 0x28;
    constexpr auto uid = 0x2C;
    constexpr auto dirty = 0x30;
    constexpr auto item_list = 0x38;
    constexpr auto temperature = 0x40;
    constexpr auto parent = 0x48;
    constexpr auto player_owner = 0x50;
    constexpr auto entity_owner = 0x58;
    constexpr auto is_server = 0x60;
    constexpr auto max_stack_size = 0x64;
}

namespace engine::offsets::flint_strike_weapon
{
    constexpr auto success_fraction = 0x3A0;
    constexpr auto strike_recoil = 0x3A8;
    constexpr auto _did_spark_this_frame = 0x3B0;
    constexpr auto _is_striking = 0x3B1;
    constexpr auto strikes = 0x3B4;
    constexpr auto last_spectator_attack = 0x3B8;
}

namespace engine::offsets::bow_weapon
{
    constexpr auto attack_ready = 0x3A0;
    constexpr auto arrow_back = 0x3A4;
    constexpr auto swap_arrows = 0x3A8;
    constexpr auto was_aiming = 0x3B0;
}

namespace engine::offsets::base_melee
{
    constexpr auto can_throw_as_projectile = 0x280;
    constexpr auto can_ai_hear_it = 0x281;
    constexpr auto only_throw_as_projectile = 0x282;
    constexpr auto damage_properties = 0x288;
    constexpr auto damage_types = 0x290;
    constexpr auto max_distance = 0x298;
    constexpr auto attack_radius = 0x29C;
    constexpr auto is_automatic = 0x2A0;
    constexpr auto block_sprint_on_attack = 0x2A1;
    constexpr auto strike_fx = 0x2A8;
    constexpr auto use_standard_hit_effects = 0x2B0;
    constexpr auto ai_strike_delay = 0x2B4;
    constexpr auto swing_effect = 0x2B8;
    constexpr auto material_strike_fx = 0x2C0;
    constexpr auto heart_stress = 0x2C8;
    constexpr auto gathering = 0x2D0;
    constexpr auto throw_ready = 0x2D8;
}