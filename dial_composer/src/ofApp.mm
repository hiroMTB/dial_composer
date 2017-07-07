#include "ofApp.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_container.h"
#include "dt_circle_param.h"
#include "ofxModifierKeys.h"
#include <cereal/archives/json.hpp>

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
	ofSetCircleResolution( 60 );
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableSmoothing();
    ofDisableArbTex();
    noise.load("img/noise2.png");
    noise.getTexture().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
	bg.set( 0.8f );
//    bgQuad.addVertex(ofVec3f(0,0,0));
//    bgQuad.addTexCoord(ofVec2f(0,0));
//    bgQuad.addVertex(ofVec3f(ofGetWidth(),0,0));
//    bgQuad.addTexCoord(ofVec3f(ofGetWidth(),0));
//    bgQuad.addVertex(ofVec3f(ofGetWidth(),ofGetHeight(),0));
//    bgQuad.addTexCoord(ofVec2f(ofGetWidth(),ofGetHeight()));
//    bgQuad.addVertex(ofVec3f(0,ofGetHeight(),0));
//    bgQuad.addTexCoord(ofVec2f(0,ofGetHeight()));
//    bgQuad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
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
    midi_sender.open_port( dt_config::DT_MIDI_OUT_PORT_NAME );
}

void ofApp::update(){
    mode_manager.update();
    cam.update();
	config.update();
	all_containers.update();
    
    [[[NSApplication sharedApplication] delegate] update_ui_every_frame];
}

void ofApp::draw(){
    ofBackground( bg );
    ofSetColor( 255 );

//    noise.getTexture().bind();
//    bgQuad.draw();
//    noise.getTexture().unbind();
    
    cam.begin(); {
        all_containers.draw();
        //cam.debugDraw();
    } cam.end();

  	osc_recorder.draw( 5, ofGetHeight()-70, ofGetWidth()-10, 64 );
    //if( dt_config::DT_SHOW_LINER_DRAWER) linear_drawer.draw( 30, 300, 30, 500, 1 );
    
//#ifdef DEBUG
	mode_manager.debug_draw();
    
    mouseX = ofGetMouseX();
    mouseY = ofGetMouseY();
    ofVec2f world = cam.screenToWorld( ofVec2f(mouseX, mouseY) );
    ofSetColor(20);
    ofDrawBitmapString( "world " + ofToString(world.x) + ", " + ofToString(world.y), mouseX, mouseY+20 );
//#endif

}

void ofApp::mouseMoved( int x, int y){
    mode_manager.current_ui->mouseMoved( x, y );
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
	bool bShift = ofGetModifierPressed( OF_KEY_SHIFT );
	bool bAlt = ofGetModifierPressed( OF_KEY_ALT );
	
    shared_ptr<dt_circle_base> sel = dt_circle_base::selected_circle;
	switch(key){
			
		case OF_KEY_UP:
            if( sel ){
                int inc = bShift ? 10 : 1;
                sel->change_shape( sel->seq->rhythm_shape_type + inc );
            }
			break;
			
		case OF_KEY_DOWN:
            if( sel ){
                int dec = bShift ? 10 : 1;
                sel->change_shape( sel->seq->rhythm_shape_type - dec );
            }
            break;

        case OF_KEY_RIGHT:
            if( sel ){
                int rot = bShift ? dt_config::DT_BEAT_RESOLUTION/2 : 1;
                sel->change_rotation( sel->data.phase_step + rot );
            }
            break;
            
        case OF_KEY_LEFT:
            if( sel ){
                int rot = bShift ? dt_config::DT_BEAT_RESOLUTION/2 : 1;
                sel->change_rotation( sel->data.phase_step - rot );
            }
            break;
            
        // view_mode
 		case OF_KEY_RETURN:
            mode_manager.toggle_mode();
            break;
			
		// play
		case ' ':
            dt_config::DT_PLAY_GEN_RHYTHM = !dt_config::DT_PLAY_GEN_RHYTHM;
            break;
            
		case 'm':
            if( sel ){
                sel->data.bMute = !sel->data.bMute;
            }
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

        case 'S':
            save("save2.json");
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
	//config.DT_SIZE_BASE *= newb / oldb;
}

#include <iostream>

void ofApp::save(string fileName){

    std::stringstream ss;

    {
        cereal::JSONOutputArchive archive(ss);
        archive(all_containers);
    }
    
    ofstream myfile(fileName);
    myfile << ss.str() << endl;
}
