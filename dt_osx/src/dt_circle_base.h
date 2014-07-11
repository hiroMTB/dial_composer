//
//  dt_circle_base.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once


#include "ofMain.h"


typedef enum dt_circle_type{
	DT_CIRCLE_BASE		= 0,
	DT_CIRCLE_NOTE_ON	= 1,
	DT_CIRCLE_NOTE_NUM	= 2,
	DT_CIRCLE_VELOCITY	= 3,
	DT_CIRCLE_DURATION	= 4,
	DT_CIRCLE_PAN		= 5,

	DT_CIRCLE_CC12		= 12,
	DT_CIRCLE_CC13		= 13,
	DT_CIRCLE_CC14		= 14,
	DT_CIRCLE_CC16		= 16,
	
	DT_CIRCLE_OSC		= 101,
	DT_CIRCLE_MIDI		= 102
};


/*
 *
 *		data
 *
 */
class dt_circle_data{
	
public:
	
	
	dt_circle_data();

	static ofFloatColor defaultColor;
	
	bool bStop;
	bool bMute;
	bool bCollide;
	bool bShowUI;
	bool bFired;
	
	int phase_step;
	int fired_ch;
	
	float radius;
	float rev_angle;
	float rev_speed;
	float rev_radius;
	float collision_radius;
	float input_connection_radius;
	float output_connection_radius;
	float fire_rate;

	int step_age;
	int speed;
	
	string name;
	
	ofVec2f position;
	ofVec2f move_speed;
	ofVec2f world_position;
	ofFloatColor indi_color;
	ofFloatColor line_color;
	ofFloatColor circle_color;
	
	dt_circle_type circle_type;
	
	ofVec2f indi_current_point;
	ofVec2f indi_next_point;
	ofVec2f indi_point_adder;
	
};


/*
 *
 *		circle
 *
 */

#include "dt_sequencer.h"
class ofApp;
class dt_dial_ui;


class dt_circle_base{
	
public:

	static dt_circle_base * selected_circle;
	dt_circle_data data;

	ofApp * app;
	
	dt_circle_base();
	virtual void setup(int beat=4) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;


	// sequencer
	dt_sequencer * seq;

	virtual void pre_srep(){};
	virtual void step();
	virtual void post_step(){};
	virtual void fire(){};
	virtual void check_sequencer();
	
	// ui
	dt_dial_ui * ui;

	// for animation
	unsigned int wait_step;
	
	void change_beat(int beat);
    
    ofTrueTypeFont * font;
    ofVboMesh text_mesh;
    ofPoint text_pos;
};

