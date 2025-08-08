#include "DirectXStub.h"
#include <iostream>

// StubDirect3DTexture9 implementation
StubDirect3DTexture9::StubDirect3DTexture9(UINT width, UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool)
    : m_refCount(1), m_width(width), m_height(height), m_levels(levels), m_usage(usage), m_format(format), m_pool(pool) {
}

StubDirect3DTexture9::~StubDirect3DTexture9() {
}

STDMETHODIMP StubDirect3DTexture9::QueryInterface(REFIID riid, void** ppvObject) {
    if (riid == IID_IUnknown || riid == IID_IDirect3DResource9 || riid == IID_IDirect3DBaseTexture9 || riid == IID_IDirect3DTexture9) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) StubDirect3DTexture9::AddRef() {
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) StubDirect3DTexture9::Release() {
    ULONG count = --m_refCount;
    if (count == 0) {
        delete this;
    }
    return count;
}

STDMETHODIMP StubDirect3DTexture9::GetDevice(IDirect3DDevice9** ppDevice) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DTexture9::SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags) { return D3D_OK; }
STDMETHODIMP StubDirect3DTexture9::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData) { return D3D_OK; }
STDMETHODIMP StubDirect3DTexture9::FreePrivateData(REFGUID refguid) { return D3D_OK; }
STDMETHODIMP_(DWORD) StubDirect3DTexture9::SetPriority(DWORD PriorityNew) { return 0; }
STDMETHODIMP_(DWORD) StubDirect3DTexture9::GetPriority() { return 0; }
STDMETHODIMP_(void) StubDirect3DTexture9::PreLoad() { }
STDMETHODIMP_(D3DRESOURCETYPE) StubDirect3DTexture9::GetType() { return D3DRTYPE_TEXTURE; }
STDMETHODIMP_(DWORD) StubDirect3DTexture9::SetLOD(DWORD LODNew) { return 0; }
STDMETHODIMP_(DWORD) StubDirect3DTexture9::GetLOD() { return 0; }
STDMETHODIMP_(DWORD) StubDirect3DTexture9::GetLevelCount() { return m_levels; }
STDMETHODIMP StubDirect3DTexture9::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType) { return D3D_OK; }
STDMETHODIMP_(D3DTEXTUREFILTERTYPE) StubDirect3DTexture9::GetAutoGenFilterType() { return D3DTEXF_LINEAR; }
STDMETHODIMP_(void) StubDirect3DTexture9::GenerateMipSubLevels() { }

STDMETHODIMP StubDirect3DTexture9::GetLevelDesc(UINT Level, D3DSURFACE_DESC* pDesc) {
    if (!pDesc) return D3DERR_INVALIDCALL;
    pDesc->Format = m_format;
    pDesc->Type = D3DRTYPE_SURFACE;
    pDesc->Usage = m_usage;
    pDesc->Pool = m_pool;
    pDesc->MultiSampleType = D3DMULTISAMPLE_NONE;
    pDesc->MultiSampleQuality = 0;
    pDesc->Width = m_width;
    pDesc->Height = m_height;
    return D3D_OK;
}

STDMETHODIMP StubDirect3DTexture9::GetSurfaceLevel(UINT Level, IDirect3DSurface9** ppSurfaceLevel) {
    if (!ppSurfaceLevel) return D3DERR_INVALIDCALL;
    *ppSurfaceLevel = new StubDirect3DSurface9(m_width, m_height, m_format, D3DMULTISAMPLE_NONE, 0);
    return D3D_OK;
}

STDMETHODIMP StubDirect3DTexture9::LockRect(UINT Level, D3DLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags) {
    if (!pLockedRect) return D3DERR_INVALIDCALL;
    pLockedRect->Pitch = m_width * 4; // Assume 32-bit
    pLockedRect->pBits = malloc(m_width * m_height * 4);
    return D3D_OK;
}

STDMETHODIMP StubDirect3DTexture9::UnlockRect(UINT Level) {
    return D3D_OK;
}

STDMETHODIMP StubDirect3DTexture9::AddDirtyRect(const RECT* pDirtyRect) {
    return D3D_OK;
}

// StubDirect3DSurface9 implementation
StubDirect3DSurface9::StubDirect3DSurface9(UINT width, UINT height, D3DFORMAT format, D3DMULTISAMPLE_TYPE multiSampleType, DWORD multiSampleQuality)
    : m_refCount(1), m_width(width), m_height(height), m_format(format), m_multiSampleType(multiSampleType), m_multiSampleQuality(multiSampleQuality) {
}

StubDirect3DSurface9::~StubDirect3DSurface9() {
}

STDMETHODIMP StubDirect3DSurface9::QueryInterface(REFIID riid, void** ppvObject) {
    if (riid == IID_IUnknown || riid == IID_IDirect3DResource9 || riid == IID_IDirect3DSurface9) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) StubDirect3DSurface9::AddRef() {
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) StubDirect3DSurface9::Release() {
    ULONG count = --m_refCount;
    if (count == 0) {
        delete this;
    }
    return count;
}

STDMETHODIMP StubDirect3DSurface9::GetDevice(IDirect3DDevice9** ppDevice) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DSurface9::SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags) { return D3D_OK; }
STDMETHODIMP StubDirect3DSurface9::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData) { return D3D_OK; }
STDMETHODIMP StubDirect3DSurface9::FreePrivateData(REFGUID refguid) { return D3D_OK; }
STDMETHODIMP_(DWORD) StubDirect3DSurface9::SetPriority(DWORD PriorityNew) { return 0; }
STDMETHODIMP_(DWORD) StubDirect3DSurface9::GetPriority() { return 0; }
STDMETHODIMP_(void) StubDirect3DSurface9::PreLoad() { }
STDMETHODIMP_(D3DRESOURCETYPE) StubDirect3DSurface9::GetType() { return D3DRTYPE_SURFACE; }

STDMETHODIMP StubDirect3DSurface9::GetContainer(REFIID riid, void** ppContainer) {
    return D3DERR_INVALIDCALL;
}

STDMETHODIMP StubDirect3DSurface9::GetDesc(D3DSURFACE_DESC* pDesc) {
    if (!pDesc) return D3DERR_INVALIDCALL;
    pDesc->Format = m_format;
    pDesc->Type = D3DRTYPE_SURFACE;
    pDesc->Usage = 0;
    pDesc->Pool = D3DPOOL_DEFAULT;
    pDesc->MultiSampleType = m_multiSampleType;
    pDesc->MultiSampleQuality = m_multiSampleQuality;
    pDesc->Width = m_width;
    pDesc->Height = m_height;
    return D3D_OK;
}

STDMETHODIMP StubDirect3DSurface9::LockRect(D3DLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags) {
    if (!pLockedRect) return D3DERR_INVALIDCALL;
    pLockedRect->Pitch = m_width * 4; // Assume 32-bit
    pLockedRect->pBits = malloc(m_width * m_height * 4);
    return D3D_OK;
}

STDMETHODIMP StubDirect3DSurface9::UnlockRect() {
    return D3D_OK;
}

STDMETHODIMP StubDirect3DSurface9::GetDC(HDC* phdc) {
    return D3DERR_INVALIDCALL;
}

STDMETHODIMP StubDirect3DSurface9::ReleaseDC(HDC hdc) {
    return D3DERR_INVALIDCALL;
}

// StubDirect3DVertexBuffer9 implementation
StubDirect3DVertexBuffer9::StubDirect3DVertexBuffer9(UINT length, DWORD usage, DWORD fvf, D3DPOOL pool)
    : m_refCount(1), m_length(length), m_usage(usage), m_fvf(fvf), m_pool(pool) {
}

StubDirect3DVertexBuffer9::~StubDirect3DVertexBuffer9() {
}

STDMETHODIMP StubDirect3DVertexBuffer9::QueryInterface(REFIID riid, void** ppvObject) {
    if (riid == IID_IUnknown || riid == IID_IDirect3DResource9 || riid == IID_IDirect3DVertexBuffer9) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) StubDirect3DVertexBuffer9::AddRef() {
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) StubDirect3DVertexBuffer9::Release() {
    ULONG count = --m_refCount;
    if (count == 0) {
        delete this;
    }
    return count;
}

STDMETHODIMP StubDirect3DVertexBuffer9::GetDevice(IDirect3DDevice9** ppDevice) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DVertexBuffer9::SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags) { return D3D_OK; }
STDMETHODIMP StubDirect3DVertexBuffer9::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData) { return D3D_OK; }
STDMETHODIMP StubDirect3DVertexBuffer9::FreePrivateData(REFGUID refguid) { return D3D_OK; }
STDMETHODIMP_(DWORD) StubDirect3DVertexBuffer9::SetPriority(DWORD PriorityNew) { return 0; }
STDMETHODIMP_(DWORD) StubDirect3DVertexBuffer9::GetPriority() { return 0; }
STDMETHODIMP_(void) StubDirect3DVertexBuffer9::PreLoad() { }
STDMETHODIMP_(D3DRESOURCETYPE) StubDirect3DVertexBuffer9::GetType() { return D3DRTYPE_VERTEXBUFFER; }

STDMETHODIMP StubDirect3DVertexBuffer9::Lock(UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags) {
    if (!ppbData) return D3DERR_INVALIDCALL;
    *ppbData = malloc(SizeToLock ? SizeToLock : m_length);
    return D3D_OK;
}

STDMETHODIMP StubDirect3DVertexBuffer9::Unlock() {
    return D3D_OK;
}

STDMETHODIMP StubDirect3DVertexBuffer9::GetDesc(D3DVERTEXBUFFER_DESC* pDesc) {
    if (!pDesc) return D3DERR_INVALIDCALL;
    pDesc->Format = D3DFMT_VERTEXDATA;
    pDesc->Type = D3DRTYPE_VERTEXBUFFER;
    pDesc->Usage = m_usage;
    pDesc->Pool = m_pool;
    pDesc->Size = m_length;
    pDesc->FVF = m_fvf;
    return D3D_OK;
}

// StubDirect3DIndexBuffer9 implementation
StubDirect3DIndexBuffer9::StubDirect3DIndexBuffer9(UINT length, DWORD usage, D3DFORMAT format, D3DPOOL pool)
    : m_refCount(1), m_length(length), m_usage(usage), m_format(format), m_pool(pool) {
}

StubDirect3DIndexBuffer9::~StubDirect3DIndexBuffer9() {
}

STDMETHODIMP StubDirect3DIndexBuffer9::QueryInterface(REFIID riid, void** ppvObject) {
    if (riid == IID_IUnknown || riid == IID_IDirect3DResource9 || riid == IID_IDirect3DIndexBuffer9) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) StubDirect3DIndexBuffer9::AddRef() {
    return ++m_refCount;
}

STDMETHODIMP_(ULONG) StubDirect3DIndexBuffer9::Release() {
    ULONG count = --m_refCount;
    if (count == 0) {
        delete this;
    }
    return count;
}

STDMETHODIMP StubDirect3DIndexBuffer9::GetDevice(IDirect3DDevice9** ppDevice) { return D3DERR_INVALIDCALL; }
STDMETHODIMP StubDirect3DIndexBuffer9::SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags) { return D3D_OK; }
STDMETHODIMP StubDirect3DIndexBuffer9::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData) { return D3D_OK; }
STDMETHODIMP StubDirect3DIndexBuffer9::FreePrivateData(REFGUID refguid) { return D3D_OK; }
STDMETHODIMP_(DWORD) StubDirect3DIndexBuffer9::SetPriority(DWORD PriorityNew) { return 0; }
STDMETHODIMP_(DWORD) StubDirect3DIndexBuffer9::GetPriority() { return 0; }
STDMETHODIMP_(void) StubDirect3DIndexBuffer9::PreLoad() { }
STDMETHODIMP_(D3DRESOURCETYPE) StubDirect3DIndexBuffer9::GetType() { return D3DRTYPE_INDEXBUFFER; }

STDMETHODIMP StubDirect3DIndexBuffer9::Lock(UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags) {
    if (!ppbData) return D3DERR_INVALIDCALL;
    *ppbData = malloc(SizeToLock ? SizeToLock : m_length);
    return D3D_OK;
}

STDMETHODIMP StubDirect3DIndexBuffer9::Unlock() {
    return D3D_OK;
}

STDMETHODIMP StubDirect3DIndexBuffer9::GetDesc(D3DINDEXBUFFER_DESC* pDesc) {
    if (!pDesc) return D3DERR_INVALIDCALL;
    pDesc->Format = m_format;
    pDesc->Type = D3DRTYPE_INDEXBUFFER;
    pDesc->Usage = m_usage;
    pDesc->Pool = m_pool;
    pDesc->Size = m_length;
    return D3D_OK;
} 