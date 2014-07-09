//
//  dt_linear_drawer.h
//  dialt_osx
//
//  Created by mtb on 2014/06/28.
//
//

#pragma once

#include "ofMain.h"

class ofApp;

class dt_linear_drawer{
	
public:
	dt_linear_drawer();

	ofApp * app;
	
	void draw(int x, int y, int w, int h, float scale);

	
	ofVbo point_vbo;
	vector<ofVec2f> points;
	vector<ofFloatColor> colors_p;

	ofVbo line_vbo;
	vector<ofVec2f> lines;
	vector<ofFloatColor> colors_l;

};