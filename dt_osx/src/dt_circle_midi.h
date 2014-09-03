//
//  dt_circle_midi.h
//  dialt_osx
//
//  Created by mtb on 2014/06/15.
//
//

#pragma once

#include "ofMain.h"
#include "dt_circle_output_base.h"
#include "dt_midi_sender.h"
#include "ofApp.h"

class dt_circle_midi : public dt_circle_output_base{
	
	
public:
	dt_circle_midi(){
		data.line_color.set( 0,0.1,0 );
		data.radius = 3;
		data.rev_radius = 15;
		data.bCollide = false;
		data.collision_radius = data.rev_radius + ofRandom( 10, 30 );
		
		setup();
		
		data.circle_type = DT_CIRCLE_MIDI;

		ch = (int)ceil(ofRandom(0, 12));
		initial = ofToString(ch);
		
	}
	
	virtual void setup( int beat=0 );
	virtual void draw();
	virtual void fire(){};
	virtual void step(){};
		
	void send_midi( int ch, int note, int vel, int dur, int pan, int cc1, int cc2, int cc3, int cc4 ){
		app->midi_sender.send_cc(1, 102, pan);
		app->midi_sender.send_cc(1, 103, cc1);
		app->midi_sender.send_cc(1, 104, cc2);
  		app->midi_sender.send_cc(1, 105, cc3);
  		app->midi_sender.send_cc(1, 106, cc4);
		app->midi_sender.send_note_on(1, note, vel, dur);
	}
};