#include "ofApp.h"

#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_container.h"
#include "dt_circle_param.h"


/*
 *	singleton
 */
ofApp * ofApp::instance = NULL;

ofApp * ofApp::init(){
	if(!instance) instance = new ofApp();
	else ofLogError("ofApp::init() Called again!!!!");
	return instance;
}

ofApp * ofApp::getInstance(){
	return instance;
}


/*
 *	setupper
 */
ofApp::ofApp()
:bShow_linear_drawer(false){
}

void ofApp::windowResized(int w, int h){
	canvas.setX(100);
	canvas.setY(50);

	canvas.width = w-200;
	canvas.height = h-230;
}

void ofApp::setup(){
	setupVisual();
	setupModule();
}

void ofApp::setupVisual(){
	cout << "setting up Visual" << endl;

	//ofSetOrientation(OF_ORIENTATION_DEFAULT);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetCircleResolution(10);
	ofDisableAlphaBlending();
	ofEnableAntiAliasing();
	ofDisableSmoothing();
	windowResized(ofGetWidth(), ofGetHeight());
}


void ofApp::setupModule(){
	
	rhythm_lib.setup(DT_RHYTHM_SHAPE_MIN_SLOT, DT_RHYTHM_SHAPE_MAX_SLOT);
	
	sequence_thread.change_bpm(5);
	sequence_thread.start();
}


/*
 *	update & draw loop
 */
void ofApp::update(){
	touch.update();
	all_containers.update();
}


void ofApp::draw(){
	ofDisableAlphaBlending();
	ofBackground(10, 20, 50);
	ofSetupScreenOrtho();
	
	all_containers.draw();
	if(bShow_linear_drawer) linear_drawer.draw(canvas.x+30, canvas.y+30, canvas.width-60, canvas.height-60, 1);
	
	ofSetColor(95);
	draw_info(canvas.x+15, canvas.y+canvas.height + 60);
}

void ofApp::draw_info(int x, int y){

	ofPushMatrix();
	ofTranslate(x, y);
	ofFill();
	
	int circle_num = all_containers.circle_base_container->circles.size();
	int noteOn_num = all_containers.note_on_container->circles.size();
	int param_num = all_containers.param_container->circles.size();
	int output_num = all_containers.output_container->circles.size();
	
	float fps = ofGetFrameRate();
	
	ofPushMatrix();{
		ofTranslate(0, 0);
		ofDrawBitmapString("Fps: " + ofToString(fps),			0, 0);
		ofDrawBitmapString("All: " + ofToString(circle_num),	150, 0);
		ofDrawBitmapString("noteOn: " + ofToString(noteOn_num), 150, 20);
		ofDrawBitmapString("Param: " + ofToString(param_num),	150, 40);
		ofDrawBitmapString("output: " + ofToString(output_num), 150, 60);
	}ofPopMatrix();
	
	// sleep time
	ofPushMatrix();{
		ofTranslate(300, 0);
		ofDrawBitmapString("sleep: " + ofToString(sequence_thread.real_sleep_micro_sec), -0, 0);
		ofDrawBitmapString("freq: "  + ofToString(sequence_thread.freq), 0, 20);
		ofDrawBitmapString("amp: "  + ofToString(sequence_thread.random_amount), 0, 40);

		ofTranslate(150, -5);
		ofLine(0, 0, 300, 0);
		int pos = sequence_thread.real_sleep_micro_sec * 0.0005;
		ofRect(pos, -2, 4, 4);
	}ofPopMatrix();
	
	// param circle color schem
	ofPushMatrix();{
		ofTranslate(canvas.width-420, 0);
		ofSetColor(dt_circle_param_base::noteNum_color);
		ofDrawBitmapString("noteNum", -25, 0);
		
		ofSetColor(dt_circle_param_base::velocity_color);
		ofDrawBitmapString("vel", 50, 0);
		
		ofSetColor(dt_circle_param_base::duration_color);
		ofDrawBitmapString("dur", 100, 0);
		
		ofSetColor(dt_circle_param_base::L_color);
		ofDrawBitmapString("L", 150, 0);
		
		ofSetColor(dt_circle_param_base::R_color);
		ofDrawBitmapString("R", 200, 0);
		
		ofSetColor(dt_circle_param_base::cc12_color);
		ofDrawBitmapString("cc12", 250, 0);
		
		ofSetColor(dt_circle_param_base::cc13_color);
		ofDrawBitmapString("cc13", 300, 0);
		
		ofSetColor(dt_circle_param_base::cc14_color);
		ofDrawBitmapString("cc14", 350, 0);
	}ofPopMatrix();

	
	ofPopMatrix();
}


/*
 *
 *	device
 *
 */
void ofApp::mousePressed(int x, int y, int button){ touch.mousePressed(x, y, button);}

void ofApp::mouseDragged(int x, int y, int button){ touch.mouseDragged(x, y, button); }

void ofApp::mouseReleased(int x, int y, int button){ touch.mousePressed(x, y, button); }

void ofApp::gotMessage(ofMessage msg){ cout << msg.message << endl; }

void ofApp::keyPressed(int key){
	bool bAlt = (key == OF_KEY_ALT);

	switch(key){
			
		case OF_KEY_UP:
			if(!bAlt) sequence_thread.change_sleep_time_microsec(sequence_thread.sleep_microsec -= 1000);
			else sequence_thread.master_delay++;
			break;
			
		case OF_KEY_DOWN:
			if(!bAlt) sequence_thread.change_sleep_time_microsec(sequence_thread.sleep_microsec += 1000);
			else sequence_thread.master_delay++;
			break;
		case OF_KEY_RIGHT:	sequence_thread.change_freq( sequence_thread.freq+1 ); break;
		case OF_KEY_LEFT:	sequence_thread.change_freq( sequence_thread.freq-1 ); break;
 		case '1': sequence_thread.change_bpm(2); break;
		case '2': sequence_thread.change_bpm(4); break;
		case '3': sequence_thread.change_bpm(8); break;
		case '4': sequence_thread.change_bpm(12); break;
		case '5': sequence_thread.change_bpm(16); break;
		case '6': sequence_thread.change_bpm(20); break;

		case '7': sequence_thread.random_amount =  5000; break;
		case '8': sequence_thread.random_amount =  40000; break;
		case '9': sequence_thread.random_amount =  300000; break;
		case '0': sequence_thread.change_freq(0); break;
			
		case ' ': sequence_thread.bHold = !sequence_thread.bHold; break;
		case 'f': ofToggleFullscreen(); break;
		case 's': all_containers.change_speed_all(1); break;
		case 'b': all_containers.change_beat_all(floor(ofRandom(DT_RHYTHM_SHAPE_MIN_SLOT, DT_RHYTHM_SHAPE_MAX_SLOT-1))); break;
		case 'p': all_containers.change_position_all(); break;
		case 'r': all_containers.change_speed_random_all(1, 128); break;
		case 'l': bShow_linear_drawer = !bShow_linear_drawer; break;
		case 'm': midi_writer.save_midi_file("_test" + ofGetTimestampString() + ".midi"); break;
		default: break;
	}
}

 /*
 *
 *	finishing
 *
 */
void ofApp::exit(){
	sequence_thread.stop();
}

