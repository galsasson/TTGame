//
//  Carpet.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#include "Carpet.h"
#include "ofxRemoteUIServer.h"
#include "Constants.h"

void Carpet::setup(TactonicInput* tt)
{
	tactonic = tt;

	setPosition(0, 0, 0);

	camTargetNode.setParent(*this);
	camTargetNode.setPosition(0, 0, 50);

	acc = ofVec3f(0, 0, 0);
	vel = ofVec3f(0, 0, 0);

	life = 3;
	bExploding = false;
	bHit = false;

	createCarpetGeometry();
	createCarpetTexture();
	renderCarpetTexture();
}

void Carpet::hit()
{
	life--;
	bHit = true;
	bHitCounter = 1;

	if (life == 0) {
		explode();
	}
}

void Carpet::explode()
{
	bExploding = true;
}

void Carpet::applyForce(const ofVec3f &f)
{
	acc += f;
}

float Carpet::getNormalizedX()
{
#ifdef FLOOR_SENSOR
	float hor = tactonic->getCenterOfMass().y;
	return ofMap(hor, 0, tactonic->getNRows()-1, 0, 1);
#else
	float hor = tactonic->getCenterOfMass().x;
	return ofMap(hor, 0, tactonic->getNCols()-1, 0, 1);
#endif
}

float Carpet::getXForce()
{
	if (tactonic->getTotalForce() < 10) {
		return 0;
	}

	float x = getNormalizedX();

//	cout<<"center of mass = "<<tactonic->getCenterOfMass()<<endl;


//	return ofMap(x, 0, 1, -1000, 1000);

	float t = abs(x*2-1);
	float nf = (x<0.5)?-pow(t, 2):pow(t, 2);
	float f = ofMap(nf, -1, 1, 2000, -2000);

	cout<<"x = "<<x<<", t = "<<t<<", nf = "<<nf<<", f = "<<f<<endl;

	return f;
}

void Carpet::update(float dt)
{
	updateParams();

#define ABSOLUTE_POS
#ifdef ABSOLUTE_POS
	float targetX = ofMap(getNormalizedX(), 0, 1, 1400, -1400);
	setPosition(getX() + (targetX-prevX)*0.15f, getY(), getZ());
	prevX = getX();
	float xForce = 0;
#else
	// calculate force
	float xForce = getXForce();

	if (getX() < -1000 &&
		xForce < 0) {

		xForce = 0;
	}
	else if (getX() > 1000 &&
			 xForce > 0) {
		xForce = 0;
	}
#endif

	if (didExplode()) {
		forwardSpeed = 0;
	}

	vel += ofVec3f(xForce, 0, forwardSpeed);
	vel.limit(forwardSpeed);

	move(vel*dt);

	acc *= 0;

	// update hit counter
	if (bHit) {
		bHitCounter-=dt;
		if (bHitCounter < 0) {
			bHit = false;
		}
	}
	
	renderCarpetTexture();
}

void Carpet::draw()
{
	ofPushMatrix();
	ofMultMatrix(getLocalTransformMatrix());



	ofFill();
	ofSetColor(255);

	carpetFbo.getTextureReference().bind();

	carpetVbo.drawElements(GL_TRIANGLES, 6);

	carpetFbo.getTextureReference().unbind();


	ofPopMatrix();
}



void Carpet::createCarpetGeometry()
{
	vector<ofVec3f> verts;
	vector<ofVec3f> normals;
	vector<ofIndexType> indices;
	vector<ofVec2f> texCoords;

	verts.push_back(ofVec3f(-100, 0, 0));
	verts.push_back(ofVec3f(100, 0, 0));
	verts.push_back(ofVec3f(-100, 0, -200));
	verts.push_back(ofVec3f(100, 0, -200));

	normals.push_back(ofVec3f(0, 1, 0));
	normals.push_back(ofVec3f(0, 1, 0));
	normals.push_back(ofVec3f(0, 1, 0));
	normals.push_back(ofVec3f(0, 1, 0));

	texCoords.push_back(ofVec2f(512, 0));
	texCoords.push_back(ofVec2f(0, 0));
	texCoords.push_back(ofVec2f(512, 1024));
	texCoords.push_back(ofVec2f(0, 1024));

	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);

	carpetVbo.setVertexData(&verts[0], verts.size(), GL_STATIC_DRAW);
	carpetVbo.setNormalData(&normals[0], normals.size(), GL_STATIC_DRAW);
	carpetVbo.setTexCoordData(&texCoords[0], texCoords.size(), GL_STATIC_DRAW);
	carpetVbo.setIndexData(&indices[0], indices.size(), GL_STATIC_DRAW);
}

void Carpet::createCarpetTexture()
{
	carpetFbo.allocate(512, 1024, GL_RGBA);
}

void Carpet::renderCarpetTexture()
{
	carpetFbo.begin();

	if (bExploding || bHit) {
		float coeff = abs(sin(0.1f*ofGetFrameNum()));
		ofClear(255, 255*coeff, 255*coeff, 255);
	}
	else {
		ofClear(255, 255, 255, 255);
	}

	ofSetColor(50, 0, 200);
	ofFill();
	ofEllipse(carpetFbo.getWidth()*0.2, carpetFbo.getHeight()*0.9, carpetFbo.getWidth()*0.17, carpetFbo.getWidth()*0.17);
	ofEllipse(carpetFbo.getWidth()*0.8, carpetFbo.getHeight()*0.9, carpetFbo.getWidth()*0.17, carpetFbo.getWidth()*0.17);

	carpetFbo.end();
}



void Carpet::setupParams()
{
	RUI_NEW_GROUP("Camera Target");

	RUI_SHARE_PARAM(targetNodePos.x, -50, 50);
	RUI_SHARE_PARAM(targetNodePos.y, -100, 100);
	RUI_SHARE_PARAM(targetNodePos.z, 0, 1000);

//	RUI_NEW_GROUP("Carpet Speed");

//	RUI_SHARE_PARAM(forwardSpeed, 0, 100);

}

void Carpet::updateParams()
{
	camTargetNode.setPosition(targetNodePos);
}