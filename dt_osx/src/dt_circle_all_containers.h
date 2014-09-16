//
//  dt_circle_all_containers.h
//  dialt
//
//  Created by mtb on 30/05/14.
//
//

#pragma once

#include "ofMain.h"

template<typename T> class dt_circle_container;
class dt_circle_base;
class dt_circle_note_on;
class dt_circle_param;

typedef dt_circle_container<dt_circle_base*>		dt_circle_base_container;
typedef dt_circle_container<dt_circle_note_on*>		dt_circle_note_on_container;
typedef dt_circle_container<dt_circle_param*>       dt_circle_param_container;

class ofApp;

class dt_circle_all_containers{

public:
	dt_circle_all_containers();
	~dt_circle_all_containers(){};
	
	void setup();
	void update();
	void draw();
	void step();
	void add_indicator( const  ofVec2f& p, const ofFloatColor &c );
	void add_connection_line( const ofVec2f &p1, const ofVec2f &p2, const ofFloatColor &c1, const ofFloatColor &c2 );

	ofApp * app;
	dt_circle_base_container * circle_base_container;
	dt_circle_note_on_container * note_on_container;
	dt_circle_param_container * param_container;
	ofVboMesh indicators;
	ofVboMesh connection_lines;
};