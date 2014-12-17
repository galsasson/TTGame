#pragma once

#include "ofMain.h"
#include "ofxRemoteUIServer.h"

#include "TactonicInput.h"
#include "ProjectorCalibration.h"
#include "Cannon.h"
#include "Mattress.h"
#include "Platforms.h"
#include "GameWorld.h"

class ofApp : public ofBaseApp{

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

	void clientDidSomething(RemoteUIServerCallBackArg & arg);

private:
	GameWorld game;
//	ProjectorCalibration calibration;
//	Cannon cannon;
//	Mattress mat;
//	Platforms platforms;


	bool bCalibrationMode;

//	bool bShowWarning;

	bool bRunning;
	
};
