#include "../../dependencies/fnv1a/fnv1a.hpp"

#include "../../renderer/menu/config/config.hpp"
#include "../engine.hpp"
#include "types.hpp"

#include <mutex>

engine::types::object_t engine::types::game_object_manager_t::last_tagged_object() const
{
	return driver.read< engine::types::object_t >(instance + offsets::object::last_tagged_object);
}

engine::types::object_t engine::types::game_object_manager_t::first_tagged_object() const
{
	return driver.read< engine::types::object_t >(instance + offsets::object::first_tagged_object);
}

engine::types::object_t engine::types::game_object_manager_t::last_camera_tagged_object() const
{
	return driver.read< engine::types::object_t >(instance + offsets::object::last_camera_tagged_object);
}

engine::types::object_t engine::types::game_object_manager_t::first_camera_tagged_object() const
{
	return driver.read< engine::types::object_t >(instance + offsets::object::first_camera_tagged_object);
}

engine::types::object_t engine::types::game_object_manager_t::last_active_object() const
{
	return driver.read< engine::types::object_t >(instance + offsets::object::last_active_object);
}

engine::types::object_t engine::types::game_object_manager_t::first_active_object() const
{
	return driver.read< engine::types::object_t >(instance + offsets::object::first_active_object);
}

engine::types::mono_object_t engine::types::game_object_t::mono_object() const
{
	return driver.read< mono_object_t >(instance, { engine::offsets::base_object::game_object, offsets::game_object::class_object });
}

engine::types::class_object_t engine::types::game_object_t::class_object() const
{
	return driver.read< class_object_t >(instance + offsets::game_object::class_object);
}

engine::types::game_object_t engine::types::base_object_t::game_object() const
{
	return driver.read< game_object_t >(instance + offsets::base_object::game_object);
}

engine::types::base_object_t engine::types::base_object_t::next_base_object() const
{
	return driver.read< base_object_t >(instance + offsets::base_object::next_base_object);
}

engine::types::realm_t engine::types::entities_t::get_entity_list() const
{
	return driver.read< realm_t >(instance + offsets::object::first_active_object);
}

engine::types::entities_t engine::types::base_networkable_t::get_client_entities() const
{
	auto vals = driver.read< uintptr_t>(driver.read< uintptr_t>(instance + offsets::game_base_networkable) + 0xB8); //System_Collections_Generic_List_BaseGameMode__c
	auto entity_realm_client = driver.read< uintptr_t>(vals + 0x20); // BaseEntity_c
	auto client_entities = driver.read< entities_t >(driver.read< uintptr_t>(entity_realm_client + 0x10) + 0x28);

	return client_entities;

	//return driver.read< entities_t >(instance, { offsets::client_entities::ent_realm, offsets::object::last_active_object, offsets::object::last_active_object, offsets::object_reference::base_entity });
}

engine::types::player_model_t engine::types::player_t::get_player_model() const
{
	return driver.read< player_model_t >(instance + offsets::base_player::player_model);
}

engine::types::parent_t engine::types::base_entity_t::get_parent() const
{
	return driver.read< parent_t  >(instance + offsets::base_entity::model);
}

engine::types::base_projectile_t engine::types::held_item_t::get_base_projectile() const
{
	return driver.read< base_projectile_t >(instance + offsets::base_combat_entity::base_projectile);
}

engine::types::recoil_properties_t engine::types::base_projectile_t::get_recoil_properties() const
{
	return driver.read< recoil_properties_t >(instance + offsets::base_projectile::recoil);
}

engine::types::player_info_t engine::types::player_t::get_player_info() const
{
	return driver.read< player_info_t >(instance, { engine::offsets::base_object::game_object, engine::offsets::game_object::class_object });
}

engine::types::base_entity_t engine::types::player_info_t::get_base_entity() const
{
	return driver.read< base_entity_t >(instance, { engine::offsets::game_object::class_object, engine::offsets::class_object::object_reference, engine::offsets::object_reference::base_entity });
}

engine::types::held_item_t engine::types::base_entity_t::get_held_item() const
{
	auto active_weapon_id = driver.read< int >(instance + offsets::base_player::cl_active_item);

	auto items = driver.read(instance, { offsets::base_player::inventory, offsets::player_inventory::container_belt, offsets::item_container::item_list, offsets::object::last_active_object });

	for (int items_on_belt = 0u; items_on_belt <= 6; items_on_belt++)
	{
		auto item = driver.read(items + offsets::generic_list::elements + (items_on_belt * sizeof(void*)));

		auto active_weapon = driver.read< std::uint32_t >(item + offsets::object_reference::base_entity);

		if (active_weapon_id == active_weapon)
			return driver.read< held_item_t >(items + offsets::generic_list::elements + (items_on_belt * sizeof(void*)));
	}

	return driver.read< held_item_t>(0);
}

bool engine::types::game_object_t::is_prefab_hash(prefab_hash_t prefab_hash) const
{
	std::string raw_name = driver.read_raw_bytes(instance, 128);

	return prefab_hash == hash_constfnv64_string(raw_name.c_str());
}

void engine::types::player_model_t::null_material() const
{
	auto skin_type = driver.read(instance + offsets::player_model::skin_type);

	auto skin_component = driver.read(instance + offsets::player_model::male_skin + (static_cast<int>(skin_type) * sizeof(void*)));

	if (!skin_component)
		skin_component = driver.read(instance + offsets::player_model::female_skin + (static_cast<int>(skin_type) * sizeof(void*)));

	auto skin = driver.read(skin_component + offsets::class_object::object_reference);

	for (auto i = 0u; i <= sizeof(skin); ++i)
	{
		auto element = driver.read< std::uintptr_t >(skin + offsets::generic_list::elements + (i * sizeof(void*)));

		driver.write(element + offsets::skin_component::head, nullptr);
		driver.write(element + offsets::skin_component::body, nullptr);
		driver.write(element + offsets::skin_component::eyes, nullptr);
	}
}

std::string engine::types::game_object_t::get_class_name(const int size = 32) const
{
	const auto pointer = 
		driver.read(driver.read(instance) + engine::offsets::class_object::name);

	if (!pointer)
		return { };

	const auto class_name = driver.read_raw_bytes(pointer, size);

	return class_name;
}

std::string engine::types::player_t::get_player_name() const
{
	const auto display_name = driver.read(instance + offsets::base_player::_display_name);

	return driver.read_unicode_string(display_name + offsets::generic_list::entry);
}

std::vector< engine::types::player_t > engine::types::realm_t::get_players(std::uintptr_t client_entities) const
{
	std::vector< engine::types::player_t > players;

	if (!instance)
		return players;

	const auto size = driver.read< std::int32_t >(client_entities + offsets::generic_list::size);

	if (!size)
		return players;

	const auto list = instance + offsets::generic_list::elements;

	for (auto iterator = 1u; iterator < size; ++iterator)
	{
		const auto player = driver.read< engine::types::player_t >(list + (iterator * sizeof(void*)));

		if (player.get_player_info().is_tag(types::tag_t::player))
		{
			if (player.instance)
				players.push_back(player);
		}
	}

	return players;
}

std::vector< std::pair< std::string, engine::types::ore_t > > engine::types::realm_t::get_ores(std::uintptr_t client_entities) const
{
	std::vector< std::pair< std::string, engine::types::ore_t > > ores;

	if (!instance)
		return ores;

	const auto size = driver.read< std::int32_t >(client_entities + offsets::generic_list::size);

	if (!size)
		return ores;

	const auto list = instance + offsets::generic_list::elements;

	for (auto iterator = 0u; iterator < size; ++iterator)
	{
		const auto element = driver.read< types::ore_t >(list + (iterator * sizeof(void*)));

		if (element.get_class_name() == xs("OreResourceEntity"))
		{
			const auto object_name = driver.read< types::ore_t >(element.mono_object().instance + offsets::game_object::prefab_name);

			if (object_name.is_prefab_hash(types::prefab_hash_t::sulfur) || object_name.is_prefab_hash(types::prefab_hash_t::sulfur_rad) || object_name.is_prefab_hash(types::prefab_hash_t::sulfur_snow))
				ores.emplace_back("sulfur", element);
			else if (object_name.is_prefab_hash(types::prefab_hash_t::stone) || object_name.is_prefab_hash(types::prefab_hash_t::sulfur_rad) || object_name.is_prefab_hash(types::prefab_hash_t::stone_snow))
				ores.emplace_back("stone", element);
			else if (object_name.is_prefab_hash(types::prefab_hash_t::metal) || object_name.is_prefab_hash(types::prefab_hash_t::metal_rad) || object_name.is_prefab_hash(types::prefab_hash_t::metal_snow))
				ores.emplace_back("metal", element);
			else
				continue;
		}
	}

	return ores;
}

engine::types::flags_t engine::types::player_t::get_player_flags() const
{
	return driver.read< flags_t >(instance + engine::offsets::base_player::player_flags);
}

engine::types::player_t engine::types::realm_t::get_local_player(std::uintptr_t client_entities) const
{
	if (!instance)
		return { 0 };

	const auto size = driver.read< std::uint32_t >(client_entities + offsets::generic_list::size);

	if (!size)
		return { 0 };

	const auto list = instance + offsets::generic_list::elements;

	return driver.read< engine::types::player_t >(list);
}

engine::types::camera_t::view_matrix_t engine::types::camera_t::get_view_matrix() const
{
	return driver.read< engine::types::camera_t::view_matrix_t  >(instance + offsets::camera::view_matrix);
}

constexpr auto M_PI = 3.14159265358979323846f;

std::optional<engine::structures::vector2_t> engine::types::camera_t::world_to_screen(const engine::structures::vector3_t& position) const
{
	const auto width = GetSystemMetrics(SM_CXSCREEN), height = GetSystemMetrics(SM_CYSCREEN);

	auto view_matrix = get_view_matrix();

	const auto first = engine::structures::vector3_t{ view_matrix._11, view_matrix._21, view_matrix._31 };
	const auto second = engine::structures::vector3_t{ view_matrix._12, view_matrix._22, view_matrix._32 };
	const auto fourth = engine::structures::vector3_t{ view_matrix._14, view_matrix._24, view_matrix._34 };

	float y = second.dot(position) + view_matrix._42;
	float x = first.dot(position) + view_matrix._41;

	const auto w = fourth.dot(position) + view_matrix._44;

	if (w < 0.098f)
		return std::nullopt;

	return std::optional< engine::structures::vector2_t >({ (1.f + (x) / w) * (width / 2), (1.f - (y) / w) * (height / 2) });
}

std::vector<engine::types::base_object_t> engine::types::game_object_manager_t::get_tagged_objects() const
{
	std::vector< base_object_t > tagged_objects;

	auto last_tagged_object = this->last_tagged_object().as< types::base_object_t >();

	if (!last_tagged_object.instance)
		return tagged_objects;

	auto current_tagged_object = types::base_object_t{ driver.read(this->first_tagged_object().instance) };

	while (current_tagged_object.instance && current_tagged_object.game_object().instance && current_tagged_object.game_object().instance != last_tagged_object.game_object().instance)
	{
		if (current_tagged_object.instance)
			tagged_objects.push_back(current_tagged_object.as< types::base_object_t >());

		current_tagged_object.instance = current_tagged_object.next_base_object().instance;
	}

	if (last_tagged_object.instance)
		tagged_objects.push_back(last_tagged_object);

	return tagged_objects;
}

std::vector<engine::types::base_object_t> engine::types::game_object_manager_t::get_camera_objects() const
{
	std::vector< base_object_t > camera_objects;

	auto last_camera_object = this->last_camera_tagged_object().as< types::base_object_t >();

	if (!last_camera_object.instance)
		return camera_objects;

	auto current_camera_object = types::base_object_t{ driver.read(this->first_camera_tagged_object().instance) };

	while (current_camera_object.instance && current_camera_object.game_object().instance && current_camera_object.game_object().instance != last_camera_object.game_object().instance)
	{
		if (current_camera_object.instance)
			camera_objects.push_back(current_camera_object.as< types::base_object_t >());

		current_camera_object.instance = current_camera_object.next_base_object().instance;
	}

	if (last_camera_object.instance)
		camera_objects.push_back(last_camera_object);

	return camera_objects;
}

std::vector<engine::types::base_object_t> engine::types::game_object_manager_t::get_active_objects() const
{
	std::vector< base_object_t > active_objects;

	auto last_active_object = this->last_active_object().as< types::base_object_t >();

	if (!last_active_object.instance)
		return active_objects;

	auto current_active_object = types::base_object_t{ driver.read(this->first_active_object().instance) };

	while (current_active_object.instance && current_active_object.game_object().instance && current_active_object.game_object().instance != last_active_object.game_object().instance)
	{
		if (current_active_object.instance)
			active_objects.push_back(current_active_object.as< types::base_object_t >());

		current_active_object.instance = current_active_object.next_base_object().instance;
	}

	if (last_active_object.instance)
		active_objects.push_back(last_active_object);

	return active_objects;
}

engine::types::base_object_t engine::types::game_object_manager_t::get_tagged_object_by_name(const name_hash_t name) const
{
	auto last_tagged_object = this->last_tagged_object().as< types::base_object_t >();

	if (!last_tagged_object.instance)
		return { 0 };

	auto current_tagged_object = types::base_object_t{ driver.read(this->last_tagged_object().instance) };

	while (current_tagged_object.instance && current_tagged_object.game_object().instance != last_tagged_object.instance)
	{
		if (current_tagged_object.instance)
		{
			const auto game_object = current_tagged_object.game_object();

			if (game_object.instance && game_object.is_hash(name))
			{
				return current_tagged_object;
			}
		}

		current_tagged_object.instance = current_tagged_object.next_base_object().instance;
	}

	if (last_tagged_object.instance)
	{
		const auto game_object = last_tagged_object.game_object();

		if (game_object.instance && game_object.is_hash(name))
		{
			return last_tagged_object.as< base_object_t >();
		}
	}

	return { 0 };
}

engine::types::base_object_t engine::types::game_object_manager_t::get_camera_object_by_name(const name_hash_t name) const
{
	auto last_camera_object = this->last_camera_tagged_object().as< types::base_object_t >();

	if (!last_camera_object.instance)
		return { 0 };

	auto current_camera_object = types::base_object_t{ driver.read(this->first_camera_tagged_object().instance) };

	while (current_camera_object.instance && current_camera_object.game_object().instance && current_camera_object.game_object().instance != last_camera_object.game_object().instance)
	{
		if (current_camera_object.instance)
		{
			const auto game_object = current_camera_object.game_object();

			if (game_object.instance && game_object.is_hash(name))
			{
				return current_camera_object;
			}
		}

		current_camera_object.instance = current_camera_object.next_base_object().instance;
	}

	if (last_camera_object.instance)
	{
		const auto game_object = last_camera_object.game_object();

		if (game_object.instance && game_object.is_hash(name))
		{
			return last_camera_object.as< base_object_t >();
		}
	}

	return { 0 };
}

engine::types::base_object_t engine::types::game_object_manager_t::get_active_object_by_name(const name_hash_t name) const
{
	auto last_active_object = this->last_active_object().as< types::base_object_t >();

	if (!last_active_object.instance)
		return { 0 };

	auto current_active_object = types::base_object_t{ driver.read(this->first_active_object().instance) };

	while (current_active_object.instance && current_active_object.game_object().instance && current_active_object.game_object().instance != last_active_object.game_object().instance)
	{
		if (current_active_object.instance)
		{
			const auto game_object = current_active_object.game_object();

			if (game_object.instance && game_object.is_hash(name))
			{
				return current_active_object;
			}
		}

		current_active_object.instance = current_active_object.next_base_object().instance;
	}

	if (last_active_object.instance)
	{
		const auto game_object = last_active_object.game_object();

		if (game_object.instance && game_object.is_hash(name))
		{
			return last_active_object.as< base_object_t >();
		}
	}

	return { 0 };
}

engine::structures::vector3_t engine::types::ore_t::get_position(std::uintptr_t object) const
{
	return driver.read<engine::structures::vector3_t>(object, { engine::offsets::ore_object::state, engine::offsets::ore_object::visual, engine::offsets::ore_object::position });
}

engine::structures::vector3_t engine::types::transform_t::get_position() const
{
	auto a1 = driver.read<uint64_t>(instance + 0x10);
	if (!a1)
		return engine::structures::vector3_t{ };

	auto v8 = driver.read<std::uintptr_t>(a1 + 0x38);

	__int64 v2; // r8
	__int64 arr; // r11
	__int64 dia; // rdx
	int di; // eax
	__int64 v7; // rcx
	__int64 ri; // rax
	__m128i temp_0; // xmm0
	__m128 v10; // xmm11
	__m128 xxxx; // xmm3
	__m128 yxwy; // xmm7
	__m128 zwxy; // xmm9
	__m128 yyyy; // xmm10
	__m128 zzzz; // xmm8
	__m128 wzyw; // xmm4
	__m128 v17{}; // xmm6

	__m128 xmmword_1220320 = { -2.f, 2.f, -2.f, 0.f };
	__m128 xmmword_1220330 = { 2.f, -2.f, -2.f, 0.f };
	__m128 xmmword_1220300 = { -2.f, -2.f, 2.f, 0.f };

	v2 = driver.read<unsigned int>(a1 + 0x38 + 8);

	arr = driver.read < std::uint64_t>(v8 + 0x18);
	dia = driver.read < std::uint64_t>(v8 + 0x20);
	di = driver.read<DWORD>(dia + 4 * v2);
	while (di >= 0)
	{
		v7 = di;
		ri = 6 * di;
		temp_0 = driver.read < __m128i>(arr + 8 * ri + 0x10);
		v10 = _mm_mul_ps(driver.read < __m128>(arr + 8 * ri + 0x20), v17);
		xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, 0));
		yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, 0x71));
		zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, 0x8E));
		yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, 0x55));
		zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, 0xAA));
		wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, 0xDB));
		v17 = _mm_add_ps(
			_mm_add_ps(
				_mm_add_ps(
					_mm_mul_ps(
						_mm_sub_ps(
							_mm_mul_ps(_mm_mul_ps(xxxx, (__m128)xmmword_1220330), zwxy),
							_mm_mul_ps(_mm_mul_ps(yyyy, (__m128)xmmword_1220300), wzyw)),
						_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0xAA))),
					_mm_mul_ps(
						_mm_sub_ps(
							_mm_mul_ps(_mm_mul_ps(zzzz, (__m128)xmmword_1220300), wzyw),
							_mm_mul_ps(_mm_mul_ps(xxxx, (__m128)xmmword_1220320), yxwy)),
						_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0x55)))),
				_mm_add_ps(
					_mm_mul_ps(
						_mm_sub_ps(
							_mm_mul_ps(_mm_mul_ps(yyyy, (__m128)xmmword_1220320), yxwy),
							_mm_mul_ps(_mm_mul_ps(zzzz, (__m128)xmmword_1220330), zwxy)),
						_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0))),
					v10)),
			driver.read < __m128>(arr + 8 * ri));
		di = driver.read<DWORD>(dia + 4 * v7);
	}
	return { v17.m128_f32[0], v17.m128_f32[1], v17.m128_f32[2] };
}

std::pair<float, float> engine::types::base_entity_t::get_health()
{
	float current = driver.read<float>(instance + offsets::base_combat_entity::_health), max = 100.f;

	return { current, max };
}

engine::types::transform_t engine::types::parent_t::get_bone_transform(engine::structures::bones bone) const
{
	if (!instance)
		return { 0 };

	if (const auto bone_transforms = driver.read(instance + offsets::model::bone_transforms))
	{
		return driver.read<engine::types::transform_t>(bone_transforms + (0x20 + static_cast<int>(bone) * 8));
	}

	return { 0 };
}

engine::structures::vector3_t engine::types::base_entity_t::get_bone_position(const engine::structures::bones bone)
{
	return get_parent().get_bone_transform(bone).get_position();
}

void engine::types::parent_t::get_bone_transforms(transform_t* buff) const
{
	if (const auto bone_transforms = driver.read(instance + offsets::model::bone_transforms))
	{
		driver.read_arr< transform_t >(bone_transforms + 0x20, buff, 67);
	}
}