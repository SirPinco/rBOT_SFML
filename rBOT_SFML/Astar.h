#pragma once
#include "PCH.h"
#include "Header.h"
#include "Grid.h"
#include "CustomFile.h"
#include <chrono>
#include <future>
#pragma warning(disable : 26495)	// Node variables cannot be initalised

namespace astar {
	void create_maze(Grid* maze_grid);
	bool solve(Grid* maze);

	namespace save {
		bool save(CustomFile* save_file);
		FutureStatus getStatus();
		bool wait();
	}
}
