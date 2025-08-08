#include "DirectXStub.h"

#ifdef TEXTMODE
// DLL entry point for DirectX stub initialization
// This ensures the stub is loaded early in the process
class DirectXStubInitializer {
public:
    DirectXStubInitializer() {
        // Initialize DirectX stub as early as possible
        DirectXStub::Initialize();
        if (DirectXStub::IsInitialized()) {
            DirectXStub::InstallHooks();
        }
    }
    
    ~DirectXStubInitializer() {
        DirectXStub::Shutdown();
    }
};

// Create a static instance to ensure early initialization
static DirectXStubInitializer g_DirectXStubInitializer;

#endif 