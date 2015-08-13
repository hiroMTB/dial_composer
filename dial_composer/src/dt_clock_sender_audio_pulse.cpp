#include "dt_clock_sender_audio_pulse.h"
#include "def.h"
#include "ofApp.h"

dt_clock_sender_audio_pulse::dt_clock_sender_audio_pulse()
:
pulsePerBeat( 4 ),
pulse_pos( 0.0f )
{
    sampling_rate = 44100;
    buffer_size = 512;
    app = ofApp::app;
}

void dt_clock_sender_audio_pulse::change_bpm( int bpm ){
    
    samplePerBeat = sampling_rate / (float) bpm;      //  44100/120 = 367.5
    pulse_width = samplePerBeat / (float)pulsePerBeat / 2.0f;
    
}

void dt_clock_sender_audio_pulse::audioRequested( float * output, int bufferSize, int nChannels ){
    
    for( int i=0; i<buffer_size; i++ ){
     
        pulse_pos = fmod( pulse_pos, samplePerBeat );
        
        bool on = (int)(pulse_pos / pulse_width) % 2 == 0;
        
        for( int ch=0; ch<nChannels; ch++ ){
            output[i*nChannels + ch] = on ? 0.8 : 0;
        }
        
        pulse_pos++;
    }
}

/*
 *      Call this func from sequencer for better synch
 */
void dt_clock_sender_audio_pulse::resetBeat(){
    pulse_pos = 0;
}



/*
                                        1 beat = samplePerBeat
                <----------------------------------------------------------------->
 

    1            _______         _______         _______         _______
                |       |       |       |       |       |       |       |
                |       |       |       |       |       |       |       |
    0           |       |_______|       |_______|       |_______|       |_________.....
 
 
*/