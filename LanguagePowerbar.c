#include "simpleini\SimpleIni.h"

void PatchLanguagePowerBar()
{
	while (IsBadReadPtr((void*)0x00573DC0, 13) || IsBadReadPtr((void*)0x0057AF98, 19))
	{ Sleep(100); }

	TCHAR tDirectory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, tDirectory);
	std::string Directory = tDirectory;
	Directory += "\\GunBoundOption.ini";

	try
	{
		CSimpleIniA IniFile;
		IniFile.SetUnicode();
		SI_Error rc = IniFile.LoadFile(Directory.c_str());
		if (rc < 0) { /* handle error */ };

		/* Language */
		char LanguagePT[13] = "language.txt"; /* br */
		char LanguageEN[13] = "language.eng"; /* en */
		char LanguageES[13] = "language.esp"; /* vt */
		char LanguageVT[13] = "language.vtn"; /* es */
		const char* Language;
		Language = IniFile.GetValue("GunBoundOption", "Language", "PT");

		/* Apply Language */
		if ((Language[0] == 'P' && Language[1] == 'T')) { memcpy((void*)0x00573DC0, &LanguagePT[0], 13); }
		if ((Language[0] == 'E' && Language[1] == 'N')) { memcpy((void*)0x00573DC0, &LanguageEN[0], 13); }
		if ((Language[0] == 'E' && Language[1] == 'S')) { memcpy((void*)0x00573DC0, &LanguageES[0], 13); }
		if ((Language[0] == 'V' && Language[1] == 'T')) { memcpy((void*)0x00573DC0, &LanguageVT[0], 13); }

		/* PowerBar */
		char PowerBarDefault[19] = "play_back_blue.img"; /* sem divisao */
		char PowerBarMilimetrico[19] = "play_back_blu1.img"; /* milimetrico */
		char PowerBarMetrico[19] = "play_back_blu2.img"; /* metrico */
		const char* PowerBar;
		PowerBar = IniFile.GetValue("GunBoundOption", "Barra", "1");

		/* Apply Power Bar */
		if (PowerBar[0] == '0') { memcpy((void*)0x0057AF98, &PowerBarMetrico[0], 19); }
		if (PowerBar[0] == '1') { memcpy((void*)0x0057AF98, &PowerBarMilimetrico[0], 19); }
		if (PowerBar[0] == '2') { memcpy((void*)0x0057AF98, &PowerBarDefault[0], 19); }

	} catch (...)
	{
		/* treat errors */
	}
}