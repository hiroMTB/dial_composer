#pragma once

struct MidiMsg{
    
public:
    MidiMsg();
    
    int ch;
    int noteNum;
    int vel;
    int dur;
    int pan;
    int cc1, cc2, cc3, cc4;
    
};

class dt_midi_send_pool{
    
public:
    dt_midi_send_pool();
    vector<MidiMsg> msgs;
    
    void add();
    
    void update(){
        for(int i=0; i<msgs.size(); i++){
            MidiMsg & m = msgs[i];
            // midiSernder.send();
        }        
    }
    
};
