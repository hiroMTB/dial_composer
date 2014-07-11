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
	#include "dt_circle_midi.h"
	#include "dt_circle_osc.h"

#include "dt_circle_container.h"
#include "dt_circle_all_containers.h"


dt_touch::dt_touch(){
	touched_circle = NULL;
	touched_circle_center.set(0,0);
	touch_entry.set(0,0);
	touch_time = -1;
	t_obj = DT_TOUCH_OBJ_NONE;

}

void dt_touch::update(){
	if(touch_time >= 0){
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
void dt_touch::mousePressed(int x, int y, int button){
	app = ofApp::getInstance();
	
	ofVec2f t(x, y);
	
	t_obj = DT_TOUCH_OBJ_NONE;
	
	// UI ELEM ?
	dt_circle_base_container * circle_base_container = app->all_containers.circle_base_container;
	vector<dt_circle_base*> &circles = circle_base_container->circles;
	for(int i=0; i<circles.size(); i++){										// do not want to iterate all
		dt_circle_base * c	= (dt_circle_base*)(circles[i]);
		if(c==NULL) continue;

		dt_dial_ui * ui = c->ui;

		if(ui && c->data.bShowUI){
			int ui_elem = ui->touch_test(t);
			if( ui_elem != DT_DIAL_UI_NONE){
				t_obj = DT_TOUCH_OBJ_UI_ELEM;
				break;
			}
		}
	}


	if(t_obj == DT_TOUCH_OBJ_NONE){
		dt_circle_base * c = (app->all_containers.circle_base_container->getTouchedCircle(t));
		
		// CIRCLE or CANVAS ?
		if( c != NULL){
			// touch circle
			touched_circle = c;
			touched_circle_center = c->data.position;
			touch_entry = t;
			dt_circle_base::selected_circle = c;
			touch_time = 0;
			
			t_obj = DT_TOUCH_OBJ_CIRCLE;
		}else{
			
			for(int i=0; i<100; i++){
				int max_slot = 10;
				
				ofVec2f random_p(ofRandom(-1, 1), ofRandom(-1, 1));
				random_p *= 3.0;
				
				// touch canvas
				float rand = ofRandom(0, 1.0);
				dt_circle_base * c = NULL;
				if(rand<0.25){
					dt_circle_note_on * no = new dt_circle_note_on();
					app->all_containers.note_on_container->addCircle(no);
					c = no;
					max_slot = DT_RHYTHM_SHAPE_MAX_SLOT;
				}else if(rand<0.33){
					dt_circle_osc * o = new dt_circle_osc();
					app->all_containers.output_container->addCircle(o);
					c = o;
				}else{
					float rand = ofRandom(1) * 0.8;
					if(rand<0.1){
						dt_circle_param_noteNum * nn = new dt_circle_param_noteNum();
						app->all_containers.param_container->addCircle(nn);
						c = nn;
					}else if(rand<0.2){
						dt_circle_param_velocity * v = new dt_circle_param_velocity();
						app->all_containers.param_container->addCircle(v);
						c = v;
					}else if(rand<0.3){
						dt_circle_param_duration * d = new dt_circle_param_duration();
						app->all_containers.param_container->addCircle(d);
						c = d;
					}else if(rand<0.4){
						dt_circle_param_pan * p = new dt_circle_param_pan();
						app->all_containers.param_container->addCircle(p);
						c = p;
					}else if(rand<0.5){
						 dt_circle_param_cc12 * y = new dt_circle_param_cc12();
						app->all_containers.param_container->addCircle(y);
						c = y;
					}else if(rand<0.6){
						dt_circle_param_cc13 * y = new dt_circle_param_cc13();
						app->all_containers.param_container->addCircle(y);
						c = y;
					}else if(rand<0.7){
						dt_circle_param_cc14 * y = new dt_circle_param_cc14();
						app->all_containers.param_container->addCircle(y);
						c = y;
					}else if(rand<0.8){
						dt_circle_param_cc16 * y = new dt_circle_param_cc16();
						app->all_containers.param_container->addCircle(y);
						c = y;
					}
				}
				if(c!= NULL){
					c->setup(ofRandom(DT_RHYTHM_SHAPE_MIN_SLOT, max_slot));
					c->data.position = t + random_p;
					app->all_containers.circle_base_container->addCircle(c);

					touched_circle = c;
					touched_circle_center = c->data.position;
					touch_entry = t;
					dt_circle_base::selected_circle = c;
					
					touch_time = -1;
					
					t_obj = DT_TOUCH_OBJ_CANVAS;
				}
			}
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
void dt_touch::mouseDragged(int x, int y, int button){
	dt_circle_base * c = touched_circle;
	ofVec2f t(x, y);

	if(c){
		ofVec2f dist = (t - touch_entry);
		c->data.position = dist + touched_circle_center;
		dt_circle_base::selected_circle = c;
	}
}

void dt_touch::mouseReleased(int x, int y, int button){

	float time = touch_time;

	// Short time touch end
	if(0<=time && time < 13){
		dt_circle_base * c = touched_circle;
		if(c && c->ui){
			if(c->data.bShowUI){
				if(c->ui->mode == DT_DIAL_UI_HOME){
					c->ui->change_mode(DT_DIAL_UI_NONE);
				}else{
					c->ui->change_mode(DT_DIAL_UI_HOME);
				}
			}else{
				c->ui->change_mode(DT_DIAL_UI_HOME);
			}
		}
	}else{
		touched_circle = NULL;
	}

	touch_time = -1;
	
	t_obj = DT_TOUCH_OBJ_NONE;
}



