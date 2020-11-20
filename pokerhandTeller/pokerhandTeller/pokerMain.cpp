#include "pokerMain.h"
#include "cardDetect.h"
#include "videocapture.h"

int main() {

	Mat img_src = imread("./card_image/img8.png");
	if (img_src.empty()) {
		printf("empty");
		return -1;
	}

	Card card(img_src);
	card.preprocess();
	card.match_number();
	card.match_suit();

	//videoncapture_basic();
	return 0;
}