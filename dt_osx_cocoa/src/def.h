//
//  def.h
//  dialt_osx
//
//  Created by mtb on 2014/07/01.
//
//

#pragma once

#include <iostream>
using namespace std;

#define NOT_USE_OF_CIRCLE 1
#define NOT_USE_OF_DRAW_TEXT 1

/*
 *	Rhythm
 */
static const int DT_RHYTHM_SHAPE_MIN_SLOT = 3;
static const int DT_RHYTHM_SHAPE_MAX_SLOT = 22;
static const int DT_QUANTIZE_RESOLUTION = 64;
static const int DT_BEAT_RESOLUTION = 64;		// hwo many steps per 1 beat

/*
 *	audio
 */
static const int DT_AUDIO_SAMPLING_RATE = 44100;
static const int DT_AUDIO_BUFFER_SIZE = 128;

/*
 *	Circle settings
 */
static const int DT_MAX_CIRCLE_NUM = 50000;
static const int DT_CONNECTION_NUM_INPUT_MAX = 10;
static const int DT_CONNECTION_NUM_OUTPUT_MAX = 1;

/*
 *	OSC
 */
static const int DT_MAX_OSC_CH = 24;
static const std::string DT_DEFAULT_OSC_ADDRESS = "localhost";
static const int DT_DEFAULT_OSC_PORT = 9999;
