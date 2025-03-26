#include "SDK.h"

void SDK::Output(const char* cFunction, const char* cLog, bool bDebug, int iMessageBox)
{
	if (cLog)
	{
		if (bDebug)
			OutputDebugString(std::format("[{}] {}\n", cFunction, cLog).c_str());
		if (iMessageBox != -1)
			MessageBox(nullptr, cLog, cFunction, iMessageBox);
	}
	else
	{
		if (bDebug)
			OutputDebugString(std::format("{}\n", cFunction).c_str());
		if (iMessageBox != -1)
			MessageBox(nullptr, "", cFunction, iMessageBox);
	}
}

bool SDK::BlacklistFile(const char* cFileName)
{
	const static char* blacklist[] = { ".ani", ".wav", ".mp3", ".vvd", ".vtx", ".vtf", ".vfe", ".cache" , /*".pcf"*/ };
	if (!cFileName || !std::strncmp(cFileName, "materials/console/", 18))
		return false;

	std::size_t len = std::strlen(cFileName);
	if (len <= 3)
		return false;

	auto ext_p = strrchr(cFileName, '.');
	if (!ext_p)
		return false;

	if (!std::strcmp(ext_p, ".vmt"))
	{
		/* Not loading it causes extreme console spam */
		if (std::strstr(cFileName, "corner"))
			return false;
		/* minor console spam */
		if (std::strstr(cFileName, "hud") || std::strstr(cFileName, "vgui"))
			return false;

		return true;
	}
	if (std::strstr(cFileName, "sound.cache") || std::strstr(cFileName, "tf2_sound") || std::strstr(cFileName, "game_sounds"))
		return false;
	if (!std::strncmp(cFileName, "sound/player/footsteps", 22))
		return false;
	if (!std::strcmp(ext_p, ".mdl"))
		return false;
	if (!std::strncmp(cFileName, "/decal", 6))
		return true;

	for (int i = 0; i < sizeof(blacklist) / sizeof(blacklist[0]); ++i)
		if (!std::strcmp(ext_p, blacklist[i]))
			return true;

	return false;
}