#include "instant_eoka.hpp"

#include "../../../engine/engine.hpp"
#include "../../../renderer/menu/config/config.hpp"

bool lol = false;

void modules::weapon::instant_eoka::callback()
{
	std::unique_lock<std::mutex> initiate_thread_locker(engine::values::global_locker);

	const auto camera_copy = engine::values::camera;

	const auto entity_realm_copy = engine::values::entity_realm;

	if (!camera_copy.instance || !entity_realm_copy.instance || !engine::values::client_entities)
		return;

	const auto local_player_copy = entity_realm_copy.get_local_player(engine::values::client_entities);

	initiate_thread_locker.unlock();

	if (std::get< bool >(menu::config::config_map[features::enable_instant_eoka]))
	{
		auto held_item = local_player_copy.get_player_info().get_base_entity().get_held_item();

		if (held_item.instance && held_item.get_base_projectile().instance && held_item.item< engine::types::item_types_t::eoka >())
		{
			driver.write<float>(held_item.get_base_projectile().instance + engine::offsets::flint_strike_weapon::success_fraction, 1.f);

			driver.write<bool>(held_item.get_base_projectile().instance + engine::offsets::flint_strike_weapon::_did_spark_this_frame, true);
		}
	}
}