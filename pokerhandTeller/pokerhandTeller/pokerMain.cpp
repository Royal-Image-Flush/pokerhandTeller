#include "pokerMain.h"
#include "findCard.h"
#include "cardDetect.h"
#include "pokerHandCalc.h"
#include "videocapture.h"
#include "imageBinarization.h"


int main() {

	/* 이미지에서 카드 인식 */
	Mat img;
	int width = img.cols;
	int height = img.rows;

	img = imread("./card_image/cards.jpg", IMREAD_GRAYSCALE);
	if (img.empty()) {
		cout << "이미지를 찾을 수 없음" << endl;
		return -1;
	}

	img = removeShadow(img);
	imshow("Image", img);
	waitKey();

	/* 카드에서 숫자와 모양 인식 */
	Mat* img_cards;
	vector<string> card_info;

	img_cards = find_cards(&img);

	for (int i = 0; i < sizeof(img_cards) / sizeof(img_cards[0]); i++) {
		Card card(img_cards[i]);

		card.preprocess();
		card_info.push_back(card.match_number() + card.match_suit());

		cout << card_info[i] << endl;
	}

	/* 어떤 패인지 계산 */

	if (card_info.size()) {
		system("CLS");

		cout << endl;
		for (vector<string>::iterator iter = card_info.begin(); iter != card_info.end(); iter++)
			cout << getPairToString(getPairToInt((*iter).at(0)) + 2) << getSuitToString(getSuitToInt((*iter).at(1))) << ", ";
		cout << endl;
		cout << "==================================" << endl;

		Rank a = checkPokerHand(card_info);

		cout << getHandToString(a.rank) << endl;
		cout << "Number: " << getPairToString(a.high_pair) << endl;
		cout << "Suit  : " << getSuitToString(a.high_suit) << endl;
	}

	return 0;
}
