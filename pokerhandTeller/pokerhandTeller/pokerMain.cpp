#include "pokerMain.h"
#include "shapeDetect.h"
#include "videocapture.h"

int main() {

	Mat img_src = imread("./card image/img3.png");
	if (img_src.empty()) {
		printf("empty");
		return -1;
	}

	Card card(img_src);
	card.preprocess();
	card.match();

	//videoncapture_basic();
	return 0;
}