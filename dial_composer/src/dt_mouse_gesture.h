//
//  dt_gesture.h
//  dial
//
//  Created by hiroshi matoba on 9/12/14.
//
//

#pragma once

#include "ofMain.h"

/*
 *
 *      mouse input analysis class
 *      
 *      notice:
 *          + singleClickStart is actually mousePressed itself,
 *            so this include first predd of all type( drag, long, double click)
 *
 *          + longClickStart is not inmplemented yet
 *
 *          + Microsoft default double click time is 500ms (from Wikipedia).
 *              To separate single or double click, should we wait 500ms!?
 *              It's not a good idea, so single click action should be overwrited by double's one.
 *              For example,
 *                  single -> select
 *                  double -> zoom to selected object, etc
 *
 */

class dt_mouse_gesture{

public:
    dt_mouse_gesture();
    
    void update();
    void mouseMoved( int x, int y);
    void mousePressed( int x, int y, int button );
	void mouseDragged( int x, int y, int button );
	void mouseReleased( int x, int y, int button );

    virtual void singleClickStart( int x, int y, int button ){};
    virtual void singleClickEnd( int x, int y, int button ){};
    virtual void doubleClickStart( int x, int y, int button ){};
    virtual void doubleClickEnd( int x, int y, int button ){};
    virtual void longClickStart( int x, int y, int button ){};
    virtual void longClickEnd( int x, int y, int button ){};
    virtual void dragStart( int x, int y, int button ){};
    virtual void dragging( int x, int y, int button ){};
    virtual void dragEnd( int x, int y, int button ){};
    
    bool bDoubleClicking, bDragging;
    bool bDouble_click_check;
    unsigned long last_press, last_release;

    /*
     *      time between Press and Release
     */
    unsigned long single_click_time;
    
    /*
     *      time between 1st Release and 2nd Press
     */
    unsigned long double_click_time;
    
    int mouseX, mouseY, mouseButton;
};

