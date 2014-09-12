#include "ofApp.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_container.h"
#include "dt_circle_param.h"

#import "AppDelegate.h"

ofApp * ofApp::instance = NULL;

ofApp * ofApp::init(){
	if(!instance){
        ofLogNotice( "ofApp", "openFrameworks v" + ofGetVersionInfo() );
        instance = new ofApp();
    }else{
        ofLogError("ofApp::init() Called again!!!!");
    }
	return instance;
}

ofApp::ofApp(){}

void ofApp::windowResized( int w, int h ){
	canvas.setX( 80 );
	canvas.setY( 50 );
	canvas.width = w-100;
	canvas.height = h-50;
	config.reset_position();
    dt_config::DT_SIZE_BASE = max( w, h )/15.0;
    cam.reset();
}

void ofApp::setup(){
	setupVisual();
	setupModule();
}

void ofApp::setupVisual(){
	ofSetFrameRate( 60 );
	ofSetVerticalSync( true );
	ofSetCircleResolution( 3 );
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableSmoothing();
    ofDisableArbTex();
    noise.loadImage("img/noise2.png");
    noise.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
	bg.set( 0.5 );
}

void ofApp::setupModule(){
	rhythm_lib.setup( 3, 24 );
	config.setup();
	all_containers.setup();
	osc_recorder.setup();
	sequence_thread.setup();
	sequence_thread.change_bpm( 120 );
	sequence_thread.start();
	mode_manager.setup();
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

#ifdef DEBUG
    cam.debugDraw();
#endif
    
    cam.end();

#ifdef DEBUG
	mode_manager.debug_draw();
    
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
#endif

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
			break;
			
		case OF_KEY_DOWN:
			break;
            
        // view_mode
 		case OF_KEY_RETURN:
            mode_manager.toggle_mode();
            break;
			
		// play
		case ' ':
            dt_config::DT_PLAY_GEN_RHYTHM = !dt_config::DT_PLAY_GEN_RHYTHM;
            config.synch_param();
            break;
            
		case OF_KEY_TAB:
            osc_recorder.toggle_play_fragment();
            config.synch_param(); break;
        
		case 'L':
            dt_config::DT_SHOW_LINER_DRAWER = !dt_config::DT_SHOW_LINER_DRAWER;
            config.synch_param();
            break;
            
		case 'C':
            config.toggle();
            break;

		case 'F':
            ofToggleFullscreen();
            break;
            
		case 'B':
            all_containers.change_beat_all(floor(ofRandom(dt_config::DT_RHYTHM_SHAPE_SLOT_MIN, dt_config::DT_RHYTHM_SHAPE_SLOT_MAX-1)));
            break;
            
		case 'P': all_containers.change_position_all();
            break;
            
		case 'R':
            cam.angle += 30;
            break;

		default: break;
	}
}

void ofApp::exit(){
	sequence_thread.stop();
}
