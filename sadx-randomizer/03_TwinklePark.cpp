#include "stdafx.h"

#define AddCam(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")


void FixRollerCoaster() {
	ObjectMaster* obj = GetCharacterObject(0);
	if (obj != nullptr)
		obj->Data1->Action = 28; //force the character to leave the RC
}

void FixRCCharacterPosition() {
	ObjectMaster* obj = GetCharacterObject(0);

	if (obj != nullptr)
		ForcePlayerAction(0, 18);

	PlaySound(0x4d,0,0,0);
	return;
}


void TP_CAM() {

	LoadCamFile(0, "0300");

	if (CurrentAct == 0)
		LoadCamFile(1, "0301");
		
	if (CurrentAct == 1 && CurrentStageVersion == AmyVersion)
		LoadCamFile(1, "0303");
	else
		LoadCamFile(1, "0301");

	LoadCamFile(2, "0302");

	return;

}


void TwinklePark_Layout() {


	if (CurrentStageVersion != AmyVersion && CurrentStageVersion != BigVersion)
		CurrentStageVersion = SonicVersion;

	if (CurrentAct == 1 && CurrentStageVersion != BigVersion)
		CurrentStageVersion = AmyVersion; 

	if (CurrentCharacter >= Characters_Gamma)
	{
		WriteData<1>((void*)0x798306, 0x84);
		WriteData<1>((void*)0x7983c4, 0x7F);
	}


	fixTCCart();
	return;
}

void __cdecl TwinklePark_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteData<5>((int*)0x61cb77, 0x90); //Fix Twinkle Park Act 2 crash when not Sonic-Amy-Big
	WriteData<1>((char*)0x61cf97, 0x08); //Allow everyone to use Amy Twinkle Park transition part 1
	WriteData<1>((int*)0x61cf99, 0x84); //Allow everyone to use Amy Twinkle Park transition part 2
	WriteData<1>((int*)0x61dd72, 0x85); //Make Rollercoaster works when not Sonic.
	
	WriteCall((void*)0x61dd82, FixRCCharacterPosition); 
	WriteCall((void*)0x61dde8, FixRollerCoaster); //Fix leaving RC when not Sonic.

	WriteCall((void*)0x422c92, TwinklePark_Layout); //TP random layout

	TPObjects_Init(path, helperFunctions);

	//Sonic
	AddLevelLayout("Twinkle Park\\", "TP0", helperFunctions);
	AddLevelLayout("Twinkle Park\\", "TP1", helperFunctions);
	AddLevelLayout("Twinkle Park\\", "TP2", helperFunctions);
	AddLevelLayout("Twinkle Park\\", "TPA", helperFunctions);
	AddLevelLayout("Twinkle Park\\", "TPB", helperFunctions);

	AddCam("CAM0300S", "CAM0300S");
	AddCam("CAM0301S", "CAM0301S");
	AddCam("CAM0302S", "CAM0302S");
	AddCam("CAM0305S", "CAM0305S");
}


ObjectListEntry TwinkleParkObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "O RING" } /* "O RING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79B2F0, "O GROUP RING" } /* "O GROUP RING" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7AC4F0, "O LINE RING V" } /* "O LINE RING V" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7ABE90, "O LINE RING" } /* "O LINE RING" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "O SPRING" } /* "O SPRING" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "O SPRING B" } /* "O SPRING B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79F860, "O SPRING H" } /* "O SPRING H" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O DUSH PANEL" } /* "O DUSH PANEL" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JUMP PANEL" } /* "O JUMP PANEL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRON BALL" } /* "O IRON BALL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O IRON BALL JG" } /* "O IRON BALL JG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE BOX" } /* "O RELEASE BOX" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 15, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ITEMBOX AIR" } /* "O ITEMBOX AIR" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "O ROCKET H" } /* "O ROCKET H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "O ROCKET HS" } /* "O ROCKET HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "O ROCKET V" } /* "O ROCKET V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "O ROCKET VS" } /* "O ROCKET VS" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O SAVE POINT" } /* "O SAVE POINT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "C WALL" } /* "C WALL" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "C OTTOTTO" } /* "C OTTOTTO" */,
	{ 2, 0, 1, 1000000, 0, (ObjectFuncPtr)0x4D4E10, "C NOT UNDER WATER" } /* "C NOT UNDER WATER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINT" } /* "O HINT" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x7AA960, "E AMEMB" } /* "E AMEMB" */,
	{ 15, 3, 1, 4000000, 0, (ObjectFuncPtr)0x79A9E0, "E CART" } /* "E CART" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7B2E00, "E BUYON" } /* "E BUYON" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x4AD140, "E SARU" } /* "E SARU" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0A70, "EROB COLLI" } /* "EROB COLLI" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x7B0EC0, "O CART STOPPER" } /* "O CART STOPPER" */,
	{ 10, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79D450, "O DASH PANEL 4 CART" } /* "O DASH PANEL 4 CART" */,
	{ 10, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79D9D0, "O JUMP PANEL 4 CART" } /* "O JUMP PANEL 4 CART" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79C430, "O ARCH 1" } /* "O ARCH 1" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79C750, "O ARCH 2" } /* "O ARCH 2" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79CB20, "O LIGHT 1" } /* "O LIGHT 1" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79CBB0, "O LIGHT 2" } /* "O LIGHT 2" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79D180, "O METEORITE 1" } /* "O METEORITE 1" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79D1A0, "O METEORITE 2" } /* "O METEORITE 2" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79D1C0, "O METEORITE 3" } /* "O METEORITE 3" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x6247C0, "O MONITOR" } /* "O MONITOR" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79DBC0, "O PANEL" } /* "O PANEL" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79D120, "O PLANET 1" } /* "O PLANET 1" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79D140, "O PLANET 2" } /* "O PLANET 2" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79D160, "O PLANET 3" } /* "O PLANET 3" */,
	{ 2, 3, 1, 12250000, 0, (ObjectFuncPtr)0x79CDF0, "O POLE" } /* "O POLE" */,
	{ 10, 3, 1, 1000000, 0, (ObjectFuncPtr)0x79C210, "O ROCKET" } /* "O ROCKET" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x79BC80, "O SATELLITE" } /* "O SATELLITE" */,
	{ 2, 3, 1, 9000000, 0, (ObjectFuncPtr)0x79B8B0, "O SHIP" } /* "O SHIP" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x624380, "O SHUTTER" } /* "O SHUTTER" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x623BB0, "O BALL" } /* "O BALL" */,
	{ 3, 3, 1, 90000, 0, (ObjectFuncPtr)0x624020, "O BARREL" } /* "O BARREL" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x61F8D0, "O BOW WINDOW" } /* "O BOW WINDOW" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x623450, "O BOWLING" } /* "O BOWLING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x61FE00, "O CANDLE 1" } /* "O CANDLE 1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x61FF50, "O CANDLE 2" } /* "O CANDLE 2" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x6223C0, "O CATAPULT" } /* "O CATAPULT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x61DC90, "O COASTER" } /* "O COASTER" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x61E5F0, "O DOOR" } /* "O DOOR" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x61E7C0, "O DOOR B" } /* "O DOOR B" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x61EAC0, "O DOUBLE DOOR" } /* "O DOUBLE DOOR" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x61F7D0, "O FENCE 1" } /* "O FENCE 1" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x61F7F0, "O FENCE 2" } /* "O FENCE 2" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x6201A0, "O FLAG 1" } /* "O FLAG 1" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x620230, "O FLAG 2" } /* "O FLAG 2" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x620540, "O FLAG W LAMP" } /* "O FLAG W LAMP" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x621850, "O FLOAT" } /* "O FLOAT" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x621BD0, "O FLYER" } /* "O FLYER" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x621DB0, "O FOOTHOLD" } /* "O FOOTHOLD" */,
	{ 2, 3, 1, 490000, 0, (ObjectFuncPtr)0x621670, "O GO ROUND" } /* "O GO ROUND" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x61F8F0, "O GIRDER" } /* "O GIRDER" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x61FA00, "O LAMP" } /* "O LAMP" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x620AF0, "O PIRATES" } /* "O PIRATES" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x6207F0, "O PIT" } /* "O PIT" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x61F810, "O PLANT 1" } /* "O PLANT 1" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x61F830, "O PLANT 2" } /* "O PLANT 2" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x61F850, "O PLANT 3" } /* "O PLANT 3" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x61F870, "O PLANT 4" } /* "O PLANT 4" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x61F890, "O PLANT 5" } /* "O PLANT 5" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x61F8B0, "O PLANT 6" } /* "O PLANT 6" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x61F4A0, "O TP RING" } /* "O TP RING" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x61F030, "O ROOF" } /* "O ROOF" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x5977F0, "S BASS" } /* "S BASS" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A7AD0, "S BIGKAERU" } /* "S BIGKAERU" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x597660, "S GENE" } /* "S GENE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A8E50, "O BUBBLE" } /* "O BUBBLE" */,
	{ 2, 4, 0, 0, 0, (ObjectFuncPtr)0x7A8A60, "O BUBBLES" } /* "O BUBBLES" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x61EEE0, "O DOOR MIRROR" } /* "O DOOR MIRROR" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" }, /* "O FROG" */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" } //Mystic Melody
};

PVMEntry TwinkleParkObjectTextures[] = {
	{ "OBJ_TWINKLE", (TexList*)0x279BF68 },
	{ "E_BUYON", (TexList*)0x38E23E4 },
	{ "E_AMENBO", (TexList*)0x38CD5E0 },
	{ "BG_SHAREOBJ", (TexList*)0x38A6BE8 },
	{ "E_SARU", (TexList*)0x962560 },
	{ "KOAR", (TexList*)0x9359B4 },
	{ "WARA", (TexList*)0x93852C },
	{ "USA", (TexList*)0x93CF74 },
	{ "ZOU", (TexList*)0x94160C },
	{ "BANB", (TexList*)0x93A8BC },
	{ "TOGEBALL_TOGEBALL", (TexList*)0x96BC54 },
	{ "E_BOMB", (TexList*)0x96B464 },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "common-obj", &SA2_OBJ_TEXLIST },
	{ 0 }
};

ObjectList TwinkleParkObjectList = { arraylengthandptrT(TwinkleParkObjectList_list, int) };


void __cdecl TPObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_TwinklePark * 8 + 1] = &TwinkleParkObjectList;
	TexLists_Obj[LevelIDs_TwinklePark] = TwinkleParkObjectTextures;
}