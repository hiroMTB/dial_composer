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
	DT_CIRCLE_TRIG	= 0,
	DT_CIRCLE_PRAM	= 1,
};


/*
 *
 *		data
 *
 */
class dt_circle_data{
	
public:
	
	dt_circle_data();
	
	bool bStop;
	bool bMute;
	bool bCollide;
	bool bShowUI;
	bool bFired;
	
	int phase_step;
	int fired_ch;
	int step_age;
	int speed;
	
	float radius;
	float rev_angle;
	float rev_speed;
	float rev_radius;
	float collision_radius;
	float input_connection_radius;
	float output_connection_radius;
	float fire_rate;

	string name;
	
	ofVec2f position;
	ofVec2f move_speed;
	ofVec2f world_position;
	ofVec2f indi_current_point;
	ofVec2f indi_next_point;
	ofVec2f indi_point_adder;
	
	static ofFloatColor defaultColor;
	ofFloatColor indi_color;
	ofFloatColor circle_color;
	
	dt_circle_type circle_type;
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

    dt_circle_base();
	virtual void setup( int beat=4 ) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
    virtual void step();
	virtual void fire(){};
	virtual void check_sequencer();
    virtual void make_vbo(){};
    
	void change_beat( int beat );
    void change_speed( int speed );
    void change_shape( int shape );
    void change_circle_color( float r, float g, float b, float a );
	void setup_text( string initial );
	void draw_initial();

    ofApp * app;

    static dt_circle_base * selected_circle;
	unsigned int wait_step;
    string initial;

	dt_circle_data data;
	dt_sequencer * seq;
    dt_dial_ui * ui;

    ofTrueTypeFont * font;
    ofVboMesh text_mesh;
    ofPoint text_pos;
};

