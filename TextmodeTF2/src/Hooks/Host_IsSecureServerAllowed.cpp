#include "../SDK/SDK.h"
#include "../Core/Core.h"

MAKE_HOOK(Host_IsSecureServerAllowed, G::Host_IsSecureServerAllowedAddr, bool)
{
	try
	{
		return *reinterpret_cast<bool*>(U::Memory.RelToAbs(G::g_bAllowSecureServersAddr)) = true;
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in Host_IsSecureServerAllowed", true);
	}
	return false;
}