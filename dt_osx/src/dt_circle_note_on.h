//
//  dt_circle_note_on.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once


#include "ofMain.h"
#include "dt_circle_base.h"
#include "dt_rhythm_lib.h"

#include "dt_circle_param.h"

class dt_circle_note_on : public dt_circle_base{

public:
	dt_circle_note_on();
	
	// override
	virtual void setup(int beat_num);
	virtual void update();
	virtual void draw();

	void set_beats(int beat_num);
	void set_speed(int speed);
	
	void check_connection();
	
	virtual void post_step();
	virtual void fire();
		
	~dt_circle_note_on();
	
	ofVbo rshape_vbo;
	vector<ofVec2f> rshape_points;
    vector<ofFloatColor> rshape_colors;
    
	void change_rshape(int type);
	void make_vbo();
	void make_potato_shape();
	void update_world_position();
	
	vector<dt_circle_base*> input_circles;
	vector<dt_circle_base*> output_circles;
	
	int note_num_count, velocity_count, duration_count, pan_count, cc12_count, cc13_count, cc14_count, cc16_count;
	   
    dt_circle_param_noteNum     noteNum;
    dt_circle_param_velocity    vel;
    dt_circle_param_duration    dur;
    dt_circle_param_pan         pan;
    dt_circle_param_cc1         cc1;
    dt_circle_param_cc2         cc2;
    dt_circle_param_cc3         cc3;
    dt_circle_param_cc4         cc4;
    
};