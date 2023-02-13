#include "no_spread.hpp"

#include "../../../engine/engine.hpp"
#include "../../../renderer/menu/config/config.hpp"

void modules::weapon::no_spread::callback()
{
	std::unique_lock<std::mutex> initiate_thread_locker(engine::values::global_locker);

	const auto camera_copy = engine::values::camera;

	const auto entity_realm_copy = engine::values::entity_realm;

	if (!camera_copy.instance || !entity_realm_copy.instance || !engine::values::client_entities)
		return;

	const auto local_player_copy = entity_realm_copy.get_local_player(engine::values::client_entities);

	initiate_thread_locker.unlock();

	if (std::get< bool >(menu::config::config_map[features::enable_no_spread]))
	{
		auto held_item = local_player_copy.get_player_info().get_base_entity().get_held_item();

		if (
			held_item.instance &&
			held_item.get_base_projectile().instance &&
			held_item.item< engine::types::item_types_t::rifle >()
			|| held_item.item< engine::types::item_types_t::smg >()
			|| held_item.item< engine::types::item_types_t::shotgun >()
			|| held_item.item< engine::types::item_types_t::pistol >()
			|| held_item.item< engine::types::item_types_t::m249 >()
			)
		{
			driver.write<float>(held_item.get_base_projectile().instance + engine::offsets::base_projectile::hip_aim_cone, 0.f);

			driver.write<float>(held_item.get_base_projectile().instance + engine::offsets::base_projectile::aim_cone, 0.f);
			driver.write<float>(held_item.get_base_projectile().instance + engine::offsets::base_projectile::aimcone_penalty, 0.f);

			driver.write<float>(held_item.get_base_projectile().instance + engine::offsets::base_projectile::stance_penalty, 0.f);
			driver.write<float>(held_item.get_base_projectile().instance + engine::offsets::base_projectile::stance_penalty_scale, 0.f);
		}
	}
}