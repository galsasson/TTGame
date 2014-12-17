//
//  ProjectorCalibration.h
//  tacvis
//
//  Created by Gal Sasson on 11/28/14.
//
//

#ifndef __tacvis__ProjectorCalibration__
#define __tacvis__ProjectorCalibration__

#include <stdio.h>
#include "ofMain.h"
#include "ofxOpenCv.h"

class ProjectorCalibration
{
public:
	void setup();

	ofMatrix4x4 getProjectionMatrix() { return projectionMat; };

	void draw();

	void begin();
	void end();

	void mouseDown(int x, int y);
	void mouseDrag(int x, int y);
	void mouseUp(int x, int y);

	ofVec2f toLocal(const ofVec2f& p);
	ofVec2f toWorld(const ofVec2f& p);

private:

	ofMatrix4x4 toScreenMat;
	ofMatrix4x4 projectionMat;
//	cv::Mat cvProjection;

	ofVec2f points[4];	// tl, bl, tr, br
	int activePoint;

	void calcProjectionMatrix();
	ofVec2f getProj(float x, float y) { return getProj(ofVec2f(x, y)); }
	ofVec2f getProj(const ofVec2f& p);

	void printMatrix(const ofMatrix4x4& mat);
};

#endif /* defined(__tacvis__ProjectorCalibration__) */
