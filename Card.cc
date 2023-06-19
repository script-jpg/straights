#include "Card.h"
#include <vector>
#include <map>
#include <iostream>

map<int, string> intToRank{{1, "A"}, {2, "2"}, {3, "3"}, {4, "4"}, {5,"5"}, {6,"6"}, {7,"7"}, {8,"8"}, {9,"9"}, {10,"T"}, {11,"J"}, {12,"Q"}, {13,"K"}};
map<string, int> ranktoInt{{"A", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9",9}, {"T", 10}, {"J", 11}, {"Q", 12}, {"K", 13}};

Card::Card(int rank, char suite, string special) : rank{rank}, suite{suite}, special{special}{};

Card::Card(string special) : special{special}{
};

string Card::getSpecial() {
    return special;
}

Card::~Card(){};

string Card::getCard() {
    return intToRank[rank] + suite;
}

Card Card::operator++() {
    if (rank == 13) {
        rank = 0;
    } else {
        ++rank;
    }
    return *this;
}

Card Card::operator--() {
    --rank;
    return *this;
}

int Card::getRank() const { return rank; }

char Card::getSuite() const { return suite; }

int Card::compare(Card &other) {
    if (rank > other.getRank()) {
        return 1;
    } else if (rank < other.getRank()) {
        return -1;
    } else {
        return 0;
    }
}

bool Card::isNullCard() { 
    return rank <= 0; 
}

Card Card::stringToCard(const string &card) {
    int rank = ranktoInt[string(1,card[0])];
    char suite = card.back();
    return Card(rank, suite);
}

bool operator==(const Card& l, const Card& r) {
    return ((l.getRank() == r.getRank()) && (l.getSuite() == r.getSuite()));
}

bool operator!=(const Card& l, const Card& r) {
    return !(l == r);
}

