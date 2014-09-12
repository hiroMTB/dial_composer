//
//  dt_mode_manager.cpp
//  dial
//
//  Created by mtb on 2014/09/11.
//
//

#pragma once

enum dt_mode{
	DT_MODE_HOME = 0,
	DT_MODE_ZOOM = 1,
	DT_MODE_HOME2ZOOM = 2,
	DT_MODE_ZOOM2HOME = 3
};

class ofApp;
class dt_circle_base;

class dt_mode_manager{
	
public:
	
	dt_mode_manager(){};
	void setup();
	void go_to_home_mode();
    void go_to_zoom_mode( dt_circle_base * target );
    void toggle_mode();
	
	void debug_draw();
	
	ofApp * app;
	dt_mode mode;
    dt_circle_base * zoom_mode_target;
};