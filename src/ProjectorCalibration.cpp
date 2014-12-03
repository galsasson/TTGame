//
//  ProjectorCalibration.cpp
//  tacvis
//
//  Created by Gal Sasson on 11/28/14.
//
//

#include "ProjectorCalibration.h"


#define POINT_SIZE	0.03

void ProjectorCalibration::setup()
{
	toScreenMat.makeIdentityMatrix();
	toScreenMat.scale(ofGetWindowWidth(), ofGetWindowHeight(), 1);
	projectionMat.makeIdentityMatrix();

	points[0] = ofVec2f(0.2, 0.1);
	points[1] = ofVec2f(0.2, 0.9);
	points[2] = ofVec2f(0.8, 0.1);
	points[3] = ofVec2f(0.8, 0.9);

	activePoint = -1;
	calcProjectionMatrix();
}

void ProjectorCalibration::draw()
{
	ofPushMatrix();
//	ofMultMatrix(projectionMat);
	ofMultMatrix(toScreenMat);

	ofFill();
	ofSetColor(255);
	for (int i=0; i<4; i++) {
		ofEllipse(points[i], POINT_SIZE, POINT_SIZE);
	}

	// draw grid
	ofMultMatrix(projectionMat);
	ofSetLineWidth(2);
	for (float i=0; i<=1.01; i+=0.1f)
	{
		ofLine(0, i, 1, i);
		ofLine(i, 0, i, 1);
	}


	ofPopMatrix();
}


void ProjectorCalibration::calcProjectionMatrix()
{
	cv::Point2f dst[4];
	cv::Point2f src[4];
	for (int i=0; i<4; i++) {
		dst[i] = cv::Point2f(points[i].x, points[i].y);
	}

	src[0] = cv::Point2f(0, 0);
	src[1] = cv::Point2f(0, 1);
	src[2] = cv::Point2f(1, 0);
	src[3] = cv::Point2f(1, 1);


	cv::Mat mat = getPerspectiveTransform(src, dst);

	projectionMat.set(
		mat.at<double>(0,0), mat.at<double>(1, 0), 0, mat.at<double>(2, 0),
		mat.at<double>(0,1), mat.at<double>(1, 1), 0, mat.at<double>(2, 1),
		0, 0, 1, 0,
		mat.at<double>(0,2), mat.at<double>(1, 2), 0, mat.at<double>(2, 2));

	printf("Projection Matrix:\n");
	printMatrix(projectionMat);
//	cout<<"projection matrix = "<<projectionMat<<endl;
}


void ProjectorCalibration::mouseDown(int x, int y)
{
	ofVec2f local = toLocal(ofVec2f(x, y));

	for (int i=0; i<4; i++) {
		if (local.distance(points[i]) < POINT_SIZE) {
			activePoint = i;
			return;
		}
	}
}


void ProjectorCalibration::mouseDrag(int x, int y)
{
	if (activePoint < 0) {
		return;
	}

	ofVec2f local = toLocal(ofVec2f(x, y));
	points[activePoint] = local;

	calcProjectionMatrix();
}

void ProjectorCalibration::mouseUp(int x, int y)
{
	activePoint = -1;
}


ofVec2f ProjectorCalibration::toLocal(const ofVec2f& p)
{
	return  (ofVec3f)p * toScreenMat.getInverse();
}

ofVec2f ProjectorCalibration::getProj(const ofVec2f &p)
{
	return (ofVec3f)p * projectionMat;
}


void ProjectorCalibration::printMatrix(const ofMatrix4x4 &mat)
{
	printf("\t\t%.04f\t\t%.04f\t\t%.04f\t\t%.04f\n",
		   mat.getRowAsVec4f(0).x,
		   mat.getRowAsVec4f(0).y,
		   mat.getRowAsVec4f(0).z,
		   mat.getRowAsVec4f(0).w
		   );
	printf("\t\t%.04f\t\t%.04f\t\t%.04f\t\t%.04f\n",
		   mat.getRowAsVec4f(1).x,
		   mat.getRowAsVec4f(1).y,
		   mat.getRowAsVec4f(1).z,
		   mat.getRowAsVec4f(1).w
		   );
	printf("\t\t%.04f\t\t%.04f\t\t%.04f\t\t%.04f\n",
		   mat.getRowAsVec4f(2).x,
		   mat.getRowAsVec4f(2).y,
		   mat.getRowAsVec4f(2).z,
		   mat.getRowAsVec4f(2).w
		   );
	printf("\t\t%.04f\t\t%.04f\t\t%.04f\t\t%.04f\n",
		   mat.getRowAsVec4f(3).x,
		   mat.getRowAsVec4f(3).y,
		   mat.getRowAsVec4f(3).z,
		   mat.getRowAsVec4f(3).w
		   );
}

