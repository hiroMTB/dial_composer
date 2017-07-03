//
//  dt_circle_base.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "ofMain.h"

enum dt_circle_type{
	DT_CIRCLE_NOTE_ON	= 0,
	DT_CIRCLE_NOTE_NUM	= 1,
	DT_CIRCLE_VELOCITY	= 2,
	DT_CIRCLE_DURATION	= 3,
	DT_CIRCLE_PAN		= 4,
	DT_CIRCLE_CC1		= 5,
	DT_CIRCLE_CC2		= 6,
	DT_CIRCLE_CC3		= 7,
	DT_CIRCLE_CC4		= 8,
};

inline string getEnumString( dt_circle_type t ){
    switch( t ){
        case DT_CIRCLE_NOTE_ON: return "NoteOn Circle";
        case DT_CIRCLE_NOTE_NUM: return "NoteNum Circle";
        case DT_CIRCLE_VELOCITY: return "Velocity Circle";
        case DT_CIRCLE_DURATION: return "Duration Circle";
        case DT_CIRCLE_PAN: return "Pan Circle";
        case DT_CIRCLE_CC1: return "Control Change 1 Circle";
        case DT_CIRCLE_CC2: return "Control Change 2 Circle";
        case DT_CIRCLE_CC3: return "Control Change 3 Circle";
        case DT_CIRCLE_CC4: return "Control Change 4 Circle";
        default: return "";
    }
}

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
    bool bShow;
	
	int phase_step;
	int fired_ch;
	int step_age;
	int speed;
    int midi_ch;
    int midi_cc_num;
    
    float output_value;
	float rev_speed;
	float rev_radius;
	float collision_radius;
	float input_connection_radius;
	float output_connection_radius;
	float fire_rate;
    float note, vel, dur, pan;  // for animation

	string name;
	string address;
	
	ofVec2f position;
	ofVec2f indi_position;
    
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
#include "dt_circle_drawer.h"

class ofApp;
class dt_dial_ui;

class dt_circle_base{
	
public:

    dt_circle_base();
    ~dt_circle_base();
	virtual void setup( int beat=4 ) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
    virtual void step();
	virtual void on_process(){};
	virtual void check_sequencer();
    void make_vbo();
    
	void change_beat( int beat );
    void change_speed( int speed );
    void change_shape( int shape );
	void change_rotation( int phase_step );
	void change_type( dt_circle_type t );
    void change_circle_color( float r, float g, float b, float a );
    void change_circle_color( ofFloatColor &c );
    void change_circle_color( ofColor &c );
	void setup_text( string initial );
	void draw_initial();
	ofVec2f calc_indi_position();

    ofApp * app;
	unsigned int wait_step;
    string initial;
    ofTrueTypeFont * font;
    ofVboMesh text_mesh;
    ofPoint text_pos;
    ofVboMesh rshape;
	ofVboMesh rguid;
    
    dt_circle_data data;
	dt_sequencer * seq;
    dt_dial_ui * ui;
    static dt_circle_base * selected_circle;
    dt_circle_base * parent;
    dt_circle_drawer circle_drawer;
    
    vector<dt_circle_base*> input_circles;
	vector<dt_circle_base*> output_circles;
	
	static ofColor noteOn_color;
	static ofColor noteNum_color;
	static ofColor velocity_color;
	static ofColor duration_color;
	static ofColor pan_color;
	static ofColor cc1_color;
	static ofColor cc2_color;
	static ofColor cc3_color;
	static ofColor cc4_color;
};
