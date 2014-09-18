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
#include "ofxModifierKeys.h"

dt_ui_zoom::dt_ui_zoom(){
}

void dt_ui_zoom::singleClickStart( int x, int y, int button ){
    app = ofApp::app;
    ofVec2f mpw = app->cam.screenToWorld( ofVec2f(x,y) );
    dt_circle_base * c = app->all_containers.circle_base_container->getTouchedCircle( mpw );
    if( c ){
        // circle -> toggle mute
        dt_circle_base::selected_circle = c;
    }else{
        bool bShift = ofGetModifierPressed( OF_KEY_SHIFT );
        if( !bShift ){
            // canvas -> create new circle
            dt_circle_param * p = new dt_circle_param();
            p->setup(ofRandom( dt_config::DT_RHYTHM_SHAPE_SLOT_MIN, dt_config::DT_RHYTHM_SHAPE_SLOT_MAX) );
            p->parent = app->mode_manager.zoom_mode_target;
            p->data.position = mpw - p->parent->data.position;
            p->change_param_type( DT_CIRCLE_PAN );
            app->all_containers.circle_base_container->addCircle( p );
            app->all_containers.param_container->addCircle( p );
            app->mode_manager.zoom_mode_target->input_circles.push_back( p );
            
            dt_circle_base::selected_circle = p;
        }
    }
    
    app->update_cocoa_ui();
}

void dt_ui_zoom::singleClickEnd( int x, int y, int button ){
}

void dt_ui_zoom::doubleClickStart( int x, int y, int button ){
    app = ofApp::app;
    ofVec2f mpw = app->cam.screenToWorld( ofVec2f(x,y) );
    dt_circle_base * c = app->all_containers.circle_base_container->getTouchedCircle( mpw );
    
    if( c ){
        // circle -> change mode
        app->mode_manager.go_to_home_mode();
    }
    
    app->update_cocoa_ui();
}

void dt_ui_zoom::doubleClickEnd( int x, int y, int button ){
}

//void dt_ui_zoom::longClickStart( int x, int y, int button ){};

void dt_ui_zoom::longClickEnd( int x, int y, int button ){
}

void dt_ui_zoom::dragStart( int x, int y, int button ){
    app = ofApp::app;
    ofVec2f mpw = app->cam.screenToWorld( ofVec2f(x,y) );
    drag_start_posw = mpw;
    app->cam.dragStartTrans = app->cam.trans;
    drag_target_circle = app->all_containers.circle_base_container->getTouchedCircle( mpw );
	
	if( drag_target_circle )
		drag_start_target_pos = drag_target_circle->data.position;
	
    app->update_cocoa_ui();
}

void dt_ui_zoom::dragging( int x, int y, int button ){
    app = ofApp::app;
    if( drag_target_circle == app->mode_manager.zoom_mode_target )
        return;

    ofVec2f mpw = app->cam.screenToWorld( ofVec2f(x,y) );
    ofVec2f dist = mpw - drag_start_posw;
    
	if( drag_target_circle ){
        // drag circle
		drag_target_circle->data.position = drag_start_target_pos + dist;		dt_circle_base::selected_circle = drag_target_circle;
	}else{
        // drag camera
        float sensitivity = 0.6;
        app->cam.trans = app->cam.dragStartTrans - dist*sensitivity;
    }
}

void dt_ui_zoom::dragEnd( int x, int y, int button ){
    drag_target_circle = NULL;
}
