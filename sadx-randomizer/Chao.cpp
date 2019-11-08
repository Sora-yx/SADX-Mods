#include "stdafx.h"
#include "RandomHelpers.h"

ObjectMaster* ChaoObject;
ObjectMaster* CurrentChao;

uint8_t SelectedChao = 0;
bool ArePvpLoaded = false;

std::vector<NJS_PLANE> waterlist = {};

FunctionPointer(int, Chao_Animation, (ObjectMaster* a1, int a2), 0x734F00);

int GetCurrentChaoStage_r() {
	if (ChaoObject) return 5;
	else return CurrentChaoStage;
}

void ChaoObj_Animate(int id, int length) {
	if (FrameCounterUnpaused % length == 0) {
		Chao_Animation(CurrentChao, id);
	}
}

void ChaoObj_Delete(ObjectMaster* a1) {
	DeleteObjectMaster(ChaoManager);
	ChaoManager = nullptr;

	//DeleteObjectMaster(CurrentChao);
	CurrentChao = nullptr;
	ChaoObject = nullptr;

	//Release the chao textures
	FreeChaoTexlists();

	//reset default water height
	float height = 0;
	WriteData((float*)0x73C24C, height);
}

void ChaoObj_Main(ObjectMaster* a1) {
	uint8_t Action = a1->Data1->Action;

	if (Action == 0) {
		if (!CurrentLandTable) return;

		//Load the chao textures
		LoadChaoTexlist("AL_DX_PARTS_TEX", (NJS_TEXLIST*)0x33A1340, 0);
		LoadChaoTexlist("AL_BODY", ChaoTexLists, 0);
		LoadChaoTexlist("AL_jewel", &ChaoTexLists[4], 0);
		LoadChaoTexlist("AL_ICON", &ChaoTexLists[3], 0);
		LoadChaoTexlist("AL_EYE", &ChaoTexLists[2], 0);
		LoadChaoTexlist("AL_MOUTH", &ChaoTexLists[5], 0);
		LoadChaoTexlist("AL_TEX_COMMON", &ChaoTexLists[1], 1u);

		//PVPs only need to be loaded once
		if (!ArePvpLoaded) {
			al_confirmload_load();
			LoadChaoPVPs();
			ArePvpLoaded = true;
		}

		ChaoManager_Load(); //Load chao behaviour

		a1->DeleteSub = ChaoObj_Delete; //When you quit a level
		a1->Data1->Action = 1; //Wait a frame before loading the chao
	}
	else if (Action == 1) {
		//We get the chao data in the savefile
		ChaoData* chaodata = new ChaoData();

		//Start position is behind the player
		NJS_VECTOR v = a1->Data1->Position;

		//Load the chao
		CurrentChao = CreateChao(chaodata, 0, CurrentChao, &v, 0);

		a1->Data1->Action = 2;
	}
	else {
		ChaoObj_Animate(2, 33);
		CurrentChao->Data1->Position = a1->Data1->Position;

		//water height
		float height = -10000000;
		WriteData((float*)0x73C24C, height);

		if (IsPlayerInsideSphere(&a1->Data1->Position, 8)) { //hitbox
			if (TimeThing != 0)
			{
				LoadLevelResults();
				DeleteObject_(a1);
			}
		}
	}
}

void Chao_Init() {
	//Trick the game into thinking we're in a specific chao garden
	//Needed to change the water height
	WriteJump((void*)0x715140, GetCurrentChaoStage_r);
}

void Chao_OnFrame() {
	if (!ChaoObject && CurrentMission == 1 && CurrentLevel < 15) {
		ChaoObject = LoadObject((LoadObj)(LoadObj_Data1), 1, ChaoObj_Main);

		NJS_VECTOR pos;
		float Yrot;

		//position for each levels
		switch (CurrentLevel)
		{
		case LevelIDs_EmeraldCoast:
			pos = { 3857.76, 597.395, -2896.18 };
			Yrot = 0x8000;
			break;
		case LevelIDs_WindyValley:
			pos = { 4156.34, -4483, -1783 };
			Yrot = 0x8000;
			break;
		case LevelIDs_Casinopolis:
			pos = { -361, 380, -40 };
			Yrot = 0x8000;
			break;
		case LevelIDs_IceCap:
			pos = { 1480.62, 573.3, -256.67 };
			Yrot = 0x8000;
			break;
		case LevelIDs_TwinklePark:
			pos = { 520, 1333, 1630 };
			Yrot = 0x8000;
			break;
		case LevelIDs_SpeedHighway:
			pos = { 4455, -368.395, 2930.18 };
			Yrot = 0x8000;
			break;
		case LevelIDs_RedMountain:
			pos = { -3861.85, 883.96, -2974.81 };
			Yrot = 0x8000;
			break;
		case LevelIDs_SkyDeck:
			pos = { 448.18, -450, 3732.73 };
			Yrot = 0x8000;
			break;
		case LevelIDs_LostWorld:
			pos = { 7410, -1964, 1316 };
			Yrot = 0x8000;
			break;
		}

		ChaoObject->Data1->Position = pos;
		ChaoObject->Data1->Rotation.y = Yrot;
	}


}


