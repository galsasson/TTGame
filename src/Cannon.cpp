//
//  Cannon.cpp
//  tacvis
//
//  Created by Gal Sasson on 11/19/14.
//
//

#include "Cannon.h"

#define RAIN_SIZE		0.005

void Cannon::setup()
{
//	ofNode::setPosition(x, y, 0);

	for (int i=0; i<300; i++) {
		circles.push_back(ofVec2f(ofRandom(0, 1), ofRandom(0, 1)));
	}
}


void Cannon::update(float dt)
{
	for (int i=0; i<circles.size(); i++) {
		float incX = (ofNoise(ofGetElapsedTimef()+i)-0.5f)*0.01;
//		float incY = (ofNoise(ofGetElapsedTimef()+i+1000)-0.5f)*0.01;
		float incY = 0.01;
		circles[i] += ofVec2f(incX, incY);
		if (circles[i].y > 1+RAIN_SIZE) {
			circles[i].y = -RAIN_SIZE;
		}
	}
}


void Cannon::draw()
{
	ofFill();
	ofSetColor(255, 100);
	for (int i=0; i<circles.size(); i++) {
//		ofEllipse(0.5, 0.5, 10, 10);
		ofEllipse(circles[i], RAIN_SIZE, RAIN_SIZE);
	}

//	cout<<circles.size();
}