#include "../SDK/SDK.h"
#include "../Core/Core.h"

MAKE_HOOK(IBaseFileSystem_Open, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IBaseFileSystemAddr), 2), FileHandle_t,
		  void* rcx, const char* pFileName, const char* pOptions, const char* pathID)
{
	try
	{
		if (SDK::BlacklistFile(pFileName))
			return nullptr;

		return CALL_ORIGINAL(rcx, pFileName, pOptions, pathID);
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in IBaseFileSystem_Open", true);
	}
	return nullptr;
}

MAKE_HOOK(IBaseFileSystem_Precache, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IBaseFileSystemAddr), 9), bool,
		  void* rcx, const char* pFileName, const char* pPathID)
{
	try
	{
		return true;
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in IBaseFileSystem_Precache", true);
	}
	return true;
}

class CUtlBuffer;

MAKE_HOOK(IBaseFileSystem_ReadFile, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IBaseFileSystemAddr), 14), bool,
		  void* rcx, const char* pFileName, const char* pPath, CUtlBuffer& buf, int nMaxBytes, int nStartingByte, FSAllocFunc_t pfnAlloc)
{
	try
	{
		if (SDK::BlacklistFile(pFileName))
			return false;

		return CALL_ORIGINAL(rcx, pFileName, pPath, buf, nMaxBytes, nStartingByte, pfnAlloc);
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in IBaseFileSystem_ReadFile", true);
	}
	return false;
}