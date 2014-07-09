//
//  dt_rhythm_lib.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

typedef vector<bool> RHYTHM_SHAPE;
typedef vector<RHYTHM_SHAPE> SLOT_SHAPE;
typedef vector<SLOT_SHAPE> SHAPE_TABLE;

class dt_rhythm_lib{

public:

	dt_rhythm_lib();
	~dt_rhythm_lib();
	
	SHAPE_TABLE shapes;
	int maxSlot;

	void setup(int start_slot, int end_slot);

	const RHYTHM_SHAPE& getRhythm(int slotNum, int type);
	int getRhythmSize(int slotNum);

};