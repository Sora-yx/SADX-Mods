#include "stdafx.h"
#include "Utils.h"
#include "EggViper.h"
#include "RandomHelpers.h"

HelperFunctions extern help;

void __cdecl EggViper_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, EV_StartPositions[0]);

	//Tails
	helperFunctions.RegisterStartPosition(Characters_Tails, EV_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EV_StartPositions[0]);

	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, EV_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, EV_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, EV_StartPositions[0]);

}


DataPointer(char, EggViperHP, 0x3c6e164);

void EggViperNerfHP() {
	EggViperHP = 3;
	Rings = 5;
}



void EggViperVoice() {

	//remplacing "See if you can make it through here; Sonic!" voice depending on the character played.
	LoadCamFile(0, "0000");

	if (CurrentLevel == LevelIDs_EggViper)
	{
		//WriteData<1>((void*)0x584c7f, 0x4); //restore original

		if (CurrentCharacter == Characters_Sonic)
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\Haha_Sonic.wma"); //restore original voice

		}

		if (CurrentCharacter == Characters_Tails)
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\GiveUpTails.wma"); //"Give up now Tails"
		}

		if (CurrentCharacter == Characters_Knuckles)
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\NoUse.wma"); //"It's no use, give up." 
		}

		if (CurrentCharacter == Characters_Amy)
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\GiveUpAmy_424.wma"); //"Give up now Amy" (sa2 voice) 
		}

		if (CurrentCharacter == Characters_Big)
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\NoUse.wma"); //"It's no use, give up." 
			//WriteData<1>((void*)0x57c321, 0x20); //X
			//WriteData<1>((void*)0x57c326, 0x40); //Fix Egg Viper platform for Big Position Y
			WriteData<1>((void*)0x57c32f, 0x20); //Fix Egg Viper platform for Big Position Z (20 Fonctionnel)
			WriteData<1>((void*)0x584c7f, 0x12); //fix Egg Viper softlock
		
			WriteCall((void*)0x57f206, EggViperNerfHP);
		}

		if (CurrentCharacter == Characters_Gamma)
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\Useless.wma"); //"I'm so dissapointed; you useless machine!" 


	}

}

void BigEggViperPlatform() {

	if (CurrentCharacter == Characters_Big)
	{
		
	}
	

}

void FixEggViperCutscene() {

	if (CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Big)
	{
		return;
	}
	else
	{
		EggViperCutscene();
	}
}
