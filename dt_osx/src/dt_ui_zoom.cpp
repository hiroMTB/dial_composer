//
//  dt_ui_zoom.cpp
//  dial
//
//  Created by hiroshi matoba on 9/12/14.
//
//

#include "dt_ui_zoom.h"
#include "ofApp.h"
#include "dt_circle_container.h"
#include "dt_circle_all_containers.h"

dt_ui_zoom::dt_ui_zoom(){
    
}

void dt_ui_zoom::singleClickStart( int x, int y, int button ){
}

void dt_ui_zoom::singleClickEnd( int x, int y, int button ){
}

void dt_ui_zoom::doubleClickStart( int x, int y, int button ){
    app = ofApp::getInstance();
    ofVec2f mpw = app->cam.screenToWorld( ofVec2f(x,y) );
    dt_circle_base * c = app->all_containers.circle_base_container->getTouchedCircle( mpw );
    
    if( c ){
        // circle -> change mode
        app->mode_manager.go_to_home_mode();
    }
}

void dt_ui_zoom::doubleClickEnd( int x, int y, int button ){
}

//void dt_ui_zoom::longClickStart( int x, int y, int button ){};

void dt_ui_zoom::longClickEnd( int x, int y, int button ){
}

void dt_ui_zoom::dragStart( int x, int y, int button ){
}

void dt_ui_zoom::dragging( int x, int y, int button ){
}

void dt_ui_zoom::dragEnd( int x, int y, int button ){
}

