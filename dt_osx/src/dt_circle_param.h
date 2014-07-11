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
	
	//override
	virtual void setup(int beat_num);

	void update();
	void draw();
	
	virtual void fire();

	void draw_vbo();
	
	~dt_circle_param_base();
	
	ofVbo rshape_vbo;
	vector<ofVec2f> rshape_points;

	void make_vbo();
	void change_rshape(int type);
	
	
	float param_on;
	float param_off;
	
	float param_min;
	float param_max;

	string initial;
	

	static const int line_color_rate = 35;		// %
	
	static ofColor noteNum_color;
	static ofColor velocity_color;
	static ofColor duration_color;
	static ofColor pan_color;
	static ofColor cc12_color;
	static ofColor cc13_color;
	static ofColor cc14_color;
	static ofColor cc16_color;
};



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
		initial = "LR";
		data.circle_color = data.indi_color = data.line_color = pan_color;
		data.line_color *= line_color_rate * 0.01;
	}
};


class dt_circle_param_cc12 : public dt_circle_param_base {
public:
	dt_circle_param_cc12(){
		data.circle_type = DT_CIRCLE_CC12;
		initial = "12";
		data.circle_color = data.indi_color = data.line_color = cc12_color;
		data.line_color *= line_color_rate * 0.01;
	};
};

class dt_circle_param_cc13 : public dt_circle_param_base {
public:
	dt_circle_param_cc13(){
		data.circle_type = DT_CIRCLE_CC13;
		initial = "13";
		data.circle_color = data.indi_color = data.line_color = cc13_color;
		data.line_color *= line_color_rate * 0.01;
	};
};

class dt_circle_param_cc14 : public dt_circle_param_base {
public:
	dt_circle_param_cc14(){
		data.circle_type = DT_CIRCLE_CC14;
		initial = "14";
		data.circle_color = data.indi_color = data.line_color = cc14_color;
		data.line_color *= line_color_rate * 0.01;
	};
};

class dt_circle_param_cc16 : public dt_circle_param_base {
public:
	dt_circle_param_cc16(){
		data.circle_type = DT_CIRCLE_CC16;
		initial = "16";
		data.circle_color = data.indi_color = data.line_color = cc16_color;
		data.line_color *= line_color_rate * 0.01;
	};
};
