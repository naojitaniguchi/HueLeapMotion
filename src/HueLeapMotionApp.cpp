#include "HueLeapMotionApp.h"

//--------------------------------------------------------------
void HueLeapMotionApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);
    
	leap.open();
    
	l1.setPosition(200, 300, 50);
	l2.setPosition(-200, -200, 50);
    
	cam.setOrientation(ofPoint(-20, 0, 0));
    ofVec3f camPos = cam.getPosition() ;
    camPos.z += 200 ;
    cam.setPosition(camPos);
    
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    gesture = HueLeapMotionGesture::getInstance();
    gesture->setDelegate(this);

    color.r = 0 ;
    color.g = 0 ;
    color.b = 0 ;

    sender.setup(HOST, PORT);
    lastHue = 0 ;
}

//--------------------------------------------------------------
void HueLeapMotionApp::update(){
	fingersFound.clear();
	
	//here is a simple example of getting the hands and using them to draw trails from the fingertips.
	//the leap data is delivered in a threaded callback - so it can be easier to work with this copied hand data
	
	//if instead you want to get the data as it comes in then you can inherit ofxLeapMotion and implement the onFrame method.
	//there you can work with the frame data directly.
    
    
    
    //Option 1: Use the simple ofxLeapMotionSimpleHand - this gives you quick access to fingers and palms.
    
    simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
		leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        for(int i = 0; i < simpleHands.size(); i++){
            
            for(int j = 0; j < simpleHands[i].fingers.size(); j++){
                int id = simpleHands[i].fingers[j].id;
                
                ofPolyline & polyline = fingerTrails[id];
                ofPoint pt = simpleHands[i].fingers[j].pos;
                
                //if the distance between the last point and the current point is too big - lets clear the line
                //this stops us connecting to an old drawing
                if( polyline.size() && (pt-polyline[polyline.size()-1] ).length() > 50 ){
                    polyline.clear();
                }
                
                //add our point to our trail
                polyline.addVertex(pt);
                
                //store fingers seen this frame for drawing
                fingersFound.push_back(id);
            }
        }
    }
    
    
    // Option 2: Work with the leap data / sdk directly - gives you access to more properties than the simple approach
    // uncomment code below and comment the code above to use this approach. You can also inhereit ofxLeapMotion and get the data directly via the onFrame callback.
    
    //	vector <Hand> hands = leap.getLeapHands();
    //	if( leap.isFrameNew() && hands.size() ){
    //
    //		//leap returns data in mm - lets set a mapping to our world space.
    //		//you can get back a mapped point by using ofxLeapMotion::getMappedofPoint with the Leap::Vector that tipPosition returns
    //		leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
    //		leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
    //		leap.setMappingZ(-150, 150, -200, 200);
    //
    //		for(int i = 0; i < hands.size(); i++){
    //            for(int j = 0; j < hands[i].fingers().count(); j++){
    //				ofPoint pt;
    //
    //				const Finger & finger = hands[i].fingers()[j];
    //
    //				//here we convert the Leap point to an ofPoint - with mapping of coordinates
    //				//if you just want the raw point - use ofxLeapMotion::getofPoint
    //				pt = leap.getMappedofPoint( finger.tipPosition() );
    //
    //				//lets get the correct trail (ofPolyline) out of our map - using the finger id as the key
    //				ofPolyline & polyline = fingerTrails[finger.id()];
    //
    //				//if the distance between the last point and the current point is too big - lets clear the line
    //				//this stops us connecting to an old drawing
    //				if( polyline.size() && (pt-polyline[polyline.size()-1] ).length() > 50 ){
    //					polyline.clear();
    //				}
    //
    //				//add our point to our trail
    //				polyline.addVertex(pt);
    //
    //				//store fingers seen this frame for drawing
    //				fingersFound.push_back(finger.id());
    //			}
    //		}	
    //	}
    //    
    
	//IMPORTANT! - tell ofxLeapMotion that the frame is no longer new. 
	leap.markFrameAsOld();	

    gesture->update( simpleHands );
}

//--------------------------------------------------------------
void HueLeapMotionApp::draw(){
	ofDisableLighting();
    ofBackground(color);
    // ofBackgroundGradient(ofColor(90, 90, 90), ofColor(30, 30, 30),  OF_GRADIENT_BAR);
	
	ofSetColor(200);
	ofDrawBitmapString("ofxLeapMotion - Example App\nMake sure the Leap.app is running while running this example\nYou may need to restart Leap.app to get data", 20, 20);
    
	cam.begin();
    
	ofPushMatrix();
    ofRotate(90, 0, 0, 1);
    ofSetColor(20);
    ofDrawGridPlane(800, 20, false);
	ofPopMatrix();
	
	ofEnableLighting();
	l1.enable();
	l2.enable();
	
	m1.begin();
	m1.setShininess(0.6);
	
    /*
	for(int i = 0; i < fingersFound.size(); i++){
		ofxStrip strip;
		int id = fingersFound[i];
		
		ofPolyline & polyline = fingerTrails[id];
		strip.generate(polyline.getVertices(), 15, ofPoint(0, 0.5, 0.5) );
		
		ofSetColor(255 - id * 15, 0, id * 25);
		strip.getMesh().draw();
	}
     */
	
    l2.disable();
    
    for(int i = 0; i < simpleHands.size(); i++){
        simpleHands[i].debugDraw();
    }
    
    gesture->draw();
    
	m1.end();
	cam.end();
	

}

//--------------------------------------------------------------
void HueLeapMotionApp::keyPressed(int key){

}

//--------------------------------------------------------------
void HueLeapMotionApp::keyReleased(int key){

}

//--------------------------------------------------------------
void HueLeapMotionApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void HueLeapMotionApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void HueLeapMotionApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void HueLeapMotionApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void HueLeapMotionApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void HueLeapMotionApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void HueLeapMotionApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void HueLeapMotionApp::exit(){
    // let's close down Leap and kill the controller
    leap.close();
}

void HueLeapMotionApp::updateByCenter( ofPoint center ){
    // 角度を求める
    ofVec3f zeroVec ;
    zeroVec.x = 1.0f ;
    zeroVec.y = 0.0f ;
    zeroVec.z = 0.0f ;
    
    ofVec3f handVec ;
    handVec.x = center.x ;
    handVec.y = 0.0f ;
    handVec.z = center.z ;
    
    handVec.normalize();
    float dotp = zeroVec.dot(handVec);
    
    handAngle = acosf( dotp );
    if ( handVec.z > 0.0f ){
        handAngle = M_PI + M_PI - handAngle ;
    }
    printf("updateByCenter x:%f, y:%f, z:%f, handAngle:%f\n",center.x, center.y, center.z, handAngle );
    
    float hAngle = ( handAngle / (2 * M_PI) ) * 360 ;

    if ( hAngle < 0 ){
        return ;
    }
    float h = (hAngle /360.0f ) * 255.f ;
    
    color.setHsb(h, 255.0f, 255.0f);
    
    printf("updateByCenter handAngle %f, h:%f, r:%d, g:%d, b:%d \n",handAngle, h, color.r, color.g, color.b );
    
    int hdiff = hAngle - lastHue ;
    if ( hdiff < 0 ){
        hdiff *= -1.0f ;
    }
    
    if ( hdiff > 10.0f ){
        ofxOscMessage m;
        
/*
        m.clear();
        m.setAddress("/hue");
        m.addIntArg(0);
        m.addIntArg(h);
        m.addIntArg(255);
        m.addIntArg(128);
        sender.sendMessage(m);
 */

    /*
        m.clear();
        m.setAddress("/hue");
        m.addIntArg(1);
        //m.addIntArg(((int)h+120)%360);
        m.addIntArg(h);
        m.addIntArg(254);
        m.addIntArg(128);
        sender.sendMessage(m);
*/
        m.clear();
        m.setAddress("/hue");
        m.addIntArg(2);
        m.addIntArg((int)h * 255);
        m.addIntArg(254);
        m.addIntArg(90);
        sender.sendMessage(m);
        lastHue = hAngle ;
    }
}

void HueLeapMotionApp::hsv2rgb(){
    float v = 1.0f ;    // y座標で変化させる
    float s = 1.0f ;
    float h = ( handAngle / M_2_PI ) * 360 ;
    
    float r = 0 ;
    float g = 0 ;
    float b = 0 ;
    
    int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		r = g = b = v;
		return;
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		default:		// case 5:
			r = v;
			g = p;
			b = q;
			break;
	}
    
    // printf("updateByCenter r:%f, g:%f, b:%f \n",r, g, b );
    color.set( r,g,b );
}




