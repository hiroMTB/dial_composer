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
	void change_rshape(int type);
	void make_vbo();
	void make_potato_shape();
	void update_world_position();
	
	vector<dt_circle_base*> input_circles;
	vector<dt_circle_base*> output_circles;
	
	int note_num_count, velocity_count, duration_count, pan_count, cc12_count, cc13_count, cc14_count, cc16_count;
	
	int intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);
};