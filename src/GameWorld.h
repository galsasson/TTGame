//
//  GameWorld.h
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#ifndef __TTGame__GameWorld__
#define __TTGame__GameWorld__

#include <stdio.h>
#include "ofMain.h"
#include "Carpet.h"
#include "FlyingObject.h"
#include "Wall.h"

class GameWorld
{
public:

	~GameWorld();

	void setup();

	void setSpeed(float speed);

	void update(float dt);
	void draw();

	void setupParams();

private:
	TactonicInput* tactonic;

	Carpet* carpet;
	vector<FlyingObject*> flyingObjects;
	vector<Wall*> walls;

	vector<ofVec3f> dust;

	ofNode camXRotNode;
	ofNode camYRotNode;
	ofCamera cam;
	ofLight light;

	void createObjects();


	// params
	void updateParams();
	ofVec3f camPos;
	ofVec3f camRotation;
	ofVec3f lightOffset;

	void createWorldGeometry();
	ofVbo vbo;
	
};

#endif /* defined(__TTGame__GameWorld__) */
