#include "pokerMain.h"

int main() {
	vector<string> temp;

	temp.push_back("AC");
	temp.push_back("2C");
	temp.push_back("5C");
	temp.push_back("TC");
	temp.push_back("4C");
	temp.push_back("4D");
	temp.push_back("3H");

	int a = checkPokerHand(temp);
	cout << a;
	return 0;
}