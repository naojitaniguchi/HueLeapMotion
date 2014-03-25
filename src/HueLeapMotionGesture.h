//
//  HueLeapMotionGesture.h
//  HueLeapMotion
//
//  Created by 谷口 直嗣 on 13/10/21.
//
//

#ifndef __HueLeapMotion__HueLeapMotionGesture__
#define __HueLeapMotion__HueLeapMotionGesture__

#include "ofMain.h"
#include "ofxLeapMotion.h"
#include <iostream>

#define THETA_DEMO_GESTURE_KEEP_POS_NUM 4

class HueLeapMotionGestureInterface{
public:
    virtual ~HueLeapMotionGestureInterface(){};
    virtual void updateByCenter( ofPoint center )= 0;
};

class HueLeapMotionGesture {
private:
    HueLeapMotionGestureInterface *delegate ;
    
    ofPoint fingerCenterPoint ;
    bool tracking ;
    int fingerNum ;
    void getCenterFromFingers(ofxLeapMotionSimpleHand *hand);
public:
    int status ;
    static HueLeapMotionGesture* getInstance(void) {
        static HueLeapMotionGesture singleton;
        return &singleton;
    }
    void update(vector <ofxLeapMotionSimpleHand> &simpleHands);
    void draw();
    void setDelegate( HueLeapMotionGestureInterface *d);
    bool isTracking();
    int getFungerNum();
};

#endif /* defined(__HueLeapMotion__HueLeapMotionGesture__) */
