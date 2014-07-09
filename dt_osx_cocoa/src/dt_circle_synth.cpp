//
//  dt_circle_synth.mm
//  dialt
//
//  Created by mtb on 5/7/14.
//
//

#include "ofApp.h"

#include "dt_circle_synth.h"
#include "dt_dial_ui.h"
#include "ofxTonicSynth.h"
#include "dt_circle_drawer.h"

using namespace Tonic;

Mixer dt_circle_synth::mixer;

dt_circle_synth::dt_circle_synth(){
	data.line_color.set(0.5);
	data.radius = 3;
	data.rev_radius = 10;
	data.bCollide = false;
	data.collision_radius = data.rev_radius + ofRandom(10, 30);
	initial = "syn";
	data.circle_type = DT_CIRCLE_SYNTH;
	setup();
}


void dt_circle_synth::setup(int fake){
	make_vbo();
	
	mixer.addInput(this->oftSynth);

	// synth setup
	ui = new dt_dial_ui(this);
	
	base_freq = ceil(ofRandom(0, 10)) * 40;
	
	// Control parameter
	ControlGenerator noteFreq	= oftSynth.addParameter("freq");
	ControlGenerator cc12 = oftSynth.addParameter("cc12");
	ControlGenerator cc13 = oftSynth.addParameter("cc13");
	ControlGenerator cc14 = oftSynth.addParameter("cc14");
	ControlGenerator env = oftSynth.addParameter("trigger");
	ControlGenerator dur = (oftSynth.addParameter("duration"));
	ControlGenerator vel = oftSynth.addParameter("velocity");
	ControlGenerator pan = oftSynth.addParameter("pan");

	// Original oscilator
	float r = ofRandom(1);
	Generator tone;
	if(r<0.25){
		 tone = SawtoothWave().freq( noteFreq );
	}else if(r<0.5){
		tone = SineWave().freq( noteFreq );
	}else if(r<0.75){
		tone = Noise();
	}else{
		tone = RectWave().freq( noteFreq );
	}

	// signal line

	// filter
	tone = LPF12().input(tone).Q(cc13).cutoff((noteFreq*3+ SineWave().freq(ofRandom(1,4)) * noteFreq * cc14));
	
	// envelope
	tone = tone * ADSR().attack(0.0001).decay(dur).sustain(dur*0.01).release(dur*0.01).trigger(env).legato(true);
	
	// delay
	tone = StereoDelay(ofRandom(0.01, 0.2), ofRandom(0.01, 0.2)).input(tone).wetLevel(cc12).feedback(0.3);

//	ControlGenerator reverb = oftSynth.addParameter("reverb");
//	tone = Reverb().input(tone).preDelayTime(0.05).roomShape(10).roomSize(10).stereoWidth(1).density(1).wetLevel(delay);
	
	// pan
	tone = MonoToStereoPanner().input(tone).pan(pan);

	// velocity
	tone = tone * vel;
	
	oftSynth.setOutputGen( tone);

}


void dt_circle_synth::update(){
	make_vbo();
	data.position += data.move_speed;
}

void dt_circle_synth::draw(){
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(data.position.x, data.position.y);
	
	ofSetColor(data.circle_color);
	ofSetLineWidth(1);
	glPointSize(1);
	ofNoFill();
#ifndef NOT_USE_OF_CIRCLE
	ofCircle(0, 0, data.rev_radius);
#else
	app->circle_drawer.draw(data.rev_radius);
#endif
	
	// vbo cloud
	glPointSize(1);
	ofSetColor(data.line_color);
	vbo.bind();
	vbo.updateVertexData(shape_points, vertex_num);
	vbo.draw(GL_POINTS, 0, vertex_num);
	vbo.unbind();
		
	ofPopMatrix();
	ofPopStyle();
}




void dt_circle_synth::make_vbo(){
	
	vertex_num = 0;
	float rate = data.rev_radius*0.4;
	float offset = data.rev_radius + 3;
	vertex_num = vertex_num_max-ofRandom(0, vertex_num_max*0.3);

	for(int i=0; i<vertex_num; i++){
		float r = offset + ofRandom(0,1) * rate;
		float deg = ofRandom(-TWO_PI, TWO_PI);
		shape_points[i].x = r * cos(deg);
		shape_points[i].y = r * sin(deg);
	}
	
	vbo.setVertexData(shape_points, vertex_num, GL_DYNAMIC_DRAW);
	
}


void dt_circle_synth::make_note(float noteNum, float velocity, float duration, float pan, float cc12, float cc13, float cc14){
	oftSynth.setParameter("freq", noteNum * base_freq);
	oftSynth.setParameter("duration", duration);
	oftSynth.setParameter("velocity", velocity);
	oftSynth.setParameter("pan", pan);
	oftSynth.setParameter("cc12", cc12);
	oftSynth.setParameter("cc13", cc13);
	oftSynth.setParameter("cc14", cc14);
	oftSynth.setParameter("trigger", 1);
}


#include "dt_circle_all_containers.h"
#include "dt_circle_container.h"
void dt_circle_synth::note_off_all_synth(){
	
	dt_circle_output_container *c = ofApp::getInstance()->all_containers.output_container;
	for(int i=0; i<c->circles.size(); i++){
		
		dt_circle_output_base * o = c->circles[i];
		if(o->data.circle_type == DT_CIRCLE_SYNTH){
			static_cast<dt_circle_synth*>(o)->make_note(0, 0, 0, 0, 0, 0, 0);
		}
	}
}
