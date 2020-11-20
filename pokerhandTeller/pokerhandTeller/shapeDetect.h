#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace cv;
using namespace std;

class Card {
private:
	Mat img_scr;
	int width;
	int height;

	Mat img_suit;
	Mat img_num;
	string suit;
	int num;

public:
	Card(Mat img);
	//void setLabel(Mat& image, string str, vector<Point> contour);
	//int GetAngleABC(Point a, Point b, Point c);
	void preprocess();
	void match();
};