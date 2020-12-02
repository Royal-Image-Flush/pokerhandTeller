#include "pokerMain.h"
#include "cardFind.h"
#include "cardDetect.h"
#include "pokerHandCalc.h"
#include "videocapture.h"
#include "imageBinarization.h"


int main() {

	Mat img = imread("./card_image/img.jpg", IMREAD_GRAYSCALE);
	int width = img.cols;
	int height = img.rows;

	if (img.empty()) {
		cout << "이미지를 찾을 수 없음" << endl;
		return -1;
	}

	img = removeShadow(img);
	imshow("Image", img);
	waitKey();

	/* 카드에서 숫자와 모양 인식 */
	vector<Mat> img_cards;
	vector<string> card_info;

	/* find cards in images */
	
	vector<Mat> img_cards;

	img_cards = find_cards(img);


	/* detect numbers and suits on cards */

	vector<string> card_info;

	for (int i = 0; i < img_cards.size(); i++) {
		Card card(img_cards[i]);

		card.preprocess();
		card_info.push_back(card.match_number() + card.match_suit());

		cout << "card" << to_string(i + 1) + " : " + card_info[i] << endl;
	}


	/* calculate ranks of hands */

	if (card_info.size() == 7) {
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
