//
//  dt_circle_note_on.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//
#include "ofApp.h"
#include "dt_circle_note_on.h"
#include "dt_rhythm_lib.h"
#include "dt_sequence_thread.h"
#include "dt_font_manager.h"
#include "dt_circle_container.h"
#include "dt_circle_param.h"
#include "dt_circle_drawer.h"
#include "dt_dial_ui.h"

dt_circle_drawer dt_circle_note_on::circle_drawer;

dt_circle_note_on::dt_circle_note_on(){
	data.circle_type = DT_CIRCLE_NOTE_ON;

//	ui = new dt_dial_ui( this );

    data.circle_color.setHsb( ofRandom( 0.0, 1.0 ), ofRandom(0.6, 0.8), 0.8 );
//    data.circle_color.set( 0.7 );
    
    if( !circle_drawer.bInitialized ){
        circle_drawer.initialize( 60 );
    }
    
    for( int i=0; i<8; i++ ){
        pair<dt_circle_type, float> p( (dt_circle_type)(i+1), 0.0 );
        prms.insert( p );
    }
}

dt_circle_note_on::~dt_circle_note_on(){
	if( ui ) {
		delete ui;
		ui = 0;
	}
    
    rguid.clear();
    rshape.clear();
}

void dt_circle_note_on::setup( int beat_num ){
    /*
     speed affet to
     - rev_angle
     
     beat_num affect to
     - seq
     - rev_speed
     - vbo
     
     fixed parameter
     - indicator radius (vboMesh)
     - rev_radius
     - collision_radius
     - input/output_connection_radius
     
     */
	seq = new dt_sequencer();
	change_beat( beat_num );
	change_speed( 1 );
    change_shape( ofRandom(-3000, 3000) );
    
	// Quantize to beat position
	//int steps_per_beat = DT_BEAT_RESOLUTION; //* data.speed;
	//int sub_step = app->sequence_thread.master_step % steps_per_beat;
	//wait_step = steps_per_beat - sub_step;
		
	wait_step = 0;
	// ROTATE little bit
	int quantize_step = 1; //dt_config::DT_BEAT_RESOLUTION / dt_config::DT_QUANTIZE_RESOLUTION;
	int rotate_step =  quantize_step * (int)round( ofRandom(0, dt_config::DT_BEAT_RESOLUTION-1) );
	seq->indicator = rotate_step;
    
    // input
    input_circles.clear();
    for( int i=0; i<8; i++){
        dt_circle_param * p = new dt_circle_param();
        p->setup( ofRandom(4, 12) );
        p->change_param_type( (dt_circle_type)(i+1) );
        p->change_shape( ofRandom(10, 100) );
        float r = app->config.DT_SIZE_BASE * 1.8;
        float rad = (-180.0+(float)i*30.0) * DEG_TO_RAD;
        float x = r * cos( rad );
        float y = r * sin( rad );
        p->data.position.set( x,y );
        p->parent = this;
        
        input_circles.push_back( p );
        app->all_containers.param_container->addCircle( p );
        app->all_containers.circle_base_container->addCircle( p );
    }
}

void dt_circle_note_on::update(){

    ofApp * app = ofApp::app;
    
    // mode switching
    dt_mode mode = app->mode_manager.mode;
    switch ( mode ) {
        case DT_MODE_HOME:
            data.bShow = true;
            break;
            
        case DT_MODE_HOME2ZOOM:
            data.bShow = true;
            break;
            
        case DT_MODE_ZOOM:
            if( app->mode_manager.zoom_mode_target != this){
                data.bShow = false;
            }
            break;
        case DT_MODE_ZOOM2HOME:
            if( app->mode_manager.zoom_mode_target != this){
                data.bShow = true;
            }
            break;
        default:
            break;
    }
    
	if( data.bShow ){
        data.indi_position = calc_indi_position();
        ofApp::app->all_containers.add_indicator( data.indi_position, data.circle_color );
    }
	
    // size update
    data.rev_radius = dt_config::DT_SIZE_BASE * 0.5;
	data.collision_radius = data.rev_radius * 1.5;
	data.input_connection_radius = data.collision_radius + 100;
	data.output_connection_radius = data.collision_radius + 100;
    
    // param animation
    data.note *= 0.9;
    data.pan *= 0.9;
    data.vel *= 0.99;
    data.dur *= 0.9;
    data.fire_rate *=0.93;
}

void dt_circle_note_on::check_connection(){
	
	//input_circles.clear();
	//output_circles.clear();
	
	//	input check
	//ofApp::app->all_containers.param_container->check_connection( this, true );
	
	// output check
	//ofApp::app->all_containers.output_container->check_connection( this, false );
}

void dt_circle_note_on::draw(){
    
    /*
     *      mode ( home, zoom )
     *      fired ( on, off )
     *      selected (on , off )
     *      mute ( on, off )
     */
    
    if( data.bShow == false ){
        return;
    }
    
	bool blink = data.fire_rate > 0.3;
	bool selected = selected_circle == this;
    bool targeted = app->mode_manager.zoom_mode_target == this;
    float scale = blink ? 1.0+data.fire_rate*0.05 : 1.0;
    
    ofPushMatrix();{
        ofTranslate( data.position.x, data.position.y );
        ofPushMatrix();{
			float angle = data.phase_step*data.rev_speed;
			ofRotateZ( angle );
            ofScale( scale, scale );
	
            // circle
            if( selected ){
                glPointSize( 4 );
                ofSetColor( data.circle_color );
            }else{
                glPointSize( 2 );
                float b = app->bg.getBrightness() * 255.0;
                ofSetColor( 255.0-b, 220 );
            }
            circle_drawer.draw( data.rev_radius * 1.26, OF_MESH_POINTS );
            
            // shape & guide
            ofPushMatrix();{
                float shape_scale = data.rev_radius * 0.01;
                ofScale( shape_scale, shape_scale, 1 );

                // guid
                glPointSize( 3 );
                rguid.draw( OF_MESH_POINTS );
                
                // shape
                ofPushMatrix();{
                    ofScale( 0.8, 0.8, 1 );
                    glLineWidth( 2 );
                    if (rshape.getNumVertices() <= 2){
                        rshape.draw( OF_MESH_WIREFRAME );
                    }else{
                        if( !data.bMute ){
                            rshape.setMode( OF_PRIMITIVE_TRIANGLE_FAN );
                            rshape.draw( OF_MESH_FILL );
                        }else{
                            rshape.setMode( OF_PRIMITIVE_LINE_LOOP );
                            rshape.draw( OF_MESH_WIREFRAME );
                        }
                    }
                }ofPopMatrix();
            }ofPopMatrix();
        
            // param animation
            {
                ofFloatColor c = data.circle_color;
                c.setBrightness( c.getBrightness()*1.5 );
                ofSetColor( c );
                ofSetLineWidth( 1.0+data.vel*5.0 );
                ofLine( 0, 0, data.pan, data.note );
                ofCircle( data.pan, data.note, 1.0+data.vel*5.0 );
            }
        }ofPopMatrix();
    }ofPopMatrix();
}

void dt_circle_note_on::on_process(){
    ofxOscMessage m;
    m.setAddress( "/" + ofToString(data.ch) );
    
    for( int i=0; i<8; i++ ){
        dt_circle_type type = ( dt_circle_type )( i+1 );
        float v = prms[type];
        m.addFloatArg( v );
    }
    
    app->osc_sender.send_message( m );
    app->osc_recorder.add_osc_message( m, data.ch );
    
	data.pan = (prms[DT_CIRCLE_PAN]-64.0)/127.0 * data.rev_radius;
    data.note = (prms[DT_CIRCLE_NOTE_NUM]-64.0)/127.0 * data.rev_radius;
    data.vel = prms[DT_CIRCLE_VELOCITY]/127.0;
    data.dur = prms[DT_CIRCLE_DURATION]/127.0;
    data.fire_rate = 1.0;
}
