#include "pokerMain.h"
#include "cardFind.h"
#include "cardDetect.h"
#include "pokerHandCalc.h"
#include "cardDrawBoundary.h"
#include "imageBinarization.h"


int main() {

	vector<string> card_info;
	vector<vector<Point>> ccontours;

	Mat frame;
	VideoCapture cap;

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


	string myText;
	/// Text Location
	cv::Point myPoint;
	myPoint.x = 10;
	myPoint.y = 40;

	/// Font Face
	int myFontFace = 2;

	/// Font Scale
	double myFontScale = 1.2;

	int curCardSize = 0;
	for (;;)
	{
		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		//resize(frame, frame, Size(960, 720), 0, 0, INTER_LINEAR);

		//Mat img = imread("./card_image/img.jpg", IMREAD_COLOR);
		int width = frame.cols;
		int height = frame.rows;

		/* find cards in images */

		vector<Mat> img_cards;

		img_cards = find_cards(frame, ccontours);
		

		/* detect numbers and suits on cards */

		if (img_cards.size() != 0 && curCardSize != img_cards.size() && img_cards.size() < 8) {
			card_info.erase(card_info.begin(), card_info.end());

			for (int i = 0; i < img_cards.size(); i++) {
				Card card(img_cards[i]);
				
				if (card.preprocess()) {
					card_info.push_back(card.match_number() + card.match_suit());
				}
				else
					cout << "error" << endl;
			}

			curCardSize = img_cards.size();

			/* calculate ranks of hands */

			//system("CLS");
			/*cout << endl;*/
			for (vector<string>::iterator iter = card_info.begin(); iter != card_info.end(); iter++)
				cout << getPairToString(getPairToInt((*iter).at(0)) + 2) << getSuitToString(getSuitToInt((*iter).at(1))) << ", ";
			//cout << endl;
			//cout << "==================================" << endl;

			Rank a = checkPokerHand(card_info);

			//cout << getHandToString(a.rank) << endl;
			//cout << "Number: " << getPairToString(a.high_pair) << endl;
			//cout << "Suit  : " << getSuitToString(a.high_suit) << endl;

			myText = "Rank: " + getHandToString(a.rank) + "(" + getPairToString(a.high_pair) + ", " + getSuitToString(a.high_suit) + ")";
			
		}
		else if (img_cards.size() == 0)
			curCardSize = 0;


		drawCard(frame, ccontours, card_info);	
		putText(frame, myText, myPoint, myFontFace, myFontScale, Scalar::all(255));

		ccontours.erase(ccontours.begin(), ccontours.end());

		// show live and wait for a key with timeout long enough to show images
		imshow("Live", frame);
		if (waitKey(5) >= 0)
			break;
	}

	return 0;
}
