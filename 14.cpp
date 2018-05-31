
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Point2f srcTri[3];
	Point2f dstTri[3];

	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	Mat wrap_mat(2, 3, CV_32FC1);
	Mat result;
	namedWindow("edges", 1);

	

	for (;;)
	{
		Mat frame;
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		result = Mat::zeros(frame.size(), frame.type());

		srcTri[0] = Point2f(0, 0);
		srcTri[1] = Point2f(frame.cols - 1, 0);
		srcTri[2] = Point2f(0, frame.rows - 1);

		dstTri[0] = Point2f(frame.cols*0.0, frame.rows*0.15);
		dstTri[1] = Point2f(frame.cols*0.7, frame.rows*0.2);
		dstTri[2] = Point2f(frame.cols*0.38, frame.rows*0.7);
		wrap_mat = getAffineTransform(srcTri, dstTri);
		warpAffine(frame, result, wrap_mat, result.size());

		imshow("edges", result);
		if (waitKey(30) >= 0)
			printf("");
	}
	return 0;
}

