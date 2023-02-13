#include "long_hand.hpp"

#include "../../../engine/engine.hpp"
#include "../../../renderer/menu/config/config.hpp"

void modules::weapon::long_hand::callback()
{
	std::unique_lock<std::mutex> initiate_thread_locker(engine::values::global_locker);

	const auto camera_copy = engine::values::camera;

	const auto entity_realm_copy = engine::values::entity_realm;

	if (!camera_copy.instance || !entity_realm_copy.instance || !engine::values::client_entities)
		return;

	const auto local_player_copy = entity_realm_copy.get_local_player(engine::values::client_entities);

	initiate_thread_locker.unlock();

	if (std::get< bool >(menu::config::config_map[features::enable_long_hand]))
	{
		auto held_item = local_player_copy.get_player_info().get_base_entity().get_held_item();

		if (held_item.instance && held_item.get_base_projectile().instance 

			&& held_item.item< engine::types::item_types_t::knife >()
			|| held_item.item< engine::types::item_types_t::bone_club >()
			|| held_item.item< engine::types::item_types_t::mace >()
			|| held_item.item< engine::types::item_types_t::machete >()
			|| held_item.item< engine::types::item_types_t::pitch_fork >()
			|| held_item.item< engine::types::item_types_t::salvaged_cleaver_sword >()
			|| held_item.item< engine::types::item_types_t::spear >()
			|| held_item.item< engine::types::item_types_t::long_sword >()
			|| held_item.item< engine::types::item_types_t::hatchet >()
			|| held_item.item< engine::types::item_types_t::pickaxe >()
			|| held_item.item< engine::types::item_types_t::slavaged_axe >()
			|| held_item.item< engine::types::item_types_t::salvaged_hammer >()
			|| held_item.item< engine::types::item_types_t::salvaged_icepick >()
			|| held_item.item< engine::types::item_types_t::stone_hatchet_pickaxe >()
			)
		{
			driver.write<float>(held_item.get_base_projectile().instance + engine::offsets::base_melee::max_distance, 5.f);
		}
	}
}