#include "ofApp.h"

//--------------------------------------------------------------
//setup
void ofApp::setup(){

	ofSetWindowTitle("Conway's Game of Life");
	
	//initialize the game board, 50 * 50
	for (int i = 0; i < num_per_row; i++) {
		std::vector<bool> temp;
		for (int j = 0; j < num_per_row; j++) {
			temp.push_back(false);
		}
		my_vector.push_back(temp);
	}

	//initialize the patterns board, 24 * 23
	for (int i = 0; i < 24; i++) {
		std::vector<bool> temp;
		for (int j = 0; j < 23; j++) {
			temp.push_back(false);
		}
		patterns.push_back(temp);
	}

	setupPatterns();
	setupInitialPlayField();

//gui components-------------------------------------------------------
	
	//frame rate slider
	ofxDatGuiSlider* frame_rate_slider = new ofxDatGuiSlider("Frame Rate", 1, 100, 12);
	frame_rate_slider->setPosition(690, 115);
	frame_rate_slider->setPrecision(0, true);
	frame_rate_slider->onSliderEvent(this, &ofApp::onSliderEvent);
	components.push_back(frame_rate_slider);
	
	//Pause/Unpause
	ofxDatGuiButton* pause_unpause = new ofxDatGuiButton("PAUSE/UNPAUSE");
	pause_unpause->setPosition(690, 155);
	pause_unpause->onButtonEvent(this, &ofApp::onButtonEvent);
	components.push_back(pause_unpause);
	
	//Clear
	ofxDatGuiButton* clear = new ofxDatGuiButton("CLEAR");
	clear->setPosition(690, 195);
	clear->setWidth(135, 95);
	clear->onButtonEvent(this, &ofApp::onButtonEvent);
	components.push_back(clear);
	
	//Restart
	ofxDatGuiButton* restart = new ofxDatGuiButton("RESTART");
	restart->setPosition(825, 195);
	restart->setWidth(135, 95);
	restart->onButtonEvent(this, &ofApp::onButtonEvent);
	components.push_back(restart);
	
	//About
	ofxDatGuiButton* about = new ofxDatGuiButton("ABOUT");
	about->setPosition(690, 235);
	about->setWidth(135, 95);
	about->onButtonEvent(this, &ofApp::onButtonEvent);
	components.push_back(about);
	
	//Exit
	ofxDatGuiButton* exit = new ofxDatGuiButton("EXIT");
	exit->setPosition(825, 235);
	exit->setWidth(135, 95);
	exit->onButtonEvent(this, &ofApp::onButtonEvent);
	components.push_back(exit);
	
	//about_back_to_game, the button when game is in ABOUT state
	about_back_to_game = new ofxDatGuiButton("BACK TO GAME");
	about_back_to_game->setPosition(690, 540);
	about_back_to_game->onButtonEvent(this, &ofApp::onButtonEvent);
}

//--------------------------------------------------------------
//of update
void ofApp::update(){

	//since about_back_to_game is not in components
	about_back_to_game->update();

	//update gui components
	for (int i = 0; i < components.size(); i++) {
		components[i]->update();
	}

	//a new generation in the game board
	if (current_state == IN_PROGRESS) {
		std::vector<std::vector<bool>> my_vector_copy = my_vector;
		for (int i = 0; i < num_per_row; i++) {
			for (int j = 0; j < num_per_row; j++) {
				my_vector_copy[i][j] = update_one_block(my_vector[i][j], i, j);
			}
		}
		my_vector = my_vector_copy;
		update_num_lives();
	}
}

//Any live cell with fewer than two live neighbours dies
//Any live cell with two or three live neighbours lives on to the next generation
//Any live cell with more than three live neighbours dies
//Any dead cell with exactly three live neighbours becomes a live cell
bool ofApp::update_one_block(bool is_live, int x_index, int y_index) {
	//count neighbours
	int num_neighbours = 0;
	for (int i = x_index - 1; i <= x_index + 1; i++) {
		for (int j = y_index - 1; j <= y_index + 1; j++) {
			if (i >= 0 && i < num_per_row &&
				j >= 0 && j < num_per_row &&
				(i != x_index || j != y_index)) {
				num_neighbours += (my_vector[i][j]) ? 1 : 0;
			}
		}
	}

	//living
	if (is_live) {
		return (num_neighbours == 2 || num_neighbours == 3);
	}
	
	//dead
	else {
		return num_neighbours == 3;
	}
}

//update number of living blocks
void ofApp::update_num_lives() {
	num_life = 0;
	for (int i = 0; i < num_per_row; i++) {
		for (int j = 0; j < num_per_row; j++) {
			num_life += (my_vector[i][j]) ? 1 : 0;
		}
	}
}

//draw blocks, both in game board and in patterns board
void ofApp::draw_blocks(){
	//each block should be 6 * 6
	//use ofDrawRectangle to draw blocks
	//black if alive, white if dead
	//not sure what to do if window is resized
	//maybe just don't let window resize

	ofSetBackgroundColor(169, 169, 169);
	//game board
	for (int i = 0; i < num_per_row; i++) {
		for (int j = 0; j < num_per_row; j++) {
			//living
			if (my_vector[i][j]) {
				ofSetColor(0, 0, 0);
				ofDrawRectangle((size + 1) * i, (size + 1) * j, size, size);
			}
			//dead
			else {
				ofSetColor(255, 255, 255);
				ofDrawRectangle((size + 1) * i, (size + 1) * j, size, size);
			}
		}
	}

	//patterns board
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 23; j++) {
			if (patterns[i][j]) {
				ofSetColor(0, 0, 0);
				ofDrawRectangle(670 + (size + 1) * i, 325 + (size + 1) * j, size, size);
			}
			else {
				ofSetColor(255, 255, 255);
				ofDrawRectangle(670 + (size + 1) * i, 325 + (size + 1) * j, size, size);
			}
		}
	}
}

//the about page
void ofApp::draw_about() {

	//title
	my_font_title.load("StoneWalls.ttf", 68);
	std::string title = "GAME OF LIFE";
	my_font_title.drawString(title, 230, 240);
	my_font_normal_text.load("UbuntuMono-Regular.ttf", 16);

	//text
	std::string message = "";
	message += "The Game of Life, also known simply as Life, is a cellular automaton\n";
	message += "devised by the British mathematician John Horton Conway in 1970.\n";
	message += "The game is a zero - player game, meaning that its evolution is\n"; 
	message += "determined by its initial state, requiring no further input. \n";
	message += "One interacts with the Game of Life by creating an initial\n"; 
	message += "configuration and observing how it evolves, or, for advanced players,\n";
	message += "by creating patterns with particular properties.";
	my_font_normal_text.drawString(message, 110, 320);
}

void ofApp::draw_gui() {

	//game title
	my_font_title.load("StoneWalls.ttf", 32);
	std::string title = "GAME OF LIFE";
	ofSetColor(0, 0, 0);
	my_font_title.drawString(title, 710, 60);
	
	//number of living cells
	my_font_normal_text.load("UbuntuMono-Regular.ttf", 16);
	ofSetColor(0, 0, 0);
	my_font_normal_text.
		drawString("Number of Lives: " + std::to_string(num_life), 710, 100);
	
	//gui components
	for (auto a : components) {
		a->draw();
	}
	
	//pre-computed patterns
	my_font_title.load("StoneWalls.ttf", 24);
	std::string pre_computed_patterns = "PRE-COMPUTED PATTERNS";
	ofSetColor(0, 0, 0);
	my_font_title.drawString(pre_computed_patterns, 675, 310);
}

//--------------------------------------------------------------
void ofApp::draw() {

	//if in progress, call draw blocks
	if (current_state == IN_PROGRESS || current_state == PAUSED) {
		draw_blocks();
		draw_gui();
	}

	//about page
	if (current_state == ABOUT) {
		draw_about();
		about_back_to_game->draw();
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	//when not dragging patterns, check if mouse is on blocks in game board
	if (!is_dragging_pattern) {
		if ((x + 1) % 13 != 0 && (y + 1) % 13 != 0 && x >= 0 && x < 650 && y >= 0 && y < 650) {
			current_state = PAUSED;
			//left click to set blocks alive
			if (button == 0) {
				int x_index = x / 13;
				int y_index = y / 13;
				my_vector[x_index][y_index] = true;
			}
			//right click to set blocks dead
			else if (button == 2) {
				int x_index = x / 13;
				int y_index = y / 13;
				my_vector[x_index][y_index] = false;
			}
		}
	}
	//dragging pre-computed patterns
	else {
		
		//to have the effect of "dragging" patterns while not changing the board
		//until mouse is released, we do this by creating a copy of the board
		//at every update and (in the board) set the blocks corresponding to the patterns alive
		
		//at next update, if mouse is not released we just set board = board_copy
		
		//determine position of each block by sutracting its relative position
		//to the mouse from the mouse's position
		my_vector = my_vector_copy;
		int x_index = x / 13;
		int y_index = y / 13;
		int width = dragging.size();
		int height = dragging[0].size();
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				//determining position
				int temp_x_index = x_index - mouse_x_index + i;
				int temp_y_index = y_index - mouse_y_index + j;
				if (temp_x_index >= 0 && temp_x_index < 50 &&
					temp_y_index >= 0 && temp_y_index < 50) {
					my_vector[temp_x_index][temp_y_index] = dragging[i][j];
				}
			}
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//making changes to blocks
	if ((x + 1) % 13 != 0 && (y + 1) % 13 != 0 && x >= 0 && x < 650 && y >= 0 && y < 650) {
		current_state = PAUSED;
		//left click to set blocks alive
		if (button == 0) {
			int x_index = x / 13;
			int y_index = y / 13;
			my_vector[x_index][y_index] = true;
		}
		//right click to set blocks dead
		else if (button == 2) {
			int x_index = x / 13;
			int y_index = y / 13;
			my_vector[x_index][y_index] = false;
		}
	}

	//selecting precomputed-patterns
	else {
		//mouse position on the patterns board
		mouse_x_index = (x - 670) / 13;
		mouse_y_index = (y - 325) / 13;

		bool clicked_on_pattern = false;

		//these are sub-regions in the patterns board corresponding to patterns
		//after clicking on a pattern, the 2d vector "dragging" will copy the area
		//for later usage
 		if (mouse_x_index >= 1 && mouse_x_index <= 2 && mouse_y_index >= 1 && mouse_y_index <= 2) {
			dragging = copy_vector(1, 2, 1, 2);
			clicked_on_pattern = true;
		}

		else if (mouse_x_index >= 6 && mouse_x_index <= 8 && mouse_y_index >= 1 && mouse_y_index <= 1) {
			dragging = copy_vector(6, 8, 1, 1);
			clicked_on_pattern = true;
		}

		else if (mouse_x_index >= 1 && mouse_x_index <= 3 && mouse_y_index >= 4 && mouse_y_index <= 6) {
			dragging = copy_vector(1, 3, 4, 6);
			clicked_on_pattern = true;
		}

		else if (mouse_x_index >= 11 && mouse_x_index <= 13 && mouse_y_index >= 1 && mouse_y_index <= 3) {
			dragging = copy_vector(11, 13, 1, 3);
			clicked_on_pattern = true;
		}

		else if (mouse_x_index >= 5 && mouse_x_index <= 8 && mouse_y_index >= 4 && mouse_y_index <= 6) {
			dragging = copy_vector(5, 8, 4, 6);
			clicked_on_pattern = true;
		}

		else if (mouse_x_index >= 10 && mouse_x_index <= 13 && mouse_y_index >= 5 && mouse_y_index <= 6) {
			dragging = copy_vector(10, 13, 5, 6);
			clicked_on_pattern = true;
		}

		else if (mouse_x_index >= 1 && mouse_x_index <= 13 && mouse_y_index >= 9 && mouse_y_index <= 21) {
			dragging = copy_vector(1, 13, 9, 21);
			clicked_on_pattern = true;
		}

		else if (mouse_x_index >= 17 && mouse_x_index <= 19 && mouse_y_index >= 1 && mouse_y_index <= 8) {
			dragging = copy_vector(17, 19, 1, 8);
			clicked_on_pattern = true;
		}

		else if (mouse_x_index >= 17 && mouse_x_index <= 20 && mouse_y_index >= 11 && mouse_y_index <= 17) {
			dragging = copy_vector(17, 19, 11, 17);
			clicked_on_pattern = true;
		}

		//if mouse clicked on one patterns
		if (clicked_on_pattern) {
			is_dragging_pattern = true;
			current_state = PAUSED;
			my_vector_copy = my_vector;
		}
	}
	
}

//of mouse released
void ofApp::mouseReleased(int x, int y, int button) {
	//if mouse is released after dragging a pattern to the board
	if (is_dragging_pattern) {
		is_dragging_pattern = false;
		current_state = PAUSED;
	}
	//want to update num_lives so that the gui part gets updated immediately
	//after mouse is released, either dragging patterns or dragging on game board
	update_num_lives();
	my_font_normal_text.load("UbuntuMono-Regular.ttf", 16);		
	ofSetColor(0, 0, 0);
	my_font_normal_text.drawString
	("Number of Lives: " + std::to_string(num_life), 710, 100);
}

//--------------------------------------------------------------
//reset
void ofApp::reset() {
	//pause to show "ILLINI"
	current_state = PAUSED;
	for (int i = 0; i < num_per_row; i++) {
		for (int j = 0; j < num_per_row; j++) {
			my_vector[i][j] = false;
		}
	}
	setupInitialPlayField();
}

//slider to control frame rate
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
	ofSetFrameRate(e.value);
}

//click on botton
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
	//pause/unpause
	if (e.target == components[1]) {
		if (current_state == PAUSED) {
			current_state = IN_PROGRESS;
		}
		else if (current_state == IN_PROGRESS) {
			current_state = PAUSED;
		}
	}
	//clear
	else if (e.target == components[2]) {
		num_life = 0;
		current_state = PAUSED;
		for (int i = 0; i < num_per_row; i++) {
			for (int j = 0; j < num_per_row; j++) {
				my_vector[i][j] = false;
			}
		}
	}
	//restart
	else if (e.target == components[3]) {
		reset();
	}
	//about
	else if (e.target == components[4]) {
		current_state = ABOUT;
	}
	//exit
	else if (e.target == components[5]) {
		ofExit();
	}
	//about_back_to_game
	else if (e.target == about_back_to_game) {
		current_state = IN_PROGRESS;
	}
}

//helper method for copying pattern and give values to the 2d vector "dragging"
//and computing relative mouse position
std::vector<std::vector<bool>> ofApp::copy_vector(int x_min, int x_max, int y_min, int y_max) {
	std::vector<std::vector<bool>> to_return;
	for (int i = x_min; i <= x_max; i++) {
		std::vector<bool> temp;
		for (int j = y_min; j <= y_max; j++) {
			temp.push_back(patterns[i][j]);
		}
		to_return.push_back(temp);
	}
	mouse_x_index -= x_min;
	mouse_y_index -= y_min;
	return to_return;
}

//set up patterns board
void ofApp::setupPatterns() {
	patterns[1][1] = true;
	patterns[1][2] = true;
	patterns[2][1] = true;
	patterns[2][2] = true;

	patterns[1][6] = true;
	patterns[2][4] = true;
	patterns[2][6] = true;
	patterns[3][5] = true;
	patterns[3][6] = true;

	patterns[6][1] = true;
	patterns[7][1] = true;
	patterns[8][1] = true;

	patterns[11][2] = true;
	patterns[12][1] = true;
	patterns[12][3] = true;
	patterns[13][2] = true;

	patterns[5][5] = true;
	patterns[6][4] = true;
	patterns[6][6] = true;
	patterns[7][4] = true;
	patterns[7][6] = true;
	patterns[8][5] = true;

	patterns[10][6] = true;
	patterns[11][5] = true;
	patterns[11][6] = true;
	patterns[12][5] = true;
	patterns[12][6] = true;
	patterns[13][5] = true;

	patterns[1][11] = true;
	patterns[1][12] = true;
	patterns[1][13] = true;
	patterns[1][17] = true;
	patterns[1][18] = true;
	patterns[1][19] = true;
	patterns[6][11] = true;
	patterns[6][12] = true;
	patterns[6][13] = true;
	patterns[6][17] = true;
	patterns[6][18] = true;
	patterns[6][19] = true;
	patterns[8][11] = true;
	patterns[8][12] = true;
	patterns[8][13] = true;
	patterns[8][17] = true;
	patterns[8][18] = true;
	patterns[8][19] = true;
	patterns[13][11] = true;
	patterns[13][12] = true;
	patterns[13][13] = true;
	patterns[13][17] = true;
	patterns[13][18] = true;
	patterns[13][19] = true;

	patterns[3][9] = true;
	patterns[3][14] = true;
	patterns[3][16] = true;
	patterns[3][21] = true;
	patterns[4][9] = true;
	patterns[4][14] = true;
	patterns[4][16] = true;
	patterns[4][21] = true;
	patterns[5][9] = true;
	patterns[5][14] = true;
	patterns[5][16] = true;
	patterns[5][21] = true;
	patterns[9][9] = true;
	patterns[9][14] = true;
	patterns[9][16] = true;
	patterns[9][21] = true;
	patterns[10][9] = true;
	patterns[10][14] = true;
	patterns[10][16] = true;
	patterns[10][21] = true;
	patterns[11][9] = true;
	patterns[11][14] = true;
	patterns[11][16] = true;
	patterns[11][21] = true;

	patterns[17][1] = true;
	patterns[17][2] = true;
	patterns[17][3] = true;
	patterns[17][4] = true;
	patterns[17][5] = true;
	patterns[17][6] = true;
	patterns[17][7] = true;
	patterns[17][8] = true;
	patterns[18][1] = true;
	patterns[18][3] = true;
	patterns[18][4] = true;
	patterns[18][5] = true;
	patterns[18][6] = true;
	patterns[18][8] = true;
	patterns[19][1] = true;
	patterns[19][2] = true;
	patterns[19][3] = true;
	patterns[19][4] = true;
	patterns[19][5] = true;
	patterns[19][6] = true;
	patterns[19][7] = true;
	patterns[19][8] = true;

	patterns[17][11] = true;
	patterns[17][12] = true;
	patterns[17][13] = true;
	patterns[17][15] = true;
	patterns[17][16] = true;
	patterns[17][17] = true;
	patterns[18][11] = true;
	patterns[18][13] = true;
	patterns[18][15] = true;
	patterns[18][17] = true;
	patterns[19][11] = true;
	patterns[19][12] = true;
	patterns[19][13] = true;
	patterns[19][15] = true;
	patterns[19][16] = true;
	patterns[19][17] = true;
}

//set up initial game board, "ILLINI"
void ofApp::setupInitialPlayField() {
	my_vector[4][15] = true;
	my_vector[5][15] = true;
	my_vector[6][15] = true;
	my_vector[7][15] = true;
	my_vector[5][15] = true;
	my_vector[5][16] = true;
	my_vector[5][17] = true;
	my_vector[5][18] = true;
	my_vector[5][19] = true;
	my_vector[5][20] = true;
	my_vector[5][21] = true;
	my_vector[5][22] = true;
	my_vector[5][23] = true;
	my_vector[5][24] = true;
	my_vector[5][25] = true;
	my_vector[5][26] = true;
	my_vector[5][27] = true;
	my_vector[3][27] = true;
	my_vector[4][27] = true;
	my_vector[6][27] = true;
	my_vector[7][27] = true;
	my_vector[10][15] = true;
	my_vector[10][16] = true;
	my_vector[10][17] = true;
	my_vector[10][18] = true;
	my_vector[10][19] = true;
	my_vector[10][20] = true;
	my_vector[10][21] = true;
	my_vector[10][22] = true;
	my_vector[10][23] = true;
	my_vector[10][24] = true;
	my_vector[10][25] = true;
	my_vector[10][26] = true;
	my_vector[10][27] = true;
	my_vector[11][27] = true;
	my_vector[12][27] = true;
	my_vector[13][27] = true;
	my_vector[14][27] = true;
	my_vector[16][15] = true;
	my_vector[16][16] = true;
	my_vector[16][17] = true;
	my_vector[16][18] = true;
	my_vector[16][19] = true;
	my_vector[16][20] = true;
	my_vector[16][21] = true;
	my_vector[16][22] = true;
	my_vector[16][23] = true;
	my_vector[16][24] = true;
	my_vector[16][25] = true;
	my_vector[16][26] = true;
	my_vector[16][27] = true;
	my_vector[17][27] = true;
	my_vector[18][27] = true;
	my_vector[19][27] = true;
	my_vector[20][27] = true;
	my_vector[22][15] = true;
	my_vector[23][15] = true;
	my_vector[24][15] = true;
	my_vector[25][15] = true;
	my_vector[26][15] = true;
	my_vector[24][16] = true;
	my_vector[24][17] = true;
	my_vector[24][18] = true;
	my_vector[24][19] = true;
	my_vector[24][20] = true;
	my_vector[24][21] = true;
	my_vector[24][22] = true;
	my_vector[24][23] = true;
	my_vector[24][24] = true;
	my_vector[24][25] = true;
	my_vector[24][26] = true;
	my_vector[24][27] = true;
	my_vector[23][27] = true;
	my_vector[25][27] = true;
	my_vector[26][27] = true;
	my_vector[29][15] = true;
	my_vector[29][16] = true;
	my_vector[29][17] = true;
	my_vector[29][18] = true;
	my_vector[29][19] = true;
	my_vector[29][20] = true;
	my_vector[29][21] = true;
	my_vector[29][22] = true;
	my_vector[29][23] = true;
	my_vector[29][24] = true;
	my_vector[29][25] = true;
	my_vector[29][26] = true;
	my_vector[29][27] = true;
	my_vector[30][16] = true;
	my_vector[30][17] = true;
	my_vector[30][18] = true;
	my_vector[31][18] = true;
	my_vector[31][19] = true;
	my_vector[31][20] = true;
	my_vector[32][20] = true;
	my_vector[32][21] = true;
	my_vector[32][22] = true;
	my_vector[33][22] = true;
	my_vector[33][23] = true;
	my_vector[33][24] = true;
	my_vector[34][24] = true;
	my_vector[34][25] = true;
	my_vector[34][26] = true;
	my_vector[35][25] = true;
	my_vector[35][26] = true;
	my_vector[35][27] = true;
	my_vector[35][15] = true;
	my_vector[35][16] = true;
	my_vector[35][17] = true;
	my_vector[35][18] = true;
	my_vector[35][19] = true;
	my_vector[35][20] = true;
	my_vector[35][21] = true;
	my_vector[35][22] = true;
	my_vector[35][23] = true;
	my_vector[35][24] = true;
	my_vector[38][15] = true;
	my_vector[39][15] = true;
	my_vector[40][15] = true;
	my_vector[41][15] = true;
	my_vector[42][15] = true;
	my_vector[40][16] = true;
	my_vector[40][17] = true;
	my_vector[40][18] = true;
	my_vector[40][19] = true;
	my_vector[40][20] = true;
	my_vector[40][21] = true;
	my_vector[40][22] = true;
	my_vector[40][23] = true;
	my_vector[40][24] = true;
	my_vector[40][25] = true;
	my_vector[40][26] = true;
	my_vector[40][27] = true;
	my_vector[38][27] = true;
	my_vector[39][27] = true;
	my_vector[41][27] = true;
	my_vector[42][27] = true;
}
