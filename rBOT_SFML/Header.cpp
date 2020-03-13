#pragma once
#include "PCH.h"
#include "Header.h"

#pragma region Globals
const filesystem::path ROOT_PATH = filesystem::current_path();
const string ICON_LOCATION = ROOT_PATH.generic_string() + "/Resources/window-icon.png";
const string FONT_LOCATION = ROOT_PATH.generic_string() + "/Resources/Pixel NES.otf";
const float LBL_OFFSET = 14;	// Offsets are mainly used horizontally
const float GRD_OFFSET = 25;
const float EP_OFFSET = 7;
const float B_OFFSET = 15;
bool has_start = false;
bool has_target = false;
int maze_size_max = 35;

const Color grey_out = Color(180, 180, 180);
Vector2i click_position = { 0, 0 };
#pragma endregion