//
//  dt_dial_ui.h
//  dialt
//
//  Created by mtb on 5/7/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

enum dt_dial_ui_mode{
	DT_DIAL_UI_NONE		= -123,
	DT_DIAL_UI_HOME		= -1,
	DT_DIAL_UI_SPEED	= 0,
	DT_DIAL_UI_SHAPE	= 1,
	DT_DIAL_UI_ROT		= 2,
	DT_DIAL_UI_MUTE		= 3,
	DT_DIAL_UI_PRAM		= 4,
};


class dt_circle_base;

class dt_dial_ui{
	
public:
	
	dt_dial_ui( weak_ptr<dt_circle_base> parent );
	~dt_dial_ui(){};
	
	static void init();
	static void make_vbo_speed();
	static void make_vbo_shape();
	static void make_vbo_mute();
	static void make_vbo_param();
	static void make_vbo_param_LR();
	void setup();
	void draw();
	void draw_HOME();
	void draw_SPEED();
	void draw_SHAPE();
	void draw_ROT();
	void draw_MUTE();
	void draw_PARAM();
	void debug_draw_touch_area();
	void turn_on();
	void turn_off();
	void change_mode( dt_dial_ui_mode mode );
	dt_dial_ui_mode touch_test( ofVec2f &t );
	
	static bool bInitialized;
	static bool bUseSvg;
	static const float ui_template_radius;
	bool bNeedParam;
	int num_home_button;
	float ui_base_radius;
	float ui_ind_radius;
	float button_radius;
	
	weak_ptr<dt_circle_base> parent;
	vector<ofVec2f> ui_elem_pos;
	dt_dial_ui_mode mode;
	
	// Speed
	static ofxSVG speed_ui_svg;
	static const int speed_step_num = 64;
	static vector<ofVec2f> speed_vbo_points;
	static vector<ofFloatColor> speed_vbo_colors;
	static ofVbo speed_vbo;
	
	// Shape
	static ofxSVG shape_ui_svg;
	static const int shape_step_num = 64;
	static vector<ofVec2f> shape_vbo_points;
	static vector<ofFloatColor> shape_vbo_colors;
	static ofVbo shape_vbo;

	// Mute
	static ofxSVG mute_ui_svg;
	
	// Param
	static const int param_step_num = 60;
	static vector<ofVec2f> param_vbo_points;
	static vector<ofFloatColor> param_vbo_colors;
	static ofVbo param_vbo;
	
	// LR
	static const int param_LR_step_num = 60;
	static vector<ofVec2f> param_LR_vbo_points;
	static vector<ofFloatColor> param_LR_vbo_colors;
	static ofVbo param_LR_vbo;
};
