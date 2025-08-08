#define INITGUID
#include <d3d9.h>
#include "DirectXStub.h"
#ifdef HAVE_DETOURS
#include <detours.h>
#endif
#include <iostream>

namespace DirectXStub {
    // Global state
    bool g_bInitialized = false;
    HMODULE g_hOriginalD3D9 = nullptr;
    IDirect3D9* (WINAPI* g_pOriginalDirect3DCreate9)(UINT SDKVersion) = nullptr;
    
    // Hooked function
    IDirect3D9* WINAPI HookedDirect3DCreate9(UINT SDKVersion) {
        // Return our stub implementation instead of the real D3D9
        return new StubDirect3D9();
    }
    
    void Initialize() {
        if (g_bInitialized) return;
        
        // Load the original d3d9.dll
        g_hOriginalD3D9 = LoadLibraryA("d3d9.dll");
        if (!g_hOriginalD3D9) {
            return;
        }
        
        // Get the original Direct3DCreate9 function
        g_pOriginalDirect3DCreate9 = (IDirect3D9* (WINAPI*)(UINT))GetProcAddress(g_hOriginalD3D9, "Direct3DCreate9");
        
        if (!g_pOriginalDirect3DCreate9) {
            return;
        }
        
        g_bInitialized = true;
    }
    
    void Shutdown() {
        if (!g_bInitialized) return;
        
        UninstallHooks();
        
        if (g_hOriginalD3D9) {
            FreeLibrary(g_hOriginalD3D9);
            g_hOriginalD3D9 = nullptr;
        }
        
        g_pOriginalDirect3DCreate9 = nullptr;
        g_bInitialized = false;
    }
    
    bool IsInitialized() {
        return g_bInitialized;
    }
    
    bool InstallHooks() {
        if (!g_bInitialized) return false;
        
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        
        // Hook Direct3DCreate9
        DetourAttach(&(PVOID&)g_pOriginalDirect3DCreate9, HookedDirect3DCreate9);
        
        LONG result = DetourTransactionCommit();
        return result == NO_ERROR;
    }
    
    bool UninstallHooks() {
        if (!g_bInitialized) return false;
        
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        
        // Unhook Direct3DCreate9
        DetourDetach(&(PVOID&)g_pOriginalDirect3DCreate9, HookedDirect3DCreate9);
        
        LONG result = DetourTransactionCommit();
        return result == NO_ERROR;
    }
} 