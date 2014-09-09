//
//  ofx2DCamera.cpp
//  dial
//
//  Created by hiroshi matoba on 9/9/14.
//
//

#include "ofx2DCamera.h"

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
    if( transX_tw.isRunning() ){
        trans.x = transX_tw.update();
    }

    if( transY_tw.isRunning() ){
        trans.y = transY_tw.update();
    }
    
    if( zoomRate_tw.isRunning() ){
        zoomRate = zoomRate_tw.update();
    }else if( bZooming &&zoomRate_tw.isCompleted() ){
//        ofVec2f center( ofGetWidth()/2, ofGetHeight()/2 );
//        ofVec2f center_w = screenToWorld( center );
//        startPivot( center_w );
//        bZooming = false;
    }
}

void ofx2DCamera::begin(){
    ofSetupScreenOrtho();
    ofPushMatrix();
        ofTranslate( ofGetWidth()/2, ofGetHeight()/2 );
        ofTranslate( trans );
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
    ofVec2f ret = ( screenXY-trans-pivot-center ) / zoomRate;
    ret.rotate( -angle );
    ret += pivot;
    return ret;
}

void ofx2DCamera::debugDraw(){

    ofSetRectMode( OF_RECTMODE_CENTER );
    
    // grid
    ofSetColor( 20 );
    ofLine( -500, 0, 500, 0 );
    ofLine( 0, -500, 0, 500 );
    
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

void ofx2DCamera::move( ofVec2f _trans, int time_ms, int delay_ms ){
    transX_tw.setParameters( 1, easingsine, ofxTween::easeInOut, trans.x, _trans.x, time_ms, delay_ms );
    transY_tw.setParameters( 2, easingsine, ofxTween::easeInOut, trans.y, _trans.y, time_ms, delay_ms );
}

void ofx2DCamera::zoom( float _zoomRate, int time_ms, int delay_ms){
    bZooming = true;
    zoomRate_tw.setParameters( 3, easingsine, ofxTween::easeInOut, zoomRate, _zoomRate, time_ms, delay_ms );
}

void ofx2DCamera::moveZoom( ofVec2f _trans, float _zoomRate, int time_ms, int delay_ms ){
    
    startPivot( _trans );
    transX_tw.setParameters( 1, easingsine, ofxTween::easeInOut, trans.x, -_trans.x, time_ms/2, delay_ms );
    transY_tw.setParameters( 2, easingsine, ofxTween::easeInOut, trans.y, -_trans.y, time_ms/2, delay_ms );
    
    bZooming = true;
    zoomRate_tw.setParameters( 3, easingsine, ofxTween::easeInOut, zoomRate, _zoomRate, time_ms/2, delay_ms+time_ms/2 );
}
