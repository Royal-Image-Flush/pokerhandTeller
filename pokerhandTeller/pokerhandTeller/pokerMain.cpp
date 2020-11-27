#include "pokerMain.h"
#include "cardDetect.h"
#include "videocapture.h"
#include "pokerHandCalc.h"

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

vector<string> randomCards() {
	vector<string> temp;
	
	string first = "23456789TJQKA";
	string second = "SDHC";
	string new_string;
	bool sameValue;
	int a, b = 0;
	srand((unsigned int)time(0));
	a = rand() % 13;
	b = rand() % 4;
	new_string.push_back(first.at(a));
	new_string.push_back(second.at(b));

	temp.push_back(new_string);

	while (temp.size() < 7) {
		sameValue = false;
		a = rand() % 13;
		b = rand() % 4;
		new_string[0] = first.at(a);
		new_string[1] = second.at(b);

		for (vector<string>::iterator iter = temp.begin(); iter != temp.end(); iter++) {
			if (new_string == (*iter)) {
				sameValue = true;
				break;
			}
		}
		if (!sameValue)
			temp.push_back(new_string);
	}
	return temp;
}