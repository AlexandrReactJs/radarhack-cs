#include "memory.h"
#include <Windows.h>
#include <thread>
#include "Config.h"

namespace offsets {

	// client.dll
	constexpr auto localPlayer = 0xDEA98C;
	constexpr auto entityList = 0x4DFFF7C;
	constexpr auto glowObjectManager = 0x535AA08;

	//enity
	constexpr auto teamNum = 0xF4;
	constexpr auto glowIndex = 0x10488;
	constexpr auto spotted = 0x93D;

}


int main()
{
	auto memory = Memory{ "csgo.exe" };
	const auto client = memory.GetModuleAddress("client.dll");

	

	while (true)
	{

		checkTogglesFunc();

		if (glowToggle) 
		{
			const auto localPlayer = memory.Read<std::uintptr_t>(client + offsets::localPlayer);
			const auto glowObjectManager = memory.Read<std::uintptr_t>(client + offsets::glowObjectManager);


			for (auto i = 1; i <= 64; ++i)
			{
				const auto entity = memory.Read<std::uintptr_t>(client + offsets::entityList + i * 0x10);


				if (memory.Read<std::uintptr_t>(entity + offsets::teamNum) == memory.Read<std::uintptr_t>(localPlayer + offsets::teamNum)) continue;

				const auto glowIndex = memory.Read<std::int32_t>(entity + offsets::glowIndex);


				memory.Write<float>(glowObjectManager + (glowIndex * 0x38) + 0x8, 1.f); // r
				memory.Write<float>(glowObjectManager + (glowIndex * 0x38) + 0xC, 0.f); // g
				memory.Write<float>(glowObjectManager + (glowIndex * 0x38) + 0x10, 0.f); // b
				memory.Write<float>(glowObjectManager + (glowIndex * 0x38) + 0x14, 1.f); // a

				memory.Write<bool>(glowObjectManager + (glowIndex * 0x38) + 0x27, true);
				memory.Write<bool>(glowObjectManager + (glowIndex * 0x38) + 0x28, true);
			}
		}
		

		if (radarHackToggle) 
		{
			const auto localPlayer = memory.Read<std::uintptr_t>(client + offsets::localPlayer);
			const auto localTeam = memory.Read<std::uintptr_t>(client + offsets::teamNum);

			for (auto i = 1; i <= 64; ++i)
			{
				const auto entity = memory.Read<std::uintptr_t>(client + offsets::entityList + i * 0x10);

				if (memory.Read<std::uintptr_t>(entity + offsets::teamNum) == localPlayer) continue;

				memory.Write<bool>(entity + offsets::spotted, true);


			}
		}
		





		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return 0;
}


