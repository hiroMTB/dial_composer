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

	void draw( int x, int y, int w, int h, float scale );

	ofApp * app;

	ofVboMesh points;
	ofVboMesh lines;

};