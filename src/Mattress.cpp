//
//  Matress.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/10/14.
//
//

#include "Mattress.h"
#include "ofxOpenCv.h"

void Mattress::setup(TactonicInput* input)
{
	ttInput = input;

	points[0] = ofVec2f(0.3, 0.5);
	points[1] = ofVec2f(0.3, 1);
	points[2] = ofVec2f(0.7, 0.5);
	points[3] = ofVec2f(0.7, 1);

//	rect = ofRectangle(points[0], points[3]);
	activePoint = -1;

	calcMatToWorldMatrix();
}


vector<ofVec3f> Mattress::getWorldForcePoints()
{
	vector<ofVec3f> forces = ttInput->getForcePoints();
	vector<ofVec3f> worldForces;

	for (int i=0; i<forces.size(); i++)
	{
		ofVec3f wForce = forces[i] * matToWorld;
		worldForces.push_back(wForce);
	}

	return worldForces;
}


void Mattress::update(float dt)
{

}

void Mattress::draw()
{
	ofFill();

	ofSetColor(50, 150, 50, 100);
	ofBeginShape();
	ofVertex(points[0].x, points[0].y);
	ofVertex(points[2].x, points[2].y);
	ofVertex(points[3].x, points[3].y);
	ofVertex(points[1].x, points[1].y);
	ofEndShape(true);

	ofSetColor(255, 0, 0, 200);
	ofPushMatrix();
	ofMultMatrix(matToWorld);

	ttInput->draw();

	ofPopMatrix();
}

void Mattress::drawDebug()
{
	ofFill();
	ofSetColor(0, 255, 0);
	ofBeginShape();
	ofVertex(points[0].x, points[0].y);
	ofVertex(points[2].x, points[2].y);
	ofVertex(points[3].x, points[3].y);
	ofVertex(points[1].x, points[1].y);
	ofEndShape(true);

	ofSetColor(0, 0, 255);
	ofEllipse(points[0], 0.03, 0.03);
	ofEllipse(points[2], 0.03, 0.03);
	ofEllipse(points[3], 0.03, 0.03);
	ofEllipse(points[1], 0.03, 0.03);

}

void Mattress::mouseDown(const ofVec2f& p)
{
	for (int i=0; i<4; i++) {
		if (p.distance(points[i]) < 0.03) {
			activePoint = i;
			return;
		}
	}
}

void Mattress::mouseDragged(const ofVec2f& p)
{
	if (activePoint < 0) {
		return;
	}

	points[activePoint] = p;
	calcMatToWorldMatrix();
}

void Mattress::mouseUp(const ofVec2f& p)
{
	activePoint = -1;
}



void Mattress::calcMatToWorldMatrix()
{
	cv::Point2f dst[4];
	cv::Point2f src[4];

	for (int i=0; i<4; i++) {
		dst[i] = cv::Point2f(points[i].x, points[i].y);
	}

	cout<<"ttInput = "<<ttInput->getNCols()<<"x"<<ttInput->getNRows()<<endl;

	src[0] = cv::Point2f(0, 0);
	src[1] = cv::Point2f(0, ttInput->getNRows()-1);
	src[2] = cv::Point2f(ttInput->getNCols()-1, 0);
	src[3] = cv::Point2f(ttInput->getNCols()-1, ttInput->getNRows()-1);


	cv::Mat mat = getPerspectiveTransform(src, dst);

	matToWorld.set(
					  mat.at<double>(0,0), mat.at<double>(1, 0), 0, mat.at<double>(2, 0),
					  mat.at<double>(0,1), mat.at<double>(1, 1), 0, mat.at<double>(2, 1),
					  0, 0, 1, 0,
					  mat.at<double>(0,2), mat.at<double>(1, 2), 0, mat.at<double>(2, 2));

	cout<<"0x0 is at = "<<ofVec3f(0, 0, 0)*matToWorld<<endl;
	cout<<"31x15 is at = "<<ofVec3f(31, 15, 0)*matToWorld<<endl;

	//	printMatrix(projectionMat);
	//	cout<<"projection matrix = "<<projectionMat<<endl;
}
