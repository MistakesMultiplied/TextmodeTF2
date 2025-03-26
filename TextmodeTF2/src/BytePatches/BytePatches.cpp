#include "BytePatches.h"

#include "../Core/Core.h"

BytePatch::BytePatch(const char* sModule, const char* sSignature, int iOffset, const char* sPatch)
{
	m_sModule = sModule;
	m_sSignature = sSignature;
	m_iOffset = iOffset;

	auto vPatch = U::Memory.PatternToByte(sPatch);
	m_vPatch = vPatch;
	m_iSize = vPatch.size();
	m_vOriginal.resize(m_iSize);
}

void BytePatch::Write(std::vector<byte>& bytes)
{
	DWORD flNewProtect, flOldProtect;
	VirtualProtect(m_pAddress, m_iSize, PAGE_EXECUTE_READWRITE, &flNewProtect);
	memcpy(m_pAddress, bytes.data(), m_iSize);
	VirtualProtect(m_pAddress, m_iSize, flNewProtect, &flOldProtect);
}

bool BytePatch::Initialize()
{
	if (m_bIsPatched)
		return true;

	m_pAddress = LPVOID(U::Memory.FindSignature(m_sModule, m_sSignature));
	if (!m_pAddress)
	{
		U::Core.AppendFailText(std::format("BytePatch::Initialize() failed to initialize:\n  {}\n  {}", m_sModule, m_sSignature).c_str());
		return false;
	}

	m_pAddress = LPVOID(uintptr_t(m_pAddress) + m_iOffset);

	DWORD flNewProtect, flOldProtect;
	VirtualProtect(m_pAddress, m_iSize, PAGE_EXECUTE_READWRITE, &flNewProtect);
	memcpy(m_vOriginal.data(), m_pAddress, m_iSize);
	VirtualProtect(m_pAddress, m_iSize, flNewProtect, &flOldProtect);

	Write(m_vPatch);
	return m_bIsPatched = true;
}

void BytePatch::Unload()
{
	if (!m_bIsPatched)
		return;

	Write(m_vOriginal);
	m_bIsPatched = false;
}

bool CBytePatches::Initialize(const char* cModule)
{
	/*
	std::vector<BytePatch> vPatches{};
	if (bEngine)
		vPatches = {
		// V_RenderView
		// Removes Sleep(15) call
		BytePatch("engine.dll", "E8 ? ? ? ? 48 85 FF 74 ? 45 33 C9 89 74 24", 0x0, "90 90 90 90 90"),
		// Skip downloading resources
		BytePatch("engine.dll", "75 ? 48 8B 0D ? ? ? ? 48 8D 93", 0x0, "71"),
		// Removes CEngineVGui::Simulate call
		// Should fix crashing in CMDLPanel::DoAnimationEvents
		// Nvm it somehow messes up auto match accept
		BytePatch("engine.dll", "48 8B C8 48 8B 10 FF 92 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 01", 0x0, "90 90 90 90 90 90 90 90 90 90 90 90"),
		// Same function, this removes a function call which gets a pointer to CEngineVGui
		// This signature is actually only findable after the previous bytepatch
		BytePatch("engine.dll", "E8 ? ? ? ? 90 90 90", 0x0, "90 90 90 90 90"),
		// Same for these 2 (i know i could've just hooked the function but i dont care)
		BytePatch("engine.dll", "48 8B C8 48 8B 10 FF 92 ? ? ? ? 48 85 DB", 0x0, "90 90 90 90 90 90 90 90 90 90 90 90"),
		BytePatch("engine.dll", "E8 ? ? ? ? 90 90 90", 0x0, "90 90 90 90 90")
	  };
	else
		vPatches = {
		// C_BaseAnimating::DoAnimationEvents
		// returns out of this function
		BytePatch("client.dll", "0F 84 ? ? ? ? 53 41 56 48 83 EC ? 83 B9", 0x0, "C3"),
		// CParticleCollection::Init
		BytePatch("client.dll", "57 48 83 EC ? 48 8B DA 48 8B F9 48 85 D2 74 ? 48 8B 0D ? ? ? ? 48 8B 89", 0x0, "31 C0 C3"),
		// CParticleSystemMgr::PrecacheParticleSystem
		BytePatch("client.dll", "74 ? 53 48 83 EC ? 80 3A", 0x0, "C3"),
		// CParticleProperty::Create
		// breaks amalgam
		BytePatch("client.dll", "44 89 44 24 ? 53 55 56 57 41 54 41 56", 0x0, "31 C0 C3"),
		// CViewRender::Render
		BytePatch("client.dll", "48 89 50 ? 55 57 41 56", 0x0, "31 C0 C3")
	};
	*/

	bool bFail{false};
	for (auto& patch : m_mPatches[cModule])
		if (!patch.Initialize())
			bFail = true;

	return !bFail;
}

void CBytePatches::Unload()
{
	for (auto [_, vPatches] : m_mPatches)
		for(auto& tPatch : vPatches)
			tPatch.Unload();
}