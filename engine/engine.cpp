#include "engine.hpp"

std::uintptr_t engine::values::unity_player = 0;
std::uintptr_t engine::values::game_assembly = 0;

std::uintptr_t engine::values::client_entities = 0;

engine::types::realm_t engine::values::entity_realm { 0 };

engine::types::game_object_manager_t engine::values::game_object_manager { 0 };
engine::types::base_networkable_t engine::values::base_networkable { 0 };
engine::types::camera_t engine::values::camera { 0 };

engine::types::player_t engine::values::local_player;

std::mutex engine::values::global_locker;
std::mutex engine::values::player_vector_locker;

std::mutex engine::values::ore_vector_locker;

std::vector< engine::types::player_t > engine::values::players { };

std::vector< std::pair< std::string, engine::types::ore_t > > engine::values::ores { };

std::once_flag setup_bases;

void engine::functions::initiate()
{
	while (true)
	{
		std::call_once(setup_bases, [=]()
			{
				engine::values::unity_player = driver.dll(xs(L"UnityPlayer.dll"));

				engine::values::game_assembly = driver.dll(xs(L"GameAssembly.dll"));

				values::game_object_manager.instance = driver.read(engine::values::unity_player + engine::offsets::game_object_manager);

				if (!values::game_object_manager.instance)
					std::printf(xs("failed to get game_object_manager\n"));
			});

		const auto temporary_camera_value = driver.read<engine::types::camera_t>( driver.read< std::uintptr_t >( driver.read< std::uintptr_t >( 
			driver.read< std::uintptr_t >( engine::values::unity_player + 0x1762E80 ) ) ), { 0x30, 0x30, 0x18 } );

		const auto temporary_client_entities = engine::values::base_networkable.get_client_entities();

		const auto temporary_entity_realm_value = temporary_client_entities.get_entity_list();

		std::unique_lock<std::mutex> initiate_thread_locker(engine::values::global_locker);

		engine::values::camera = temporary_camera_value;

		engine::values::entity_realm = temporary_entity_realm_value;

		engine::values::client_entities = temporary_client_entities.instance;

		values::base_networkable.instance = engine::values::game_assembly;

		if (settings::values::debug)
		{
			std::printf(xs("camera %p\n"), engine::values::camera.instance);
			std::printf(xs("client_entities %p\n"), engine::values::client_entities);
			std::printf(xs("base_networkable %p\n"), values::base_networkable.instance);
		}

		initiate_thread_locker.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void engine::functions::update_players_vector()
{
	while (true)
	{
		std::unique_lock<std::mutex> update_players_global_locker(engine::values::global_locker);

		if (!engine::values::camera.instance || !engine::values::base_networkable.instance)
		{
			update_players_global_locker.unlock();

			std::unique_lock<std::mutex> update_players_locker(engine::values::player_vector_locker);

			engine::values::players.clear();

			update_players_locker.unlock();

			continue;
		}

		types::base_networkable_t base_networkable_clone{ engine::values::base_networkable.instance };

		update_players_global_locker.unlock();

		const auto temporary_players = base_networkable_clone.get_client_entities().get_entity_list().get_players(engine::values::client_entities);

		std::unique_lock<std::mutex> update_players_locker(engine::values::player_vector_locker);

		engine::values::local_player = values::entity_realm.get_local_player(values::client_entities);

		engine::values::players = temporary_players;

		update_players_locker.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void engine::functions::update_ores_vector()
{
	while (true)
	{
		std::unique_lock<std::mutex> update_ores_global_locker(engine::values::global_locker);

		if (!engine::values::camera.instance || !engine::values::base_networkable.instance)
		{
			update_ores_global_locker.unlock();

			std::unique_lock<std::mutex> update_ores_locker(engine::values::ore_vector_locker);

			engine::values::ores.clear();

			update_ores_locker.unlock();

			continue;
		}

		types::base_networkable_t base_networkable_clone{ engine::values::base_networkable.instance };

		update_ores_global_locker.unlock();

		const auto temporary_ores = base_networkable_clone.get_client_entities().get_entity_list().get_ores(engine::values::client_entities);

		std::unique_lock<std::mutex> update_ores_locker(engine::values::ore_vector_locker);

		engine::values::ores = temporary_ores;

		update_ores_locker.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}