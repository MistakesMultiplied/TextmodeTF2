#include "Core.h"

#include "../SDK/SDK.h"
#include "../BytePatches/BytePatches.h"
#include <filesystem>

#define LOAD_WAIT 0 - m_bTimeout
#define LOAD_FAIL -1
#define CHECK(x) if (x == LOAD_FAIL) {m_bUnload = true; return;}

void CCore::AppendFailText(const char* sMessage, bool bCritical)
{
	if (!m_bTimeout)
		return;

	ssFailStream << std::format("{}\n", sMessage);
	OutputDebugStringA(std::format("{}\n", sMessage).c_str());
}

int CCore::LoadSDL()
{
	G::SDL_CreateWindowAddr = U::Memory.GetModuleExport<uintptr_t>("SDL2.dll", "SDL_CreateWindow");
	if (!G::SDL_CreateWindowAddr)
		return LOAD_WAIT;

	if (!U::Hooks.Initialize("SDL_CreateWindow"))
		return LOAD_FAIL;

	return m_bSDLLoaded = true;
}

int CCore::LoadFilesystem()
{
	G::IFileSystemAddr = reinterpret_cast<uintptr_t>(U::Memory.FindInterface("filesystem_stdio.dll", "VFileSystem022"));
	if (!G::IFileSystemAddr)
		return LOAD_WAIT;

	G::IBaseFileSystemAddr = G::IFileSystemAddr + 0x8;

	static std::vector<const char*> vFileSystemHooks
	{
		"IFileSystem_FindFirst", "IFileSystem_FindNext",
		"IFileSystem_AsyncReadMultiple", "IFileSystem_OpenEx",
		"IFileSystem_ReadFileEx", "IFileSystem_AddFilesToFileCache",
		"IBaseFileSystem_Open", "IBaseFileSystem_Precache",
		"IBaseFileSystem_ReadFile"
	};

	for (auto cHook : vFileSystemHooks)
		if (!U::Hooks.Initialize(cHook))
			return LOAD_FAIL;

	return m_bFilesystemLoaded = true;
}

int CCore::LoadEngine()
{
	static bool bStartupGraphicHookInit{ false };
	G::CVideoModeCommon_SetupStartupGraphicAddr = U::Memory.FindSignature("engine.dll", "48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 8B F9");
	if (!bStartupGraphicHookInit && G::CVideoModeCommon_SetupStartupGraphicAddr)
	{
		if (!U::Hooks.Initialize("CVideoModeCommon_SetupStartupGraphic"))
			return LOAD_FAIL;
		bStartupGraphicHookInit = true;
	}

	static bool bInsecureBypassInit{ false };
	G::g_bAllowSecureServersAddr = U::Memory.FindSignature("engine.dll", "40 88 35 ? ? ? ? 40 84 FF");
	G::Host_IsSecureServerAllowedAddr = U::Memory.FindSignature("engine.dll", "48 83 EC ? FF 15 ? ? ? ? 48 8D 15 ? ? ? ? 48 8B C8 4C 8B 00 41 FF 50 ? 85 C0 75");
	if (G::g_bAllowSecureServersAddr && G::Host_IsSecureServerAllowedAddr)
	{
		if (!U::Hooks.Initialize("Host_IsSecureServerAllowed"))
			return LOAD_FAIL;
		bInsecureBypassInit = true;
	}

	static bool bTextmodeInit{ false };
	G::g_bTextModeAddr = U::Memory.FindSignature("engine.dll", "88 15 ? ? ? ? 48 8B 4E");

	// Enables textmode
	if (!bTextmodeInit && G::g_bTextModeAddr)
		*reinterpret_cast<bool*>(U::Memory.RelToAbs(G::g_bTextModeAddr, 0x2)) = bTextmodeInit = true;

	static bool bBytePatchesInit{ false };
	if (!bBytePatchesInit && U::BytePatches.Initialize("engine"))
		bBytePatchesInit = true;

	if(!bStartupGraphicHookInit || !bInsecureBypassInit || !bTextmodeInit || !bBytePatchesInit)
		return LOAD_WAIT;

	return m_bEngineLoaded = true;
}

int CCore::LoadVGui()
{
	if (!U::BytePatches.Initialize("vgui"))
		return LOAD_WAIT;

	return m_bVGuiLoaded = true;
}

int CCore::LoadMatSys()
{
	if (!U::Interfaces.Initialize())
		return LOAD_WAIT;

	I::MaterialSystem->SetInStubMode(true);

	static std::vector<const char*> vMatSystemHooks
	{
		"IMaterialSystem_CreateRenderTargetTexture", "IMaterialSystem_CreateNamedRenderTargetTextureEx",
		"IMaterialSystem_CreateNamedRenderTargetTexture", "IMaterialSystem_CreateNamedRenderTargetTextureEx2",
		"IMaterialSystem_SwapBuffers"
	};

	for (auto cHook : vMatSystemHooks)
		if (!U::Hooks.Initialize(cHook))
			return LOAD_FAIL;

	return m_bMatSysLoaded = true;
}

int CCore::LoadClient()
{
	if (!U::BytePatches.Initialize("client"))
		return LOAD_WAIT;

	return m_bClientLoaded = true;
}

void CCore::Load()
{
	auto StartTime = std::chrono::steady_clock::now();
	G::CurrentPath = std::filesystem::current_path().string() + "\\TextmodeTF2";

	do
	{
		// 5 seconds should be enough for tf2 to load all modules (unless youre running 100 game instances)
		m_bTimeout = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - StartTime).count() >= 20;

		Sleep(10);
		int iSDL = m_bSDLLoaded ? 1 : LoadSDL();
		CHECK(iSDL)
		int iFilesystem = m_bFilesystemLoaded ? 1 : LoadFilesystem();
		CHECK(iFilesystem)
		int iEngine = m_bEngineLoaded ? 1 : LoadEngine();
		CHECK(iEngine)
		//int iVGui = m_bVGuiLoaded ? 1 : LoadVGui();
		//CHECK(iVGui)
		int iMatSys = m_bMatSysLoaded ? 1 : LoadMatSys();
		CHECK(iMatSys)
		int iClient = m_bClientLoaded ? 1 : LoadClient();
		CHECK(iClient)
	}
	while (!m_bSDLLoaded || !m_bFilesystemLoaded || !m_bEngineLoaded /*|| !m_bVGuiLoaded*/ || !m_bMatSysLoaded || !m_bClientLoaded);

	SDK::Output("TextmodeTF2", "Loaded", true);
}

void CCore::Loop()
{
	while (true)
	{
		if (m_bUnload)
			break;

		Sleep(15);
	}
}

void CCore::Unload()
{	
	U::Hooks.Unload();
	U::BytePatches.Unload();

	ssFailStream << "\nCtrl + C to copy. Logged to TextmodeTF2\\fail_log.txt. \n";
	ssFailStream << "Built @ " __DATE__ ", " __TIME__;
//	SDK::Output("Failed to load", ssFailStream.str().c_str(), true, MB_OK | MB_ICONERROR);
	ssFailStream << "\n\n\n\n";
	std::ofstream file;
	file.open(G::CurrentPath + "\\fail_log.txt", std::ios_base::app);
	file << ssFailStream.str();
	file.close();
	return;
}