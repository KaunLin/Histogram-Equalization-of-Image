#include <stdio.h>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("07-1before-HE-Alhambra9.bmp");
	if (!img.data)
	{
		cout << "errow!!!" << endl;
	}
	else
	{
		cout << "OK!!!" << endl;
	}

	namedWindow("input", 1);
	imshow("input", img);

	////450 cols ¼e
	////300 rows °ª
	int width = img.cols;
	int height = img.rows;
	int countB[256] = { 0 };
	int countG[256] = { 0 };
	int countR[256] = { 0 };
	int newvalueB[256] = { 0 };
	int newvalueG[256] = { 0 };
	int newvalueR[256] = { 0 };
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int nowpixelB = img.at<Vec3b>(i, j)[0];
			int nowpixelG = img.at<Vec3b>(i, j)[1];
			int nowpixelR = img.at<Vec3b>(i, j)[2];
			countB[nowpixelB]++;
			countG[nowpixelG]++;
			countR[nowpixelR]++;
		}
	}
	float pixel = img.cols * img.rows;
	float sumB = 0, sumG = 0, sumR = 0;
	for (int i = 0; i < 256; i++)
	{
		sumB += countB[i];
		sumG += countG[i];
		sumR += countR[i];
		newvalueB[i] = sumB / pixel * 255;
		newvalueG[i] = sumG / pixel * 255;
		newvalueR[i] = sumR / pixel * 255;
	}
	
	Mat dst;
	dst.create(img.size(), img.type());
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int oldvalueB = img.at<Vec3b>(i, j)[0];
			int oldvalueG = img.at<Vec3b>(i, j)[1];
			int oldvalueR = img.at<Vec3b>(i, j)[2];
			int newB = newvalueB[oldvalueB];
			int newG = newvalueG[oldvalueG];
			int newR = newvalueR[oldvalueR];
			dst.at<Vec3b>(i, j)[0] = newB;
			dst.at<Vec3b>(i, j)[1] = newG;
			dst.at<Vec3b>(i, j)[2] = newR;
		}
	}
	
	namedWindow("output", 1);
	imshow("output", dst);

	imwrite("07-2after-HE-Alhambra9.bmp", dst);
	waitKey(0);
}