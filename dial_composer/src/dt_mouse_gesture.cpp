//
//  dt_gesture.cpp
//  dial
//
//  Created by hiroshi matoba on 9/12/14.
//
//

#include "dt_mouse_gesture.h"

/*
 *
 *      analyse click/tap and separate task
 *      
 *          - single click
 *          - double click
 *          - drag end/start
 *          - long press end/start
 *
 */

dt_mouse_gesture::dt_mouse_gesture()
:
bDragging( false ),
bDoubleClicking( false ),
bDouble_click_check( false ),
last_press( 0 ),
last_release( 0 ),
single_click_time( 300 ),
double_click_time( 200 ),
mouseX( 0 ),
mouseY( 0 ),
mouseButton( 0 )
{
}

void dt_mouse_gesture::update(){
    unsigned long now = ofGetElapsedTimeMillis();

    if( bDouble_click_check ){
        unsigned long wait_time = now-last_release;
        // double click time over
        if( wait_time > double_click_time ){
            bDouble_click_check = false;

            /*
             *
             *      single tap end
             *
             */
            ofLogNotice( "single click end");
            singleClickEnd( mouseX, mouseY, mouseButton );
        }
    }
}

void dt_mouse_gesture::mouseMoved( int x, int y){
    mouseX = x;
    mouseY = y;
    //mouseButton = button;
}

void dt_mouse_gesture::mousePressed( int x, int y, int button ){
    mouseX = x;
    mouseY = y;
    mouseButton = button;

    singleClickStart( mouseX, mouseY, mouseButton );
    
    unsigned long now = ofGetElapsedTimeMillis();
    if( bDouble_click_check ){
        unsigned long wait_time = now - last_release;
        if( last_release!=0 && wait_time < double_click_time ){
            /*
             *
             *      double click start
             *
             */
            ofLogNotice( "double click start" );
            bDoubleClicking = true;
            doubleClickStart( mouseX, mouseY, mouseButton );
        }
        bDouble_click_check = false;
    }
    last_press = now;
}

void dt_mouse_gesture::mouseDragged( int x, int y, int button ){
    mouseX = x;
    mouseY = y;
    mouseButton = button;

    if( bDragging == false ){
        /*
         *
         *      drag start here
         *
         */
        ofLogNotice( "drag start" );
        dragStart( mouseX, mouseY, mouseButton );
    }else{
        dragging( mouseX, mouseY, mouseButton );
    }

    bDragging = true;
}

void dt_mouse_gesture::mouseReleased( int x, int y, int button ){
    mouseX = x;
    mouseY = y;
    mouseButton = button;
    unsigned long now = ofGetElapsedTimeMillis();
    unsigned long click_time = now - last_press;

    if( !bDragging ){
        if( click_time < single_click_time ){
            if( !bDoubleClicking ) {
                /*
                 *
                 *      single click end BUT may be double click coming
                 *      So wait/check little bit in updateloop
                 *
                 */
                bDouble_click_check = true;
            }else{
                /*
                 *
                 *      double click end
                 *
                 */
                ofLogNotice( "double click end");
                doubleClickEnd( mouseX, mouseY, mouseButton );
                bDoubleClicking = false;
            }
        }else {
            
            /*
             *
             *      long click end
             *
             */
            ofLogNotice( "long click end" );
            longClickEnd( mouseX, mouseY, mouseButton );
        }
    }else{
        bDragging = false;

        /*
         *  
         *      drag end
         *
         */
        ofLogNotice( "drag end" );
        dragEnd( mouseX, mouseY, mouseButton );
    }
    
    last_release = now;
}
