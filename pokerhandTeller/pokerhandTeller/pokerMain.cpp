#include "pokerMain.h"
#include "cardFind.h"
#include "cardDetect.h"
#include "pokerHandCalc.h"
#include "videocapture.h"
#include "imageBinarization.h"


int main() {
	Mat frame;
	//--- INITIALIZE VIDEOCAPTURE
	VideoCapture cap;
	// open the default camera using default API
	// cap.open(0);
	// OR advance usage: select any API backend
	int deviceID = 0;             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	// open selected camera using selected API
	cap.open(deviceID, apiID);
	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	//--- GRAB AND WRITE LOOP
	cout << "Start grabbing" << endl
		<< "Press any key to terminate" << endl;
	for (;;)
	{
		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}

		//Mat img = imread("./card_image/img.jpg", IMREAD_COLOR);
		int width = frame.cols;
		int height = frame.rows;

		//if (img.empty()) {
		//	cout << "이미지를 찾을 수 없음" << endl;
		//	return -1;
		//}

		frame = removeShadow(frame);
		//imshow("Image", frame);
		//waitKey();


		/* find cards in images */

		vector<Mat> img_cards;

		img_cards = find_cards(frame);


		/* detect numbers and suits on cards */

		if (img_cards.size() > 0) {
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
		}

		// show live and wait for a key with timeout long enough to show images
		imshow("Live", frame);
		if (waitKey(5) >= 0)
			break;
	}

	return 0;
}
