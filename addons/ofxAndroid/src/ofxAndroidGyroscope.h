/***********************************************************************
 
 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 * ***********************************************************************/ 

#pragma once

#include "ofTypes.h"
#include "ofPoint.h"
#include "ofVec3f.h"
#include "ofEvents.h"
#include "ofLog.h"

typedef void (*ofxGyroCB)(ofVec3f&);			// typedef for accelerometer callback

class ofxAndroidGyroscopeHandler {
public:
	ofxAndroidGyroscopeHandler() {
		callback = NULL;
		// setForceSmoothing(0.1f);					// little bit of smoothing for force
		// setOrientationSmoothing(0.9f);				// lots of smoothing for orientation / matrix
	}
	
	// call this to set it all up
	void setup();
	
	// call this when you no longer need the accelerometer
	void exit();
	
	// returns current smoothed accelerometer data (value in number of g's (1g = gravity, 9.8m/s^2)
	ofVec3f &getRotation() {
		return gyroReal;
	}
	
	
	// if you have a callback which conforms to ofxAccelCB, pass it to this to have it called when motion is detected
	void setCallback(ofxGyroCB new_callback) {
		callback = new_callback;
	}
	
	
	// platform specific accelerometer engine should call this when motion is detected
	void update(float x, float y, float z, float w) {

		stringstream ss;
		ss << " ofxAndroidGyroscope::update " << x << " " << y << " " << z << " " << w;
		ofLogNotice(ss.str());

		gyroReal.set(x, y, z);
		
		
		if(callback) callback(gyroReal);
		ofNotifyEvent(gyroChanged,gyroReal,this);
	}

	ofEvent<ofVec3f> gyroChanged;
	
protected:
	ofxGyroCB callback;
    ofVec3f gyroReal;           // current acceleration

};

extern ofxAndroidGyroscopeHandler ofxAndroidGyroscope;

template<class T>
void ofxRegisterGyroEvents(T * listener){
	ofAddListener(ofxAndroidGyroscope.gyroChanged,listener,&T::gyroscopeChanged);
}

