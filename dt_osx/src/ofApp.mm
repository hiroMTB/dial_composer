#include "ofApp.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_container.h"
#include "dt_circle_param.h"

#import "AppDelegate.h"

ofApp * ofApp::instance = NULL;

ofApp * ofApp::init(){
	if(!instance) instance = new ofApp();
	else ofLogError("ofApp::init() Called again!!!!");
	return instance;
}

ofApp::ofApp(){}

void ofApp::windowResized( int w, int h ){
	canvas.setX( 80 );
	canvas.setY( 50 );
	canvas.width = w-100;
	canvas.height = h-50;
	
	config.reset_position();
    dt_config::DT_SIZE_BASE = max( w, h )/12.0;

    cam.reset();
}

void ofApp::setup(){
	setupVisual();
	setupModule();
    bg.set( 0.5 );
}

void ofApp::setupVisual(){
	cout << "setting up Visual" << endl;

	ofSetFrameRate( 60 );
	ofSetVerticalSync( true );
	ofSetCircleResolution( 3 );
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableSmoothing();

    ofDisableArbTex();
    noise.loadImage("img/noise2.png");
    noise.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
    view_mode = 0;
}

void ofApp::setupModule(){
	rhythm_lib.setup( 3, 24 );

	config.setup();
	all_containers.setup();
	osc_recorder.setup();
	
	sequence_thread.setup();
	sequence_thread.change_bpm( 120 );
	sequence_thread.start();
}

void ofApp::update(){
    cam.update();
	touch.update();
	config.update();
	all_containers.update();
	osc_recorder.update( canvas.x+30, canvas.y + canvas.height + 30, canvas.width-70, 100 );

    // update Cocoa UI
    AppDelegate *  d = (AppDelegate*)[NSApplication sharedApplication].delegate;

    if( d ) [d update_ui];
}

void ofApp::draw(){
    ofBackground( bg );
    ofSetColor( 255, 170 );

    float w = ofGetWidth();
    float h = ofGetHeight();
    noise.width = w;
    noise.height = h;
    noise.draw( 0, 0 );

    cam.begin();
    all_containers.draw();
    
    
    /*switch( view_mode ){
        case 0:
            all_containers.draw();
            break;

        case 1:
        {
            dt_circle_base * sel = dt_circle_base::selected_circle;
            if( sel ){
                sel->draw();
                dt_circle_type t = sel->data.circle_type;
                if( t == DT_CIRCLE_NOTE_ON ){
                    dt_circle_note_on * o = static_cast<dt_circle_note_on*>(sel);
                    for( int i=0; i<o->input_circles.size(); i++ ){
                        o->input_circles[i]->draw();
                    }
                }
            }
            break;
        }
    }
    */
    
    cam.debugDraw();
    cam.end();
    
    ofPushMatrix();
    if( dt_config::DT_SHOW_LINER_DRAWER) linear_drawer.draw(canvas.x+30, canvas.y+30, canvas.width-60, canvas.height-60, 1 );
    config.draw();
    ofPopMatrix();

    mouseX = ofGetMouseX();
    mouseY = ofGetMouseY();
    ofRect( mouseX, mouseY, 5, 5 );
    ofSetColor(20);
    ofDrawBitmapString( "mouse " + ofToString(mouseX) + ", " + ofToString(mouseY), mouseX, mouseY );
    
    ofVec2f world = cam.screenToWorld( ofVec2f(mouseX, mouseY) );
    ofDrawBitmapString( "world " + ofToString(world.x) + ", " + ofToString(world.y), mouseX, mouseY+20 );
}

void ofApp::mousePressed( int x, int y, int button ){
	touch.mousePressed( x, y, button );
}

void ofApp::mouseDragged( int x, int y, int button ){
	touch.mouseDragged( x, y, button );
}

void ofApp::mouseReleased( int x, int y, int button ){
	touch.mouseReleased( x, y, button );
}

void ofApp::gotMessage( ofMessage msg ){
	cout << msg.message << endl;
}

void ofApp::keyPressed( int key ){
	bool bAlt = (key == OF_KEY_ALT);
	// bool bShift = (key == OF_KEY_SHIFT); does not work?
	
	switch(key){
			
		case OF_KEY_UP:
			if(!bAlt) sequence_thread.change_sleep_time_microsec(sequence_thread.sleep_microsec -= 1000);
			else sequence_thread.master_delay++;
			break;
			
		case OF_KEY_DOWN:
			if(!bAlt) sequence_thread.change_sleep_time_microsec(sequence_thread.sleep_microsec += 1000);
			else sequence_thread.master_delay++;
			break;
            
        // view_mode
 		case '0':  change_view( 0 ); break;
 		case '1':  change_view( 1 ); break;
			
		// play
		case ' ': dt_config::DT_PLAY_GEN_RHYTHM = !dt_config::DT_PLAY_GEN_RHYTHM; config.synch_param(); break;
		case OF_KEY_TAB: osc_recorder.toggle_play_fragment(); config.synch_param(); break;

		case 'q': if(bAlt) all_containers.change_speed_random_all(1, 1);
		else dt_config::DT_BEAT_SPEED_MAX = 1; config.synch_param();
				break;
			
		case 'a': all_containers.change_beat_resolution_all(4); break;

		case 'L': dt_config::DT_SHOW_LINER_DRAWER = !dt_config::DT_SHOW_LINER_DRAWER; config.synch_param(); break;
		case 'C': config.toggle(); break;
		case 'F': ofToggleFullscreen(); break;
		case 'B': all_containers.change_beat_all(floor(ofRandom(dt_config::DT_RHYTHM_SHAPE_SLOT_MIN, dt_config::DT_RHYTHM_SHAPE_SLOT_MAX-1))); break;
		case 'P': all_containers.change_position_all(); break;
		case 'R':
            cam.angle += 30;
            break;

		default: break;
	}
}

void ofApp::exit(){
	sequence_thread.stop();
}


void ofApp::change_view( int _view_mode ){
    
    switch( _view_mode ){
        case 0:
            cam.zoom( 1.0, 500 );
            cam.move( ofVec2f(0,0), 500, 501);
            view_mode = _view_mode;
            break;
        case 1:
        {
            dt_circle_base * sel = dt_circle_base::selected_circle;
            if( sel ){
                cam.moveZoom( sel->data.position, 1.5, 1000 );
                view_mode = _view_mode;
            }
            break;
        }
    }
}

