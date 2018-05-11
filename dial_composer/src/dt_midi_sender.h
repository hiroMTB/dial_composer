//
//  dt_midi_sender.h
//  dialt_osx
//
//  Created by mtb on 2014/06/15.
//
//

#pragma once

#include "ofxMidi.h"

class dt_midi_sender{
	
public:
	dt_midi_sender(){}
	
	~dt_midi_sender(){
		midi_out.closePort();
	}
    
	void open_port( string port_name ){
		midi_out.openVirtualPort( port_name );
	}

	void send_note_on( int ch, int noteNum, int vel, int dur_micro_sec ){
		midi_out.sendNoteOn( ch, noteNum, vel );
		if( dur_micro_sec>0 ){
            std::thread noteOffThread( &dt_midi_sender::send_note_off, this, ch, noteNum, dur_micro_sec );
            noteOffThread.detach();
		}
	}
	
	void send_cc( int ch, int cc, int value ){
		midi_out.sendControlChange( ch, cc, value );
	}
	
	void send_note_off( int ch, int noteNum, int after_micro_sec ){
        
        if(after_micro_sec>0)
            std::this_thread::sleep_for( chrono::microseconds(after_micro_sec) );
        
        vector<unsigned char> noteOff;
        noteOff.push_back(MIDI_NOTE_OFF+(ch));
        noteOff.push_back(noteNum);
        noteOff.push_back(0);
        if(midi_out.isOpen()){
            ofPtr<ofxBaseMidiOut> ofOut = midi_out.midiOut;
            ofxRtMidiOut * rtOut = static_cast<ofxRtMidiOut*>(ofOut.get());
            rtOut->midiOut.sendMessage(&noteOff);
        }
	}

    ofxMidiOut & getMidiOut(){ return midi_out; }
    
private:
	ofxMidiOut midi_out;

};
