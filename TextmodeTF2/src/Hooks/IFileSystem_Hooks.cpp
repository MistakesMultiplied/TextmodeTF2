#include "../SDK/SDK.h"

MAKE_HOOK(IFileSystem_FindNext, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 28), const char*,
		  void* rcx, FileFindHandle_t handle)
{
	const char* p;
	do
		p = CALL_ORIGINAL(rcx, handle);
	while (p && SDK::BlacklistFile(p));

	return p;
}

MAKE_HOOK(IFileSystem_FindFirst, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 27), const char*,
		  void* rcx, const char* pWildCard, FileFindHandle_t* pHandle)
{
	auto p = CALL_ORIGINAL(rcx, pWildCard, pHandle);
	while (p && SDK::BlacklistFile(p))
		p = Hooks::IFileSystem_FindNext::Func(rcx, *pHandle);

	return p;
}

MAKE_HOOK(IFileSystem_AsyncReadMultiple, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 37), FSAsyncStatus_t,
		  void* rcx, const FileAsyncRequest_t* pRequests, int nRequests, FSAsyncControl_t* phControls)
{
	for (int i = 0; pRequests && i < nRequests; ++i)
	{
		// fprintf(stderr, "AsyncReadMultiple %d %s\n", nRequests, pRequests[i]);
		if (SDK::BlacklistFile(pRequests[i].pszFilename))
		{
			if (nRequests > 1)
				fprintf(stderr, "FIXME: blocked AsyncReadMultiple for %d requests due to some filename being blacklisted\n", nRequests);
			return FSASYNC_ERR_FILEOPEN;
		}
	}
	return CALL_ORIGINAL(rcx, pRequests, nRequests, phControls);
}

MAKE_HOOK(IFileSystem_OpenEx, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 69), FileHandle_t,
		  void* rcx, const char* pFileName, const char* pOptions, unsigned flags, const char* pathID, char** ppszResolvedFilename)
{
	// fprintf(stderr, "OpenEx: %s\n", pFileName);
	if (pFileName && SDK::BlacklistFile(pFileName))
		return nullptr;

	return CALL_ORIGINAL(rcx, pFileName, pOptions, flags, pathID, ppszResolvedFilename);
}

MAKE_HOOK(IFileSystem_ReadFileEx, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 71), int,
		  void* rcx, const char* pFileName, const char* pPath, void** ppBuf, bool bNullTerminate, bool bOptimalAlloc, int nMaxBytes, int nStartingByte, FSAllocFunc_t pfnAlloc)
{
	// fprintf(stderr, "ReadFileEx: %s\n", pFileName);
	if (SDK::BlacklistFile(pFileName))
		return 0;

	return CALL_ORIGINAL(rcx, pFileName, pPath, ppBuf, bNullTerminate, bOptimalAlloc, nMaxBytes, nStartingByte, pfnAlloc);
}

MAKE_HOOK(IFileSystem_AddFilesToFileCache, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IFileSystemAddr), 103), void,
		  void* rcx, FileCacheHandle_t cacheId, const char** ppFileNames, int nFileNames, const char* pPathID)
{
	fprintf(stderr, "AddFilesToFileCache: %d\n", nFileNames);
	for (int i = 0; i < nFileNames; ++i)
		fprintf(stderr, "%s\n", ppFileNames[i]);
}