#include "../SDK/SDK.h"
#include "../Core/Core.h"

MAKE_HOOK(CVideoModeCommon_SetupStartupGraphic, G::CVideoModeCommon_SetupStartupGraphicAddr, void*,
		  void* rcx)
{
	return nullptr;
}