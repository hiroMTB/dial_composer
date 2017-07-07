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


dt_circle_drawer dt_circle_note_on::bg_circle_drawer;

dt_circle_note_on::dt_circle_note_on(){
	data.circle_type = DT_CIRCLE_NOTE_ON;
    
    if( !bg_circle_drawer.bInitialized ){
        bg_circle_drawer.initialize( 60 );
    }
    
    for( int i=0; i<8; i++ ){
        pair<dt_circle_type, float> p( (dt_circle_type)(i+1), 0.0 );
        prms.insert( p );
    }
    
    data.output_value = 1;
}

dt_circle_note_on::~dt_circle_note_on(){
	if( ui ) {
		delete ui;
		ui = 0;
	}
    
    rguid.clear();
    rshape.clear();
    
    cout << "note on ---- ";
}

void dt_circle_note_on::setup( int beat_num ){
    /*
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
    change_type( DT_CIRCLE_NOTE_ON );
    
	// Quantize to beat position
	int steps_per_beat = dt_config::DT_BEAT_RESOLUTION; //* data.speed;
	int sub_step = app->sequence_thread.master_step % steps_per_beat;
	wait_step = steps_per_beat - sub_step;
		
//	wait_step = 0;
	// ROTATE little bit
	int quantize_step = 1; //dt_config::DT_BEAT_RESOLUTION / dt_config::DT_QUANTIZE_RESOLUTION;
	int rotate_step =  quantize_step * (int)round( ofRandom(0, dt_config::DT_BEAT_RESOLUTION-1) );
	seq->indicator = rotate_step;
    
    // input
    input_circles.clear();
    for( int j=0; j<2; j++){

        for( int i=0; i<8; i++){
            shared_ptr<dt_circle_param> p(new dt_circle_param());
            p->setup( ofRandom(4, 12) );
            p->parent = shared_from_this();
            p->change_type( (dt_circle_type)(i+1) );
            p->change_shape( ofRandom(10, 100) );

            if(1){
                //circle layout
                float r = dt_config::DT_SIZE_BASE*1.6 + j*dt_config::DT_SIZE_BASE*0.6;
                float rad = (-180.0+(float)i*30.0) * DEG_TO_RAD;
                float x = r * cos( rad );
                float y = r * sin( rad );
                p->data.position.set( x, y );
            }else{
                float w = dt_config::DT_SIZE_BASE*0.6 + p->data.rev_radius;
                float h =dt_config::DT_SIZE_BASE*0.6 + p->data.rev_radius;
                float x = w * (i-3) - w/2;
                float y = h * (j+2) - h/3;
                p->data.position.set( x, -y );
            }
            
            input_circles.push_back( p );
            app->all_containers.param_container.addCircle( p );
            app->all_containers.circle_base_container.addCircle( p );
        }
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
            data.bShow = app->mode_manager.zoom_mode_target == shared_from_this();
            break;
            
        case DT_MODE_ZOOM2HOME:
            data.bShow = true;
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
    data.note *= 0.95;
    data.pan *= 0.95;
    data.vel *= 0.95;
    data.dur *= 0.95;
    data.fire_rate *=0.95;
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
	bool selected = selected_circle == shared_from_this();
    bool targeted = app->mode_manager.zoom_mode_target == shared_from_this();
    float scale = blink ? 1.0+data.fire_rate*0.05 : 1.0;
    
    ofPushMatrix();{
        ofTranslate( data.position.x, data.position.y );
        ofPushMatrix();{
            
			float angle = -data.phase_step*data.rev_speed;
			ofRotateZ( angle );
            ofScale( scale, scale );
	
            // circle
            if( selected ){
                glPointSize( 4 );
                ofSetColor( data.circle_color );

                ofNoFill();
                ofSetLineWidth( 1 );
                ofSetRectMode( OF_RECTMODE_CENTER );
                ofRect( 0, 0, data.rev_radius*3.1, data.rev_radius*3.1 );
                ofSetRectMode( OF_RECTMODE_CORNER );
                
            }else{
                glPointSize( 2 );
                float b = app->bg.getBrightness() * 255.0;
                ofSetColor( 255.0-b, 220 );
            }

            bg_circle_drawer.draw( data.rev_radius * 1.26, OF_MESH_POINTS );
            
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
                c.setBrightness( c.getBrightness()*2.0 );
                c.setSaturation( 0.3 );
                ofSetColor( c );
                ofSetLineWidth( 1.0+data.vel*5.0 );
                ofLine( 0, 0, data.pan, data.note );
                ofCircle( data.pan, data.note, 1.0+data.vel*14.0 );
            }
        }ofPopMatrix();
    }ofPopMatrix();
}

void dt_circle_note_on::on_process(){
    if(dt_config::DT_OSC_OUT_ENABLE){
        
        ofxOscMessage m;
        m.setAddress( dt_config::DT_OSC_OUT_TOP_ADDRESS + data.address );
        m.addIntArg( data.output_value );

        if( dt_config::DT_OSC_OUT_PACK_RHYTHM_PARAM ){
            // here we do packing and send
            
            for( int i=0; i<8; i++ ){
                dt_circle_type type = ( dt_circle_type )( i+1 );
                float v = prms[type];
                m.addFloatArg( v );
            }
        }

        // send osc
        app->osc_sender.send_message( m );
        app->osc_recorder.add_osc_message( m, 1 );
    }
    
    // send midi
    if( dt_config::DT_MIDI_OUT_ENABLE ){
        if( dt_config::DT_MIDI_OUT_PACK_RHYTHM_PARAM ){
            app->midi_sender.send_cc( data.midi_ch, CCs[DT_CIRCLE_PAN], prms[DT_CIRCLE_PAN] );
            app->midi_sender.send_cc( data.midi_ch, CCs[DT_CIRCLE_CC1], prms[DT_CIRCLE_CC1] );
            app->midi_sender.send_cc( data.midi_ch, CCs[DT_CIRCLE_CC2], prms[DT_CIRCLE_CC2] );
            app->midi_sender.send_cc( data.midi_ch, CCs[DT_CIRCLE_CC3], prms[DT_CIRCLE_CC3] );
            app->midi_sender.send_cc( data.midi_ch, CCs[DT_CIRCLE_CC4], prms[DT_CIRCLE_CC4] );
        }
        app->midi_sender.send_note_on( data.midi_ch, prms[DT_CIRCLE_NOTE_NUM], prms[DT_CIRCLE_VELOCITY], prms[DT_CIRCLE_DURATION]*1000 );
    }
    
    // update for animation
    data.pan = (prms[DT_CIRCLE_PAN]-64.0)/127.0 * data.rev_radius;
    data.note = (prms[DT_CIRCLE_NOTE_NUM]-64.0)/127.0 * data.rev_radius;
    data.vel = prms[DT_CIRCLE_VELOCITY]/127.0;
    data.dur = prms[DT_CIRCLE_DURATION]/127.0;
    data.fire_rate = 1.0;
}

