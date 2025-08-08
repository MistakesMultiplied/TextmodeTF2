#pragma once

#include <d3d9.h>
#include <windows.h>
#include <unordered_map>
#include <memory>

// Forward declarations
class StubDirect3D9;
class StubDirect3DDevice9;
class StubDirect3DTexture9;
class StubDirect3DSurface9;
class StubDirect3DVertexBuffer9;
class StubDirect3DIndexBuffer9;
class StubDirect3DVertexDeclaration9;
class StubDirect3DVertexShader9;
class StubDirect3DPixelShader9;
class StubDirect3DStateBlock9;
class StubDirect3DQuery9;

#ifndef HAVE_DETOURS
/*
 * Provide a minimal stub of the Detours API used in DirectXStub.cpp so that we can
 * build without the external Detours library.  The real detours functions are only
 * required when we actually want to patch system DLLs at runtime.  For the purposes
 * of this text-mode stub build they can be replaced with no-op implementations that
 * simply return NO_ERROR.
 */
#define DETOURS_STUB
#include <windows.h>
inline LONG DetourTransactionBegin() { return NO_ERROR; }
inline LONG DetourTransactionCommit() { return NO_ERROR; }
inline LONG DetourUpdateThread(HANDLE) { return NO_ERROR; }
inline LONG DetourAttach(PVOID* /*ppPointer*/, PVOID /*pDetour*/) { return NO_ERROR; }
inline LONG DetourDetach(PVOID* /*ppPointer*/, PVOID /*pDetour*/) { return NO_ERROR; }
#else
#include <detours.h>
#endif

namespace DirectXStub {
    void Initialize();
    void Shutdown();
    bool IsInitialized();
    
    // Hook installation
    bool InstallHooks();
    bool UninstallHooks();
    
    // Original function storage
    extern HMODULE g_hOriginalD3D9;
    extern IDirect3D9* (WINAPI* g_pOriginalDirect3DCreate9)(UINT SDKVersion);
}

// Stub Direct3D9 implementation
class StubDirect3D9 : public IDirect3D9 {
private:
    ULONG m_refCount;
    
public:
    StubDirect3D9();
    virtual ~StubDirect3D9();
    
    // IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) override;
    STDMETHOD_(ULONG, AddRef)() override;
    STDMETHOD_(ULONG, Release)() override;
    
    // IDirect3D9 methods
    STDMETHOD(RegisterSoftwareDevice)(void* pInitializeFunction) override;
    STDMETHOD_(UINT, GetAdapterCount)() override;
    STDMETHOD(GetAdapterIdentifier)(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier) override;
    STDMETHOD_(UINT, GetAdapterModeCount)(UINT Adapter, D3DFORMAT Format) override;
    STDMETHOD(EnumAdapterModes)(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode) override;
    STDMETHOD(GetAdapterDisplayMode)(UINT Adapter, D3DDISPLAYMODE* pMode) override;
    STDMETHOD(CheckDeviceType)(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed) override;
    STDMETHOD(CheckDeviceFormat)(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat) override;
    STDMETHOD(CheckDeviceMultiSampleType)(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels) override;
    STDMETHOD(CheckDepthStencilMatch)(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat) override;
    STDMETHOD(CheckDeviceFormatConversion)(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat) override;
    STDMETHOD(GetDeviceCaps)(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps) override;
    STDMETHOD_(HMONITOR, GetAdapterMonitor)(UINT Adapter) override;
    STDMETHOD(CreateDevice)(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface) override;
};

// Stub Direct3DDevice9 implementation
class StubDirect3DDevice9 : public IDirect3DDevice9 {
private:
    ULONG m_refCount;
    StubDirect3D9* m_pD3D;
    D3DPRESENT_PARAMETERS m_presentParams;
    D3DVIEWPORT9 m_viewport;
    
    // Resource tracking
    std::unordered_map<void*, std::shared_ptr<StubDirect3DTexture9>> m_textures;
    std::unordered_map<void*, std::shared_ptr<StubDirect3DSurface9>> m_surfaces;
    std::unordered_map<void*, std::shared_ptr<StubDirect3DVertexBuffer9>> m_vertexBuffers;
    std::unordered_map<void*, std::shared_ptr<StubDirect3DIndexBuffer9>> m_indexBuffers;
    
public:
    StubDirect3DDevice9(StubDirect3D9* pD3D, const D3DPRESENT_PARAMETERS& presentParams);
    virtual ~StubDirect3DDevice9();
    
    // IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) override;
    STDMETHOD_(ULONG, AddRef)() override;
    STDMETHOD_(ULONG, Release)() override;
    
    // IDirect3DDevice9 methods - Core
    STDMETHOD(TestCooperativeLevel)() override;
    STDMETHOD_(UINT, GetAvailableTextureMem)() override;
    STDMETHOD(EvictManagedResources)() override;
    STDMETHOD(GetDirect3D)(IDirect3D9** ppD3D9) override;
    STDMETHOD(GetDeviceCaps)(D3DCAPS9* pCaps) override;
    STDMETHOD(GetDisplayMode)(UINT iSwapChain, D3DDISPLAYMODE* pMode) override;
    STDMETHOD(GetCreationParameters)(D3DDEVICE_CREATION_PARAMETERS* pParameters) override;
    
    // Cursor methods
    STDMETHOD(SetCursorProperties)(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap) override;
    STDMETHOD_(void, SetCursorPosition)(int X, int Y, DWORD Flags) override;
    STDMETHOD_(BOOL, ShowCursor)(BOOL bShow) override;
    
    // Swap chain methods
    STDMETHOD(CreateAdditionalSwapChain)(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain) override;
    STDMETHOD(GetSwapChain)(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain) override;
    STDMETHOD_(UINT, GetNumberOfSwapChains)() override;
    STDMETHOD(Reset)(D3DPRESENT_PARAMETERS* pPresentationParameters) override;
    STDMETHOD(Present)(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion) override;
    
    // Back buffer methods
    STDMETHOD(GetBackBuffer)(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer) override;
    STDMETHOD(GetRasterStatus)(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus) override;
    STDMETHOD(SetDialogBoxMode)(BOOL bEnableDialogs) override;
    STDMETHOD_(void, SetGammaRamp)(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP* pRamp) override;
    STDMETHOD_(void, GetGammaRamp)(UINT iSwapChain, D3DGAMMARAMP* pRamp) override;
    
    // Resource creation methods
    STDMETHOD(CreateTexture)(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle) override;
    STDMETHOD(CreateVolumeTexture)(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle) override;
    STDMETHOD(CreateCubeTexture)(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle) override;
    STDMETHOD(CreateVertexBuffer)(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle) override;
    STDMETHOD(CreateIndexBuffer)(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle) override;
    STDMETHOD(CreateRenderTarget)(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) override;
    STDMETHOD(CreateDepthStencilSurface)(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) override;
    STDMETHOD(UpdateSurface)(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, const POINT* pDestPoint) override;
    STDMETHOD(UpdateTexture)(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture) override;
    STDMETHOD(GetRenderTargetData)(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface) override;
    STDMETHOD(GetFrontBufferData)(UINT iSwapChain, IDirect3DSurface9* pDestSurface) override;
    STDMETHOD(StretchRect)(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter) override;
    STDMETHOD(ColorFill)(IDirect3DSurface9* pSurface, const RECT* pRect, D3DCOLOR color) override;
    STDMETHOD(CreateOffscreenPlainSurface)(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) override;
    
    // Render target methods
    STDMETHOD(SetRenderTarget)(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget) override;
    STDMETHOD(GetRenderTarget)(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget) override;
    STDMETHOD(SetDepthStencilSurface)(IDirect3DSurface9* pNewZStencil) override;
    STDMETHOD(GetDepthStencilSurface)(IDirect3DSurface9** ppZStencilSurface) override;
    
    // Scene methods
    STDMETHOD(BeginScene)() override;
    STDMETHOD(EndScene)() override;
    STDMETHOD(Clear)(DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) override;
    
    // Transform methods
    STDMETHOD(SetTransform)(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix) override;
    STDMETHOD(GetTransform)(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) override;
    STDMETHOD(MultiplyTransform)(D3DTRANSFORMSTATETYPE, const D3DMATRIX*) override;
    
    // Viewport methods
    STDMETHOD(SetViewport)(const D3DVIEWPORT9* pViewport) override;
    STDMETHOD(GetViewport)(D3DVIEWPORT9* pViewport) override;
    
    // Material methods
    STDMETHOD(SetMaterial)(const D3DMATERIAL9* pMaterial) override;
    STDMETHOD(GetMaterial)(D3DMATERIAL9* pMaterial) override;
    
    // Light methods
    STDMETHOD(SetLight)(DWORD Index, const D3DLIGHT9*) override;
    STDMETHOD(GetLight)(DWORD Index, D3DLIGHT9*) override;
    STDMETHOD(LightEnable)(DWORD Index, BOOL Enable) override;
    STDMETHOD(GetLightEnable)(DWORD Index, BOOL* pEnable) override;
    
    // Clip plane methods
    STDMETHOD(SetClipPlane)(DWORD Index, const float* pPlane) override;
    STDMETHOD(GetClipPlane)(DWORD Index, float* pPlane) override;
    
    // Render state methods
    STDMETHOD(SetRenderState)(D3DRENDERSTATETYPE State, DWORD Value) override;
    STDMETHOD(GetRenderState)(D3DRENDERSTATETYPE State, DWORD* pValue) override;
    
    // State block methods
    STDMETHOD(CreateStateBlock)(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB) override;
    STDMETHOD(BeginStateBlock)() override;
    STDMETHOD(EndStateBlock)(IDirect3DStateBlock9** ppSB) override;
    
    // Texture stage state methods
    STDMETHOD(SetTextureStageState)(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) override;
    STDMETHOD(GetTextureStageState)(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue) override;
    
    // Sampler state methods
    STDMETHOD(SetSamplerState)(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) override;
    STDMETHOD(GetSamplerState)(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue) override;
    
    // Validation methods
    STDMETHOD(ValidateDevice)(DWORD* pNumPasses) override;

    // Missing clip / patch APIs so the class is concrete
    STDMETHOD(SetClipStatus)(const D3DCLIPSTATUS9* pClipStatus) override;
    STDMETHOD(GetClipStatus)(D3DCLIPSTATUS9* pClipStatus) override;
    STDMETHOD(DrawRectPatch)(UINT Handle, const float* pNumSegs, const D3DRECTPATCH_INFO* pRectPatchInfo) override;
    STDMETHOD(DrawTriPatch)(UINT Handle, const float* pNumSegs, const D3DTRIPATCH_INFO* pTriPatchInfo) override;
    STDMETHOD(DeletePatch)(UINT Handle) override;
    
    // Palette methods
    STDMETHOD(SetPaletteEntries)(UINT PaletteNumber, const PALETTEENTRY* pEntries) override;
    STDMETHOD(GetPaletteEntries)(UINT PaletteNumber, PALETTEENTRY* pEntries) override;
    STDMETHOD(SetCurrentTexturePalette)(UINT PaletteNumber) override;
    STDMETHOD(GetCurrentTexturePalette)(UINT *PaletteNumber) override;
    
    // Scissor rect methods
    STDMETHOD(SetScissorRect)(const RECT* pRect) override;
    STDMETHOD(GetScissorRect)(RECT* pRect) override;
    
    // Software vertex processing methods
    STDMETHOD(SetSoftwareVertexProcessing)(BOOL bSoftware) override;
    STDMETHOD_(BOOL, GetSoftwareVertexProcessing)() override;
    
    // N-patches methods
    STDMETHOD(SetNPatchMode)(float nSegments) override;
    STDMETHOD_(float, GetNPatchMode)() override;
    
    // Drawing methods
    STDMETHOD(DrawPrimitive)(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) override;
    STDMETHOD(DrawIndexedPrimitive)(D3DPRIMITIVETYPE, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) override;
    STDMETHOD(DrawPrimitiveUP)(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride) override;
    STDMETHOD(DrawIndexedPrimitiveUP)(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride) override;
    
    // Pixel/vertex shader methods
    STDMETHOD(ProcessVertices)(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags) override;
    STDMETHOD(CreateVertexDeclaration)(const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl) override;
    STDMETHOD(SetVertexDeclaration)(IDirect3DVertexDeclaration9* pDecl) override;
    STDMETHOD(GetVertexDeclaration)(IDirect3DVertexDeclaration9** ppDecl) override;
    STDMETHOD(SetFVF)(DWORD FVF) override;
    STDMETHOD(GetFVF)(DWORD* pFVF) override;
    STDMETHOD(CreateVertexShader)(const DWORD* pFunction, IDirect3DVertexShader9** ppShader) override;
    STDMETHOD(SetVertexShader)(IDirect3DVertexShader9* pShader) override;
    STDMETHOD(GetVertexShader)(IDirect3DVertexShader9** ppShader) override;
    STDMETHOD(SetVertexShaderConstantF)(UINT StartRegister, const float* pConstantData, UINT Vector4fCount) override;
    STDMETHOD(GetVertexShaderConstantF)(UINT StartRegister, float* pConstantData, UINT Vector4fCount) override;
    STDMETHOD(SetVertexShaderConstantI)(UINT StartRegister, const int* pConstantData, UINT Vector4iCount) override;
    STDMETHOD(GetVertexShaderConstantI)(UINT StartRegister, int* pConstantData, UINT Vector4iCount) override;
    STDMETHOD(SetVertexShaderConstantB)(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount) override;
    STDMETHOD(GetVertexShaderConstantB)(UINT StartRegister, BOOL* pConstantData, UINT BoolCount) override;
    STDMETHOD(CreatePixelShader)(const DWORD* pFunction, IDirect3DPixelShader9** ppShader) override;
    STDMETHOD(SetPixelShader)(IDirect3DPixelShader9* pShader) override;
    STDMETHOD(GetPixelShader)(IDirect3DPixelShader9** ppShader) override;
    STDMETHOD(SetPixelShaderConstantF)(UINT StartRegister, const float* pConstantData, UINT Vector4fCount) override;
    STDMETHOD(GetPixelShaderConstantF)(UINT StartRegister, float* pConstantData, UINT Vector4fCount) override;
    STDMETHOD(SetPixelShaderConstantI)(UINT StartRegister, const int* pConstantData, UINT Vector4iCount) override;
    STDMETHOD(GetPixelShaderConstantI)(UINT StartRegister, int* pConstantData, UINT Vector4iCount) override;
    STDMETHOD(SetPixelShaderConstantB)(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount) override;
    STDMETHOD(GetPixelShaderConstantB)(UINT StartRegister, BOOL* pConstantData, UINT BoolCount) override;
    
    // Stream source methods
    STDMETHOD(SetStreamSource)(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride) override;
    STDMETHOD(GetStreamSource)(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride) override;
    STDMETHOD(SetStreamSourceFreq)(UINT StreamNumber, UINT Setting) override;
    STDMETHOD(GetStreamSourceFreq)(UINT StreamNumber, UINT* pSetting) override;
    STDMETHOD(SetIndices)(IDirect3DIndexBuffer9* pIndexData) override;
    STDMETHOD(GetIndices)(IDirect3DIndexBuffer9** ppIndexData) override;
    
    // Texture methods
    STDMETHOD(SetTexture)(DWORD Stage, IDirect3DBaseTexture9* pTexture) override;
    STDMETHOD(GetTexture)(DWORD Stage, IDirect3DBaseTexture9** ppTexture) override;
    
    // Query methods
    STDMETHOD(CreateQuery)(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery) override;
};

// Minimal stub implementations for other interfaces
class StubDirect3DTexture9 : public IDirect3DTexture9 {
private:
    ULONG m_refCount;
    UINT m_width, m_height, m_levels;
    DWORD m_usage;
    D3DFORMAT m_format;
    D3DPOOL m_pool;
    
public:
    StubDirect3DTexture9(UINT width, UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool);
    virtual ~StubDirect3DTexture9();
    
    // IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) override;
    STDMETHOD_(ULONG, AddRef)() override;
    STDMETHOD_(ULONG, Release)() override;
    
    // IDirect3DResource9 methods
    STDMETHOD(GetDevice)(IDirect3DDevice9** ppDevice) override;
    STDMETHOD(SetPrivateData)(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags) override;
    STDMETHOD(GetPrivateData)(REFGUID refguid, void* pData, DWORD* pSizeOfData) override;
    STDMETHOD(FreePrivateData)(REFGUID refguid) override;
    STDMETHOD_(DWORD, SetPriority)(DWORD PriorityNew) override;
    STDMETHOD_(DWORD, GetPriority)() override;
    STDMETHOD_(void, PreLoad)() override;
    STDMETHOD_(D3DRESOURCETYPE, GetType)() override;
    
    // IDirect3DBaseTexture9 methods
    STDMETHOD_(DWORD, SetLOD)(DWORD LODNew) override;
    STDMETHOD_(DWORD, GetLOD)() override;
    STDMETHOD_(DWORD, GetLevelCount)() override;
    STDMETHOD(SetAutoGenFilterType)(D3DTEXTUREFILTERTYPE FilterType) override;
    STDMETHOD_(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)() override;
    STDMETHOD_(void, GenerateMipSubLevels)() override;
    
    // IDirect3DTexture9 methods
    STDMETHOD(GetLevelDesc)(UINT Level, D3DSURFACE_DESC* pDesc) override;
    STDMETHOD(GetSurfaceLevel)(UINT Level, IDirect3DSurface9** ppSurfaceLevel) override;
    STDMETHOD(LockRect)(UINT Level, D3DLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags) override;
    STDMETHOD(UnlockRect)(UINT Level) override;
    STDMETHOD(AddDirtyRect)(const RECT* pDirtyRect) override;
};

// Additional stub classes would be implemented similarly...
class StubDirect3DSurface9 : public IDirect3DSurface9 {
private:
    ULONG m_refCount;
    UINT m_width, m_height;
    D3DFORMAT m_format;
    D3DMULTISAMPLE_TYPE m_multiSampleType;
    DWORD m_multiSampleQuality;
    
public:
    StubDirect3DSurface9(UINT width, UINT height, D3DFORMAT format, D3DMULTISAMPLE_TYPE multiSampleType, DWORD multiSampleQuality);
    virtual ~StubDirect3DSurface9();
    
    // IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) override;
    STDMETHOD_(ULONG, AddRef)() override;
    STDMETHOD_(ULONG, Release)() override;
    
    // IDirect3DResource9 methods
    STDMETHOD(GetDevice)(IDirect3DDevice9** ppDevice) override;
    STDMETHOD(SetPrivateData)(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags) override;
    STDMETHOD(GetPrivateData)(REFGUID refguid, void* pData, DWORD* pSizeOfData) override;
    STDMETHOD(FreePrivateData)(REFGUID refguid) override;
    STDMETHOD_(DWORD, SetPriority)(DWORD PriorityNew) override;
    STDMETHOD_(DWORD, GetPriority)() override;
    STDMETHOD_(void, PreLoad)() override;
    STDMETHOD_(D3DRESOURCETYPE, GetType)() override;
    
    // IDirect3DSurface9 methods
    STDMETHOD(GetContainer)(REFIID riid, void** ppContainer) override;
    STDMETHOD(GetDesc)(D3DSURFACE_DESC* pDesc) override;
    STDMETHOD(LockRect)(D3DLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags) override;
    STDMETHOD(UnlockRect)() override;
    STDMETHOD(GetDC)(HDC* phdc) override;
    STDMETHOD(ReleaseDC)(HDC hdc) override;
};

// Additional stub classes for vertex buffers, index buffers, etc.
class StubDirect3DVertexBuffer9 : public IDirect3DVertexBuffer9 {
private:
    ULONG m_refCount;
    UINT m_length;
    DWORD m_usage;
    DWORD m_fvf;
    D3DPOOL m_pool;
    
public:
    StubDirect3DVertexBuffer9(UINT length, DWORD usage, DWORD fvf, D3DPOOL pool);
    virtual ~StubDirect3DVertexBuffer9();
    
    // IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) override;
    STDMETHOD_(ULONG, AddRef)() override;
    STDMETHOD_(ULONG, Release)() override;
    
    // IDirect3DResource9 methods
    STDMETHOD(GetDevice)(IDirect3DDevice9** ppDevice) override;
    STDMETHOD(SetPrivateData)(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags) override;
    STDMETHOD(GetPrivateData)(REFGUID refguid, void* pData, DWORD* pSizeOfData) override;
    STDMETHOD(FreePrivateData)(REFGUID refguid) override;
    STDMETHOD_(DWORD, SetPriority)(DWORD PriorityNew) override;
    STDMETHOD_(DWORD, GetPriority)() override;
    STDMETHOD_(void, PreLoad)() override;
    STDMETHOD_(D3DRESOURCETYPE, GetType)() override;
    
    // IDirect3DVertexBuffer9 methods
    STDMETHOD(Lock)(UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags) override;
    STDMETHOD(Unlock)() override;
    STDMETHOD(GetDesc)(D3DVERTEXBUFFER_DESC* pDesc) override;
};

class StubDirect3DIndexBuffer9 : public IDirect3DIndexBuffer9 {
private:
    ULONG m_refCount;
    UINT m_length;
    DWORD m_usage;
    D3DFORMAT m_format;
    D3DPOOL m_pool;
    
public:
    StubDirect3DIndexBuffer9(UINT length, DWORD usage, D3DFORMAT format, D3DPOOL pool);
    virtual ~StubDirect3DIndexBuffer9();
    
    // IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) override;
    STDMETHOD_(ULONG, AddRef)() override;
    STDMETHOD_(ULONG, Release)() override;
    
    // IDirect3DResource9 methods
    STDMETHOD(GetDevice)(IDirect3DDevice9** ppDevice) override;
    STDMETHOD(SetPrivateData)(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags) override;
    STDMETHOD(GetPrivateData)(REFGUID refguid, void* pData, DWORD* pSizeOfData) override;
    STDMETHOD(FreePrivateData)(REFGUID refguid) override;
    STDMETHOD_(DWORD, SetPriority)(DWORD PriorityNew) override;
    STDMETHOD_(DWORD, GetPriority)() override;
    STDMETHOD_(void, PreLoad)() override;
    STDMETHOD_(D3DRESOURCETYPE, GetType)() override;
    
    // IDirect3DIndexBuffer9 methods
    STDMETHOD(Lock)(UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags) override;
    STDMETHOD(Unlock)() override;
    STDMETHOD(GetDesc)(D3DINDEXBUFFER_DESC* pDesc) override;
}; 