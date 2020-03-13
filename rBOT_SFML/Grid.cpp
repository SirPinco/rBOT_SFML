#pragma once
#include "PCH.h"
#include "Grid.h"

#pragma region public:
Grid::Grid() {
	// Object constructor, creates an empty grid.

	grid_position = { 0, 0 };
	focus = false;

	srand(time(0));
}

void Grid::setMapSize(int size) {
	// Sets the size of the grid by changing the amount of cells.

	// TODO: Right now I'm doing a square so I use only one of the coords, should update it so that I use both X and Y to create a rectangle
	map_size.x = size;
	map_size.y = size;

	if (map_size.x > 0) {
		grid.resize(map_size.x);

		for (size_t k = 0; k < grid.size(); k++) {
			grid[k].resize(map_size.y);
		}

		reset_map();
		setPosition(grid_position.x, grid_position.y);
	}
	else if (map_size.x == 0) {
		grid.clear();
	}
	else
		cout << "ERROR Wrong map size?" << endl;
}

Vector2f Grid::getMapSize() {
	// Returns a Vector2f with the map size.

	return map_size;
}

Vector2f Grid::getSize() {
	// Returns a Vector2f with the graphical size.

	float width;
	float height;

	if (grid.size() > 1) {
		width = grid[0][0].getPosition().x + grid[0][grid.size() - 1].getLimitPosition().x;
	}
	else {
		width = 0;
	}

	if (grid.size() > 1) {
		height = grid[0][0].getPosition().y + grid[grid.size() - 1][0].getLimitPosition().y;
	}
	else {
		height = 0;
	}

	return Vector2f(width, height);
}

void Grid::setPosition(float x, float y) {
	// Sets the position of the grid.
	grid_position.x = x;
	grid_position.y = y;

	// Sets the position of the cells with an offset of <padding> between each other; left-to-right, top to bottom.
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid.size(); j++) {
			grid[i][j].setPosition(grid_position.x + grid[i][j].getSize().x * j + padding * j,
				grid_position.y + grid[i][j].getSize().y * i + padding * i);
		}
	}
}

Vector2f Grid::getPosition() {
	// Returns a Vector2f with the coordinates of the grid.

	if (grid.size() > 0) {
		return grid[0][0].getPosition();	// Top-most, left-most cell.
	}

	return Vector2f(0, 0);
}

void Grid::setFocus(bool value) {
	// Sets the grid in focus and reacts with the cell according to the click position.

	focus = value;

	//TODO: EXTREMELY inefficient!
	for (size_t i = 0; i < map_size.x; i++) {
		for (size_t j = 0; j < map_size.x; j++) {
			if (click_in_bounds(click_position, getBounds(&grid[i][j]))) {
				grid[i][j].setType(CellType::cycle);		// Cycle cell type
				if (grid[i][j].getType() == CellType::Start) {	// Record start cell coordinates
					startX = i;
					startY = j;
				}
				else if (grid[i][j].getType() == CellType::Target) {	// Record start cell coordinates
					targetX = i;
					targetY = j;
				}
				else if (grid[i][j].getType() == CellType::Normal) {
					for (size_t k = 0; k < map_size.x; k++) {
						for (size_t l = 0; l < map_size.y; l++) {
							if (grid[k][l].getType() == CellType::Path || grid[k][l].getType() == CellType::Visited) {
								grid[k][l].setType(CellType::Normal);
							}
						}
					}
				}
			}
		}
	}

	if (has_target == false || has_start == false) {
		for (size_t i = 0; i < map_size.x; i++) {
			for (size_t j = 0; j < map_size.y; j++) {
				if (grid[i][j].getType() != CellType::Start && grid[i][j].getType() != CellType::Target && grid[i][j].getType() != CellType::Wall) {
					grid[i][j].setType(CellType::Normal);
				}
			}
		}
	}
}

bool Grid::isFocused() {
	// Returns the focus type.True = focused, false = not in focus.

	return focus;
}

Vector2f Grid::getLimitPosition() {
	// Returns position of right-most point of object (.x) or bottom-most (.y)

	if (grid.size() > 0) {
		return grid[grid.size() - 1][grid.size() - 1].getLimitPosition();
	}

	return Vector2f(0, 0);
}

void Grid::reset_map() {
	// Resets all cell to Normal type, resets start and target locations.

	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid.size(); j++) {
			grid[i][j].setType(CellType::Normal);
		}
	}

	startX = -1;
	startY = -1;
	targetX = -1;
	targetY = -1;

	has_start = false;
	has_target = false;
}

void Grid::clear() {
	// Placeholder necessary for focus_object() and tie().
}

void Grid::randomizeWalls(int multiplier) {
	// Sets walls randomly, <multiplier> changes the amount of walls by changing the chances of picking 1.

	for (size_t x = 0; x < grid.size(); x++) {
		for (size_t y = 0; y < grid[x].size(); y++) {
			if (grid[x][y].getType() != CellType::Start && grid[x][y].getType() != CellType::Target) {
				if ((rand() % multiplier) == 1)
					grid[x][y].setType(CellType::Wall);
				else
					grid[x][y].setType(CellType::Normal);
			}
		}
	}
}
#pragma endregion