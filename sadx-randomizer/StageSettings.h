#pragma once
void Set_BackRing();
void BackRing();
void BackRing2();

void ResetTime_R();
void FixLayout_StartPosition_R();
void FixRestartCheckPoint();

ObjectFunc(EggHornet_Load, 0x572230);
void __cdecl CheckLoadBalloon_r(ObjectMaster* a1);
void __cdecl CheckLoadFroggy_r(ObjectMaster* a1);

enum Color {
	BlackColor, BlueColor, GreenColor, LightBlueColor, OrangeColor, PurpleColor, RedColor
};