#include "ofApp.h"

#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_container.h"
#include "dt_circle_param.h"

/*
 *
 *	singleton
 *
 */
ofApp * ofApp::instance = NULL;

ofApp * ofApp::init(){
	if(!instance) instance = new ofApp();
	else ofLogError("ofApp::init() Called again!!!!");
	return instance;
}

/*
 *
 *	setup
 *
 */
ofApp::ofApp(){}

void ofApp::windowResized(int w, int h){
	canvas.setX(80);
	canvas.setY(50);

	canvas.width = w-160;
	canvas.height = h-450;
	
	config.reset_position();
}

void ofApp::setup(){
	windowResized(ofGetWidth(), ofGetHeight());
	setupVisual();
	setupModule();
}

void ofApp::setupVisual(){
	cout << "setting up Visual" << endl;

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetCircleResolution(10);
	ofDisableAlphaBlending();
	ofEnableAntiAliasing();
	ofDisableSmoothing();
}

void ofApp::setupModule(){
	rhythm_lib.setup(3, 24);

	config.setup();
	all_containers.setup();
	osc_recorder.setup();
	
	sequence_thread.setup();
	sequence_thread.change_bpm(300);
	sequence_thread.start();
}


/*
 *
 *	update & draw loop
 *
 */
void ofApp::update(){
	touch.update();
	config.update();
	all_containers.update();

	dt_config::DT_MASSIVE_MODE = (all_containers.circle_base_container->circles.size() >= 5000);

	osc_recorder.update(canvas.x+30, canvas.y + canvas.height + 30, canvas.width-70, 100);
}


void ofApp::draw(){
	ofDisableAlphaBlending();
	ofBackground(7, 17, 40);
	ofSetupScreenOrtho();
	
	all_containers.draw();
	
	if(dt_config::DT_SHOW_LINER_DRAWER) linear_drawer.draw(canvas.x+30, canvas.y+30, canvas.width-60, canvas.height-60, 1);
		
	config.draw();
}

void ofApp::mousePressed(int x, int y, int button){ touch.mousePressed(x, y, button);}

void ofApp::mouseDragged(int x, int y, int button){ touch.mouseDragged(x, y, button); }

void ofApp::mouseReleased(int x, int y, int button){ /*touch.mouseReleased(x, y, button);*/ }

void ofApp::gotMessage(ofMessage msg){ cout << msg.message << endl; }

void ofApp::keyPressed(int key){
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
//		case OF_KEY_RIGHT:	sequence_thread.change_freq( sequence_thread.freq+1 ); break;
//		case OF_KEY_LEFT:	sequence_thread.change_freq( sequence_thread.freq-1 ); break;
 		case '1': sequence_thread.change_bpm(100); break;
		case '2': sequence_thread.change_bpm(200); break;
		case '3': sequence_thread.change_bpm(300); break;
		case '4': sequence_thread.change_bpm(400); break;
		case '5': sequence_thread.change_bpm(500); break;
		case '6': sequence_thread.change_bpm(600); break;
		case '7': sequence_thread.change_bpm(700); break;
		case '8': sequence_thread.change_bpm(800); break;
		case '9': sequence_thread.change_bpm(900); break;
		case '0': sequence_thread.change_bpm(1000); break;
			
		// play
		case ' ': dt_config::DT_PLAY_GEN_RHYTHM = !dt_config::DT_PLAY_GEN_RHYTHM; config.synch_param(); break;
		case OF_KEY_TAB: osc_recorder.toggle_play_fragment(); config.synch_param(); break;

		case 'q': if(bAlt) all_containers.change_speed_random_all(1, 1);
		else dt_config::DT_BEAT_SPEED_MAX = 1; config.synch_param();
				break;
		case 'w': if(bAlt) all_containers.change_speed_random_all(1, 4);
				else dt_config::DT_BEAT_SPEED_MAX = 4; config.synch_param();
				break;
		case 'r': if(bAlt)all_containers.change_speed_random_all(1, 8);
				else dt_config::DT_BEAT_SPEED_MAX = 8; config.synch_param();
				break;
		case 't': if(bAlt) all_containers.change_speed_random_all(1, 16);
				else dt_config::DT_BEAT_SPEED_MAX = 16; config.synch_param();
				break;
		case 'y': if(bAlt) all_containers.change_speed_random_all(1, 32);
				else dt_config::DT_BEAT_SPEED_MAX = 32; config.synch_param();
				break; 
		case 'u': if(bAlt) all_containers.change_speed_random_all(1, 64);
				else dt_config::DT_BEAT_SPEED_MAX = 64; config.synch_param();
				break;
		case 'i': if(bAlt) all_containers.change_speed_random_all(1, 128);
				else dt_config::DT_BEAT_SPEED_MAX = 128; config.synch_param();
				break;
		case 'o': if(bAlt) all_containers.change_speed_random_all(1, 256);
				else dt_config::DT_BEAT_SPEED_MAX = 256; config.synch_param();
				break;
		case 'p': if(bAlt) all_containers.change_speed_random_all(1, 512);
				else dt_config::DT_BEAT_SPEED_MAX = 512; config.synch_param();
				break;
		case '@': if(bAlt) all_containers.change_speed_random_all(1, 1024);
				else dt_config::DT_BEAT_SPEED_MAX = 1024; config.synch_param();
				break;
			
		case 'a': all_containers.change_beat_resolution_all(4); break;
		case 's': all_containers.change_beat_resolution_all(8); break;
		case 'd': all_containers.change_beat_resolution_all(16); break;
		case 'f': all_containers.change_beat_resolution_all(32); break;
		case 'g': all_containers.change_beat_resolution_all(64); break;
		case 'h': all_containers.change_beat_resolution_all(128); break;
		case 'j': all_containers.change_beat_resolution_all(256); break;
		case 'k': all_containers.change_beat_resolution_all(512); break;
		case 'l': all_containers.change_beat_resolution_all(1024); break;

		case 'L': dt_config::DT_SHOW_LINER_DRAWER = !dt_config::DT_SHOW_LINER_DRAWER; config.synch_param(); break;
		case 'G': config.toggle(); break;
		case 'F': ofToggleFullscreen(); break;
		case 'B': all_containers.change_beat_all(floor(ofRandom(dt_config::DT_RHYTHM_SHAPE_SLOT_MIN, dt_config::DT_RHYTHM_SHAPE_SLOT_MAX-1))); break;
		case 'P': all_containers.change_position_all(); break;
		case 'R': dt_config::DT_SHOW_BUFFERED_RHYTHM = !dt_config::DT_SHOW_BUFFERED_RHYTHM; config.synch_param(); break;

		case OF_KEY_RETURN:
			touch.make_random_circle(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 100); break;
			
		default: break;
	}
}


void ofApp::exit(){
	sequence_thread.stop();
}
