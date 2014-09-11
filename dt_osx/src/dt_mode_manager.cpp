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
}

void dt_mode_manager::change_mode( dt_mode m ){
	switch( m ){
		case DT_MODE_HOME:
			mode = DT_MODE_ZOOM2HOME;
			app->cam.zoomMove( 1.0, ofVec2f(0,0), 1000, ^(float * arg){
				ofApp::getInstance()->mode_manager.mode = DT_MODE_HOME;
			});
			break;

		case DT_MODE_ZOOM:
		{
			mode = DT_MODE_HOME2ZOOM;
			dt_circle_base * sel = dt_circle_base::selected_circle;
			if( sel ){
				app->cam.moveZoom( sel->data.position, 1.7, 1000, ^(float *arg){
					ofApp::getInstance()->mode_manager.mode = DT_MODE_ZOOM;
				});
			}
			break;
		}
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