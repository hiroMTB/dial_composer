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
class dt_circle_output_base;

typedef dt_circle_container<dt_circle_base*>		dt_circle_base_container;
typedef dt_circle_container<dt_circle_note_on*>		dt_circle_note_on_container;
typedef dt_circle_container<dt_circle_param*>       dt_circle_param_container;
typedef dt_circle_container<dt_circle_output_base*> dt_circle_output_container;


class ofApp;

class dt_circle_all_containers{

public:
	ofApp * app;
	
	// Containers
	dt_circle_base_container * circle_base_container;
	dt_circle_note_on_container * note_on_container;
	dt_circle_param_container * param_container;
	dt_circle_output_container * output_container;

	ofVboMesh indicators;
	ofVboMesh connection_lines;
	
	dt_circle_all_containers();
	~dt_circle_all_containers(){};
	
	void setup();
	void update();
	void draw();
	void step();
	
	void add_indicator( const  ofVec2f& p, const ofFloatColor &c );
	void add_connection_line( const ofVec2f &p1, const ofVec2f &p2, const ofFloatColor &c1, const ofFloatColor &c2 );
	
	void change_speed_random_all( int min, int max );
	void change_beat_all( int beat );
	void change_position_all();
	void change_beat_resolution_all( int res );
	void change_osc_ch_all();
};