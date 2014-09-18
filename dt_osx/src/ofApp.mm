#include "ofApp.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_container.h"
#include "dt_circle_param.h"
#include "ofxModifierKeys.h"

#import  "AppDelegate.h"

ofApp * ofApp::app = NULL;

ofApp * ofApp::init(){

#ifdef DEBUG
    ofSetLogLevel( OF_LOG_VERBOSE );
#else
    ofSetLogLevel( OF_LOG_ERROR );
#endif
    
	if(!app){
        ofLogNotice( "ofApp", "openFrameworks v" + ofGetVersionInfo() );
        app = new ofApp();
    }else{
        ofLogError("ofApp::init() Called again!!!!");
    }
	return app;
}

ofApp::ofApp()
:
backingScale( 1 )
{}

void ofApp::windowResized( int w, int h ){
	backingScale = [[NSScreen mainScreen] backingScaleFactor];
    dt_config::DT_SIZE_BASE = max( w, h )/14.0 * backingScale;
}

void ofApp::setup(){

    //Visual
	ofSetFrameRate( 60 );
	ofSetVerticalSync( true );
	ofSetCircleResolution( 24 );
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableSmoothing();
    ofDisableArbTex();
    noise.loadImage("img/noise2.png");
    noise.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
	bg.set( 0.1 );
    
    //Module
	rhythm_lib.setup( 3, 24 );
	config.setup();
	all_containers.setup();
	osc_recorder.setup();
	sequence_thread.setup();
	sequence_thread.change_bpm( 120 );
	sequence_thread.start();
	mode_manager.setup();
	cam.reset();
}

void ofApp::update(){
    mode_manager.update();
    cam.update();
	config.update();
	all_containers.update();
    
    [[[NSApplication sharedApplication] delegate] update_ui];
}

void ofApp::draw(){
    ofBackground( bg );
    ofSetColor( 255, 30 );

    float w = ofGetWidth();
    float h = ofGetHeight();
    noise.width = w;
    noise.height = h;
    noise.draw( 0, 0 );

    cam.begin(); {
        all_containers.draw();
    } cam.end();

  	osc_recorder.draw( 5, ofGetHeight()-70, ofGetWidth()-10, 64 );
    if( dt_config::DT_SHOW_LINER_DRAWER) linear_drawer.draw( 30, 300, 30, 500, 1 );
    
#ifdef DEBUG
	mode_manager.debug_draw();
    
    mouseX = ofGetMouseX();
    mouseY = ofGetMouseY();
    ofVec2f world = cam.screenToWorld( ofVec2f(mouseX, mouseY) );
    ofSetColor(20);
    ofDrawBitmapString( "world " + ofToString(world.x) + ", " + ofToString(world.y), mouseX, mouseY+20 );
#endif

}

void ofApp::mouseMoved( int x, int y, int button ){
    mode_manager.current_ui->mouseMoved( x, y, button );
}

void ofApp::mousePressed( int x, int y, int button ){
	mode_manager.current_ui->mousePressed( x, y, button );
}

void ofApp::mouseDragged( int x, int y, int button ){
	mode_manager.current_ui->mouseDragged( x, y, button );
}

void ofApp::mouseReleased( int x, int y, int button ){
	mode_manager.current_ui->mouseReleased( x, y, button );
}

void ofApp::gotMessage( ofMessage msg ){
	cout << msg.message << endl;
}

void ofApp::keyPressed( int key ){
	bool bShitt = ofGetModifierPressed( OF_KEY_SHIFT );
	bool bAlt = ofGetModifierPressed( OF_KEY_ALT );
	
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
            break;
            
		case OF_KEY_TAB:
            osc_recorder.toggle_play_fragment();
            break;
        
		case 'L':
            dt_config::DT_SHOW_LINER_DRAWER = !dt_config::DT_SHOW_LINER_DRAWER;
            break;
            
		case 'F':
            ofToggleFullscreen();
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

void ofApp::update_cocoa_ui(){
    // update Cocoa UI
    bool bToolbar_open = true;
    if( bToolbar_open ){
        AppDelegate *  d = (AppDelegate*)[NSApplication sharedApplication].delegate;
        if( d ) [d update_ui];
    }
}

void ofApp::backingScaleChanged( float newb, float oldb ){
	backingScale = newb;
	config.DT_SIZE_BASE *= newb / oldb;
}

