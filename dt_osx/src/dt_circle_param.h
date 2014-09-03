//
//  dt_circle_param_base.h
//  dialt
//
//  Created by mtb on 5/12/14.
//
//

#pragma once


#include "ofMain.h"
#include "dt_circle_base.h"


class dt_circle_param_base : public dt_circle_base{

public:
	dt_circle_param_base();
	~dt_circle_param_base();
	
	//override
	virtual void setup(int beat_num);
	virtual void fire();
	void update();
	void draw();
	void draw_vbo();
	void make_vbo();
	void change_rshape(int type);

	float param_on;
	float param_off;
	float param_min;
	float param_max;
	static ofColor noteNum_color;
	static ofColor velocity_color;
	static ofColor duration_color;
	static ofColor pan_color;
	static ofColor cc1_color;
	static ofColor cc2_color;
	static ofColor cc3_color;
	static ofColor cc4_color;
	ofVbo rshape_vbo;
	vector<ofVec2f> rshape_points;
};

float line_color_rate = 35.0;

class dt_circle_param_noteNum : public dt_circle_param_base{
public:
	dt_circle_param_noteNum(){
		data.circle_type = DT_CIRCLE_NOTE_NUM;
		initial = "N";
		data.circle_color = data.indi_color = data.line_color = noteNum_color;
		data.line_color *= line_color_rate * 0.01;
	}
};

class dt_circle_param_velocity : public dt_circle_param_base {
public:
	dt_circle_param_velocity(){
		data.circle_type = DT_CIRCLE_VELOCITY;  initial = "V";
		data.circle_color = data.indi_color = data.line_color = velocity_color;
		data.line_color *= line_color_rate * 0.01;
	};
};

class dt_circle_param_duration : public dt_circle_param_base {
public:
	dt_circle_param_duration(){
		data.circle_type = DT_CIRCLE_DURATION;
		initial = "D";
		data.circle_color = data.indi_color = data.line_color = duration_color;
		data.line_color *= line_color_rate * 0.01;
	};
};

class dt_circle_param_pan : public dt_circle_param_base {
public:
	dt_circle_param_pan(){
		data.circle_type = DT_CIRCLE_PAN;
		initial = "P";
		data.circle_color = data.indi_color = data.line_color = pan_color;
		data.line_color *= line_color_rate * 0.01;
	}
};


class dt_circle_param_cc1 : public dt_circle_param_base {
public:
	dt_circle_param_cc1(){
		data.circle_type = DT_CIRCLE_CC1;
		initial = "C1";
		data.circle_color = data.indi_color = data.line_color = cc1_color;
		data.line_color *= line_color_rate * 0.01;
	};
};

class dt_circle_param_cc2 : public dt_circle_param_base {
public:
	dt_circle_param_cc2(){
		data.circle_type = DT_CIRCLE_CC2;
		initial = "C2";
		data.circle_color = data.indi_color = data.line_color = cc2_color;
		data.line_color *= line_color_rate * 0.01;
	};
};

class dt_circle_param_cc3 : public dt_circle_param_base {
public:
	dt_circle_param_cc3(){
		data.circle_type = DT_CIRCLE_CC3;
		initial = "C3";
		data.circle_color = data.indi_color = data.line_color = cc3_color;
		data.line_color *= line_color_rate * 0.01;
	};
};

class dt_circle_param_cc4 : public dt_circle_param_base {
public:
	dt_circle_param_cc4(){
		data.circle_type = DT_CIRCLE_CC4;
		initial = "C4";
		data.circle_color = data.indi_color = data.line_color = cc4_color;
		data.line_color *= line_color_rate * 0.01;
	};
};
