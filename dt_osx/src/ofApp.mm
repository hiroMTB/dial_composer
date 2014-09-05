#include "ofApp.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_container.h"
#include "dt_circle_param.h"

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
    dt_config::DT_SIZE_BASE = max( w, h )/13.0;
}

void ofApp::setup(){
	windowResized(ofGetWidth(), ofGetHeight());
	setupVisual();
	setupModule();
    bg.set( 0.8 );
}

void ofApp::setupVisual(){
	cout << "setting up Visual" << endl;

	ofSetFrameRate( 60 );
	ofSetVerticalSync( true );
	ofSetCircleResolution( 3 );
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableSmoothing();
    
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
	touch.update();
	config.update();
	all_containers.update();

	osc_recorder.update( canvas.x+30, canvas.y + canvas.height + 30, canvas.width-70, 100 );
}

void ofApp::draw(){
    ofBackground( bg );

    switch( view_mode ){
        case 0:
            ofSetupScreenOrtho();
            all_containers.draw();
            if( dt_config::DT_SHOW_LINER_DRAWER) linear_drawer.draw(canvas.x+30, canvas.y+30, canvas.width-60, canvas.height-60, 1 );
            config.draw();
            break;

        case 1:
            // draw rhythm screen
            ofSetupScreenOrtho();
            break;

        default:
            break;
    }
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
 		case '0':  view_mode = 0; break;
 		case '1':  view_mode = 1; break;
			
		// play
		case ' ': dt_config::DT_PLAY_GEN_RHYTHM = !dt_config::DT_PLAY_GEN_RHYTHM; config.synch_param(); break;
		case OF_KEY_TAB: osc_recorder.toggle_play_fragment(); config.synch_param(); break;

		case 'q': if(bAlt) all_containers.change_speed_random_all(1, 1);
		else dt_config::DT_BEAT_SPEED_MAX = 1; config.synch_param();
				break;
			
		case 'a': all_containers.change_beat_resolution_all(4); break;


		case 'L': dt_config::DT_SHOW_LINER_DRAWER = !dt_config::DT_SHOW_LINER_DRAWER; config.synch_param(); break;
		case 'G': config.toggle(); break;
		case 'F': ofToggleFullscreen(); break;
		case 'B': all_containers.change_beat_all(floor(ofRandom(dt_config::DT_RHYTHM_SHAPE_SLOT_MIN, dt_config::DT_RHYTHM_SHAPE_SLOT_MAX-1))); break;
		case 'P': all_containers.change_position_all(); break;
		case 'R': dt_config::DT_SHOW_BUFFERED_RHYTHM = !dt_config::DT_SHOW_BUFFERED_RHYTHM; config.synch_param(); break;

		default: break;
	}
}

void ofApp::exit(){
	sequence_thread.stop();
}
