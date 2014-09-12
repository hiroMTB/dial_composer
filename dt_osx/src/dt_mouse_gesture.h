//
//  dt_gesture.h
//  dial
//
//  Created by hiroshi matoba on 9/12/14.
//
//

#pragma once

#include "ofMain.h"

class dt_mouse_gesture{

public:
    dt_mouse_gesture();
    
    void update();
    void mouseMoved( int x, int y, int button );
    void mousePressed( int x, int y, int button );
	void mouseDragged( int x, int y, int button );
	void mouseReleased( int x, int y, int button );
    
    virtual void singleClickEnd( int x, int y, int button ){};
    virtual void doubleClickStart( int x, int y, int button ){};
    virtual void doubleClickEnd( int x, int y, int button ){};
    //virtual void longClickStart( int x, int y, int button ){};    // not implemented yet
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