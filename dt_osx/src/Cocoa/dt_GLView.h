//
//  dt_GLView.h
//  dialt_osx_cocoa
//
//  Created by mtb on 2014/07/07.
//
//

#pragma once

#include "ofApp.h"
#include "ofxCocoaGLView.h"

@interface dt_GLView : ofxCocoaGLView {

@private
	ofApp * app;
}

- (void)setup;
- (void)update;
- (void)draw;
- (void)exit;
- (void)keyPressed:(int)key;
- (void)keyReleased:(int)key;
- (void)mouseMoved:(NSPoint)p;
- (void)mouseDragged:(NSPoint)p button:(int)button;
- (void)mousePressed:(NSPoint)p button:(int)button;
- (void)mouseReleased:(NSPoint)p button:(int)button;
- (void)windowResized:(NSSize)size;

@end
