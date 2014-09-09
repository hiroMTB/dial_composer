//
//  dt_touch.mm
//  dialt
//
//  Created by mtb on 5/5/14.
//
//

#include "dt_touch.h"
#include "ofApp.h"
#include "dt_dial_ui.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_param.h"
#include "dt_circle_container.h"
#include "dt_circle_all_containers.h"

dt_touch::dt_touch(){
	touched_circle = NULL;
	touched_circle_center.set( 0,0 );
	touch_entry.set( 0,0 );
	touch_time = -1;
	t_obj = DT_TOUCH_OBJ_NONE;
}

void dt_touch::update(){
	if( touch_time >= 0 ){
		touch_time++;
	}
}

//
//	where does user touch?
//
//	control ui?			1st priority
//	selection ui?
//	circle?
//	canvas?
//
void dt_touch::mousePressed( int tx, int ty, int button ){
	app = ofApp::getInstance();
	
	ofVec2f wp = app->cam.screenToWorld( ofVec2f(tx,ty) );
    touch_entry = wp;

	t_obj = DT_TOUCH_OBJ_NONE;
	
	// UI ELEM ?
	dt_circle_base_container * circle_base_container = app->all_containers.circle_base_container;
	vector<dt_circle_base*> &circles = circle_base_container->circles;
	for( int i=0; i<circles.size(); i++ ){										// do not want to iterate all
		dt_circle_base * c	= (dt_circle_base*)( circles[i] );
		if( c == NULL ) continue;

		dt_dial_ui * ui = c->ui;

		if( ui && c->data.bShowUI ){
			int ui_elem = ui->touch_test( wp );
			if( ui_elem != DT_DIAL_UI_NONE ){
				t_obj = DT_TOUCH_OBJ_UI_ELEM;
				break;
			}
		}
	}

	if( t_obj == DT_TOUCH_OBJ_NONE ){
		dt_circle_base * c = app->all_containers.circle_base_container->getTouchedCircle( wp );
		
		// CIRCLE or CANVAS ?
		if( c != NULL ){
			// touch circle
			touched_circle = c;
			touched_circle_center = c->data.position;
			dt_circle_base::selected_circle = c;
			touch_time = 0;
			t_obj = DT_TOUCH_OBJ_CIRCLE;
		}else{
			// touch canvas
			touch_time = 0;
			t_obj = DT_TOUCH_OBJ_CANVAS;
            touched_circle = NULL;
            app->cam.dragStartPos = app->cam.trans;
		}
	}
}

/*
 *
 *		drag control ui ?
 *		move circle ?
 *		mvoe camera ?
 *
 */
void dt_touch::mouseDragged( int tx, int ty, int button ){

    ofVec2f wp = app->cam.screenToWorld( ofVec2f(tx,ty) );
    ofVec2f dist = wp - touch_entry;

    dt_circle_base * c = touched_circle;

	if( c ){
        // drag circle
		c->data.position = touched_circle_center + dist;
		dt_circle_base::selected_circle = c;
	}else{
        // drag camera
        app->cam.trans = app->cam.dragStartPos - dist*0.3;
    }
}

void dt_touch::mouseReleased( int tx, int ty, int button ){

    ofVec2f wp = app->cam.screenToWorld( ofVec2f(tx,ty) );
    
	float time = touch_time;

	// Short time touch end
	if( 0<=time && time < 13 ){
		if( touched_circle && touched_circle->ui ){
			if( touched_circle->data.bShowUI ){
				if( touched_circle->ui->mode == DT_DIAL_UI_HOME ){
					touched_circle->ui->change_mode( DT_DIAL_UI_NONE );
				}else{
					touched_circle->ui->change_mode( DT_DIAL_UI_HOME );
				}
			}else{
				touched_circle->ui->change_mode( DT_DIAL_UI_HOME );
			}
		}else{
            // create new circle
            dt_circle_note_on * c = new dt_circle_note_on();
			app->all_containers.note_on_container->addCircle( c );
            c->setup(ofRandom( dt_config::DT_RHYTHM_SHAPE_SLOT_MIN, dt_config::DT_RHYTHM_SHAPE_SLOT_MAX) );
			c->data.position = wp;
			app->all_containers.circle_base_container->addCircle( c );
			touched_circle = c;
			touched_circle_center = c->data.position;
 			dt_circle_base::selected_circle = c;
        }
	}else{
		touched_circle = NULL;
	}

	touch_time = -1;
	
	t_obj = DT_TOUCH_OBJ_NONE;
}