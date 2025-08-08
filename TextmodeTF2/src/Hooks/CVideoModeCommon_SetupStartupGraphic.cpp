#include "../SDK/SDK.h"
#include "../Core/Core.h"

MAKE_HOOK(CVideoModeCommon_SetupStartupGraphic, G::CVideoModeCommon_SetupStartupGraphicAddr, void*,
		  void* rcx)
{
	try
	{
		return nullptr;
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in CVideoModeCommon_SetupStartupGraphic", true);
	}
	return nullptr;
}