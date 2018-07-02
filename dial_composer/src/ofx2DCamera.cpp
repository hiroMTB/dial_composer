//
//  ofx2DCamera.cpp
//  dial
//
//  Created by hiroshi matoba on 9/9/14.
//
//

#include "ofx2DCamera.h"
#include "ofApp.h"

ofx2DCamera::ofx2DCamera(){
    reset();
}

void ofx2DCamera::reset(){
    trans.zero();
    pivot.zero();
    angle = 0;
    zoomRate = 1;
}

void ofx2DCamera::update(){
    // tweener.update();
}

void ofx2DCamera::begin(){
    ofSetupScreenOrtho();
    ofPushMatrix();
        ofTranslate( ofGetWidth()/2, ofGetHeight()/2 );
        ofRotate( 180, 1, 0, 0);    
        ofTranslate( -trans );
        ofTranslate( pivot );
        ofRotate( angle, 0, 0, 1);
        ofScale( zoomRate, zoomRate);
        ofTranslate( -pivot );
}

void ofx2DCamera::end(){
    ofPopMatrix();
}

void ofx2DCamera::startPivot( ofVec2f pivotXY ){
    ofVec2f pd = pivotXY - pivot;
    ofVec2f v = -pd * zoomRate;
    v.rotate( angle );
    trans -= pd+v;
    pivot = pivotXY;
}

ofVec2f ofx2DCamera::worldToScreen( ofVec2f worldXY ) const{
    // TODO
    return  ofVec2f(0, 0);
}

ofVec2f ofx2DCamera::screenToWorld( ofVec2f screenXY ) const{
    ofVec2f center( ofGetWidth()/2, ofGetHeight()/2 );
    ofVec2f ret = ( screenXY+trans-pivot-center ) / zoomRate;
    ret.rotate( -angle );
    ret += pivot;
    return ret;
}

void ofx2DCamera::debugDraw(){

    ofSetRectMode( OF_RECTMODE_CENTER );
    
    // center guide
    ofSetColor( 20 );
    ofLine( -100, 0, 100, 0 );
    ofLine( 0, -100, 0, 100 );
    
    // trans
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor( 255, 0, 0 );
    ofRect( trans.x, trans.y, 5, 5 );
    ofDrawBitmapString("trans " + ofToString(trans.x) + ", " + ofToString(trans.y), trans );
    
    ofLine( 0, 0, trans.x, trans.y );
    
    // pivot
    ofNoFill();
    ofSetColor( 0, 255, 0 );
    ofRect( pivot.x, pivot.y, 15, 15 );
    ofDrawBitmapString("pivot " + ofToString(pivot.x) + ", " + ofToString(pivot.y), pivot+ofVec2f(0,20) );
    ofLine( 0, 0, pivot.x, pivot.y );
    
    ofSetRectMode( OF_RECTMODE_CORNER );
}

void ofx2DCamera::move( ofVec2f _trans, int time_ms, void (^callback)(float *arg) ){
	float time = (float) time_ms * 0.001;
	// tweener.addTween(trans.x, _trans.x, time, callback );
	// tweener.addTween(trans.y, _trans.y, time, callback );
}

void ofx2DCamera::zoom( float _zoomRate, int time_ms, void (^callback)(float *arg) ){
	float time = (float) time_ms * 0.001;
    // tweener.addTween( zoomRate, _zoomRate, time, callback );
}

void ofx2DCamera::moveZoom( ofVec2f _trans, float _zoomRate, int time_ms, void (^callback)(float *arg)){
	float time = (float) time_ms * 0.001 * 0.5;
	float delay = time;
    startPivot( _trans );
	// tweener.addTween( trans.x, _trans.x, time, &ofxTransitions::easeInOutSine );
	// tweener.addTween( trans.y, _trans.y, time, &ofxTransitions::easeInOutSine );
	// tweener.addTween( zoomRate, _zoomRate, time, &ofxTransitions::easeInOutSine, delay, callback );
}

void ofx2DCamera::zoomMove( float _zoomRate, ofVec2f _trans, int time_ms, void (^callback)(float *arg) ){
	float time = (float) time_ms * 0.001 * 0.5;
	float delay = time;
	// tweener.addTween( zoomRate, _zoomRate, time, &ofxTransitions::easeInOutSine );
	// tweener.addTween( trans.x, _trans.x, time, &ofxTransitions::easeInOutSine, delay );
	// tweener.addTween( trans.y, _trans.y, time, &ofxTransitions::easeInOutSine, delay, callback );
}
