#include "imageBinarization.h"

Mat removeShadow(Mat src_Image) {
//	Mat src_Image = imread("./card_image/6.jpg", IMREAD_GRAYSCALE);
	Mat dst_Image;

	Mat srcImage_f32;
	src_Image.convertTo(srcImage_f32, CV_32F);
	//int count = src_Image.rows*src_Image.cols;

	Mat A(src_Image.rows * src_Image.cols, 3, CV_32FC1);//행렬 A 생성
	Mat Z(src_Image.rows * src_Image.cols, 1, CV_32FC1);//행렬 Z결과값 생성	

	int count = 0;
	for (unsigned int i = 0; i < src_Image.rows; i++) {
		for (unsigned int j = 0; j < src_Image.cols; j++) {
			A.at<float>(count, 0) = j;
			A.at<float>(count, 1) = i;
			A.at<float>(count, 2) = 1;
			Z.at<float>(count, 0) = srcImage_f32.at<float>(i, j);
			count++;
		}
	}
	count = 0;

	float mean;
	float sum = 0;
	for (unsigned int i = 0; i < src_Image.rows; i++) {
		for (unsigned int j = 0; j < src_Image.cols; j++) {
			sum += srcImage_f32.at<float>(i, j);
		}
	}
	mean = sum / (src_Image.rows * src_Image.cols);
	Mat X = (A.t() * A).inv() * A.t() * Z;//파라미터 값 계산

	float aValue, bValue, cValue;
	aValue = X.at<float>(0);
	bValue = X.at<float>(1);
	cValue = X.at<float>(2);

	Mat m;
	srcImage_f32.convertTo(m, CV_8U);
	//m 제거된 이미지 

	for (int y = 0; y < src_Image.rows; ++y) {
		uchar* fgPtr = src_Image.ptr(y);
		for (int x = 0; x < src_Image.cols; ++x) {
			float Z1 = aValue * x + bValue * y + cValue;
			srcImage_f32.at<float>(y, x) = abs(Z1 - srcImage_f32.at<float>(y, x) + mean);// > 120 ? 255 : 0;
		}
	}
	Mat gray_img;
	srcImage_f32.convertTo(gray_img, CV_8U);
	//Printmat("inverted= ", X);
	return gray_img;
}

//void Printmat(const char* strName, Mat m)
//{
//	int x, y;
//	float fValue;
//
//	for (y = 0; y < m.rows; y++) {
//		for (x = 0; x < m.cols; x++) {
//			fValue = m.at<float>(y, x);
//		}
//		cout << endl;
//	}
//	cout << endl;
//}