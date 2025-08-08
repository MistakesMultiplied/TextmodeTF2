#include "../SDK/SDK.h"
#include "../Core/Core.h"

// Hook for model precaching during map load
MAKE_HOOK(CModelPrecache_PrecacheModel, U::Signatures.GetEngineSignature("48 89 5C 24 ? 57 48 83 EC ? 80 3A ? 41 0F B6 F8 48 8B DA 7F ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 40 0F B6 D7 48 8B CB E8 ? ? ? ? 85 C0 79 ? 48 8B D3 48 8D 0D ? ? ? ? E8 ? ? ? ? 33 C0 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC 48 89 5C 24 ? 57 48 83 EC ? 80 3A ? 41 0F B6 F8 48 8B DA 7F ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 40 0F B6 D7 48 8B CB E8 ? ? ? ? 85 C0 79 ? 48 8B D3 48 8D 0D ? ? ? ? E8 ? ? ? ? 33 C0 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC 48 83 EC"), int,
          void* rcx, const char* modelName, bool bPreload)
{
    try
    {
        // Always skip non-essential model precaching
        if (modelName)
        {
            static auto IsEssentialModel = [](const char* name) -> bool
            {
                if (!name) return false;
                // Core gameplay models that bot logic references
                if (std::strstr(name, "models/player"))   return true;
                if (std::strstr(name, "models/weapons"))  return true;
                if (std::strstr(name, "models/v_models")) return true;
                if (std::strstr(name, "models/w_models")) return true;
                if (std::strstr(name, "models/error.mdl")) return true;
                if (std::strstr(name, "world")) return true; // fallback world boxes
                return false; // dynamic props, physics props, gibs, etc.
            };

            if (!IsEssentialModel(modelName))
            {
                return 0; // Skip dynamic / physics / prop models
            }
        }
        
        return CALL_ORIGINAL(rcx, modelName, bPreload);
    }
    catch (const std::exception& e)
    {
        U::Core.AppendFailText(e.what(), true);
    }
    catch (...)
    {
        U::Core.AppendFailText("Unknown exception in CModelPrecache_PrecacheModel", true);
    }
    return 0;
}

// Hook for sound precaching during map load
MAKE_HOOK(CSoundPrecache_PrecacheSound, U::Signatures.GetEngineSignature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B F2"), int,
          void* rcx, const char* soundName, bool bPreload)
{
    try
    {
        return 0;
    }
    catch (const std::exception& e)
    {
        U::Core.AppendFailText(e.what(), true);
    }
    catch (...)
    {
        U::Core.AppendFailText("Unknown exception in CSoundPrecache_PrecacheSound", true);
    }
    return 0;
}

// Hook for particle system precaching
MAKE_HOOK(CParticleSystemMgr_PrecacheParticleSystem, U::Signatures.GetClientSignature("48 85 D2 74 ? 53 48 83 EC ? 80 3A"), bool,
          void* rcx, const char* particleName)
{
    try
    {
        // Always skip particle precaching
        return true;
        
        return CALL_ORIGINAL(rcx, particleName);
    }
    catch (const std::exception& e)
    {
        U::Core.AppendFailText(e.what(), true);
    }
    catch (...)
    {
        U::Core.AppendFailText("Unknown exception in CParticleSystemMgr_PrecacheParticleSystem", true);
    }
    return false;
}

// Hook for decal precaching
MAKE_HOOK(CDecalPrecache_PrecacheDecal, U::Signatures.GetEngineSignature("48 89 5C 24 ? 57 48 83 EC ? 80 3A ? 41 0F B6 F8 48 8B DA 7F ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 40 0F B6 D7 48 8B CB E8 ? ? ? ? 85 C0 79 ? 48 8B D3 48 8D 0D ? ? ? ? E8 ? ? ? ? 33 C0 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC 48 89 5C 24 ? 57 48 83 EC ? 80 3A ? 41 0F B6 F8 48 8B DA 7F ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 40 0F B6 D7 48 8B CB E8 ? ? ? ? 85 C0 79 ? 48 8B D3 48 8D 0D ? ? ? ? E8 ? ? ? ? 33 C0 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC 48 89 5C 24"), int,
          void* rcx, const char* decalName, bool bPrecache)
{
    try
    {
        // Always skip decal precaching
        return 0;
        
        return CALL_ORIGINAL(rcx, decalName, bPrecache);
    }
    catch (const std::exception& e)
    {
        U::Core.AppendFailText(e.what(), true);
    }
    catch (...)
    {
        U::Core.AppendFailText("Unknown exception in CDecalPrecache_PrecacheDecal", true);
    }
    return 0;
}
