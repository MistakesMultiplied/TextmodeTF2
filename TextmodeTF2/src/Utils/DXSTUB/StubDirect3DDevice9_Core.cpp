#include "DirectXStub.h"
#include <iostream>

StubDirect3DDevice9::StubDirect3DDevice9(StubDirect3D9* pD3D, const D3DPRESENT_PARAMETERS& presentParams) 
    : m_refCount(1), m_pD3D(pD3D), m_presentParams(presentParams) {
    
    if (m_pD3D) {
        m_pD3D->AddRef();
    }
    
    // Initialize viewport with default values
    m_viewport.X = 0;
    m_viewport.Y = 0;
    m_viewport.Width = presentParams.BackBufferWidth;
    m_viewport.Height = presentParams.BackBufferHeight;
    m_viewport.MinZ = 0.0f;
    m_viewport.MaxZ = 1.0f;
}

StubDirect3DDevice9::~StubDirect3DDevice9() {
    if (m_pD3D) {
        m_pD3D->Release();
    }
}

// IUnknown methods
STDMETHODIMP StubDirect3DDevice9::QueryInterface(REFIID riid, void** ppvObject) {
    if (riid == IID_IUnknown || riid == IID_IDirect3DDevice9) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) StubDirect3DDevice9::AddRef() {
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) StubDirect3DDevice9::Release() {
    ULONG count = --m_refCount;
    if (count == 0) {
        delete this;
    }
    return count;
}

// Core device methods
STDMETHODIMP StubDirect3DDevice9::TestCooperativeLevel() {
    return D3D_OK;
}

STDMETHODIMP_(UINT) StubDirect3DDevice9::GetAvailableTextureMem() {
    return 128 * 1024 * 1024; // 128MB fake memory
}

STDMETHODIMP StubDirect3DDevice9::EvictManagedResources() {
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetDirect3D(IDirect3D9** ppD3D9) {
    if (!ppD3D9) return D3DERR_INVALIDCALL;
    *ppD3D9 = m_pD3D;
    if (m_pD3D) m_pD3D->AddRef();
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetDeviceCaps(D3DCAPS9* pCaps) {
    if (!pCaps) return D3DERR_INVALIDCALL;
    return m_pD3D->GetDeviceCaps(0, D3DDEVTYPE_HAL, pCaps);
}

STDMETHODIMP StubDirect3DDevice9::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode) {
    if (iSwapChain != 0 || !pMode) return D3DERR_INVALIDCALL;
    
    pMode->Width = m_presentParams.BackBufferWidth;
    pMode->Height = m_presentParams.BackBufferHeight;
    pMode->RefreshRate = 60;
    pMode->Format = m_presentParams.BackBufferFormat;
    
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters) {
    if (!pParameters) return D3DERR_INVALIDCALL;
    
    pParameters->AdapterOrdinal = 0;
    pParameters->DeviceType = D3DDEVTYPE_HAL;
    pParameters->hFocusWindow = m_presentParams.hDeviceWindow;
    pParameters->BehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    
    return D3D_OK;
}

// Scene methods
STDMETHODIMP StubDirect3DDevice9::BeginScene() {
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::EndScene() {
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::Clear(DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion) {
    // Do nothing - we're not actually presenting
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) {
    if (!pPresentationParameters) return D3DERR_INVALIDCALL;
    
    // Update our stored parameters
    m_presentParams = *pPresentationParameters;
    
    // Update viewport
    m_viewport.Width = pPresentationParameters->BackBufferWidth;
    m_viewport.Height = pPresentationParameters->BackBufferHeight;
    
    return D3D_OK;
}

// Viewport methods
STDMETHODIMP StubDirect3DDevice9::SetViewport(const D3DVIEWPORT9* pViewport) {
    if (!pViewport) return D3DERR_INVALIDCALL;
    m_viewport = *pViewport;
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetViewport(D3DVIEWPORT9* pViewport) {
    if (!pViewport) return D3DERR_INVALIDCALL;
    *pViewport = m_viewport;
    return D3D_OK;
}

// Render state methods
STDMETHODIMP StubDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue) {
    if (!pValue) return D3DERR_INVALIDCALL;
    
    // Return default values for common render states
    switch (State) {
        case D3DRS_ZENABLE:
            *pValue = D3DZB_TRUE;
            break;
        case D3DRS_FILLMODE:
            *pValue = D3DFILL_SOLID;
            break;
        case D3DRS_SHADEMODE:
            *pValue = D3DSHADE_GOURAUD;
            break;
        case D3DRS_ZWRITEENABLE:
            *pValue = TRUE;
            break;
        case D3DRS_ALPHATESTENABLE:
            *pValue = FALSE;
            break;
        case D3DRS_LASTPIXEL:
            *pValue = TRUE;
            break;
        case D3DRS_SRCBLEND:
            *pValue = D3DBLEND_ONE;
            break;
        case D3DRS_DESTBLEND:
            *pValue = D3DBLEND_ZERO;
            break;
        case D3DRS_CULLMODE:
            *pValue = D3DCULL_CCW;
            break;
        case D3DRS_ZFUNC:
            *pValue = D3DCMP_LESSEQUAL;
            break;
        case D3DRS_DITHERENABLE:
            *pValue = FALSE;
            break;
        case D3DRS_ALPHABLENDENABLE:
            *pValue = FALSE;
            break;
        case D3DRS_FOGENABLE:
            *pValue = FALSE;
            break;
        case D3DRS_SPECULARENABLE:
            *pValue = FALSE;
            break;
        case D3DRS_LIGHTING:
            *pValue = TRUE;
            break;
        case D3DRS_AMBIENT:
            *pValue = 0;
            break;
        default:
            *pValue = 0;
            break;
    }
    
    return D3D_OK;
}

// Transform methods
STDMETHODIMP StubDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix) {
    if (!pMatrix) return D3DERR_INVALIDCALL;
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) {
    if (!pMatrix) return D3DERR_INVALIDCALL;
    
    // Return identity matrix
    ZeroMemory(pMatrix, sizeof(D3DMATRIX));
    pMatrix->m[0][0] = 1.0f;
    pMatrix->m[1][1] = 1.0f;
    pMatrix->m[2][2] = 1.0f;
    pMatrix->m[3][3] = 1.0f;
    
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix) {
    if (!pMatrix) return D3DERR_INVALIDCALL;
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

// Drawing methods
STDMETHODIMP StubDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

STDMETHODIMP StubDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride) {
    // Do nothing - we're not actually rendering
    return D3D_OK;
}

// Validation methods
STDMETHODIMP StubDirect3DDevice9::ValidateDevice(DWORD* pNumPasses) {
    if (!pNumPasses) return D3DERR_INVALIDCALL;
    *pNumPasses = 1;
    return D3D_OK;
} 

// ---------------------------------------------------------------------------
// Stubs for rarely-used fixed-function N-patch / patch / clip-status APIs so
// that the class is no longer abstract.  The engine never calls these when we
// are running in text-mode, so simple ‘not implemented’ results are sufficient.
// ---------------------------------------------------------------------------
STDMETHODIMP StubDirect3DDevice9::SetClipStatus(const D3DCLIPSTATUS9* /*pClipStatus*/) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9* /*pClipStatus*/) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DDevice9::DrawRectPatch(UINT /*Handle*/, const float* /*pNumSegs*/, const D3DRECTPATCH_INFO* /*pRectPatchInfo*/) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::DrawTriPatch(UINT /*Handle*/, const float* /*pNumSegs*/, const D3DTRIPATCH_INFO* /*pTriPatchInfo*/) { return D3D_OK; }
STDMETHODIMP StubDirect3DDevice9::DeletePatch(UINT /*Handle*/) { return D3D_OK; } 