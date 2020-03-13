#pragma once
#pragma region Requirements
#include "PCH.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <filesystem>
#include <chrono>

//NOTICE!!!: To hide console change subsystem to Windows and add sfml-main.lib to additional libraries in LINKER.

//TODO: Fix warnings
//#pragma warning( disable : 4018) // signed/unsigned mismatch
#pragma warning( disable : 4244)	// int to float, data loss

using namespace std;
using namespace sf;
#pragma endregion

#pragma region Globals
// TODO: some of these may be class privates
extern const filesystem::path ROOT_PATH;
extern const string ICON_LOCATION;
extern const string FONT_LOCATION;
extern const float LBL_OFFSET;		// Offsets are mainly used horizontally
extern const float GRD_OFFSET;
extern const float EP_OFFSET;
extern const float B_OFFSET;
extern int startY;
extern int startX;
extern int targetY;
extern int targetX;
extern bool has_start;
extern bool has_target;
extern int maze_size_max;

extern const Color grey_out;
extern Vector2i click_position;
enum class CellType { Normal, Start, Target, Wall, Path, Visited, cycle };
enum class FutureStatus { Running, Finished, Other };
#pragma endregion

#pragma region Templates and Functions
template<typename ObjectType>
void focus_object(Vector2i click, ObjectType* object) {
	// Template function used to select <object>.

	if (click.x >= object->getPosition().x && click.x <= object->getPosition().x + object->getSize().x
		&& click.y >= object->getPosition().y && click.y <= object->getPosition().y + object->getSize().y) {	// Checks if the click is inside the object boundaries
		object->setFocus(true);	// Gives focus to object
		object->clear();		// When focused reset to default state.

		return;
	}
	else {
		object->setFocus(false);
		return;
	}
}

template<typename ObjectType>
vector<Vector2i> getBounds(ObjectType* object) {
	// Returns a Vector2i with the graphical size of <object> including every outline and 'external' element.

	vector<Vector2i> bounds;
	bounds.clear();
	bounds.resize(2);

	bounds[0] = Vector2i(object->getPosition().x, object->getPosition().y);
	bounds[1] = Vector2i(object->getLimitPosition().x,
		object->getLimitPosition().y);

	return bounds;
}

inline bool click_in_bounds(Vector2i click, vector<Vector2i> bounds) {
	// Checks if click is inside <bounds>

	if (click.x > bounds[0].x&& click.x < bounds[1].x
		&& click.y > bounds[0].y&& click.y < bounds[1].y) {
		return true;
	}

	return false;
}

template<typename ObjectType1, typename ObjectType2>
void tieObjects(ObjectType1* obj_1, ObjectType2* obj_2) {
	// Connects 2 objects by reciprocally passing each other as a variable.

	obj_1->tieTo(obj_2);
	obj_2->tieTo(obj_1);
}

inline void windowResize(RenderWindow* window_name, Vector2u new_size) {
	// Function needed to resize the window (and necessary view update)

	View view(window_name->getDefaultView());

	window_name->setSize(new_size);
	window_name->setView(view = View(FloatRect(0.f, 0.f,
		static_cast<float>(window_name->getSize().x),
		static_cast<float>(window_name->getSize().y))));
}
#pragma endregion
