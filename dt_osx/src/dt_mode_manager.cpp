//
//  dt_mode_manager.h
//  dial
//
//  Created by mtb on 2014/09/11.
//
//

#include "dt_mode_manager.h"
#include "ofMain.h"
#include "ofApp.h"
#include "dt_circle_base.h"

void dt_mode_manager::setup(){
	app = ofApp::getInstance();
	mode = DT_MODE_HOME;
    current_ui = &ui_home;
}

void dt_mode_manager::update(){
    
    current_ui->update();
}

void dt_mode_manager::go_to_home_mode(){
    mode = DT_MODE_ZOOM2HOME;
    current_ui = &ui_home;
    app->cam.zoomMove( 1.0, ofVec2f(0,0), 1000, ^(float * arg){
        ofApp::getInstance()->mode_manager.mode = DT_MODE_HOME;
    });
}

void dt_mode_manager::go_to_zoom_mode( dt_circle_base *target ){
    mode = DT_MODE_HOME2ZOOM;
    if( target ){
        zoom_mode_target = target;
        current_ui = &ui_zoom;
        app->cam.moveZoom( zoom_mode_target->data.position, 1.5, 1000, ^(float *arg){
            ofApp::getInstance()->mode_manager.mode = DT_MODE_ZOOM;
        });
    }
}

void dt_mode_manager::toggle_mode(){
    if( mode == DT_MODE_HOME ){
        go_to_zoom_mode( dt_circle_base::selected_circle );
    }else if( mode == DT_MODE_ZOOM ){
        go_to_home_mode();
    }
}

void dt_mode_manager::debug_draw(){
	
	string mode_s = "";
	switch ( mode ) {
		case DT_MODE_HOME:
			mode_s = "DT_MODE_HOME";
			break;
			
		case DT_MODE_ZOOM:
			mode_s = "DT_MODE_ZOOM";
			break;

		case DT_MODE_HOME2ZOOM:
			mode_s = "DT_MODE_HOME2ZOOM";
			break;
			
		case DT_MODE_ZOOM2HOME:
			mode_s = "DT_MODE_ZOOM2HOME";
			break;
			
		default:
			break;
	}
	ofPushMatrix();
	ofSetColor( 255, 0, 0 );
	ofDrawBitmapString("MODE: " + mode_s, 20, 20 );
	ofPopMatrix();
}

