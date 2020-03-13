#pragma once
#include "PCH.h"
#include "Cell.h"
#include <ctime>
#include <cstdlib>

class Grid : public Drawable {
public:
	Grid();

	void setMapSize(int size);
	Vector2f getMapSize();
	Vector2f getSize();
	void setPosition(float x, float y);
	Vector2f getPosition();
	void setFocus(bool value);
	bool isFocused();
	Vector2f getLimitPosition();
	vector<vector<Cell>> grid;
	void reset_map();
	void randomizeWalls(int multiplier = 5);
	void clear();

private:
	// Necessary draw function ovverride for custom Drawables
	virtual void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (size_t i = 0; i < grid.size(); i++) {
			for (size_t j = 0; j < grid.size(); j++) {
				target.draw(grid[i][j], states);
			}
		}
	}

	Vector2f map_size = Vector2f(0, 0);
	bool focus;

	int padding = 0;	// Space between cells
	Vector2f grid_position;
};