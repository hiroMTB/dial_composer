//
//  dt_touch_home.mm
//  dialt
//
//  Created by mtb on 5/5/14.
//
//

#include "dt_ui_home.h"
#include "ofApp.h"
#include "dt_dial_ui.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_param.h"
#include "dt_circle_container.h"
#include "dt_circle_all_containers.h"
#include "ofxModifierKeys.h"

dt_ui_home::dt_ui_home()
:
drag_start_posw( ofVec2f(0,0) ),
drag_target_circle( NULL )
{
}

void dt_ui_home::singleClickStart(int x, int y, int button){
    app = ofApp::getInstance();
    ofVec2f mpw = app->cam.screenToWorld( ofVec2f(x,y) );
    dt_circle_base * c = app->all_containers.note_on_container->getTouchedCircle( mpw );
    if( c ){
        // circle -> toggle mute
        dt_circle_base::selected_circle = c;
    }else{
        bool bShift = ofGetModifierPressed( OF_KEY_SHIFT );
        if( !bShift ){
            // canvas -> create new circle
            dt_circle_note_on * nc = new dt_circle_note_on();
            nc->setup(ofRandom( dt_config::DT_RHYTHM_SHAPE_SLOT_MIN, dt_config::DT_RHYTHM_SHAPE_SLOT_MAX) );
            nc->data.position = mpw;
            app->all_containers.circle_base_container->addCircle( nc );
            app->all_containers.note_on_container->addCircle( nc );
            dt_circle_base::selected_circle = nc;
        }
    }
}

void dt_ui_home::singleClickEnd( int x, int y, int button ){
}

void dt_ui_home::doubleClickStart( int x, int y, int button ){
    app = ofApp::getInstance();
    ofVec2f mpw = app->cam.screenToWorld( ofVec2f(x,y) );
    dt_circle_base * c = app->all_containers.note_on_container->getTouchedCircle( mpw );

    if( c ){
        // circle -> change mode
        app->mode_manager.go_to_zoom_mode( c );
    }
}

//void dt_ui_home::longClickStart( int x, int y, int button ){}

void dt_ui_home::longClickEnd( int x, int y, int button ){
}

void dt_ui_home::dragStart( int x, int y, int button ){

    app = ofApp::getInstance();
    ofVec2f mpw = app->cam.screenToWorld( ofVec2f(x,y) );
    drag_start_posw = mpw;
    app->cam.dragStartTrans = app->cam.trans;
    drag_target_circle = app->all_containers.note_on_container->getTouchedCircle( mpw );
    
}

void dt_ui_home::dragging( int x, int y, int button ){
    app = ofApp::getInstance();
    ofVec2f mpw = app->cam.screenToWorld( ofVec2f(x,y) );
    ofVec2f dist = mpw - drag_start_posw;
    
	if( drag_target_circle ){
        // drag circle
		drag_target_circle->data.position = drag_start_posw + dist;
		dt_circle_base::selected_circle = drag_target_circle;
	}else{
        // drag camera
        float sensitivity = 0.6;
        app->cam.trans = app->cam.dragStartTrans - dist*sensitivity;
    }
}

void dt_ui_home::dragEnd( int x, int y, int button ){
    drag_target_circle = NULL;
}
