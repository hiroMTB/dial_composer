//
//  dt_sequence_thread.h
//  dialt
//
//  Created by mtb on 2014/06/08.
//
//

#pragma once

//#define USE_AUDIO_THREAD

#ifndef USE_AUDIO_THREAD
	#define USE_BOOST_THREAD

	#ifdef USE_BOOST_THREAD
		#include "dt_sequence_thread_boost.h"
		#define dt_sequence_thread dt_sequence_thread_boost
	#else
		#include "dt_sequence_thread_oF.h"
		#define dt_sequence_thread dt_sequence_thread_oF
	#endif
#else
	#include "dt_sequence_thread_audio.h"
	#define dt_sequence_thread dt_sequence_thread_audio
#endif