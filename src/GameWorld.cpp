//
//  GameWorld.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#include "GameWorld.h"
#include "ofxRemoteUIServer.h"

GameWorld::~GameWorld()
{
	tactonic->stop();
	delete tactonic;
}

void GameWorld::setup()
{
	tactonic = new TactonicInput();
	tactonic->setup();

	carpet.setup(tactonic);

	cam.setPosition(camPos);
	cam.setParent(carpet);
	cam.lookAt(carpet.getCamTarget(), ofVec3f(0, 1, 0));
	cam.setFarClip(100000);

	// light
	lightOffset = ofVec3f(-100, 10000, 500);
	light.setup();
	light.setSpotlight();
	light.setAmbientColor(ofColor(50));
	light.setDiffuseColor(ofColor(200));
	light.setSpecularColor(ofColor(255));
	light.setPosition(carpet.getGlobalPosition() + lightOffset);
	light.lookAt(ofVec3f(0, 0, 0));


	for (int i=0; i<100; i++) {
		FlyingObject* fo = new FlyingObject();
		fo->setup(ofRandom(-1000, 1000), 0, ofRandom(3000, 100000), FlyingObject::POINT);

		flyingObjects.push_back(fo);
	}

	for (int i=0; i<200; i++) {
		dust.push_back(ofVec3f(ofRandom(-1000, 1000), ofRandom(-300, 0), ofRandom(0, 10000)));
	}
}

void GameWorld::setSpeed(float speed)
{
	carpet.setSpeed(speed);
}

void GameWorld::update(float dt)
{
	tactonic->update();

	carpet.update(dt);

	updateParams();

	for (int i=0; i<flyingObjects.size(); i++)
	{
		flyingObjects[i]->update(dt);
	}

	for (int i=0; i<dust.size(); i++) {
		if (carpet.getZ() > dust[i].z) {
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


	carpet.draw();
	for (int i=0; i<flyingObjects.size(); i++)
	{
		flyingObjects[i]->draw();
	}

	ofSetColor(200);
	ofFill();
	for (int i=0; i<dust.size(); i++) {
		ofPushMatrix();
		ofTranslate(dust[i]);

		ofDrawPlane(0, 0, 10, 10);

		ofPopMatrix();
	}


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

	carpet.setupParams();
}


void GameWorld::updateParams()
{
	cam.setPosition(camPos);
//	cam.lookAt(carpet.getCamTarget(), carpet.getGlobalPosition() + ofVec3f(0, 1, 0));
	light.setPosition(carpet.getGlobalPosition() + lightOffset);
}

void GameWorld::createWorldGeometry()
{
}