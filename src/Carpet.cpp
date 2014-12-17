//
//  Carpet.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#include "Carpet.h"
#include "ofxRemoteUIServer.h"


void Carpet::setup(TactonicInput* tt)
{
	tactonic = tt;

	setPosition(0, 0, 0);

	camTargetNode.setParent(*this);
	camTargetNode.setPosition(0, 0, 100);

	acc = ofVec3f(0, 0, 0);
	vel = ofVec3f(0, 0, 0);

	createCarpetGeometry();
	createCarpetTexture();
	renderCarpetTexture();
}

void Carpet::applyForce(const ofVec3f &f)
{
	acc += f;
}

void Carpet::update(float dt)
{
	updateParams();

	// calculate force
	float xForce = 0;
	float hor = tactonic->getCenterOfMass().x;
	cout<<"center of mass = "<<tactonic->getCenterOfMass()<<endl;
	xForce = ofMap(hor, 0, tactonic->getNCols(), 1000, -1000);

	vel += ofVec3f(xForce, 0, forwardSpeed);
	vel.limit(forwardSpeed);

	move(vel*dt);

	acc *= 0;
}

void Carpet::draw()
{
	ofPushMatrix();
	ofMultMatrix(getLocalTransformMatrix());



	ofFill();
	ofSetColor(50);

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
	verts.push_back(ofVec3f(-100, 0, -400));
	verts.push_back(ofVec3f(100, 0, -400));

	normals.push_back(ofVec3f(0, 1, 0));
	normals.push_back(ofVec3f(0, 1, 0));
	normals.push_back(ofVec3f(0, 1, 0));
	normals.push_back(ofVec3f(0, 1, 0));

	texCoords.push_back(ofVec2f(512, 0));
	texCoords.push_back(ofVec2f(0, 0));
	texCoords.push_back(ofVec2f(512, 2048));
	texCoords.push_back(ofVec2f(0, 2048));

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
	carpetFbo.allocate(512, 2048, GL_RGBA);
}

void Carpet::renderCarpetTexture()
{
	carpetFbo.begin();
	ofClear(128, 0, 128, 255);


	ofSetColor(200, 0, 0);
	ofFill();
	ofRect(50, 50, 50, 50);

	ofSetColor(0, 200, 0);
	ofFill();
	ofRect(carpetFbo.getWidth()-100, carpetFbo.getHeight()-100, 50, 50);

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