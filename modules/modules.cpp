#include "modules.hpp"

#include <thread>
#include "../settings/settings.hpp"

#include "weapon/no_recoil/no_recoil.hpp"
#include "weapon/no_spread/no_spread.hpp"
#include "weapon/force_auto/force_auto.hpp"
#include "weapon/long_hand/long_hand.hpp"
#include "weapon/run_on_hit/run_on_hit.hpp"
#include "weapon/instant_eoka/instant_eoka.hpp"
#include "weapon/thick_bullet/thick_bullet.hpp"

#include "misc/admin/admin.hpp"
#include "misc/spiderman/spiderman.hpp"

std::array< modules::module_t, 6 > modules::weapon_module_array =
{
	modules::module_t{ false, modules::weapon::no_recoil::callback },
	modules::module_t{ false, modules::weapon::no_spread::callback },

	modules::module_t{ false, modules::weapon::long_hand::callback },
	modules::module_t{ false, modules::weapon::force_auto::callback },

	modules::module_t{ false, modules::weapon::run_on_hit::callback },
	modules::module_t{ false, modules::weapon::instant_eoka::callback }
};

std::array< modules::module_t, 2 > modules::misc_module_array =
{
	modules::module_t{ false, modules::misc::admin::callback },
	modules::module_t{ false, modules::misc::spiderman::callback },
}; 

std::array< modules::module_t, 1 > modules::projectile_module_array =
{
	modules::module_t{ false, modules::weapon::thick_bullet::callback }
};

void modules::fire_weapon_modules()
{
	while (true)
	{
		for (const auto& [premium, callback] : weapon_module_array)
		{
			if (!premium || settings::values::premium)
				callback();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(module_update_interval));
	}
}

void modules::fire_misc_modules()
{
	while (true)
	{
		for (const auto& [premium, callback] : misc_module_array)
		{
			if (!premium || settings::values::premium)
				callback();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(fast_module_update_interval));
	}
}

void modules::fire_projectile_modules()
{
	while (true)
	{
		for (const auto& [premium, callback] : projectile_module_array)
		{
			if (!premium || settings::values::premium)
				callback();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(fast_module_update_interval));
	}
}