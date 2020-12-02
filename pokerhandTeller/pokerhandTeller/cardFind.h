#pragma once

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

#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<cstdio>
#include<math.h>
#include<algorithm>

using namespace cv;
using namespace std;

bool compare_approx_x(Point2f a, Point2f b);
bool compare_approx_y(Point2f a, Point2f b);
vector<Mat> find_cards(Mat& img);