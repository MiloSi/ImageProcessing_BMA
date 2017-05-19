#pragma once

#pragma warning(disable : 4996)
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;


/*
	Studied (Exactly Learned) Multimedia using OpenCV
	Block Matching Algorithm
*/



int main(int argc, char** argv)
{
	String fileName1, fileName2;

	fileName1 = "caltrain000.png";
	fileName2 = "caltrain001.png";

	Point2i p;

	int Max = 655360;
	int tempMax = 0;

	Mat mat1 = imread(fileName1, IMREAD_GRAYSCALE);
	Mat mat2 = imread(fileName2, IMREAD_GRAYSCALE);

	if (mat1.empty() || mat2.empty())
	{
		cerr << "ERROR" << endl;
		return 1;
	}

	Mat dst(mat1.rows, mat1.cols, CV_8U, Scalar(0));
	for (int y = 0; y < mat1.rows - 16; y = y + 16)
	{
		for (int x = 0; x < mat1.cols - 16; x = x + 16)
		{
			Mat from(mat1, Rect(x, y, 16, 16));

			int i = x - 8;
			int j = y - 8;

			if (i < 0) i = 0;
			if (j < 0) j = 0;

			int width = x + 24;
			int height = y + 24;

			if (width >= mat1.cols)
				height = mat1.cols - 1;
			if (height >= mat1.rows)
				height = mat1.rows - 1;

			Max = 655360;
			p.x = 0;
			p.y = 0;

			for (int y1 = j; y1 < height - 16; y1++)
			{
		
				for (int x1 = i; x1 < width - 16; x1++)
				{
					Mat to(mat2, Rect(x1, y1, 16, 16));
					tempMax = 0;
					for (int k = 0; k < 16; k++)
					{
						for (int l = 0; l < 16; l++)
						{

							int temp2 = (int) from.at<uchar>(k, l) - (int) to.at<uchar>(k, l);
							if (temp2 < 0) temp2 = temp2 * -1;
							tempMax += temp2;
						}
					}
					if (Max > tempMax) {
						Max = tempMax;
						p.x = x1;
						p.y = y1;
					}
				}
			}
			int mx = p.x - x; 
			int my = p.y - y;

			int mag = sqrt(pow(mx, 2) + pow(my, 2));

			for (int y1 = y; y1 < mat1.rows; y1++)
			{
				for (int x1 = x; x1 < mat1.cols; x1++)
				{
					dst.at<uchar>(y1, x1) = (uchar)(mag * 16);
				}
			}
			mag = 0;
		}
	}

	imshow("dst", dst);

	waitKey(0);


}