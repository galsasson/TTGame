//
//  FlyingObjectPiece.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#include "FlyingObjectPiece.h"


void FlyingObjectPiece::setup(float x, float y, float z, ofColor c)
{
	setPosition(x, y, z);

	color = c;

	flyRotation = ofVec3f(ofRandom(0, 100),
						  ofRandom(0, 100),
						  ofRandom(0, 100));
	velocity = ofVec3f(x, y, z);

}

void FlyingObjectPiece::update(float dt)
{
	rotate(flyRotation.x, ofVec3f(1, 0, 0));
	rotate(flyRotation.y, ofVec3f(0, 1, 0));
	rotate(flyRotation.z, ofVec3f(0, 0, 1));

	move(velocity);
}

void FlyingObjectPiece::draw()
{
	ofPushMatrix();
	ofMultMatrix(getLocalTransformMatrix());

	ofFill();
	ofSetColor(color);
	ofDrawBox(0, 0, 0, 10, 10, 10);

	ofPopMatrix();
}