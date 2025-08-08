#include "../SDK/SDK.h"
#include "../Core/Core.h"

MAKE_HOOK(IMaterialSystem_SwapBuffers, U::Memory.GetVFunc(I::MaterialSystem, 40), void, // 40
		  void* rcx)
{
	try
	{
		return;
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in IMaterialSystem_SwapBuffers", true);
	}
}

MAKE_HOOK(IMaterialSystem_CreateRenderTargetTexture, U::Memory.GetVFunc(I::MaterialSystem, 84), ITexture*, // 84
		  void* rcx, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat	format, MaterialRenderTargetDepth_t depth)
{
	try
	{
		// Use a minimal but valid 1x1 target to keep the engine happy while still
		// avoiding large memory allocations. Using 0 would cause shaderapidx9
		// to attempt to create a zero-sized texture which crashes in text-mode.
		return CALL_ORIGINAL(rcx, 1, 1, sizeMode, format, depth);
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in IMaterialSystem_CreateRenderTargetTexture", true);
	}
	return nullptr;
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx, U::Memory.GetVFunc(I::MaterialSystem, 85), ITexture*, // 85
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
	try
	{
		return CALL_ORIGINAL(rcx, pRTName, 1, 1, sizeMode, format, depth, textureFlags, renderTargetFlags);
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in IMaterialSystem_CreateNamedRenderTargetTextureEx", true);
	}
	return nullptr;
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTexture, U::Memory.GetVFunc(I::MaterialSystem, 86), ITexture*, // 86
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, bool bClampTexCoords, bool bAutoMipMap)
{
	try
	{
		return CALL_ORIGINAL(rcx, pRTName, 1, 1, sizeMode, format, depth, bClampTexCoords, bAutoMipMap);
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in IMaterialSystem_CreateNamedRenderTargetTexture", true);
	}
	return nullptr;
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx2, U::Memory.GetVFunc(I::MaterialSystem, 87), ITexture*, // 87
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
	try
	{
		return CALL_ORIGINAL(rcx, pRTName, 1, 1, sizeMode, format, depth, textureFlags, renderTargetFlags);
	}
	catch (const std::exception& e)
	{
		U::Core.AppendFailText(e.what(), true);
	}
	catch (...)
	{
		U::Core.AppendFailText("Unknown exception in IMaterialSystem_CreateNamedRenderTargetTextureEx2", true);
	}
	return nullptr;
}
