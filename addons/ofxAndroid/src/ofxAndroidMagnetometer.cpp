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

#include <jni.h>
#include "ofxAndroidMagnetometer.h"
#include "ofxAndroidUtils.h"
#include "ofLog.h"


ofxAndroidMagnetometerHandler ofxAndroidMagnetometer;

/*
 * ofxAndroidAccelerometer.cpp
 *
 *  Created on: 28/11/2010
 *      Author: arturo
 */

extern "C"{
void
Java_cc_openframeworks_OFAndroidMagnetometer_updateMagnetometer( JNIEnv*  env, jobject  thiz, jfloat x, jfloat y, jfloat z ){
	ofLogNotice(" ofxAndroidMagnetometer update ");
	ofxAndroidMagnetometer.update(x,y,z);
}
}

void ofxAndroidMagnetometerHandler::setup(){
	if(!ofGetJavaVMPtr()){
		ofLogError("ofxAndroidMagentometer") << "setup(): couldn't find java virtual machine";
		return;
	}
	JNIEnv *env;
	if (ofGetJavaVMPtr()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		ofLogError("ofxAndroidMagentometerr") << "setup(): failed to get environment using GetEnv()";
		return;
	}
	jclass javaClass = env->FindClass("cc/openframeworks/OFAndroid");

	if(javaClass==0){
		ofLogError("ofxAndroidMagentometer") << "setup(): couldn't find OFAndroid java class";
		return;
	}

	jmethodID setupMagnetometer = env->GetStaticMethodID(javaClass,"setupMagnetometer","()V");
	if(!setupMagnetometer){
		ofLogError("ofxAndroidMagnetometer") << "setup(): couldn't find OFAndroid.setupMagnetometer method";
		return;
	}
	env->CallStaticVoidMethod(javaClass,setupMagnetometer);
}

void ofxAndroidMagnetometerHandler::exit(){

}
