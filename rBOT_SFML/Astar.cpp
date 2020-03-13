#pragma once
#include "PCH.h"
#include "Astar.h"

namespace astar {
	struct Node {
		int x;
		int y;
		float globalGoal;
		float localGoal;
		CellType type = CellType::Normal;
		vector<Node*> neighbours;
		Node* parent;
	};

	bool  successful = false;
	double processing_time;
	vector<vector<Node>>  maze;
	Node* nodeStart;
	Node* nodeEnd;
	list<Node*> SolutionPath;
	list<Node*> Walls;

	// Initialize the grid, converts the graphical maze to a grid of Nodes*.
	void create_maze(Grid* maze_grid) {

		maze.clear();
		SolutionPath.clear();
		Walls.clear();

		maze.resize(maze_grid->getMapSize().x);

		for (size_t x = 0; x < maze_grid->getMapSize().x; x++) {
			maze[x].resize(maze_grid->getMapSize().y);
		}

		for (int x = 0; x < maze_grid->getMapSize().x; x++) {
			for (int y = 0; y < maze_grid->getMapSize().y; y++) {
				maze[x][y].x = x;
				maze[x][y].y = y;
				maze[x][y].globalGoal = INFINITY;
				maze[x][y].localGoal = INFINITY;
				maze[x][y].parent = nullptr;
				maze[x][y].type = maze_grid->grid[x][y].getType();
			}
		}

		for (int x = 0; x < maze_grid->getMapSize().x; x++) {
			for (int y = 0; y < maze_grid->getMapSize().y; y++) {
				if (x - 1 >= 0 && x - 1 < maze_grid->getMapSize().x && y >= 0 && y < maze_grid->getMapSize().y) {			// LEFT : x - 1
					maze[x][y].neighbours.push_back(&maze[x - 1][y]);
				}

				if (x + 1 >= 0 && x + 1 < maze_grid->getMapSize().x && y >= 0 && y < maze_grid->getMapSize().y) {			// RIGHT : x + 1
					maze[x][y].neighbours.push_back(&maze[x + 1][y]);
				}

				if (x >= 0 && x < maze_grid->getMapSize().x && y - 1 >= 0 && y - 1 < maze_grid->getMapSize().y) {			// DOWN : y - 1
					maze[x][y].neighbours.push_back(&maze[x][y - 1]);
				}

				if (x >= 0 && x < maze_grid->getMapSize().x && y + 1 >= 0 && y + 1 < maze_grid->getMapSize().y) {			// UP : y + 1
					maze[x][y].neighbours.push_back(&maze[x][y + 1]);
				}
			}
		}

		for (int x = 0; x < maze_grid->getMapSize().x; x++) {
			for (int y = 0; y < maze_grid->getMapSize().y; y++) {
				if (maze_grid->grid[x][y].getType() == CellType::Wall) {
					Walls.push_back(&maze[x][y]);
					maze[x][y].type = CellType::Wall;
				}
			}
		}

		nodeStart = &maze[startX][startY];
		nodeEnd = &maze[targetX][targetY];
	}

	// Solve the maze
	bool solve(Grid* GRD_maze) {
		chrono::time_point start_time = chrono::steady_clock::now();

		create_maze(GRD_maze);

		auto distance = [](Node* a, Node* b) {
			return sqrtf((float)((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y)));
		};

		auto heuristic = [distance](Node* a, Node* b) {
			return distance(a, b);
		};

		Node* nodeCurrent = nodeStart;
		nodeStart->localGoal = 0.0f;
		nodeStart->globalGoal = heuristic(nodeStart, nodeEnd);

		list<Node*> nodesToTest;
		nodesToTest.push_back(nodeStart);

		while (!nodesToTest.empty() && nodeCurrent != nodeEnd) {
			nodesToTest.sort([](const Node* lhs, const Node* rhs) {return lhs->globalGoal < rhs->globalGoal; });

			while (!nodesToTest.empty() && (nodesToTest.front()->type == CellType::Visited)) {
				nodesToTest.pop_front();
			}

			if (nodesToTest.empty())
				break;

			nodeCurrent = nodesToTest.front();
			nodeCurrent->type = CellType::Visited;
			if (nodeCurrent != nodeStart && nodeCurrent != nodeEnd) {
				GRD_maze->grid[nodeCurrent->x][nodeCurrent->y].setType(CellType::Visited);
			}

			for (auto nodeNeighbour : nodeCurrent->neighbours) {
				if ((nodeNeighbour->type != CellType::Visited) && nodeNeighbour->type != CellType::Wall) {
					nodesToTest.push_back(nodeNeighbour);
				}

				float PossiblyLowerGoal = nodeCurrent->localGoal + distance(nodeCurrent, nodeNeighbour);

				if (PossiblyLowerGoal < nodeNeighbour->localGoal) {
					nodeNeighbour->parent = nodeCurrent;
					nodeNeighbour->localGoal = PossiblyLowerGoal;

					nodeNeighbour->globalGoal = nodeNeighbour->localGoal + heuristic(nodeNeighbour, nodeEnd);
				}
			}
		}

		if (nodeEnd != nullptr) {
			Node* p = nodeEnd;
			while (p->parent != nullptr && p->parent != nodeStart) {
				p = p->parent;
				SolutionPath.push_back(p);
				GRD_maze->grid[p->x][p->y].setType(CellType::Path);
				maze[p->x][p->y].type = CellType::Path;
			}

			chrono::time_point end_time = chrono::steady_clock::now();
			processing_time = chrono::duration <double, milli>(end_time - start_time).count();
			return successful = true;
		}
		else {
			chrono::time_point end_time = chrono::steady_clock::now();
			processing_time = chrono::duration <double, milli>(end_time - start_time).count();
			return successful = false;
		}
	}

	// Format of save, function hidden in namespace from outside access. See astar::save::save().
	bool save_func(CustomFile* save_file) {
		maze[nodeStart->x][nodeStart->y].type = CellType::Start;
		maze[nodeEnd->x][nodeEnd->y].type = CellType::Target;
		save_file->clear();
		save_file->write("Starting position:\t" + to_string(nodeStart->x) + "-" + to_string(nodeStart->y) + "\n");
		save_file->write("Target position:\t" + to_string(nodeEnd->x) + "-" + to_string(nodeEnd->y) + "\n");

		save_file->write("Walls: ");
		int wall_amount = Walls.size();
		if (wall_amount != 0) {
			for (int i = 0; i < wall_amount; i++) {
				save_file->write("(" + to_string(Walls.front()->y) + "-" + to_string(Walls.front()->x) + ") ");
				Walls.pop_front();
			}
		}
		else
			save_file->write("None");

		save_file->write("\n\n");

		save_file->write("Successful: ");
		if (successful == true) {
			save_file->write("TRUE");
		}
		else
			save_file->write("FALSE");

		save_file->write("\n");
		save_file->write("Solutions: START -> ");

		int path_size = SolutionPath.size();
		for (int i = 0; i < path_size; i++) {
			save_file->write("(" + to_string(SolutionPath.back()->y) + "-" + to_string(SolutionPath.back()->x) + ") -> ");
			SolutionPath.pop_back();
		}
		save_file->write("TARGET");
		save_file->write("\n\n");
		save_file->write("Maze graphical representation:\n");

		save_file->write("#");
		for (size_t i = 0; i <= (maze[1].size() * 2); i++) {
			save_file->write("-");
		}
		save_file->write("#");
		save_file->write("\n");

		for (unsigned int x = 0; x < maze.size(); x++) {
			save_file->write("| ");
			for (unsigned int y = 0; y < maze[1].size(); y++) {
				switch (maze[x][y].type) {
				case CellType::Normal:
					save_file->write("·");
					break;

				case CellType::Start:
					save_file->write("S");
					break;

				case CellType::Target:
					save_file->write("T");
					break;

				case CellType::Wall:
					save_file->write("#");
					break;

				case CellType::Path:
					save_file->write("■");
					break;

				case CellType::Visited:
					save_file->write("≡");
					break;
				}
				save_file->write(" ");
			}
			save_file->write("|\n");
		}

		save_file->write("#");
		for (size_t i = 0; i <= (maze[1].size() * 2); i++) {
			save_file->write("-");
		}
		save_file->write("#");
		save_file->write("\n");
		save_file->write("Elapsed time: ");
		save_file->write(to_string(processing_time));
		save_file->write("ms");

		return true;
	}

	// Namespace for saving operations.
	namespace save {
		future<bool> saving_thread;

		// save_func() is a slow running, non-crucial function, it gets started in an async thread.
		bool save(CustomFile* save_file) {
			saving_thread = async(launch::async, astar::save_func, save_file);

			return true;
		}

		// Gets the status of thread spawned by astar::save::save().
		FutureStatus getStatus() {
			try {	// May have issues checking the future's status, so we use try-catch(...). (eg: future has been destroyed earlier).
				if (saving_thread.valid() && saving_thread.wait_for(chrono::milliseconds(0)) != future_status::ready) {
					return FutureStatus::Running;
				}
				else if (saving_thread.valid() && saving_thread.wait_for(chrono::milliseconds(0)) == future_status::ready) {
					return FutureStatus::Finished;
				}
			}
			catch (...) {
				cout << "[ERROR] Status of future is not defined." << endl;
			}

			return FutureStatus::Other;
		}

		// Wait for save_func() to finish. Used mainly for saving before the programs gets terminated.
		bool wait() {
			saving_thread.wait();
			return true;
		}
	}
}