#include "DirectXStub.h"
#include <iostream>

StubDirect3D9::StubDirect3D9() : m_refCount(1) {
    // Initialize stub D3D9 object
}

StubDirect3D9::~StubDirect3D9() {
    // Cleanup
}

// IUnknown methods
STDMETHODIMP StubDirect3D9::QueryInterface(REFIID riid, void** ppvObject) {
    if (riid == IID_IUnknown || riid == IID_IDirect3D9) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) StubDirect3D9::AddRef() {
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) StubDirect3D9::Release() {
    ULONG count = --m_refCount;
    if (count == 0) {
        delete this;
    }
    return count;
}

// IDirect3D9 methods
STDMETHODIMP StubDirect3D9::RegisterSoftwareDevice(void* pInitializeFunction) {
    return D3D_OK;
}

STDMETHODIMP_(UINT) StubDirect3D9::GetAdapterCount() {
    return 1; // Always return 1 adapter
}

STDMETHODIMP StubDirect3D9::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier) {
    if (Adapter != 0 || !pIdentifier) return D3DERR_INVALIDCALL;
    
    // Fill with dummy data
    strcpy_s(pIdentifier->Driver, "Amalgam Stub Driver");
    strcpy_s(pIdentifier->Description, "Amalgam DirectX Stub Adapter");
    strcpy_s(pIdentifier->DeviceName, "\\\\.\\DISPLAY1");
    pIdentifier->DriverVersion.QuadPart = 0x0001000000000000;
    pIdentifier->VendorId = 0x10DE; // NVIDIA
    pIdentifier->DeviceId = 0x1234; // Fake device ID
    pIdentifier->SubSysId = 0x0000;
    pIdentifier->Revision = 0x00;
    pIdentifier->DeviceIdentifier = { 0 };
    pIdentifier->WHQLLevel = 1;
    
    return D3D_OK;
}

STDMETHODIMP_(UINT) StubDirect3D9::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format) {
    if (Adapter != 0) return 0;
    return 1; // Return 1 mode
}

STDMETHODIMP StubDirect3D9::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode) {
    if (Adapter != 0 || Mode != 0 || !pMode) return D3DERR_INVALIDCALL;
    
    // Return a dummy display mode
    pMode->Width = 800;
    pMode->Height = 600;
    pMode->RefreshRate = 60;
    pMode->Format = D3DFMT_X8R8G8B8;
    
    return D3D_OK;
}

STDMETHODIMP StubDirect3D9::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode) {
    if (Adapter != 0 || !pMode) return D3DERR_INVALIDCALL;
    
    // Return current display mode
    pMode->Width = 1;
    pMode->Height = 480;
    pMode->RefreshRate = 1;
    pMode->Format = D3DFMT_X8R8G8B8;
    
    return D3D_OK;
}

STDMETHODIMP StubDirect3D9::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed) {
    if (Adapter != 0) return D3DERR_INVALIDCALL;
    return D3D_OK; // Always succeed
}

STDMETHODIMP StubDirect3D9::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat) {
    if (Adapter != 0) return D3DERR_INVALIDCALL;
    return D3D_OK; // Always succeed
}

STDMETHODIMP StubDirect3D9::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels) {
    if (Adapter != 0) return D3DERR_INVALIDCALL;
    if (pQualityLevels) *pQualityLevels = 0;
    return D3D_OK;
}

STDMETHODIMP StubDirect3D9::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat) {
    if (Adapter != 0) return D3DERR_INVALIDCALL;
    return D3D_OK;
}

STDMETHODIMP StubDirect3D9::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat) {
    if (Adapter != 0) return D3DERR_INVALIDCALL;
    return D3D_OK;
}

STDMETHODIMP StubDirect3D9::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps) {
    if (Adapter != 0 || !pCaps) return D3DERR_INVALIDCALL;
    
    // Fill with minimal caps
    ZeroMemory(pCaps, sizeof(D3DCAPS9));
    pCaps->DeviceType = D3DDEVTYPE_HAL;
    pCaps->AdapterOrdinal = 0;
    pCaps->Caps = D3DCAPS_READ_SCANLINE;
    pCaps->PresentationIntervals = D3DPRESENT_INTERVAL_DEFAULT;
    pCaps->CursorCaps = D3DCURSORCAPS_COLOR | D3DCURSORCAPS_LOWRES;
    pCaps->DevCaps = D3DDEVCAPS_EXECUTESYSTEMMEMORY | D3DDEVCAPS_EXECUTEVIDEOMEMORY;
    pCaps->RasterCaps = D3DPRASTERCAPS_DITHER | D3DPRASTERCAPS_COLORPERSPECTIVE;
    pCaps->MaxTextureWidth = 2048;
    pCaps->MaxTextureHeight = 2048;
    pCaps->MaxVolumeExtent = 256;
    pCaps->MaxTextureRepeat = 2048;
    pCaps->MaxTextureAspectRatio = 2048;
    pCaps->MaxAnisotropy = 16;
    pCaps->MaxVertexW = 1e10f;
    pCaps->GuardBandLeft = -1e9f;
    pCaps->GuardBandTop = -1e9f;
    pCaps->GuardBandRight = 1e9f;
    pCaps->GuardBandBottom = 1e9f;
    pCaps->ExtentsAdjust = 0.0f;
    pCaps->MaxTextureBlendStages = 8;
    pCaps->MaxSimultaneousTextures = 8;
    pCaps->VertexProcessingCaps = D3DVTXPCAPS_DIRECTIONALLIGHTS | D3DVTXPCAPS_POSITIONALLIGHTS;
    pCaps->MaxActiveLights = 8;
    pCaps->MaxUserClipPlanes = 6;
    pCaps->MaxVertexBlendMatrices = 4;
    pCaps->MaxVertexBlendMatrixIndex = 255;
    pCaps->MaxPointSize = 64.0f;
    pCaps->MaxPrimitiveCount = 0xFFFF;
    pCaps->MaxVertexIndex = 0xFFFF;
    pCaps->MaxStreams = 16;
    pCaps->MaxStreamStride = 255;
    pCaps->VertexShaderVersion = D3DVS_VERSION(3, 0);
    pCaps->MaxVertexShaderConst = 256;
    pCaps->PixelShaderVersion = D3DPS_VERSION(3, 0);
    pCaps->PixelShader1xMaxValue = 8.0f;
    
    return D3D_OK;
}

STDMETHODIMP_(HMONITOR) StubDirect3D9::GetAdapterMonitor(UINT Adapter) {
    if (Adapter != 0) return nullptr;
    return MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTOPRIMARY);
}

STDMETHODIMP StubDirect3D9::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface) {
    if (Adapter != 0 || !pPresentationParameters || !ppReturnedDeviceInterface) return D3DERR_INVALIDCALL;
    
    // Create our stub device
    *ppReturnedDeviceInterface = new StubDirect3DDevice9(this, *pPresentationParameters);
    
    return D3D_OK;
} 