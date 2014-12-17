#pragma once

#include "ofMain.h"
#include "TactonicInput.h"
#include "ProjectorCalibration.h"
#include "Cannon.h"
#include "Mattress.h"
#include "Platforms.h"

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


private:
	TactonicInput tactonic;
	ProjectorCalibration calibration;
	Cannon cannon;
	Mattress mat;
	Platforms platforms;


	bool bCalibrationMode;

	bool bShowWarning;
	
};
