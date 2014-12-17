#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetFrameRate(60);

	bCalibrationMode = false;

	tactonic.setup();

	mat.setup(&tactonic);

	calibration.setup();

	cannon.setup();

	platforms.setup();

	bShowWarning = false;
	bRunning = false;

}

//--------------------------------------------------------------
void ofApp::update(){
	float DT = 1.0f / 60.0f;

	tactonic.update();

	mat.update(DT);

	if (bRunning) {
		cannon.update(DT);
		platforms.update(DT);
	}

	vector<ofVec3f> worldForce = mat.getWorldForcePoints();
	bShowWarning = platforms.isOneForceOffPlatforms(worldForce);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(0);


	calibration.begin();

	mat.draw();
	cannon.draw();
	platforms.draw();

	if (bShowWarning) {
		ofSetColor(200, 0, 0);
		ofFill();
		ofRect(0, 0, 0.05, 1);
		ofRect(0, 0, 1, 0.05);
		ofRect(0.95, 0, 0.05, 1);
		ofRect(0, 0.95, 1, 0.05);
	}

	calibration.end();


	if (bCalibrationMode) {
		calibration.draw();
		calibration.begin();
		mat.drawDebug();
		calibration.end();
	}


	// draw mouse
	ofSetColor(255);
	ofFill();
	ofEllipse(ofGetMouseX(), ofGetMouseY(), 3, 3);

//	calibration.begin();
//
//	tactonic.draw();
//
//	calibration.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'g') {
		bCalibrationMode = !bCalibrationMode;
	}
	else if (key == 'm') {
		CGDisplayShowCursor(kCGDirectMainDisplay);
	}
	else if (key == ' ') {
		bRunning = !bRunning;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (bCalibrationMode) {
		calibration.mouseDrag(x, y);

		ofVec2f local = calibration.toWorld(ofVec2f(x, y));
		mat.mouseDragged(local);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (bCalibrationMode) {
		calibration.mouseDown(x, y);

		ofVec2f local = calibration.toWorld(ofVec2f(x, y));
		mat.mouseDown(local);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (bCalibrationMode) {
		calibration.mouseUp(x, y);

		ofVec2f local = calibration.toWorld(ofVec2f(x, y));
		mat.mouseUp(local);
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
