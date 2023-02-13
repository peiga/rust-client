#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "../offsets/offsets.hpp"
#include "../structures/structures.hpp"

#include "../../driver/driver.hpp"

namespace engine::types
{
	enum class name_hash_t : std::uint64_t
	{
		fps_camera = 0x656D614320535046 // "FPS Came"
	};

	enum prefab_hash_t : std::uint64_t
	{
		stone = 0x175B3386F784DC7E,
		stone_rad = 0x4C82D4E759BBB5EA,
		stone_snow = 0x3C04DD1BF015BBCA,

		sulfur = 0xE864653A5C20727E,
		sulfur_rad = 0xAFDCA4D43760AB24,
		sulfur_snow = 0x710844C3DAB1D9D0,

		metal = 0x201FFFDEB3FEBB80,
		metal_rad = 0x4C232C4D8D7709FC,
		metal_snow = 0x547637F47E621608,
	};

	enum item_types_t : std::uintptr_t
	{
		rifle = 0x6C006600690072,
		smg = 0x2E0067006D0073,
		shotgun = 0x74006F00680073,

		pistol = 0x74007300690070,
		eoka = 0x74007300690070,

		m249 = 0x2E0067006D006C,

		bow = 0x2E0077006F0062,
		compound_bow = 0x73006F00720063,

		knife = 0x660069006E006B,
		bone_club = 0x65006E006F0062,
		mace = 0x6500630061006D,
		machete = 0x6800630061006D,
		paddle = 0x64006400610070,
		pitch_fork = 0x63007400690070,
		salvaged_cleaver_sword = 0x76006C00610073,
		spear = 0x61006500700073,
		long_sword = 0x67006E006F006C,
		hatchet = 0x63007400610068,
		pickaxe = 0x6B006300690070,
		slavaged_axe = 0x2E006500780061,
		salvaged_hammer = 0x6D006D00610068,
		salvaged_icepick = 0x70006500630069,
		stone_hatchet_pickaxe = 0x6E006F00740073
	};

	enum tag_t : std::uint16_t
	{
		player = 6
	};

	struct object_t
	{
		template< class type_t = std::uintptr_t >
		[[nodiscard]] type_t as() const
		{
			return type_t{ instance };
		}

		std::uintptr_t instance;
	};

	struct class_object_t : public object_t
	{
		template< class type_t = std::uintptr_t >
		type_t get_object() const
		{
			return driver.read< type_t >(instance + engine::offsets::class_object::object_reference);
		}
	};

	struct mono_object_t : public object_t
	{
		template< class type_t = std::uintptr_t >
		type_t get_class_object() const
		{
			return driver.read< type_t >(instance + engine::offsets::game_object::class_object);
		}
	};

	struct game_object_t : public object_t
	{
		[[nodiscard]] bool is_hash(name_hash_t name_hash) const
		{
			return name_hash == driver.read< name_hash_t >(instance, { offsets::game_object::name, 0x0 });
		}

		[[nodiscard]] bool is_prefab_hash(prefab_hash_t prefab_hash) const;		

		[[nodiscard]] bool is_tag(tag_t tag) const
		{
			return tag == driver.read< std::uint16_t >(instance + offsets::game_object::name);
		}

		[[nodiscard]] std::string get_class_name(const int size) const;

		template< item_types_t type >
		[[nodiscard]] bool item() const
		{
			if (!instance)
				return false;

			const auto info = driver.read(instance + 0x20);
			const auto display_name = driver.read(info, { 0x20, 0x14 });

			return display_name == type;
		}

		bool operator==(const game_object_t& obj)
		{
			return instance == obj.instance;
		}

		bool operator==(std::uintptr_t comparative)
		{
			return instance == comparative;
		}

		operator bool()
		{
			return instance != 0;
		}

		[[nodiscard]] mono_object_t mono_object() const;

		[[nodiscard]] class_object_t class_object() const;
	};

	struct player_model_t
	{
		[[nodiscard]] bool is_visible() const
		{
			return driver.read< bool >(instance + engine::offsets::player_model::visible);
		};

		[[nodiscard]] void null_material() const;

		std::uintptr_t instance;
	};

	struct base_object_t : public object_t
	{
		[[nodiscard]] game_object_t game_object() const;

		[[nodiscard]] base_object_t next_base_object() const;
	};

	struct transform_t : public object_t
	{
		[[nodiscard]] engine::structures::vector3_t get_position() const;
	};

	struct parent_t : public object_t
	{
		transform_t get_bone_transform(const engine::structures::bones bone) const;

		void get_bone_transforms(transform_t* buff) const;
	};

	struct recoil_properties_t : public game_object_t
	{

	};

	struct base_projectile_t : public game_object_t
	{
		[[nodiscard]] recoil_properties_t get_recoil_properties() const;
	};

	struct held_item_t : public game_object_t
	{
		[[nodiscard]] base_projectile_t get_base_projectile() const;
	};

	struct base_entity_t : public game_object_t
	{
		[[nodiscard]] parent_t get_parent() const;

		[[nodiscard]] std::pair<float, float> get_health();

		[[nodiscard]] held_item_t get_held_item() const;

		[[nodiscard]] engine::structures::vector3_t get_bone_position(const engine::structures::bones bone);
	};

	struct player_info_t : public game_object_t
	{
		[[nodiscard]] base_entity_t get_base_entity() const;
	};

	struct flags_t : public game_object_t
	{
		[[nodiscard]] bool check_flag(engine::structures::player_flags flag) const
		{
			return (instance & static_cast<int32_t>(flag)) == static_cast<int32_t>(flag);
		};

		[[nodiscard]] void give_flag(std::uintptr_t player_instance, engine::structures::player_flags flag)
		{
			driver.write<int32_t>(player_instance + engine::offsets::base_player::player_flags, static_cast<int32_t>(instance) | static_cast<int32_t>(flag));
		}

		[[nodiscard]] void remove_flag(std::uintptr_t player_instance, engine::structures::player_flags flag)
		{
			driver.write<int32_t>(player_instance + engine::offsets::base_player::player_flags, static_cast<int32_t>(instance) & ~static_cast<int32_t>(flag));
		}
	};

	struct player_t : public game_object_t
	{
		[[nodiscard]] player_info_t get_player_info() const;

		[[nodiscard]] player_model_t get_player_model() const;

		[[nodiscard]] flags_t get_player_flags() const;

		[[nodiscard]] std::string get_player_name() const;
	};

	struct ore_t : public game_object_t
	{
		[[nodiscard]] engine::structures::vector3_t get_position(std::uintptr_t object) const;
	};

	struct realm_t : public object_t
	{
		[[nodiscard]] std::vector< player_t > get_players(std::uintptr_t client_entities) const;

		[[nodiscard]] std::vector< std::pair< std::string, ore_t > > get_ores(std::uintptr_t client_entities) const;

		[[nodiscard]] player_t get_local_player(std::uintptr_t client_entities) const;
	};

	struct entities_t : public object_t
	{
		[[nodiscard]] realm_t get_entity_list() const;
	};

	struct base_networkable_t : public object_t
	{
		[[nodiscard]] entities_t get_client_entities() const;
	};

	struct camera_t : public object_t
	{
		union view_matrix_t
		{
			struct
			{
				const float        _11, _12, _13, _14;
				const float        _21, _22, _23, _24;
				const float        _31, _32, _33, _34;
				const float        _41, _42, _43, _44;

			};

			const float m[4][4];
		};

		[[nodiscard]] view_matrix_t get_view_matrix() const;

		[[nodiscard]] std::optional< engine::structures::vector2_t > world_to_screen(const engine::structures::vector3_t& position) const;
	};

	struct game_object_manager_t : public object_t
	{
		[[nodiscard]] object_t last_tagged_object() const;
		[[nodiscard]] object_t first_tagged_object() const;

		[[nodiscard]] object_t last_camera_tagged_object() const;
		[[nodiscard]] object_t first_camera_tagged_object() const;

		[[nodiscard]] object_t last_active_object() const;
		[[nodiscard]] object_t first_active_object() const;

		[[nodiscard]] std::vector< base_object_t > get_tagged_objects() const;
		[[nodiscard]] std::vector< base_object_t > get_camera_objects() const;
		[[nodiscard]] std::vector< base_object_t > get_active_objects() const;

		[[nodiscard]] base_object_t get_tagged_object_by_name(const name_hash_t name) const;
		[[nodiscard]] base_object_t get_camera_object_by_name(const name_hash_t name) const;
		[[nodiscard]] base_object_t get_active_object_by_name(const name_hash_t name) const;
	};
}