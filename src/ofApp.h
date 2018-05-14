#pragma once

#include "ofMain.h"
#include <vector>
#include "ofxDatGui.h"

//game states
enum GameState {
	IN_PROGRESS = 0,
	PAUSED,
	ABOUT
};

class ofApp : public ofBaseApp{

	//the back to game button at about page
	ofxDatGuiButton* about_back_to_game;
	//other gui components using ofxDatGui
	vector<ofxDatGuiComponent*> components;

	//normal text font
	ofTrueTypeFont my_font_normal_text;
	//title font
	ofTrueTypeFont my_font_title;

	//game state variables
	GameState current_state = IN_PROGRESS;
	GameState temp;
	int num_life = 0;

	//dragging patterns
	bool is_dragging_pattern = false;
	int mouse_x_index, mouse_y_index;
	std::vector<std::vector<bool>> dragging;

	//constant values
	const int num_per_row = 50;
	const int size = 12;
	
	//game board
	std::vector<std::vector<bool>> my_vector;
	
	//copy of board when dragging patterns
	std::vector<std::vector<bool>> my_vector_copy;

	//patterns board
	std::vector<std::vector<bool>> patterns;
	
	//determine if a block is alive or dead in next generation
	bool update_one_block(bool is_live, int x_index, int y_index);
	
	//helper method
	void update_num_lives();

	//copy vectors
	std::vector<std::vector<bool>>
		copy_vector(int x_min, int x_max, int y_min, int y_max);

	public:
		void setup();
		void update();
		
		void draw();
		void draw_blocks();
		void draw_about();
		void draw_gui();

		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		void reset();
		void setupPatterns();
		void setupInitialPlayField();

		void onSliderEvent(ofxDatGuiSliderEvent e);
		void onButtonEvent(ofxDatGuiButtonEvent e);
};
