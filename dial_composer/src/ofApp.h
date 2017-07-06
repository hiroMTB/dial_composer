#pragma once

#include "ofMain.h"
#include "def.h"
#include "dt_midi_writer.h"
#include "dt_osc_sender.h"
#include "dt_midi_sender.h"
#include "dt_font_manager.h"
#include "dt_rhythm_lib.h"
#include "dt_linear_drawer.h"
#include "dt_sequence_thread.h"
#include "dt_circle_all_containers.h"
#include "dt_config.h"
#include "dt_osc_recorder.h"
#include "dt_mode_manager.h"
#include "ofx2DCamera.h"
#include "dt_serialize.h"
#include "ofxCereal.h"

class ofApp : public ofBaseApp {

private:
	ofApp();
	
public:
	static ofApp * app;
	static ofApp * init();
	
	void setup();	
	void update();
	void draw();
	void draw_info( int x, int y );
	void keyPressed( int key );
	void keyReleased( int key ){};
    void mouseMoved( int x, int y, int button );
	void mousePressed( int x, int y, int button );
	void mouseDragged( int x, int y, int button );
	void mouseReleased( int x, int y, int button );
	void mouseMoved( int x, int y );
	void windowResized( int w, int h );
	void dragEvent( ofDragInfo dragInfo ){};
	void gotMessage( ofMessage msg );
	void exit();
    void update_cocoa_ui();
	void backingScaleChanged( float newb, float oldb );
    void save(string fileName);
    
    ofFloatColor bg;
    ofImage noise;
    ofVboMesh bgQuad;
    
	dt_osc_sender		osc_sender;
	dt_midi_sender		midi_sender;
	dt_midi_writer		midi_writer;
	dt_font_manager		font_manager;
	dt_rhythm_lib		rhythm_lib;
	//dt_linear_drawer	linear_drawer;
	dt_sequence_thread	sequence_thread;
	dt_config			config;
	dt_osc_recorder		osc_recorder;
	dt_circle_all_containers all_containers;
	dt_mode_manager		mode_manager;

    ofx2DCamera         cam;
	float backingScale;
    dt_serialize serializer;
    
    OFX_CEREAL_DEFINE(all_containers);
};

