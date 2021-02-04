#include "stdafx.h"


void EmeraldRadar_R() {

	if (CurrentStageVersion == KnucklesVersion && CurrentMission < Mission2_100Rings)
	{
		LoadObject((LoadObj)2, 6, EmeraldRadarHud_Load_Load);

		if (CurrentCharacter != Characters_Knuckles)
		{
			KnuxCheck2 = 0; //fix Trial Mode Crash

			switch (CurrentLevel)
			{
			case LevelIDs_SpeedHighway:
				if (CurrentCharacter == Characters_Gamma && KnuxEmerald2 >= 48 && KnuxEmerald2 <= 53) //Gamma cannot break the trash.
				{
					do {
						Knuckles_SetRNG();
					} while (KnuxEmerald2 >= 48 && KnuxEmerald2 <= 53);
				}
				break;
			case LevelIDs_RedMountain:
				if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37) //If diggable emeralds, rand again.
				{
					do {
						Knuckles_SetRNG();
					} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37);
				}
				break;
			case LevelIDs_LostWorld:
				if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37) //If diggable emeralds, rand again.
				{
					do {
						Knuckles_SetRNG();
					} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37);
				}
				break;
			case LevelIDs_SkyDeck:
				if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 35) //If diggable emeralds, rand again.
				{
					do {
						Knuckles_SetRNG();
					} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 35);
				}
				break;
			}
		}
	}

	return;
}

int KnuxRadarEmeraldCheck() {  //trick the game to make it think we are playing Knuckles

	if (CurrentStageVersion == KnucklesVersion && CurrentMission < Mission2_100Rings)
		return Characters_Knuckles;

	return 8; //Doesn't exist so the game won't load anything
}

//Set Emerald RNG when not Knuckles

void SetRNGKnuckles() {

	if (CurrentMission < Mission2_100Rings && CurrentStageVersion == KnucklesVersion && CurrentCharacter != Characters_Knuckles)
	{
		LoadPVM("KNU_EFF", &KNU_EFF_TEXLIST);
		WriteData<1>((void*)0x416F06, 0x08);
		WriteData<1>((void*)0x4153E1, 0x08);
		WriteData<1>((void*)0x416f08, 0x74);
		WriteData<1>((void*)0x4153e3, 0x74);
	}

	return;
}

//restore original values
void RestoreRNGValueKnuckles() {
	WriteData<1>((void*)0x416F06, 0x03);
	WriteData<1>((void*)0x4153E1, 0x03);
	WriteData<1>((void*)0x416f08, 0x75);
	WriteData<1>((void*)0x4153e3, 0x75);

	return;
}

Trampoline KnucklesHint_Main_t((int)KnucklesHint_Main, (int)KnucklesHint_Main + 0x7, KnucklesHintMain_r);

void KnucklesHintMain_r(ObjectMaster* obj) {

	if (CurrentMission < Mission2_100Rings)
	{
		ObjectFunc(origin, KnucklesHint_Main_t.Target());
		origin(obj);
	}

	return;
}


void FixRadarSFX() {

	if (CurrentCharacter != Characters_Knuckles)
		PlayCustomSound(CommonSound_RadarBlink);
	else
		PlaySound(0x314, 0, 0, 0);

	return;
}

void FixEmeraldGetSFX() {

	if (CurrentCharacter != Characters_Knuckles)
		PlayCustomSound(CommonSound_EmeraldGet);
	else
		PlaySound(0x313, 0, 0, 0);

	return;
}



void FixTikalHintSFX() {

	if (CurrentCharacter != Characters_Knuckles)
		PlayCustomSound(CommonSound_TikalHint);
	else
		PlaySound(0x316, 0, 0, 0);

	return;
}


Trampoline PlayKnuxVoice_EmeraldGet(0x474f50, 0x474f55, PlayCharaVoice_EmeraldGet);

void PlayCharaVoice_EmeraldGet(ObjectMaster* a1) {
	ObjectMaster* P1 = GetCharacterObject(0);
	int CurChar = P1->Data1->CharID;

	if (P1 != nullptr)
	{
		switch (CurChar)
		{
		case Characters_Sonic:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_R(1826);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_R(315);
			break;
		case Characters_Tails:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_R(1812);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_R(1456);
			break;
		case Characters_Amy:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_R(5020);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_R(1737);
			break;
		case Characters_Gamma:
			if (EmeraldKnuxCheck == 1 || EmeraldKnuxCheck == 2)
				PlayVoice_R(5023);
			break;
		case Characters_Big:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_R(5021);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_R(5022);
			break;
		}
	}

	if (CurChar == Characters_Knuckles)
	{
		ObjectFunc(origin, PlayKnuxVoice_EmeraldGet.Target());
		origin(a1);
	}
	else
		CheckThingButThenDeleteObject(a1);

	return;
}


void Init_TreasureHunting() {

	WriteData<6>((void*)0x475E7C, 0x90u); // make radar work when not Knuckles
	WriteData<6>((void*)0x4764CC, 0x90u); // make Tikal hints work when not Knuckles
	WriteData<6>((void*)0x4a31f0, 0x90u); // Display the emerald grab thing when not Knuckles.
	WriteCall((void*)0x4762a6, FixRadarSFX);
	WriteCall((void*)0x477e14, FixEmeraldGetSFX);
	WriteCall((void*)0x7a907f, FixTikalHintSFX);
	WriteCall((void*)0x475852, KnuxRadarEmeraldCheck); //radar chara check
	WriteCall((void*)0x4a306a, KnuxRadarEmeraldCheck); //display piece
	WriteCall((void*)0x476661, KnuxRadarEmeraldCheck); //display piece
	WriteCall((void*)0x477d96, KnuxRadarEmeraldCheck); //display piece	

	//Allow characters to break box in Speed Highway
	WriteData<1>((void*)0x61A5B8, 0x8);
	WriteData<1>((void*)0x61a5b9, 0x74);
}