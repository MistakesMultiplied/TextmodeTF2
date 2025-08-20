#include "../SDK/SDK.h"

MAKE_HOOK(IFileSystem_FindNext, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 28), const char*,
		  void* rcx, FileFindHandle_t handle)
{
	// Always skip file finding for performance.
	return nullptr;

	/*
	const char* p;
	do
		p = CALL_ORIGINAL(rcx, handle);
	while (p && SDK::BlacklistFile(p));

	return p;
	*/
}

MAKE_HOOK(IFileSystem_FindFirst, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 27), const char*,
		  void* rcx, const char* pWildCard, FileFindHandle_t* pHandle)
{
	auto p = CALL_ORIGINAL(rcx, pWildCard, pHandle);
	while (p && SDK::BlacklistFile(p))
		p = Hooks::IFileSystem_FindNext::Hook.Call<const char*>(rcx, *pHandle);

	return p;
}

MAKE_HOOK(IFileSystem_AsyncReadMultiple, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 37), FSAsyncStatus_t,
		  void* rcx, const FileAsyncRequest_t* pRequests, int nRequests, FSAsyncControl_t* phControls)
{
	// Always skip non-essential async reads.
	bool hasEssential = false;
	for (int i = 0; pRequests && i < nRequests; ++i)
	{
		if (pRequests[i].pszFilename && std::strstr(pRequests[i].pszFilename, ".bsp"))
		{
			hasEssential = true;
			break;
		}
	}
	if (!hasEssential)
		return FSASYNC_ERR_FILEOPEN;

	for (int i = 0; pRequests && i < nRequests; ++i)
	{
		if (SDK::BlacklistFile(pRequests[i].pszFilename))
		{
			if (nRequests > 1)
				SDK::Output("IFileSystem_AsyncReadMultiple", std::format("FIXME: blocked AsyncReadMultiple for {} requests due to some filename being blacklisted", nRequests).c_str());
			return FSASYNC_ERR_FILEOPEN;
		}
	}
	return CALL_ORIGINAL(rcx, pRequests, nRequests, phControls);
}

MAKE_HOOK(IFileSystem_OpenEx, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 69), FileHandle_t,
		  void* rcx, const char* pFileName, const char* pOptions, unsigned flags, const char* pathID, char** ppszResolvedFilename)
{
	if (pFileName && SDK::BlacklistFile(pFileName))
		return nullptr;

	return CALL_ORIGINAL(rcx, pFileName, pOptions, flags, pathID, ppszResolvedFilename);
}

MAKE_HOOK(IFileSystem_ReadFileEx, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 71), int,
		  void* rcx, const char* pFileName, const char* pPath, void** ppBuf, bool bNullTerminate, bool bOptimalAlloc, int nMaxBytes, int nStartingByte, FSAllocFunc_t pfnAlloc)
{
	if (SDK::BlacklistFile(pFileName))
		return 0;

	return CALL_ORIGINAL(rcx, pFileName, pPath, ppBuf, bNullTerminate, bOptimalAlloc, nMaxBytes, nStartingByte, pfnAlloc);
}

MAKE_HOOK(IFileSystem_AddFilesToFileCache, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 103), void,
		  void* rcx, FileCacheHandle_t cacheId, const char** ppFileNames, int nFileNames, const char* pPathID)
{
	// Always skip adding files to the file cache.
	return;

	/*
	SDK::Output("IFileSystem_AddFilesToFileCache", std::format("AddFilesToFileCache: {}", nFileNames).c_str());
	for (int i = 0; i < nFileNames; ++i)
		SDK::Output("IFileSystem_AddFilesToFileCache", ppFileNames[i]);

	// Call original only if not in aggressive map loading mode
	return CALL_ORIGINAL(rcx, cacheId, ppFileNames, nFileNames, pPathID);
	*/
}