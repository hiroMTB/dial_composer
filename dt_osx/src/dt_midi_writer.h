//
//  dt_midi_writer.h
//  dialt_osx
//
//  Created by mtb on 2014/06/16.
//
//

/*
 *	@param framesPerSecond      must be 24, 25, 29 or 30
 *	@param subframeResolution   the sub-second resolution, e.g. 4 (midi time code),
 *								8, 10, 80 (SMPTE bit resolution), or 100.
 *	setSmpteTimeFormat (25, 40)		:	1 = 1 msec
 *	setSmpteTimeFormat (30, 100)	:	1 = 0.333... msec
 *
 */

#pragma once

#include "ofMain.h"

#include "def.h"
#include "dt_controler.h"
#include "dt_config.h"
#include "AppConfig.h"
#include "modules/juce_core/juce_core.h"
#include "modules/juce_audio_basics/juce_audio_basics.h"

using namespace juce;

struct dt_trigger_event{
	
public:
	dt_trigger_event(int _time, int _ch, int _note, int _vel, int _dur, int _cc9, int _cc12, int _cc13, int _cc14, int _cc15)
	:time(_time), ch(_ch), note(_note), vel(_vel), dur(_dur), cc9(_cc9), cc12(_cc12), cc13(_cc13), cc14(_cc14), cc15(_cc15)
	{}
	
	int time, ch, note, vel, dur, cc9, cc12, cc13, cc14, cc15;
};


class dt_midi_writer{
	
public:
	
	vector<dt_trigger_event> events;
	
	int track_num;
		
	dt_midi_writer(){};
	
	void add_trigger_event(dt_trigger_event&e){
		events.push_back(e);
	}
	

	void save_midi_file(string file_name){
		MidiFile midi_file;
		midi_file.setTicksPerQuarterNote(960);	// max 32767, cubase default 1/16=480

		
		track_num = dt_config::DT_MAX_OSC_CH;
		MidiMessageSequence tracks;
	
		for(int i=0; i<events.size(); i++){
			dt_trigger_event & e = events[i];
			
			MidiMessage note_on =	MidiMessage::noteOn(e.ch, e.note, (uint8)e.vel);
			MidiMessage note_off =	MidiMessage::noteOff(e.ch, e.note);
			MidiMessage cc9  =		MidiMessage::controllerEvent(e.ch,  9, e.cc9);
			MidiMessage cc12 =		MidiMessage::controllerEvent(e.ch, 12, e.cc12);
			MidiMessage cc13 =		MidiMessage::controllerEvent(e.ch, 13, e.cc13);
			MidiMessage cc14 =		MidiMessage::controllerEvent(e.ch, 14, e.cc14);
			MidiMessage cc15 =		MidiMessage::controllerEvent(e.ch, 15, e.cc15);
		
			int time = e.time * 240;
			tracks.addEvent(note_on,	time);
			tracks.addEvent(note_off,	time + e.dur);
			tracks.addEvent(cc9,		time);
			tracks.addEvent(cc12,		time);
			tracks.addEvent(cc13,		time);
			tracks.addEvent(cc14,		time);
			tracks.addEvent(cc15,		time);
		}
		
		
		midi_file.addTrack(tracks);
		
		File file;
		file = File::createFileWithoutCheckingPath(ofToDataPath("midi_out/"+file_name, true));
		FileOutputStream stream(file);

		midi_file.writeTo(stream);
	}
	
};
