#include "DirectXStub.h"
#include <iostream>

// Resource creation methods
STDMETHODIMP StubDirect3DDevice9::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle) {
    if (!ppTexture) return D3DERR_INVALIDCALL;
    
    // Create our stub texture
    StubDirect3DTexture9* pStubTexture = new StubDirect3DTexture9(Width, Height, Levels, Usage, Format, Pool);
    *ppTexture = pStubTexture;
    
    // Store reference for tracking
    m_textures[pStubTexture] = std::shared_ptr<StubDirect3DTexture9>(pStubTexture);
    
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle) {
    if (!ppVertexBuffer) return D3DERR_INVALIDCALL;
    
    // Create our stub vertex buffer
    StubDirect3DVertexBuffer9* pStubBuffer = new StubDirect3DVertexBuffer9(Length, Usage, FVF, Pool);
    *ppVertexBuffer = pStubBuffer;
    
    // Store reference for tracking
    m_vertexBuffers[pStubBuffer] = std::shared_ptr<StubDirect3DVertexBuffer9>(pStubBuffer);
    
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle) {
    if (!ppIndexBuffer) return D3DERR_INVALIDCALL;
    
    // Create our stub index buffer
    StubDirect3DIndexBuffer9* pStubBuffer = new StubDirect3DIndexBuffer9(Length, Usage, Format, Pool);
    *ppIndexBuffer = pStubBuffer;
    
    // Store reference for tracking
    m_indexBuffers[pStubBuffer] = std::shared_ptr<StubDirect3DIndexBuffer9>(pStubBuffer);
    
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) {
    if (!ppSurface) return D3DERR_INVALIDCALL;
    
    // Create our stub surface
    StubDirect3DSurface9* pStubSurface = new StubDirect3DSurface9(Width, Height, Format, MultiSample, MultisampleQuality);
    *ppSurface = pStubSurface;
    
    // Store reference for tracking
    m_surfaces[pStubSurface] = std::shared_ptr<StubDirect3DSurface9>(pStubSurface);
    
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) {
    if (!ppSurface) return D3DERR_INVALIDCALL;
    
    // Create our stub surface
    StubDirect3DSurface9* pStubSurface = new StubDirect3DSurface9(Width, Height, Format, MultiSample, MultisampleQuality);
    *ppSurface = pStubSurface;
    
    // Store reference for tracking
    m_surfaces[pStubSurface] = std::shared_ptr<StubDirect3DSurface9>(pStubSurface);
    
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) {
    if (!ppSurface) return D3DERR_INVALIDCALL;
    
    // Create our stub surface
    StubDirect3DSurface9* pStubSurface = new StubDirect3DSurface9(Width, Height, Format, D3DMULTISAMPLE_NONE, 0);
    *ppSurface = pStubSurface;
    
    // Store reference for tracking
    m_surfaces[pStubSurface] = std::shared_ptr<StubDirect3DSurface9>(pStubSurface);
    
    return D3D_OK;
}

// Texture/Surface methods
STDMETHODIMP StubDirect3DDevice9::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture) {
    if (!ppTexture) return D3DERR_INVALIDCALL;
    *ppTexture = nullptr;
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget) {
    if (!ppRenderTarget) return D3DERR_INVALIDCALL;
    *ppRenderTarget = nullptr;
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface) {
    if (!ppZStencilSurface) return D3DERR_INVALIDCALL;
    *ppZStencilSurface = nullptr;
    return D3D_OK;
}

// Stream source methods
STDMETHODIMP StubDirect3DDevice9::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride) {
    if (!ppStreamData) return D3DERR_INVALIDCALL;
    *ppStreamData = nullptr;
    if (pOffsetInBytes) *pOffsetInBytes = 0;
    if (pStride) *pStride = 0;
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9* pIndexData) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9** ppIndexData) {
    if (!ppIndexData) return D3DERR_INVALIDCALL;
    *ppIndexData = nullptr;
    return D3D_OK;
}

// Back buffer methods
STDMETHODIMP StubDirect3DDevice9::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer) {
    if (iSwapChain != 0 || iBackBuffer != 0 || !ppBackBuffer) return D3DERR_INVALIDCALL;
    
    // Create a dummy back buffer surface
    StubDirect3DSurface9* pBackBuffer = new StubDirect3DSurface9(
        m_presentParams.BackBufferWidth,
        m_presentParams.BackBufferHeight,
        m_presentParams.BackBufferFormat,
        m_presentParams.MultiSampleType,
        m_presentParams.MultiSampleQuality
    );
    
    *ppBackBuffer = pBackBuffer;
    
    return D3D_OK;
}

// Stub methods that don't need implementation
STDMETHODIMP StubDirect3DDevice9::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap) { return D3D_OK; }
STDMETHODIMP_(void) StubDirect3DDevice9::SetCursorPosition(int X, int Y, DWORD Flags) { }
STDMETHODIMP_(BOOL) StubDirect3DDevice9::ShowCursor(BOOL bShow) { return FALSE; }
STDMETHODIMP StubDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain) { return D3DERR_INVALIDCALL; }
STDMETHODIMP_(UINT) StubDirect3DDevice9::GetNumberOfSwapChains() { return 1; }
STDMETHODIMP StubDirect3DDevice9::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::SetDialogBoxMode(BOOL bEnableDialogs) { return D3D_OK; }
STDMETHODIMP_(void) StubDirect3DDevice9::SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP* pRamp) { }
STDMETHODIMP_(void) StubDirect3DDevice9::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp) { }
STDMETHODIMP StubDirect3DDevice9::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::UpdateSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, const POINT* pDestPoint) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::StretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::ColorFill(IDirect3DSurface9* pSurface, const RECT* pRect, D3DCOLOR color) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetMaterial(const D3DMATERIAL9* pMaterial) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetMaterial(D3DMATERIAL9* pMaterial) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetLight(DWORD Index, const D3DLIGHT9* pLight) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetLight(DWORD Index, D3DLIGHT9* pLight) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::LightEnable(DWORD Index, BOOL Enable) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetLightEnable(DWORD Index, BOOL* pEnable) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetClipPlane(DWORD Index, const float* pPlane) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetClipPlane(DWORD Index, float* pPlane) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::BeginStateBlock() { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9** ppSB) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue) { if (pValue) *pValue = 0; return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue) { if (pValue) *pValue = 0; return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY* pEntries) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetCurrentTexturePalette(UINT* PaletteNumber) { if (PaletteNumber) *PaletteNumber = 0; return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetScissorRect(const RECT* pRect) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetScissorRect(RECT* pRect) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetSoftwareVertexProcessing(BOOL bSoftware) { return D3D_OK; }
STDMETHODIMP_(BOOL) StubDirect3DDevice9::GetSoftwareVertexProcessing() { return FALSE; }
STDMETHODIMP StubDirect3DDevice9::SetNPatchMode(float nSegments) { return D3D_OK; }
STDMETHODIMP_(float) StubDirect3DDevice9::GetNPatchMode() { return 0.0f; }
STDMETHODIMP StubDirect3DDevice9::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::CreateVertexDeclaration(const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::SetFVF(DWORD FVF) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetFVF(DWORD* pFVF) { if (pFVF) *pFVF = 0; return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::CreateVertexShader(const DWORD* pFunction, IDirect3DVertexShader9** ppShader) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9** ppShader) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::CreatePixelShader(const DWORD* pFunction, IDirect3DPixelShader9** ppShader) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9** ppShader) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetPixelShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetPixelShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::SetStreamSourceFreq(UINT StreamNumber, UINT Setting) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetStreamSourceFreq(UINT StreamNumber, UINT* pSetting) { if (pSetting) *pSetting = 1; return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery) { return D3DERR_INVALIDCALL; } 