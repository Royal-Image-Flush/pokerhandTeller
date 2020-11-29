#include<core.hpp>
#include<imgproc.hpp>
#include<highgui.hpp>
#include<iostream>
#include<cstdio>
#include<math.h>
#include<algorithm>

using namespace cv;
using namespace std;

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
bool compare_approx_x(Point2f a, Point2f b) {
	return a.x < b.x;
}
bool compare_approx_y(Point2f a, Point2f b) {
	return a.y < b.y;
}

void find_cards(Mat* img) {
	vector<vector<Point> > contours;
	vector<Point2f> approx;

	Mat img_gray;
	Mat detected_edges;
	Mat cards[9];

	int lowThreshold = 50;
	int highThreshold = 150;


	/*gray scale image*/
	cvtColor(*img, img_gray, COLOR_BGR2GRAY);
	/*detect edges*/
	blur(img_gray, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, lowThreshold, highThreshold, 3);
	/*transform edges into coordinates*/
	findContours(detected_edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

	for (int i = 0; i < contours.size(); i++) {
		/*find vertex using contours*/
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);

		///*sort order of vertex*/
		int max_index[2];
		float length, max_width, max = 0;
		Point2f temp(0, 0);
		sort(approx.begin(), approx.end(), compare_approx_y);
		sort(approx.begin(), approx.end(), compare_approx_x);
		temp = approx[2]; approx[2] = approx[3]; approx[3] = temp;

		/*find longest edge*/
		for (int i = 0; i < 4; i++) {
			length = sqrt(pow(approx[i % 4].x - approx[(i + 1) % 4].x, 2) + pow(approx[i % 4].y - approx[(i + 1) % 4].y, 2));
			if (length > max) {
				max = length;
				max_index[0] = i % 4;
				max_index[1] = (i + 1) % 4;
			}
		}

		/* 세로변이 가장 긴 형태일 경우*/
		if ((max_index[0] == 0 && max_index[1] == 1) ||
			(max_index[0] == 2 && max_index[1] == 3)) {
			max_width = max / 88 * 62;
		}
		/* 가로변이 가장 긴 형태일 경우*/
		else {
			max_width = max / 62 * 88;
		}
		
		vector<Point2f> vertex{
			Point2f(0, 0), Point2f(0, max),
			Point2f(max_width, max), Point2f(max_width , 0)
		};
		Mat affine = getPerspectiveTransform(approx, vertex);
		warpPerspective(*img, cards[i], affine, Size(max_width, max));
		resize(cards[i], cards[i], Size(62, 88), 62 / max_width, 88 / max);
	}

	/* 테스트 출력*/
	for (int i = 0; i < contours.size(); i++) {
		cout << i << " image" << endl;
  		imshow("Result", cards[i]);
		waitKey(0);
	}
}


int main() {
	Mat img;

	int width = img.cols;
	int height = img.rows;
	
	img = imread("C:/input/cards_soft.jpg", IMREAD_COLOR);
	if (img.empty()) {
		cout << "이미지를 찾을 수 없음" << endl;
		return 1;
	}

	find_cards(&img);

	return 0;
}
