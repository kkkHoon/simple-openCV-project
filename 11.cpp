
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void cvtBGR2CMY(Mat *src, Mat *dst);
void cvtCMY2BGR(Mat *src, Mat *dst);
void BGR_Intensitiy(Mat *src, float k);
void YCbCr_Intensitiy(Mat *src, float k);
void CMY_Intensitiy(Mat *src, float k);
void HSV_Intensity(Mat *src, float k);

int main(int argc, char** argv)
{
	string imageName("./data/Lena_color.png");
	float k;

	printf("Please type k(0 <= k <= 1)");
	scanf("%f", &k);
	if (!(0 <= k && k <= 1))
		return 0;


	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat RGB, YCbCr, CMY, HSV, CMY2BGR;	
	RGB = imread(imageName.c_str(), IMREAD_COLOR);

	if (RGB.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	YCbCr = Mat::zeros(RGB.size(), RGB.type());
	CMY = Mat::zeros(RGB.size(), RGB.type());
	HSV = Mat::zeros(RGB.size(), RGB.type());
	CMY2BGR = Mat::zeros(RGB.size(), RGB.type());

	cvtColor(RGB, YCbCr, CV_BGR2YCrCb);
	cvtBGR2CMY(&RGB, &CMY);
	cvtColor(RGB, HSV, CV_BGR2HSV);

	//Intensity change
	BGR_Intensitiy(&RGB, k);
	YCbCr_Intensitiy(&YCbCr, k);
	CMY_Intensitiy(&CMY, k);
	HSV_Intensity(&HSV, k);

	//conver other color spaces to RGB color space
	cvtColor(YCbCr, YCbCr, CV_YCrCb2BGR);
	cvtCMY2BGR(&CMY, &CMY2BGR);
	cvtColor(HSV, HSV, CV_HSV2BGR);
	
	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", RGB);

	namedWindow("YCbCr", WINDOW_AUTOSIZE);
	imshow("YCbCr", YCbCr);

	namedWindow("CMY", WINDOW_AUTOSIZE);
	imshow("CMY", CMY2BGR);

	namedWindow("HSV", WINDOW_AUTOSIZE);
	imshow("HSV", HSV);

	waitKey(0);

	return 0;
}

void cvtBGR2CMY(Mat *src, Mat *dst)
{
	Mat src_clone = src->clone();
	for (int row = 0; row < src->rows; row++)
	{
		for (int col = 0; col < src->cols; col++)
		{
			dst->at<Vec3b>(row, col)[0] = saturate_cast<uchar>(255 - src_clone.at<Vec3b>(row, col)[0]); // R channel -> C channel
			dst->at<Vec3b>(row, col)[1] = saturate_cast<uchar>(255 - src_clone.at<Vec3b>(row, col)[1]); // G channel -> M channel
			dst->at<Vec3b>(row, col)[2] = saturate_cast<uchar>(255 - src_clone.at<Vec3b>(row, col)[2]); // B channel -> Y channel
		}
	}
}

void cvtCMY2BGR(Mat *src, Mat *dst)
{
	Mat src_clone = src->clone();
	for (int row = 0; row < src->rows; row++)
	{
		for (int col = 0; col < src->cols; col++)
		{
			dst->at<Vec3b>(row, col)[0] = saturate_cast<uchar>(255 - src_clone.at<Vec3b>(row, col)[0]); // V channel -> B channel
			dst->at<Vec3b>(row, col)[1] = saturate_cast<uchar>(255 - src_clone.at<Vec3b>(row, col)[1]); // M channel -> G channel
			dst->at<Vec3b>(row, col)[2] = saturate_cast<uchar>(255 - src_clone.at<Vec3b>(row, col)[2]); // C channel -> R channel
		}
	}
}

void BGR_Intensitiy(Mat *src, float k)
{
	for (int row = 0; row < src->rows; row++)
	{
		for (int col = 0; col < src->cols; col++)
		{
			for (int ch = 0; ch < 3; ch++)
				src->at<Vec3b>(row, col)[ch] = saturate_cast<uchar>(src->at<Vec3b>(row, col)[ch] * k);
		}
	}
}

void YCbCr_Intensitiy(Mat *src, float k)
{
	for (int row = 0; row < src->rows; row++)
	{
		for (int col = 0; col < src->cols; col++)
		{
			src->at<Vec3b>(row, col)[0] = saturate_cast<uchar>(src->at<Vec3b>(row, col)[0] * k);
		}
	}
}

void CMY_Intensitiy(Mat *src, float k)
{
	for (int row = 0; row < src->rows; row++)
	{
		for (int col = 0; col < src->cols; col++)
		{
			for (int ch = 0; ch < 3; ch++)
				src->at<Vec3b>(row, col)[ch] = saturate_cast<uchar>(src->at<Vec3b>(row, col)[ch] * k + 255*(1 - k));
		}
	}
}

void HSV_Intensity(Mat *src, float k)
{
	for (int row = 0; row < src->rows; row++)
	{
		for (int col = 0; col < src->cols; col++)
		{
			src->at<Vec3b>(row, col)[2] = saturate_cast<uchar>(src->at<Vec3b>(row, col)[2] * k);
		}
	}
}