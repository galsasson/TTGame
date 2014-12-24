//
//  GameWorld.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#include "GameWorld.h"
#include "ofxRemoteUIServer.h"
#include "Constants.h"

#define MIN_X	-1000
#define MAX_X	1000
#define MAX_Z	1000000

GameWorld::~GameWorld()
{
	tactonic->stop();
	delete tactonic;
}

void GameWorld::setup()
{
	tactonic = new TactonicInput();
	tactonic->setup();

	carpet = new Carpet();
	carpet->setup(tactonic);

	camXRotNode.setParent(*carpet);
	camYRotNode.setParent(camXRotNode);
//	camYRotNode.rotate(180, ofVec3f(0, 1, 0));
	cam.setPosition(0, 0, camPos.z);
	cam.setParent(camYRotNode);
//	cam.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, 1, 0));
	cam.lookAt(carpet->getCamTarget(), ofVec3f(0, 1, 0));
	cam.setFarClip(100000);
	cam.setFov(100);

#ifdef FLOOR_SENSOR
	cam.roll(180);
#endif

	// light
	lightOffset = ofVec3f(-100, 10000, 500);
	light.setup();
	light.setSpotlight();
	light.setAmbientColor(ofColor(50));
	light.setDiffuseColor(ofColor(200));
	light.setSpecularColor(ofColor(255));
	light.setPosition(carpet->getGlobalPosition() + lightOffset);
	light.lookAt(ofVec3f(0, 0, 0));

#if 0
	// create flying objects
	for (int i=0; i<100; i++) {
		FlyingObject* fo = new FlyingObject();
		FlyingObject::Type t;
		if (ofRandom(1) < 0.3f) {
			t = FlyingObject::BARRIER;
		}
		else {
			t = FlyingObject::POINT;
		}
		fo->setup(ofRandom(-1000, 1000), 0, ofRandom(3000, 400000), t);

		flyingObjects.push_back(fo);
	}

	// create walls
	for (int i=0; i<10; i++) {
		float z = ofRandom(5000, 100000);
		Wall* wall = new Wall();
		wall->setup(z);
		walls.push_back(wall);
	}
#else
	createObjects();
#endif
	// creat dust
	for (int i=0; i<200; i++) {
		dust.push_back(ofVec3f(ofRandom(-1000, 1000), ofRandom(-10, 0), ofRandom(0, 10000)));
	}
}


void GameWorld::createObjects()
{
	float z = 3000;
	float x = 0;

	while (z < MAX_Z) {
		if (ofRandom(1) < 0.12) {
			// add bullet and wall
			Wall* w = new Wall();
			w->setup(z);
			walls.push_back(w);

			// add bullet
			FlyingObject* fo = new FlyingObject();
			float x = ofRandom(MIN_X, MAX_X);
			fo->setup(x, 35, z-ofRandom(5000, 15000), FlyingObject::BULLET);
			flyingObjects.push_back(fo);

		}
		else {
			// add point or barrier
			FlyingObject::Type t = FlyingObject::POINT;
			if (ofRandom(1) < 0.2) {
				t = FlyingObject::BARRIER;
			}

			float x = ofRandom(MIN_X, MAX_X);
			FlyingObject* fo = new FlyingObject();
			fo->setup(x, 35, z, t);
			flyingObjects.push_back(fo);
		}

		z += ofRandom(500, 5000);
	}
}


void GameWorld::setSpeed(float speed)
{
	carpet->setSpeed(speed);
}

void GameWorld::update(float dt)
{
	updateParams();

	tactonic->update();

	carpet->update(dt);

	// handle shootings from the carpet
	if (carpet->isShooting()) {
		for (int i=0; i<walls.size(); i++)
		{
			if (walls[i]->getZ() - carpet->getZ() < 4000 &&
				!walls[i]->didExplode()) {
				walls[i]->explode();
			}
		}
	}


	vector<int> deadObjects;

	for (int i=0; i<flyingObjects.size(); i++)
	{
		FlyingObject* fo = flyingObjects[i];

		fo->update(dt);

		if (!fo->isExploding() &&
			fo->getPosition().distance(carpet->getPosition()) < 100)
		{
			if (fo->type == FlyingObject::POINT ||
				fo->type == FlyingObject::BARRIER) {
				cout<<"explode!!!"<<endl;
				fo->explode();
			}
			else {
				deadObjects.push_back(i);
				carpet->takeBullet();
			}

			if (fo->type == FlyingObject::BARRIER) {
				carpet->hit();
			}
		}

		if (!fo->isAlive()) {
			deadObjects.push_back(i);
		}

		// push forward if we missed it
		if (fo->getZ() < carpet->getZ()-300 &&
			!fo->isExploding())
		{
			deadObjects.push_back(i);
		}
	}

	for (int i=deadObjects.size()-1; i>=0; i--)
	{
		delete flyingObjects[deadObjects[i]];
		flyingObjects.erase(flyingObjects.begin() + deadObjects[i]);
	}
	deadObjects.clear();

	// update walls
	for (int i=0; i<walls.size(); i++)
	{
		walls[i]->update(dt);

		if (abs(walls[i]->getZ() - carpet->getZ()) < 50 &&
			carpet->isFootDown() &&
			!walls[i]->didExplode())
		{
			walls[i]->explode();
			carpet->hit();
		}

		if (walls[i]->getZ() < carpet->getZ()-300) {
			deadObjects.push_back(i);
		}
	}

	for (int i=deadObjects.size()-1; i>=0; i--)
	{
		delete walls[deadObjects[i]];
		walls.erase(walls.begin() + deadObjects[i]);
	}
	deadObjects.clear();

	// update dust
	for (int i=0; i<dust.size(); i++) {
		if (carpet->getZ() > dust[i].z) {
			dust[i].z += 10000;
		}
	}

}

void GameWorld::draw()
{
	ofEnableDepthTest();
	ofEnableLighting();

	cam.begin();
	light.enable();


	carpet->draw();
	for (int i=0; i<flyingObjects.size(); i++)
	{
		flyingObjects[i]->draw();
	}

	for (int i=0; i<walls.size(); i++)
	{
		walls[i]->draw();
	}

	ofSetColor(200);
	ofFill();
	ofPushMatrix();
	for (int i=0; i<dust.size(); i++) {
		ofPushMatrix();
		ofTranslate(dust[i]);
		ofRotateX(270);

		ofDrawPlane(0, 0, 20, 50);

		ofPopMatrix();
	}
	ofPopMatrix();


	ofDrawAxis(1000);

	light.disable();
	cam.end();

	ofDisableLighting();
	ofDisableDepthTest();

}


void GameWorld::setupParams()
{
	RUI_NEW_GROUP("Camera");

	RUI_SHARE_PARAM(camPos.x, -50, 50);
	RUI_SHARE_PARAM(camPos.y, 0, 500);
	RUI_SHARE_PARAM(camPos.z, -1000, 100);

	RUI_SHARE_PARAM(camRotation.x, -180, 180);
	RUI_SHARE_PARAM(camRotation.y, -180, 180);

	carpet->setupParams();
}


void GameWorld::updateParams()
{
	cam.setPosition(camPos);

	camYRotNode.setOrientation(ofVec3f(0, camRotation.y, 0));
	camXRotNode.setOrientation(ofVec3f(camRotation.x, 0, 0));
//	cam.lookAt(carpet.getCamTarget(), carpet.getGlobalPosition() + ofVec3f(0, 1, 0));
	light.setPosition(carpet->getGlobalPosition() + lightOffset);
}

void GameWorld::createWorldGeometry()
{
}