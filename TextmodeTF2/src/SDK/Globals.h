#pragma once
#include "Definitions/Definitions.h"
#include "../Utils/Signatures/Signatures.h"
#include "../Utils/Memory/Memory.h"

namespace G
{
	inline std::string CurrentPath{};
	inline uintptr_t CVideoModeCommon_SetupStartupGraphicAddr{};
	inline uintptr_t IFileSystemAddr{};
	inline uintptr_t IBaseFileSystemAddr{};
	inline uintptr_t g_bTextModeAddr{};
	inline uintptr_t g_bAllowSecureServersAddr{};
	inline uintptr_t Host_IsSecureServerAllowedAddr{};
};