#pragma once
#include <array>

namespace modules
{
	constexpr auto module_update_interval = 500u;
	constexpr auto fast_module_update_interval = 1u;

	using module_callback_t = void(*)();

	struct module_t
	{
		bool is_premium;

		module_callback_t callback;
	};

	extern std::array< module_t, 6 > weapon_module_array;
	
	extern std::array< module_t, 2 > misc_module_array; extern std::array< module_t, 1 > projectile_module_array;

	void fire_weapon_modules(), fire_misc_modules(), fire_projectile_modules();
}
