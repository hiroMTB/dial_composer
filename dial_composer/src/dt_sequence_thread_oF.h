//
//  dt_sequence_thread_oF.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "ofMain.h"
#include "dt_sequence_thread_base.h"

class dt_sequence_thread_oF : public dt_sequence_thread_base, public ofThread{

public:
	
	dt_sequence_thread_oF();
	virtual void threadedFunction() override;
    virtual void setup() override;
    virtual void start() override;
	virtual void stop() override;

};
