#include "pokerHandCalc.h"

string getHandToString(int rank) {
	switch (rank) {
	case 1:
		return "High Card";
	case 2:
		return "One Pair";
	case 3:
		return "Two Pair";
	case 4:
		return "Three Of A Kind";
	case 5:
		return "Straight";
	case 6:
		return "Flush";
	case 7:
		return "Full House";
	case 8:
		return "Four Of A Kind";
	case 9:
		return "Straight Flush";
	case 10:
		return "Royal Flush";
	}
}

string getSuitToString(int pair) {
	switch (pair) {
		case 0:
			return "♣";
		case 1:
			return "♡";
		case 2:
			return "◇";
		case 3:
			return "♠";
		default:
			return "";
	}
}
string getPairToString(int pair) {
	switch (pair) {
		case 14:
			return "A";
		case 2:
			return "2";
		case 3:
			return "3";
		case 4:
			return "4";
		case 5:
			return "5";
		case 6:
			return "6";
		case 7:
			return "7";
		case 8:
			return "8";
		case 9:
			return "9";
		case 10:
			return "10";
		case 11:
			return "J";
		case 12:
			return "Q";
		case 13:
			return "K";
		default:
			return "";
	}
}

int getPairToInt(char pair) {
	switch (pair) {
		case 'A':
			return 12;
		case '2':
			return 0;
		case '3':
			return 1;
		case '4':
			return 2;
		case '5':
			return 3;
		case '6':
			return 4;
		case '7':
			return 5;
		case '8':
			return 6;
		case '9':
			return 7;
		case 'T':
			return 8;
		case 'J':
			return 9;
		case 'Q':
			return 10;
		case 'K':
			return 11;
		default:
			return NULL;
	}
}

int getSuitToInt(char suit) {
	switch (suit) {
		case 'S':
			return 3;
		case 'D':
			return 2;
		case 'H':
			return 1;
		case 'C':
			return 0;
		default:
			return NULL;
	}
}

Rank checkPokerHand(vector<string> a) {
	int table[4][13] = {0};
	int sum_pairs[13] = { 0 };
	int sum_suits[4] = { 0 };

	for (vector<string>::iterator iter = a.begin(); iter != a.end(); iter++) {
		int pair_idx = getPairToInt(iter->at(0));
		int suit_idx = getSuitToInt(iter->at(1));
		table[suit_idx][pair_idx]++;
		sum_pairs[pair_idx]++;
		sum_suits[suit_idx]++;
	}
	
	return calcRank(table, sum_pairs, sum_suits);
}


/*
Straight 이상의 족보를 두 명 이상이 가지고 있을 경우
제일 높은 숫자의 모양순 대로 순위 (스-다-하-클)


10 Royal Flush		- 10 J Q K A 같은 모양@
09 Straight Flush	- Straight + Flush@
08 Four Of A Kind	- 네 개 같은 숫자 
07 Full House		- One Pair + Three Of A Kind
06 Flush			- 같은 무늬 다섯 장 @

Mountain		- 10 J Q K A @
05 Straight		- 연속 숫자 다섯 개 @
Back Straight	- A 2 3 4 5 @

04 Three Of A Kind - 세 개 같은 숫자
03 Two Pair		- One Pair 두 개
02 One Pair		- 두 개 같은 숫자 
01 High Card		- 제일 높은 숫자 
*/
Rank calcRank(int table[4][13], int *sum_pairs, int *sum_suits) {
	Rank rank;

	int sum_pairs_temp[14];
	sum_pairs_temp[0] = sum_pairs[12];
	for (int i = 0; i < 13; i++)
		sum_pairs_temp[i + 1] = sum_pairs[i];
	
	int table_temp[4][14];
	for (int i = 0; i < 4; i++) {
		table_temp[i][0] = table[i][12];
		for (int j = 0; j < 13; j++)
			table_temp[i][j + 1] = table[i][j];
	}

	int count = 0;
	for (int i = 0; i < sizeof(sum_pairs_temp) / sizeof(int); i++) {
		if (sum_pairs_temp[i] != 0)
			count++;
		else
			count = 0;
		
		if (count >= 5) {
			rank.rank = 5;
			rank.high_pair = i + 1;
			for (int j = 3; j >= 0; j--)
				if (table_temp[j][i] != 0) {
					rank.high_suit = j;
					break;
				}
		}
	}

	// check if the hand is royal flush or straight flush or flush
	if (rank.rank == 5) {
		for (int i = 0; i < 4; i++) {
			if (sum_suits[i] >= 5) {
				count = 0;
				for (int j = 0; j < sizeof(sum_pairs_temp) / sizeof(int); j++) {
					if (table[i][j] != 0) {
						count++;
						rank.high_pair = j + 1;
					}
					else
						count = 0;

					if (count >= 5) {
						if (j + 1 == 14)
							rank.rank = 10;
						else
							rank.rank = 9;
					}
				}

				if (rank.rank != 5)
					return rank;
			}
		}
	}

	//four, full house, flush, straight, three, two pair, one pair, high
	bool one_pair = false;
	bool three_of_a_kind = false;
	int three_high_pair = 0;
	int three_suit = 0;

	bool two_pair = false;
	int two_high_pair = 0;
	int two_suit = 0;

	int high_card_high_pair = 0;
	int high_suit = 0;

	for (int i = 0; i < 13; i++)
	{
		if (sum_pairs[i] == 4) {
			rank.rank = 8;
			rank.high_pair = i + 2;
			rank.high_suit = 3;
			return rank;
		}
		else if (sum_pairs[i] == 3) {
			three_of_a_kind = true;
			three_high_pair = i + 2;
			for (int j = 3; j >= 0; j--)
				if (table[j][i] != 0) {
					three_suit = j;
					break;
				}
		}
		else if (sum_pairs[i] == 2) {
			if (one_pair)
				two_pair = true;
			else
				one_pair = true;
			two_high_pair = i + 2;

			for (int j = 3; j >= 0; j--)
				if (table[j][i] != 0) {
					two_suit = j;
					break;
				}
		}
		else if (sum_pairs[i] == 1) {
			high_card_high_pair = i + 2;
			for (int j = 3; j >= 0; j--)
				if (table[j][i] != 0) {
					high_suit = j;
					break;
				}
		}
	}
	if (one_pair && three_of_a_kind) {
		rank.rank = 7;
		rank.high_pair = three_high_pair;
		rank.high_suit = three_suit;
		return rank;
	}

	for (int i = 0; i < 4; i++) {
		if (sum_suits[i] >= 5) {
			rank.high_suit = i;
			for(int j = 12; j >= 0; j--)
				if (table[i][j] != 0) {
					rank.high_pair = j + 2;
					break;
				}
			rank.rank = 6;
			return rank;
		}
	}
	if (rank.rank == 5)
		return rank;

	if (three_of_a_kind) {
		rank.rank = 4;
		rank.high_pair = three_high_pair;
		rank.high_suit = three_suit;
		return rank;
	}
	if (two_pair) {
		rank.rank = 3;
		rank.high_pair = two_high_pair;
		rank.high_suit = two_suit;
		return rank;
	}
	if (one_pair) {
		rank.rank = 2;
		rank.high_pair = two_high_pair;
		rank.high_suit = two_suit;
		return rank;
	}

	rank.high_pair = high_card_high_pair;
	rank.high_suit = high_suit;
	return rank;
}