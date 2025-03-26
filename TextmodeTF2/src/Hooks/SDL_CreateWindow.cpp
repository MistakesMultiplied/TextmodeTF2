#include "../SDK/SDK.h"

// It doesnt look like its being called anywhere

MAKE_HOOK(SDL_CreateWindow, G::SDL_CreateWindowAddr, void*,
		  void* a1, void* a2, void* a3, void* a4, void* a5, int flags)
{
	static int iCall = 1;
	auto returnAddr = reinterpret_cast<uintptr_t>(_ReturnAddress());
	MessageBoxA(NULL, std::format("{}", returnAddr).c_str(), std::format("SDL_CreateWindow ret addr (Call: {})", iCall).c_str(), MB_OK);
	iCall++;
	return CALL_ORIGINAL(a1, a2, a3, a4, a5, 0x8);
}