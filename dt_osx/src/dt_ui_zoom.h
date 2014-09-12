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

typedef enum DT_UI_ZOOM_OBJ{
    DT_UI_ZOOM_OBJ_NONE,
    DT_UI_ZOOM_OBJ_CANVAS,
    DT_UI_ZOOM_OBJ_NOTE_ON,
    DT_UI_ZOOM_OBJ_PARAM
}dt_ui_zoom_obj;

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
    
    ofApp * app;
    dt_ui_zoom_obj t_obj;
    
};