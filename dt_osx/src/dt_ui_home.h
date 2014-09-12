//
//  dt_touch.h
//  dialt
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "ofMain.h"
#include "dt_mouse_gesture.h"

class ofApp;
class dt_circle_base;

typedef enum DT_UI_HOME_OBJ{
	DT_UI_HOME_OBJ_NONE,
	DT_UI_HOME_OBJ_CANVAS,
	DT_UI_HOME_OBJ_CIRCLE,
	DT_UI_HOME_OBJ_UI_ELEM
}dt_ui_home_obj;

class dt_ui_home : public dt_mouse_gesture{
	
public:
	dt_ui_home();
    
    virtual void singleClickStart( int x, int y, int button );
    virtual void singleClickEnd( int x, int y, int button );
    virtual void doubleClickStart( int x, int y, int button );
    virtual void doubleClickEnd( int x, int y, int button ){};
    //virtual void longClickStart( int x, int y, int button ){};
    virtual void longClickEnd( int x, int y, int button );
    virtual void dragStart( int x, int y, int button );
    virtual void dragging( int x, int y, int button );
    virtual void dragEnd( int x, int y, int button );

    ofApp * app;
    ofVec2f drag_start_posw;
    dt_circle_base * drag_target_circle;
};