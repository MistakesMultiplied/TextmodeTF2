#include <Windows.h>
#include "Core/Core.h"
#include "Utils/CrashLog/CrashLog.h"
#include <exception>

DWORD WINAPI MainThread(LPVOID lpParam)
{
	try
	{
		U::Core.Load();
		U::Core.Loop();
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception caught in MainThread", true);
	}

	CrashLog::Unload(); // 0xC0000409
	U::Core.Unload();

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		CrashLog::Initialize();

		if (const auto hMainThread = CreateThread(nullptr, 0, MainThread, hinstDLL, 0, nullptr))
			CloseHandle(hMainThread);
	}

	return TRUE;
}