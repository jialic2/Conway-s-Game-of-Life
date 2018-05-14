# Conway's Game of Life (CS126 SP 18 Final Project)
This project is an implementation of the Conway's Game of Life (for more information, see https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) using the open source C++ toolkit openFramworks (http://openframeworks.cc/) for CS 126 final project spring 2018 by Jiali Chen. Also uses the ofxDatGui addon to improve graphical user interface (http://braitsch.github.io/ofxDatGui/).
## Getting Started
This part mainly focuses on helping you setting up a copy of the project on your local machine.
### Prerequisites
- Visual Studio or Xcode or other IDEs that openFrameworks can be integrated in, see more at http://openframeworks.cc/download/
### Installing
- Download openFrameworks from http://openframeworks.cc/download/.
- Download this project to your local machine.
- Clone or download the ofxDatGui addon from https://github.com/braitsch/ofxDatGui and place it under your openFrameworks/addons directory
- Create a new OF project by the project generator under your openFrameworks/projectGenerator directory, include ofxDatGui by selecting the addons button in the generator (if it says ofxDatGui not found, choose ofxDatGui-master if that is the case).
- Go to your project directory, go to the directory bin/data (if /data has not been created, create one), copy the ofxbraitsch directory in the root of ofxDatGui directory to your project's bin/data directory. This directory contains the fonts & icons used by ofxDatGui. Also copy the fonts directory to bin/data, as the two files under this directory are fonts used by this project.
### Build
- Build the project in your IDE and run
## Game Rules
- Any live cell with fewer than two live neighbours dies
- Any live cell with two or three live neighbours lives on to the next generation
- Any live cell with more than three live neighbours dies
- Any dead cell with exactly three live neighbours becomes a live cell
## Features
This implementation of Conway's Game of Life features:
- Number of living blocks
- Current Frame Rate
- Set frame rate      
- Pause/Unpause
- Set blocks living/dead
- About    
- Restart
- Clear    
- Exit      
- Dragging pre-computed patterns to the game board
## Author
- Jiali Chen - https://github.com/jialic2
## Acknowledgements
- Myself
- openFrameworks Documentation
- Stephen Braitsch - https://github.com/braitsch for ofxDatGui addon
- All TAs and moderators offering help to me in person or through Piazza
