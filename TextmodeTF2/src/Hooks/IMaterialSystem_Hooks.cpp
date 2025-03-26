#include "../SDK/SDK.h"

MAKE_SIGNATURE(IMaterialSystem_CreateMaterial, "materialsystem.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B C2", 0x0)
MAKE_SIGNATURE(IMaterialSystem_FindMaterial, "materialsystem.dll", "48 83 EC ? 48 8B 44 24 ? 4C 8B 11", 0x0)
MAKE_SIGNATURE(IMaterialSystem_FindTexture, "materialsystem.dll", "40 55 57 41 55", 0x0)
MAKE_SIGNATURE(IMaterialSystem_NextMaterial, "materialsystem.dll", "48 81 C1 ? ? ? ? E9 ? ? ? ? CC CC CC CC 89 15", 0x0)
MAKE_SIGNATURE(IMaterialSystem_CreateProceduralTexture, "materialsystem.dll", "48 83 EC ? 8B 84 24 ? ? ? ? 48 8B 0D", 0x0)
MAKE_SIGNATURE(IMaterialSystem_CreateRenderTargetTexture, "materialsystem.dll", "48 83 EC ? 8B 84 24 ? ? ? ? 4C 8B 11", 0x0)
MAKE_SIGNATURE(IMaterialSystem_CreateNamedRenderTargetTextureEx, "materialsystem.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 8B 9C 24", 0x0)
MAKE_SIGNATURE(IMaterialSystem_CreateNamedRenderTargetTexture, "materialsystem.dll", "44 0F B6 54 24 ? 4C 8B 19", 0x0)
MAKE_SIGNATURE(IMaterialSystem_CreateNamedRenderTargetTextureEx2, "materialsystem.dll", "48 83 EC ? 80 B9 ? ? ? ? ? 75", 0x0)
MAKE_SIGNATURE(IMaterialSystem_SwapBuffers, "materialsystem.dll", "4C 8B DC 49 89 5B ? 49 89 6B ? 49 89 73 ? 57 41 54 41 57", 0x0)

// NOT USED
MAKE_HOOK(IMaterialSystem_CreateMaterial, S::IMaterialSystem_CreateMaterial(), IMaterial*, // 70
		  void* rcx, const char* pMaterialName, KeyValues* pVMTKeyValues)
{
	static IMaterial* st;
	if (!st)
		st = CALL_ORIGINAL(rcx, pMaterialName, pVMTKeyValues);
	return st;
}

// NOT USED
MAKE_HOOK(IMaterialSystem_CreateProceduralTexture, S::IMaterialSystem_CreateProceduralTexture(), ITexture*,
		  void* rcx, const char* pTextureName, const char* pTextureGroupName, int w, int h, ImageFormat fmt, int nFlags) // 81
{
	static ITexture* st;
	if (!st)
		st = CALL_ORIGINAL(rcx, pTextureName, pTextureGroupName, w, h, fmt, nFlags);
	return st;
}

// NOT USED
MAKE_HOOK(IMaterialSystem_FindMaterial, S::IMaterialSystem_FindMaterial(), IMaterial*, // 70
		  void* rcx, char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix)
{
	static IMaterial* st = CALL_ORIGINAL(rcx, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	return st;
}

// NOT USED
MAKE_HOOK(IMaterialSystem_FindTexture, S::IMaterialSystem_FindTexture(), ITexture*,
		  void* rcx, char const* pTextureName, const char* pTextureGroupName, bool complain, int nAdditionalCreationFlags) // 81
{
	static ITexture* st = CALL_ORIGINAL(rcx, pTextureName, pTextureGroupName, complain, nAdditionalCreationFlags);
	return st;
}

// NOT USED
MAKE_HOOK(IMaterialSystem_NextMaterial, S::IMaterialSystem_NextMaterial(), __int64,
		  void* rcx)
{
	*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(rcx) + 0x358) = -1;
	return CALL_ORIGINAL(rcx);
}

MAKE_HOOK(IMaterialSystem_CreateRenderTargetTexture, S::IMaterialSystem_CreateRenderTargetTexture(), ITexture*, // 84
		  void* rcx, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat	format, MaterialRenderTargetDepth_t depth)
{
	return CALL_ORIGINAL(rcx, 0, 0, sizeMode, format, depth);
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx, S::IMaterialSystem_CreateNamedRenderTargetTextureEx(), ITexture*, // 85
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
	return CALL_ORIGINAL(rcx, pRTName, 0, 0, sizeMode, format, depth, textureFlags, renderTargetFlags);
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTexture, S::IMaterialSystem_CreateNamedRenderTargetTexture(), ITexture*, // 86
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, bool bClampTexCoords, bool bAutoMipMap)
{
	return CALL_ORIGINAL(rcx, pRTName, 0, 0, sizeMode, format, depth, bClampTexCoords, bAutoMipMap);
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx2, S::IMaterialSystem_CreateNamedRenderTargetTextureEx2(), ITexture*, // 87
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
	return CALL_ORIGINAL(rcx, pRTName, 0, 0, sizeMode, format, depth, textureFlags, renderTargetFlags);
}

MAKE_HOOK(IMaterialSystem_SwapBuffers, S::IMaterialSystem_SwapBuffers(), void,
		  void* rcx)
{
	return;
}