#include <windows.h>
#include <cstdint>
#include <thread>

#include "engine/engine.hpp"
#include "driver/driver.hpp"

#include "integrity/integrity.hpp"
#include "settings/settings.hpp"

#include "modules/modules.hpp"

#include "renderer/renderer.hpp"

__forceinline void open_console(const char* const console_name)
{
	FILE* input_output_stream;

	AllocConsole();

	freopen_s(&input_output_stream, "CONIN$", "r", stdin);
	freopen_s(&input_output_stream, "CONOUT$", "w", stdout);
	freopen_s(&input_output_stream, "CONOUT$", "w", stderr);

	SetConsoleTitleA(console_name);
}

int core()
{
	bool integrity_status = true;

	/*if constexpr (!settings::values::using_auth)
		integrity_status = integrity::check();

	if (integrity_status)
	{*/
		while (!FindWindowA(xs("UnityWndClass"), xs("Rust")))
			std::this_thread::sleep_for(std::chrono::seconds(15));

		if (settings::values::debug)
			open_console(xs("NZXT CAM"));

		driver.initiate(xs("UnityWndClass"));

		std::thread{ engine::functions::initiate }.detach();

		std::thread{ engine::functions::update_players_vector }.detach();
		std::thread{ engine::functions::update_ores_vector }.detach();

		std::thread{ modules::fire_misc_modules }.detach();
		std::thread{ modules::fire_weapon_modules }.detach();
		std::thread{ modules::fire_projectile_modules }.detach();

		renderer::start(xs("UnityWndClass"));
	/*}
	else
	{
		_Exit(0);
	}*/

	return 0;
}

bool DllMain(void*, const std::uint32_t injection_reason, void*)
{
	if (injection_reason == DLL_PROCESS_ATTACH)
		std::thread{ core }.detach();

	return true;
}