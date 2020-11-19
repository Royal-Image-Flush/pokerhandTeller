#include "pokerHandCalc.h"

// A23456789TJQKA SDHC
// compare_list: 23456789TJQKA SDHC
int checkPokerHand(vector<string> a) {
	string input;
	string result;
	string pair;
	string suit;

	for (vector<string>::iterator iter = a.begin(); iter != a.end(); iter++)
		input += *iter;
	
	for (int i = 0; i < COMPARE_LIST.length(); i++)
		result += count(input, COMPARE_LIST.at(i));
	result.insert(0, 1, result.at(12));

	pair = result.substr(0, 14);
	suit = result.substr(14, 4);

	
	return calcRank(pair, suit);
}


/*
Straight 이상의 족보를 두 명 이상이 가지고 있을 경우
제일 높은 숫자의 모양순 대로 순위 (스-다-하-클)


10 Royal Flush		- 10 J Q K A 같은 모양
09 Straight Flush	- Straight + Flush
08 Four Of A Kind	- 네 개 같은 숫자 @
07 Full House		- One Pair + Three Of A Kind @
06 Flush			- 같은 무늬 다섯 장 @

Mountain		- 10 J Q K A @
05 Straight		- 연속 숫자 다섯 개 @
Back Straight	- A 2 3 4 5 @

04 Three Of A Kind - 세 개 같은 숫자 @
03 Two Pair		- One Pair 두 개 @
02 One Pair		- 두 개 같은 숫자 @
01 High Card		- 제일 높은 숫자 @
*/
int calcRank(string pair, string suit) {
	if (pair.find('4') != string::npos)
		return 8;
	if (pair.find('3') != string::npos && pair.find('2') != string::npos)
		return 7;
	if (suit.find('5') != string::npos)
		return 6;
	if (checkStraight(pair))
		return 5;
	if (pair.find('3') != string::npos)
		return 4;
	if (count(pair, '2') == 2)
		return 3;
	if (count(pair, '2') == 1)
		return 2;

	return 1;
}

bool checkStraight(string pair) {
	int count = 0;
	int maxCount = 0;
	int number = 0;

	for (int i = 0; pair[i]; i++) {
		if (pair[i] != '0') {
			count++;

			if (count > maxCount) {
				maxCount = count;
				number = i + 1;
			}
		}
		else
			count = 0;
	}

	if (count >= 5)
		return true;
	return false;
}

int count(string input, char charToFind) {
	int result = 0;
	for (int i = 0; input[i]; i++)
		if (input[i] == charToFind)
			result++;
	return result;
}