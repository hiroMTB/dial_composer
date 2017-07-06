//
//  dt_ui_zoom.h
//  dial
//
//  Created by hiroshi matoba on 9/12/14.
//
//

#pragma once

#include "ofMain.h"
#include "dt_mouse_gesture.h"

class ofApp;
class dt_circle_base;

class dt_ui_zoom : public dt_mouse_gesture {
    
public:
    dt_ui_zoom();
    virtual void singleClickStart( int x, int y, int button );
    virtual void singleClickEnd( int x, int y, int button );
    virtual void doubleClickStart( int x, int y, int button );
    virtual void doubleClickEnd( int x, int y, int button );
    //virtual void longClickStart( int x, int y, int button );
    virtual void longClickEnd( int x, int y, int button );
    virtual void dragStart( int x, int y, int button );
    virtual void dragging( int x, int y, int button );
    virtual void dragEnd( int x, int y, int button );
    bool mode_check();
    
    ofApp * app;
    ofVec2f drag_start_posw;
	ofVec2f drag_start_target_pos;
    shared_ptr<dt_circle_base> drag_target_circle;
};
