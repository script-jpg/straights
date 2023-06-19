#include "Player.h"
#include "iostream"
#include "Card.h"

#include <algorithm>

using namespace std;

Player::Player(bool isBot) : isBot{isBot} {};

Player::~Player(){};

int Player::getGamePoints() {
    return gamePoints;
}

int Player::getRoundPoints() {
    return roundPoints;
}

bool Player::isemptyHand() {
    return hand.empty();
}

list<Card>& Player::getHand() {
    return hand;
}

void Player::endRound() {
    gamePoints += roundPoints;
    roundPoints = 0;
}

void Player::clearDiscards() {
    roundDiscards.clear();
}

bool Player::removeCard(Card card) {
    auto it = find(hand.begin(), hand.end(), card);
    if (it != hand.end()) {
        hand.erase(it);
        return true;
    }
    return false;
}

bool Player::isPlayerBot() {
    return isBot;
}

void Player::setBot() {
    isBot = true;
}

void Player::addCard(Card card) {
    hand.emplace_back(card);
}

void Player::printDiscards() {
    for (Card c : roundDiscards) {
        cout << " " << c.getCard();
    }
    cout << endl;
}

void Player::addDiscard(Card card) {
    roundDiscards.emplace_back(card);
}


void Player::setRoundPoints(int amount) {
    roundPoints = amount;
}