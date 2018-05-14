# Conway's Game of Life (CS126 Sp 18 Final Project)
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
- Go to your project directory, go to the directory bin/data (if /data has not been created, create one), copy the ofxbraitsch directory in the root of ofxDatGui directory to your project's bin/data directory. This directory contains the fonts & icons used by ofxDatGui. Also copy the "StoneWalls.ttf" and ""UbuntuMono-Regular.ttf" files to bin/data, as these two files are fonts used by this project.
### Build
