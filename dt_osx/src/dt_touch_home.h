//
//  dt_touch.h
//  dialt
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "ofMain.h"

class ofApp;
class dt_circle_base;

typedef enum DT_TOUCH_HOME_OBJ{
	DT_TOUCH_HOME_OBJ_NONE,
	DT_TOUCH_HOME_OBJ_CANVAS,
	DT_TOUCH_HOME_OBJ_CIRCLE,
	DT_TOUCH_HOME_OBJ_UI_ELEM
}dt_touch_home_obj;

class dt_touch_home{
	
public:
	dt_touch_home();
	void update();
	void mousePressed( int x, int y, int button );
	void mouseDragged( int x, int y, int button );
	void mouseReleased( int x, int y, int button );
	
	ofApp * app;
    bool bDouble_tap;
	float touch_time;
    unsigned long last_tap;
    unsigned long double_tap_time;
	ofVec2f touched_circle_center;
	ofVec2f touch_entry;
	dt_circle_base * touched_circle;
	dt_touch_home_obj t_obj;
};