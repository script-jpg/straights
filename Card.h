#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

class Card {
    int rank;
    char suite;
    string special;
    public:
        Card(int rank, char suite = '0', string special = "");
        Card(string special);
        ~Card();
        // getCard() returns a string representation of the card i.e. "7S"
        string getCard();
        // getSpecial() returns the special effect of the card. "" if not a special card.
        string getSpecial();
        // getRank() returns rank
        int getRank() const;
        // getRank() returns suite
        char getSuite() const;
        // operator++ returns a card with 1 rank greater and same suite if it exists
        Card operator++();
        // operator-- returns a card with 1 rank lesser and same suite if it exists
        Card operator--();
        // compare(other) compares this card with other and returns 0 if equal, -1 if lesser, 1 if greater
        int compare(Card &other);
        // isNullCard() determines whether this card represents a card a null
        bool isNullCard();
        // stringToCard(card) returns a Card given a string representation of it
        static Card stringToCard(const string &card);
        
        friend bool operator==(const Card& l, const Card& r);
        friend bool operator!=(const Card& l, const Card& r);
};



#endif