#include "pokerMain.h"

int main() {
	int x;
	cin >> x;

	while (x == 1) {
		vector<string> temp;

		temp = randomCards();
		
		system("CLS");

		cout << endl;
		for (vector<string>::iterator iter = temp.begin(); iter != temp.end(); iter++)
			cout << getPairToString(getPairToInt((*iter).at(0)) + 2) << getSuitToString(getSuitToInt((*iter).at(1))) << ", ";
		cout << endl;
		cout << "==================================" << endl;

		Rank a = checkPokerHand(temp);

		cout << getHandToString(a.rank) << endl;
		cout << "Number: " << getPairToString(a.high_pair) << endl;
		cout << "Suit  : " << getSuitToString(a.high_suit) << endl;
		
		cin >> x;
	}
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