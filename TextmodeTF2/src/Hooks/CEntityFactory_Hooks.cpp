#include "../SDK/SDK.h"
#include <unordered_set>
#include <string>
#include "../Core/Core.h"

// Forward-declare CBaseEntity to use it as a pointer type without needing the full header.
class CBaseEntity;

static bool ShouldBlockEntity(const char* cls)
{
    if (!cls) return false;
    // Block visual/physics props that are not needed in textmode.
    if (!_stricmp(cls, "prop_dynamic")) return true;
    if (!_stricmp(cls, "prop_dynamic_override")) return true;
    if (!_stricmp(cls, "prop_dynamic_glow")) return true;
    if (!_stricmp(cls, "prop_physics")) return true;
    if (!_stricmp(cls, "prop_physics_multiplayer")) return true;
    if (!_stricmp(cls, "prop_physics_override")) return true;
    if (!_stricmp(cls, "prop_ragdoll")) return true;
    if (!_stricmp(cls, "func_breakable")) return true;
    if (!_stricmp(cls, "func_breakable_surf")) return true;
    if (strstr(cls, "gib")) return true;
    return false;
}

// Hook for the client's entity factory.
MAKE_HOOK(Client_CreateEntityByName, U::Signatures.GetClientSignature("55 8B EC 83 EC 14 53 56 8B 75 08 8D 45 EC"), CBaseEntity*,
          void* rcx, const char* pszName)
{
    try
    {
        static std::unordered_set<std::string> s_logged;
        if (pszName && ShouldBlockEntity(pszName))
        {
            // Log once per classname to avoid spam
            static std::unordered_set<std::string> s_logged;
            if (s_logged.emplace(pszName).second)
            {
                SDK::Output("Client_CreateEntityByName", std::format("Blocked client entity: {}", pszName).c_str());
            }
            return nullptr; // Prevent spawn
        }
        return CALL_ORIGINAL(rcx, pszName);
    }
    catch (const std::exception& e)
    {
        U::Core.AppendFailText(e.what(), true);
    }
    catch (...)
    {
        U::Core.AppendFailText("Unknown exception in Client_CreateEntityByName", true);
    }
    return nullptr;
}
