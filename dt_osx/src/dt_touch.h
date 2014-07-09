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

typedef enum DT_TOUCH_OBJ{
	DT_TOUCH_OBJ_NONE,
	DT_TOUCH_OBJ_CANVAS,
	DT_TOUCH_OBJ_CIRCLE,
	DT_TOUCH_OBJ_UI_ELEM
}dt_touch_obj;


class dt_touch{
	
public:
	dt_touch();
	
	ofApp * app;
	
		
	void update();
	
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	dt_circle_base * touched_circle;

	ofVec2f touched_circle_center;
	ofVec2f touch_entry;
	float touch_time;

	dt_touch_obj t_obj;

};