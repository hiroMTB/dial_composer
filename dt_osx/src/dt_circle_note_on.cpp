//
//  dt_circle_note_on.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//
#include "dt_circle_note_on.h"
#include "ofMain.h"
#include "ofApp.h"
#include "dt_rhythm_lib.h"
#include "dt_sequence_thread.h"
#include "dt_font_manager.h"
#include "dt_circle_container.h"
#include "dt_circle_param.h"
#include "dt_circle_drawer.h"
#include "dt_dial_ui.h"

dt_param_state::dt_param_state(){
    reset();
}

void dt_param_state::reset(){
    bNote = bVel = bDur = bPan = bCc1 = bCc2 = bCc3 = bCc4 = false;
    note = vel = dur = pan = cc1 = cc2 = cc3 = cc4 = 0.0;
}

dt_circle_note_on::dt_circle_note_on(){
	data.circle_type = DT_CIRCLE_NOTE_ON;

	ui = new dt_dial_ui( this );

	data.circle_color.setHsb( ofRandom( 0.0, 1.0 ), ofRandom(0.6, 0.8), 0.8 );
}

dt_circle_note_on::~dt_circle_note_on(){
	if( ui ) {
		delete ui;
		ui = 0;
	}
    
    rguid.clear();
    rshape.clear();
}

/*
		speed affet to 
            ...
 
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
void dt_circle_note_on::setup( int beat_num ){

	seq = new dt_sequencer();

	set_beats( beat_num );
	set_speed( 1 );

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

}

void dt_circle_note_on::set_beats( int beat_num ){
	seq->setup( beat_num );
	data.rev_speed = (float)360.0 / (float)seq->total_steps;
	change_rshape( ofRandom(-1000, 1000) );
	set_speed( data.speed );
}

void dt_circle_note_on::set_speed( int speed ){
	data.speed = speed;
	data.rev_angle = seq->indicator * data.rev_speed;
}

void dt_circle_note_on::update(){
	data.fire_rate*=0.8;

    ofApp * app = ofApp::getInstance();
    
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
        case DT_MODE_ZOOM2HOME:
            if( app->mode_manager.zoom_mode_target != this){
                data.bShow = false;
            }
        default:
            break;
    }
    
	if( data.bShow ){
        data.indi_position = calc_indi_position();
    }else{
        data.indi_position = data.position;
    }
    
	ofApp::getInstance()->all_containers.add_indicator( data.indi_position, data.circle_color );
	
    // size update
    data.rev_radius = dt_config::DT_SIZE_BASE * 0.5;
	data.collision_radius = data.rev_radius * 1.5;
	data.input_connection_radius = data.collision_radius + 100;
	data.output_connection_radius = data.collision_radius + 100;
}

void dt_circle_note_on::check_connection(){
	
	//input_circles.clear();
	//output_circles.clear();
	
	//	input check
	//ofApp::getInstance()->all_containers.param_container->check_connection( this, true );
	
	// output check
	//ofApp::getInstance()->all_containers.output_container->check_connection( this, false );
}

/*
 *      mode
 *      fired
 *      selected
 */
void dt_circle_note_on::draw(){
    
    if( data.bShow == false ){
        return;
    }
    
	bool fired = data.fire_rate > 0.3;
	bool selected = selected_circle == this;
  	
	float waiting_rate = (float)(dt_config::DT_BEAT_RESOLUTION-wait_step) / (float)dt_config::DT_BEAT_RESOLUTION;
	float waiting_animation_rate = 0.5 + waiting_rate*0.5;
    float scale = fired ? waiting_animation_rate+data.fire_rate*0.2 : waiting_animation_rate;
	
    ofPushMatrix();{
        ofTranslate( data.position.x, data.position.y );
        ofScale( scale, scale );
	
        // circle
        {
            if( selected ){
                glPointSize( 4 );
                ofSetColor( data.circle_color );
            }else{
                glPointSize( 2 );
                float b = app->bg.getBrightness() * 255.0;
                ofSetColor( 255.0-b, 220 );
            }
            app->circle_drawer.draw( data.rev_radius * 1.26, OF_MESH_POINTS );
        }
        
        // shape
        {
            ofPushMatrix();{
                float shape_scale = data.rev_radius * 0.01;
                ofScale( shape_scale, shape_scale, 1 );

                // guid
                glPointSize( 3 );
                rguid.draw( OF_MESH_POINTS );
                
                // shape
                ofPushMatrix();{
                    ofScale( 0.8, 0.8, 1 );
                    glLineWidth( 3 );
                    if (rshape.getNumVertices() <= 2){
                        rshape.draw( OF_MESH_WIREFRAME );
                    }else{
                        rshape.draw( OF_MESH_FILL );
                    }
                }ofPopMatrix();
        
            }ofPopMatrix();
        }
        
        if( data.bShowUI )
            ui->draw();
            
    }ofPopMatrix();
}

void dt_circle_note_on::change_rshape( int type ){
	seq->setRhythmShape( type );
	make_vbo();
}

void dt_circle_note_on::fire(){
	
    ofxOscMessage m;
    m.setAddress( "1" );
    m.addIntArg( 255 );
    app->osc_sender.send_message( m );

    data.fire_rate = 1.0;
}

void dt_circle_note_on::make_vbo(){

    rguid.clear();
    rshape.clear();
    
	int beat_num = seq->total_beats;
	float start_angle = 0;
    float h = data.circle_color.getHue();
    float s = data.circle_color.getSaturation();
    float b = data.circle_color.getBrightness();
    
    int vertIndex = 0;
    
	for( int i=0; i<beat_num; i++ ){
        bool on = seq->getDataFromBeat( i );
        float angle = start_angle + ( i * data.rev_speed * dt_config::DT_BEAT_RESOLUTION );
        float cos = cosf( angle*DEG_TO_RAD );
        float sin = sinf( angle*DEG_TO_RAD );
        float r = 100.0;
        float x = r * cos;
        float y = r * sin;
		if( on ){
            ofFloatColor c = data.circle_color;
            c.setHsb( h + i*0.005, MAX( 0.6,s+ofRandom(-0.05, 0.05) ), 0.8 );
            rshape.addVertex( ofVec3f(x, y, 0) );
            rshape.addIndex( vertIndex++ );
            rshape.addColor( c );
		}
    
        // guide shape
        rguid.addVertex( ofVec3f(x, y, 0) );
        rguid.addIndex( i );
        if( on ){
            rguid.addColor( data.circle_color );
        }else{
            rguid.addColor( ofFloatColor(0.4, 1) );
            
        }
	}
    
    // setup Mode and Usage
    if( vertIndex <=2 ){
        rshape.setMode(OF_PRIMITIVE_LINES );
    }else{
        rshape.setMode( OF_PRIMITIVE_TRIANGLE_FAN );
    }
    rguid.setMode( OF_PRIMITIVE_POINTS);
    
    rshape.setUsage( GL_DYNAMIC_DRAW );
    rguid.setUsage( GL_DYNAMIC_DRAW );

}
