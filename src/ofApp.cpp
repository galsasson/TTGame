#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetFrameRate(60);

	RUI_SETUP();




	bCalibrationMode = false;
	game.setup();
	game.setupParams();



//	mat.setup(&tactonic);

//	calibration.setup();

//	cannon.setup();

//	platforms.setup();

//	bShowWarning = false;
	bRunning = false;

	RUI_LOAD_FROM_XML();

}

//--------------------------------------------------------------
void ofApp::update(){
	float DT = 1.0f / 60.0f;

	game.update(DT);
}

//--------------------------------------------------------------

void ofApp::draw()
{
	ofBackground(0);

	game.draw();
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
		if (bRunning) {
			game.setSpeed(1000);
		}
		else {
			game.setSpeed(0);
		}
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
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
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




//define a callback method to get notifications of client actions
void ofApp::clientDidSomething(RemoteUIServerCallBackArg &arg){

	switch (arg.action) {
		case CLIENT_CONNECTED: cout << "CLIENT_CONNECTED" << endl; break;
		case CLIENT_DISCONNECTED: cout << "CLIENT_DISCONNECTED" << endl; break;
		case CLIENT_UPDATED_PARAM: cout << "CLIENT_UPDATED_PARAM: "<< arg.paramName << " - ";
			arg.param.print();
			break;
		case CLIENT_DID_SET_PRESET: cout << "CLIENT_DID_SET_PRESET" << endl; break;
		case CLIENT_SAVED_PRESET: cout << "CLIENT_SAVED_PRESET" << endl; break;
		case CLIENT_DELETED_PRESET: cout << "CLIENT_DELETED_PRESET" << endl; break;
		case CLIENT_SAVED_STATE: cout << "CLIENT_SAVED_STATE" << endl; break;
		case CLIENT_DID_RESET_TO_XML: cout << "CLIENT_DID_RESET_TO_XML" << endl; break;
		case CLIENT_DID_RESET_TO_DEFAULTS: cout << "CLIENT_DID_RESET_TO_DEFAULTS" << endl; break;
		default:
			break;
	}
}
