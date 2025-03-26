#include "../SDK/SDK.h"
#include "../Utils/Feature/Feature.h"

class BytePatch
{
	const char* m_sModule = nullptr;
	const char* m_sSignature = nullptr;
	int m_iOffset = 0x0;
	std::vector<byte> m_vPatch = {};
	std::vector<byte> m_vOriginal = {};
	size_t m_iSize = 0;
	LPVOID m_pAddress = 0;
	bool m_bIsPatched = false;

	void Write(std::vector<byte>& bytes);

public:
	BytePatch(const char* sModule, const char* sSignature, int iOffset, const char* sPatch);

	bool Initialize();
	void Unload();
};

class CBytePatches
{
public:
	bool Initialize(const char* cModule);
	void Unload();

	std::unordered_map<const char*, std::vector<BytePatch>> m_mPatches =
	{
		{"engine",
		{
			BytePatch("engine.dll", "E8 ? ? ? ? 48 85 FF 74 ? 45 33 C9 89 74 24", 0x0, "90 90 90 90 90"),
			BytePatch("engine.dll", "75 ? 48 8B 0D ? ? ? ? 48 8D 93", 0x0, "71")
			//BytePatch("engine.dll", "48 8B C8 48 8B 10 FF 92 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 01", 0x0, "90 90 90 90 90 90 90 90 90 90 90 90"),
			//BytePatch("engine.dll", "E8 ? ? ? ? 90 90 90", 0x0, "90 90 90 90 90"),
			//BytePatch("engine.dll", "48 8B C8 48 8B 10 FF 92 ? ? ? ? 48 85 DB", 0x0, "90 90 90 90 90 90 90 90 90 90 90 90"),
			//BytePatch("engine.dll", "E8 ? ? ? ? 90 90 90", 0x0, "90 90 90 90 90") 
		}},
		//{"vgui",
		//{
		//	BytePatch("vgui2.dll", "FF 92 ? ? ? ? 48 85 FF", 0x0, "90 90 90 90 90 90")
		//}},
		{"client",
		{
			BytePatch("client.dll", "0F 84 ? ? ? ? 53 41 56 48 83 EC ? 83 B9", 0x0, "C3"),
			BytePatch("client.dll", "57 48 83 EC ? 48 8B DA 48 8B F9 48 85 D2 74 ? 48 8B 0D ? ? ? ? 48 8B 89", 0x0, "31 C0 C3"),
			BytePatch("client.dll", "74 ? 53 48 83 EC ? 80 3A", 0x0, "C3"),
			BytePatch("client.dll", "44 89 44 24 ? 53 55 56 57 41 54 41 56", 0x0, "31 C0 C3"),
			BytePatch("client.dll", "48 89 50 ? 55 57 41 56", 0x0, "31 C0 C3"),
			BytePatch("client.dll", "4D 85 F6 0F 84 ? ? ? ? 49 8B CE E8 ? ? ? ? 83 F8", 0x0, "83 F6 00") // This fixes the datacache.dll crash
		}}
	};
};

ADD_FEATURE_CUSTOM(CBytePatches, BytePatches, U);