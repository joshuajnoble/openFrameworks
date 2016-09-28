/*
 * ofxAndroidAccelerometer.cpp
 *
 *  Created on: 28/11/2010
 *      Author: arturo
 */


#include <jni.h>

#include "ofxAndroidDeviceOrientation.h"
#include "ofxAndroidUtils.h"
#include "ofLog.h"


ofxAndroidDeviceOrientationHandler ofxAndroidDeviceOrientation;

extern "C"{
void
Java_cc_openframeworks_OFAndroidDeviceOrientation_updateDeviceOrientation( JNIEnv*  env, jobject  thiz, jfloat x, jfloat y, jfloat z ){
	// android reports these in m/s^2, but ofxAccelerometer expects g's (1g = gravity = 9.81m/s^2)
	ofxAndroidDeviceOrientation.update(x, y, z);
}
}

void ofxAndroidDeviceOrientationHandler::setup(){
	if(!ofGetJavaVMPtr()){
		ofLogError("ofxAndroidGyroscope") << "setup(): couldn't find java virtual machine";
		return;
	}
	JNIEnv *env;
	if (ofGetJavaVMPtr()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		ofLogError("ofxDeviceOrientation") << "setup(): failed to get environment using GetEnv()";
		return;
	}
	jclass javaClass = env->FindClass("cc/openframeworks/OFAndroid");

	if(javaClass==0){
		ofLogError("ofxDeviceOrientation") << "setup(): couldn't find OFAndroid java class";
		return;
	}

	jmethodID setupDeviceOrientation = env->GetStaticMethodID(javaClass,"setupDeviceOrientation","()V");
	if(!setupDeviceOrientation){
		ofLogError("ofxDeviceOrientation") << "setup(): couldn't find OFAndroid.setupDeviceOrientation method";
		return;
	}
	env->CallStaticVoidMethod(javaClass,setupDeviceOrientation);
}

void ofxAndroidDeviceOrientationHandler::exit(){

}
