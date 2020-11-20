#include<core.hpp>
#include<imgproc.hpp>
#include<highgui.hpp>
#include<iostream>
#include<cstdio>
#include<math.h>

using namespace cv;
using namespace std;

enum point_pos {
	UP_LEFT,
	UP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};
//opencv 사용 함수
//카드 크기 62*88
/*
arcLength()함수는 contours 둘레의 길이를 계산하는 함수이다. 
parameter1: 둘레를 계산할 contour이다.
parameter2: contour가 폐곡선인지 계곡선인지 여부를 타나낸다. True는 폐곡선을 의미한다. 
0.1: 둘레의 길이에 10%를 나타낸다. 

approxPolyDP()함수는 다각형을 대상으로 꼭지점을 점점 줄여나가는 함수이다. 
epsilon(오차)만큼을 최대한으로 해서 꼭지점을 줄여나간다. 
epsilon값이 작을수록 원본과 비숫한 결과가 도출되고 
epsilon(오차)값이 크면 클수록 꼭지점의 개수가 점점 더 줄어든다. 
epsilon이 너무 크면 꼭지점이 계속해서 줄어나가게 되니까 결국 꼭지점의 개수가 0인 점으로 결과가 나올 수 있다. 
parameter1에는 꼭지점의 개수를 줄일 contour를 넣고 
parameter2로 줄여나갈 오차 epsilon을 넣고 
parameter3는 폐곡선인지 계곡선인지 여부를 넣는다.
*/

void find_edge(Mat* img) {
	vector<vector<Point> > contours;
	vector<Point2f> approx;

	Mat img_gray;
	Mat detected_edges;
	Mat img_result = (*img).clone();

	int lowThreshold = 50;
	int highThreshold = 150;

	cvtColor(*img, img_gray, COLOR_BGR2GRAY);
	blur(img_gray, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, lowThreshold, highThreshold, 3);
	findContours(detected_edges, contours, RETR_LIST, CHAIN_APPROX_SIMPLE, Point());

	for (size_t i = 0; i < contours.size(); i++){
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);
	}

	float length, max_width, max =0;
	for (int i = 0; i < 4; i++) {
		length = sqrt(pow(approx[i%4].x - approx[(i+1)%4].x, 2) + pow(approx[i % 4].y - approx[(i + 1) % 4].y, 2));
		if (length > max)
			max = length;
	}

	max_width = max / 88 * 62;
	vector<Point2f> vertex{ 
		Point2f(0, 0), Point2f(0, max), 
		Point2f(max_width, max), Point2f(max_width , 0) 
	};
	Mat affine = getPerspectiveTransform(approx, vertex);
	warpPerspective(*img, *img, affine, Size(max_width,max));
	resize(*img, *img, Size(310, 440), 310 / max_width, 440 / max);
}


int main() {
	Mat img;

	int width = img.cols;
	int height = img.rows;
	
	img = imread("C:/input/card_5.jpg", IMREAD_COLOR);
	if (img.empty()) {
		cout << "이미지를 찾을 수 없음" << endl;
		return 1;
	}

	find_edge(&img);
	imshow("Result", img);

	waitKey(0);
	return 0;
}
