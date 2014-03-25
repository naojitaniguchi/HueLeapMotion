//
//  HueLeapMotionGesture.cpp
//  HueLeapMotion
//
//  Created by 谷口 直嗣 on 13/10/21.
//
//

#include "HueLeapMotionGesture.h"

#define HUE_LEAP_MOTION_GESTURE_CENTER_SHERER_RAD       10.0f


#define THETA_DEMO_GESTURE_Y_DIFF_RANGE 10.0
#define THETA_DEMO_GESTURE_X_THRESHOLD  0.1f
#define THETA_DEMO_GESTURE_Z_THRESHOLD  0.1f
#define THETA_DEMO_GESTURE_SWIPE_TOTAL_ANGLE_MIN 0.1f
#define THETA_DEMO_GEUSTURE_SWIPE_LENGTH_MIN    10.0f


// ofxLeapMotionSimpleHand
void HueLeapMotionGesture::getCenterFromFingers(ofxLeapMotionSimpleHand *hand){

    ofPoint pt ;
    pt.zero();

    for(int i = 0; i < hand->fingers.size(); i++){
        pt += hand->fingers[i].pos;
    }
    fingerNum = hand->fingers.size() ;
    
    pt.x /= (float)fingerNum ;
    pt.y /= (float)fingerNum ;
    pt.z /= (float)fingerNum ;
    
    fingerCenterPoint = pt ;
}


void HueLeapMotionGesture::update(vector <ofxLeapMotionSimpleHand> &simpleHands){
    tracking = false ;

    if ( simpleHands.size() > 0 ){
        tracking = true ;
        getCenterFromFingers(&simpleHands[0]);
        delegate->updateByCenter(fingerCenterPoint);
    }
}

void HueLeapMotionGesture::draw(){
    // 真ん中の点を表示する
    // Sphereを表示する
    if ( tracking ){
        ofSetColor(0,255,0,128);
        ofDrawSphere((const ofPoint)fingerCenterPoint, HUE_LEAP_MOTION_GESTURE_CENTER_SHERER_RAD);
    }
}

void HueLeapMotionGesture::setDelegate( HueLeapMotionGestureInterface *d){
    delegate = d ;
}

bool HueLeapMotionGesture::isTracking(){
    return tracking ;
}

int HueLeapMotionGesture::getFungerNum(){
    return fingerNum ;
}

