#pragma once
#include "PCH.h"
#include "Header.h"
#include "Label.h"
#include "Textbox.h"
#include "Grid.h"
#include "ErrorProvider.h"
#include "Button.h"
#include "AestethicShape.h"
#include "Astar.h"
#include "CustomFile.h"

// Setting default pre-run values
int targetX = -1;
int targetY = -1;
int startX = -1;
int startY = -1;
int default_win_x;
int default_win_y;

Image window_icon;
RenderWindow WND_Main(VideoMode(250, 250), "rBOT", Style::Close | Style::Titlebar);

Label LBL_MazeSize("Maze size:");
Label LBL_Start("Start:");
Label LBL_StartCoords;
Label LBL_Target("Target:");
Label LBL_TargetCoords;
Label LBL_Status("Status:");
Label LBL_Saving;
Textbox TB_MazeSize(true);
Grid GRD_Map;
ErrorProvider EP_MazeSize;
Button B_Run("RUN");
Button B_Reset("RESET");
Button B_RandomWalls("random walls");
AestethicShape  SHP_Separator;		// Grey line between info and maze
AestethicShape  SHP_BackBox;		// Light box behind info
CustomFile CF_Outcome("Results.log");

/*
	Inizialisation of all graphical objects.
*/
void OBJs_INIT() {
	LBL_MazeSize.setPosition(1.5 * LBL_OFFSET, 1.5 * LBL_OFFSET);

	LBL_Start.setCharacterSize(18);
	LBL_Start.setPosition(LBL_MazeSize.getPosition().x, LBL_MazeSize.getLimitPosition().y + 1.5 * LBL_OFFSET);
	LBL_Target.setCharacterSize(18);
	LBL_Target.setPosition(LBL_Start.getPosition().x, LBL_Start.getLimitPosition().y + LBL_OFFSET);

	//TODO: Make it so that the coords' dash stays still while the numbers change
	//TODO: GetLimitPosition has to take into account where the origin is
	LBL_StartCoords.setCharacterSize(12);
	LBL_StartCoords.setTextColor(Color::Green);
	LBL_StartCoords.setOutlineThickness(2);
	LBL_StartCoords.setOutlineColor(Color::Black);
	LBL_StartCoords.setString(to_string((int)pow(10, TB_MazeSize.getMaxLength() - 1)) + " - " + to_string((int)pow(10, TB_MazeSize.getMaxLength() - 1)));
	LBL_StartCoords.setOrigin(LBL_StartCoords.getGlobalBounds().width / 2, LBL_StartCoords.getOrigin().y - LBL_StartCoords.getOutlineThickness());		// Center origin in the middle of the dash.
	LBL_StartCoords.setPosition(LBL_Start.getPosition().x + 11 * LBL_OFFSET,
		LBL_Start.getPosition().y + (LBL_Start.getGlobalBounds().height - LBL_StartCoords.getGlobalBounds().height) / 2);			// !!!: Center is in the middle of the dash!

	LBL_TargetCoords.setCharacterSize(12);
	LBL_TargetCoords.setTextColor(Color::Red);
	LBL_TargetCoords.setOutlineThickness(2);
	LBL_TargetCoords.setOutlineColor(Color::Black);
	LBL_TargetCoords.setString(to_string((int)pow(10, TB_MazeSize.getMaxLength() - 1)) + " - " + to_string((int)pow(10, TB_MazeSize.getMaxLength() - 1)));
	LBL_TargetCoords.setOrigin(LBL_TargetCoords.getGlobalBounds().width / 2, LBL_TargetCoords.getOrigin().y - LBL_TargetCoords.getOutlineThickness());	// Center origin in the middle of the dash.
	LBL_TargetCoords.setPosition(LBL_StartCoords.getPosition().x,
		LBL_Target.getPosition().y + (LBL_Target.getGlobalBounds().height - LBL_TargetCoords.getGlobalBounds().height) / 2);	// !!!: Center is in the middle of the dash!

	LBL_StartCoords.setString("-");
	LBL_StartCoords.setOrigin(LBL_StartCoords.getGlobalBounds().width / 2, LBL_StartCoords.getOrigin().y - LBL_StartCoords.getOutlineThickness());
	LBL_TargetCoords.setString("-");
	LBL_TargetCoords.setOrigin(LBL_TargetCoords.getGlobalBounds().width / 2, LBL_TargetCoords.getOrigin().y - LBL_TargetCoords.getOutlineThickness());

	TB_MazeSize.setTextSize(18);
	TB_MazeSize.setPosition(LBL_MazeSize.getLimitPosition().x + 2 * LBL_OFFSET,
		LBL_MazeSize.getPosition().y + (LBL_MazeSize.getGlobalBounds().height - TB_MazeSize.getTextBounds().height) / 2);

	SHP_Separator.setSize(1, WND_Main.getSize().y);
	SHP_Separator.setFillColor(grey_out);
	SHP_Separator.setPosition(TB_MazeSize.getLimitPosition().x + LBL_MazeSize.getPosition().x + TB_MazeSize.getOutlineThickness(), 0);

	B_Run.setFillColor(Color(84, 255, 89));
	B_Run.setSize((TB_MazeSize.getLimitPosition().x + TB_MazeSize.getOutlineThickness() - LBL_MazeSize.getPosition().x - B_OFFSET) / 2, 30);
	B_Run.setPosition(LBL_Target.getPosition().x, LBL_Target.getLimitPosition().y + 3 * LBL_OFFSET);

	B_Reset.setFillColor(Color(255, 69, 22));
	B_Reset.setSize(B_Run.getSize().x, B_Run.getSize().y);
	B_Reset.setPosition(B_Run.getLimitPosition().x - B_Run.getOutlineThickness() + B_OFFSET, B_Run.getPosition().y);

	B_RandomWalls.setFillColor(Color(grey_out));
	B_RandomWalls.setSize(B_Reset.getLimitPosition().x - B_Run.getPosition().x, 20);
	B_RandomWalls.setPosition(B_Run.getPosition().x, B_Run.getPosition().y - B_RandomWalls.getGlobalBounds().height - 5);

	SHP_BackBox.setFillColor(Color(235, 235, 235));
	SHP_BackBox.setOutlineThickness(2);
	SHP_BackBox.setOutlineColor(Color::Black);
	SHP_BackBox.setSize(SHP_Separator.getPosition().x - LBL_MazeSize.getPosition().x, B_Run.getLimitPosition().y);
	SHP_BackBox.setPosition(LBL_MazeSize.getPosition().x / 2, LBL_MazeSize.getPosition().y / 2);

	LBL_Saving.setString("Saving to /" + CF_Outcome.getFileName() + "...");
	LBL_Saving.setCharacterSize(12);
	LBL_Saving.setTextColor(Color::Black);
	LBL_Saving.setPosition(SHP_BackBox.getPosition().x, floor(SHP_BackBox.getLimitPosition().y + LBL_OFFSET));

	windowResize(&WND_Main, Vector2u(SHP_Separator.getPosition().x, SHP_BackBox.getLimitPosition().y - SHP_BackBox.getOutlineThickness() + LBL_MazeSize.getPosition().x / 2));

	GRD_Map.setPosition(SHP_Separator.getLimitPosition().x + GRD_OFFSET, SHP_BackBox.getPosition().y);
	default_win_x = WND_Main.getSize().x;
	default_win_y = WND_Main.getSize().y;
}

//- ####################################################################################################

//- ####################################################################################################

int main() {
	if (window_icon.loadFromFile(ICON_LOCATION)) {	// Loads window icon
		cout << "Icon loaded from: " << ICON_LOCATION << endl;
		WND_Main.setIcon(512, 512, window_icon.getPixelsPtr());
	}
	else {
		cout << "[ERROR] Failed to load icon.";
		return EXIT_FAILURE;
	}

	if (filesystem::exists(FONT_LOCATION)) {		// Check if default font file is available
		cout << "Font loaded from: " << FONT_LOCATION << endl;
	}
	else {
		cout << "[ERROR] Failed to locate font file.";
		return EXIT_FAILURE;
	}

	OBJs_INIT();
	tieObjects(&TB_MazeSize, &EP_MazeSize);

	//-------------------------------------------------------------------------------------------------------

	while (WND_Main.isOpen()) {
		WND_Main.setFramerateLimit(60);
		Event event;

		while (WND_Main.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:		// Closes the program correctly when the red 'X' is clicked.
				if (astar::save::getStatus() == FutureStatus::Running)
					astar::save::wait();
				WND_Main.close();

			case Event::TextEntered:	// Enters text in the focused TB (textbox)
				if (TB_MazeSize.isFocused()) {	// Check if TB_MazeSize is selected
					if (TB_MazeSize.input(event.text.unicode)) {	// If an acceptable char is entered proceed
						TB_MazeSize.setTextColor(Color::Black);
						if (TB_MazeSize.getString().getSize() == 0) {	// No text (number) means that there is no maze (size = 0)
							GRD_Map.setMapSize(0);
						}
						else if (stoi(string(TB_MazeSize.getString())) == 0		// Maze size must be resonable (longer path = longer process time)
							|| stoi(string(TB_MazeSize.getString())) > maze_size_max) {
							TB_MazeSize.setEP(true);	// Raise red dot to signal there is an error: number too big or 0
						}
						else {
							GRD_Map.setMapSize(stoi(TB_MazeSize.getString().toAnsiString()));	// Input number = maze size
							TB_MazeSize.setEP(false);	// Disable a previously raised error dot
						}

						// Resize window according to the grid size
						windowResize(&WND_Main, Vector2u(
							max(GRD_Map.getLimitPosition().x + GRD_OFFSET, (float)default_win_x),
							max(GRD_Map.getLimitPosition().y + GRD_Map.getPosition().y, (float)default_win_y)));

						// Resize grey line (separator) according to the new window height
						SHP_Separator.setSize(SHP_Separator.getSize().x, WND_Main.getSize().y);
					}
				}

			case Event::MouseButtonPressed:	// Registers a click
				click_position = Mouse::getPosition(WND_Main);	// Record position
				if (event.mouseButton.button == Mouse::Left) {	// Check if it was a left click (main mouse button)
					focus_object(click_position, &TB_MazeSize);		// Focus on the object corresponding the location
					focus_object(click_position, &B_Run);			// ''
					focus_object(click_position, &B_Reset);			// ''
					focus_object(click_position, &B_RandomWalls);	// ''

					if (GRD_Map.getMapSize().x > 0 && GRD_Map.getMapSize().y > 0) {
						focus_object(click_position, &GRD_Map);	// Focus GRD as long as it exists

						//Update start and target coordinates labels.
						if (startX >= 0 && startX <= maze_size_max && startY >= 0 && startY <= maze_size_max) {
							LBL_StartCoords.setString(to_string(startY) + " - " + to_string(startX));
						}
						else {
							LBL_StartCoords.setString("-");
						}
						if (targetX >= 0 && targetX <= maze_size_max && targetY >= 0 && targetY <= maze_size_max) {
							LBL_TargetCoords.setString(to_string(targetY) + " - " + to_string(targetX));
						}
						else {
							LBL_TargetCoords.setString("-");
						}

						// Set the origin in the middle of the dash.
						LBL_TargetCoords.setOrigin(floor(LBL_TargetCoords.getGlobalBounds().width / 2), LBL_TargetCoords.getOrigin().y);
						LBL_StartCoords.setOrigin(floor(LBL_StartCoords.getGlobalBounds().width / 2), LBL_StartCoords.getOrigin().y);
					}
					if (B_Run.isFocused()) {	// "Press" button
						if (has_start && has_target && astar::save::getStatus() != FutureStatus::Running) {
							astar::solve(&GRD_Map);				// Find the path.
							astar::save::save(&CF_Outcome);		// Save result to file.
						}
						else
							cout << "[ERROR] BASIC START CONDITIONS NOT SET" << endl;
					}
					if (B_Reset.isFocused()) {	// "Press" button
						GRD_Map.reset_map();
						LBL_StartCoords.setString("-");
						LBL_StartCoords.setOrigin(floor(LBL_StartCoords.getGlobalBounds().width / 2), LBL_StartCoords.getOrigin().y);
						LBL_TargetCoords.setString("-");
						LBL_TargetCoords.setOrigin(floor(LBL_TargetCoords.getGlobalBounds().width / 2), LBL_TargetCoords.getOrigin().y);
					}
					if (B_RandomWalls.isFocused()) {	// "Press" button
						if (TB_MazeSize.getString().getSize() != 0 && EP_MazeSize.isRaised() == false) {
							GRD_Map.randomizeWalls(3);
						}
					}
				}
			}
		}

		// Clear from previous frame
		WND_Main.clear(Color::White);

		// Draw next frame
		WND_Main.draw(SHP_BackBox);
		WND_Main.draw(SHP_Separator);
		WND_Main.draw(LBL_MazeSize);
		WND_Main.draw(LBL_Start);
		WND_Main.draw(LBL_Target);
		WND_Main.draw(LBL_StartCoords);
		WND_Main.draw(LBL_TargetCoords);
		WND_Main.draw(TB_MazeSize);

		if (astar::save::getStatus() == FutureStatus::Running) {	// Draw LBL_Saving only if the thread with astar::save::save() is running (= it's saving).
			if ((LBL_Saving.getLimitPosition().y + LBL_OFFSET / 2) > WND_Main.getSize().y) {	// Resize the window if saving is outside WND_Main.
				windowResize(&WND_Main, Vector2u(WND_Main.getSize().x, LBL_Saving.getLimitPosition().y + LBL_OFFSET / 2));
				SHP_Separator.setSize(SHP_Separator.getSize().x, WND_Main.getSize().y);
			}
			WND_Main.draw(LBL_Saving);
		}
		else if (astar::save::getStatus() == FutureStatus::Finished) {			// If window was resized earlier, bring it back to correct size.
			if (LBL_Saving.getLimitPosition().y > GRD_Map.getLimitPosition().y) {
				windowResize(&WND_Main, Vector2u(WND_Main.getSize().x, default_win_y));
				SHP_Separator.setSize(SHP_Separator.getSize().x, WND_Main.getSize().y);
			}
		}

		WND_Main.draw(GRD_Map);
		WND_Main.draw(EP_MazeSize);
		WND_Main.draw(B_Run);
		WND_Main.draw(B_Reset);
		WND_Main.draw(B_RandomWalls);

		WND_Main.display();
	}
	return EXIT_SUCCESS;
}