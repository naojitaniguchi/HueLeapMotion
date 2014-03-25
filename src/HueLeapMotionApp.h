#pragma once

#include "ofMain.h"
#include "ofxLeapMotion.h"
#include "ofxStrip.h"
#include "HueLeapMotionGesture.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class HueLeapMotionApp : public ofBaseApp, public HueLeapMotionGestureInterface{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void exit();
    
        void updateByCenter( ofPoint center );
        void hsv2rgb();
    
        ofxLeapMotion leap;
        vector <ofxLeapMotionSimpleHand> simpleHands;
    
        HueLeapMotionGesture *gesture ;
    
        vector <int> fingersFound;
        ofEasyCam cam;
        ofLight l1;
        ofLight l2;
        ofMaterial m1;
	
        map <int, ofPolyline> fingerTrails;
    
        float handAngle ;
        ofColor color ;
    
        ofxOscSender sender;
        int lastHue ;
};
