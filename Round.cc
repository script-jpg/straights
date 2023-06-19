#include "Round.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <map>
#include <algorithm>


Round::Round(vector<Card>& deck, vector<shared_ptr<Player>>& players, int seed) :
Game(deck, players, seed){
    deal();
    whosTurn = findFirst();
};

Round::~Round(){};

void Round::setState(Card card) {
    char pile = card.getSuite();
    map<char, list<Card>*> selectPile{{'D', &diamonds}, {'C', &clubs}, {'H', &hearts}, {'S', &spades}};
    if (selectPile[pile]->empty()) {
        selectPile[pile]->push_back(card);
    } else if (selectPile[pile]->back().compare(card) == -1) { //compare value of cards
        selectPile[pile]->push_back(card); // card is greater than "back" of pile, make new back
    } else if (selectPile[pile]->back().compare(card) == 1) { 
        selectPile[pile]->push_front(card); // card is lesser than "front" of pile, make new front
    } else {
      cout << "invalid pile: " << pile << endl;
    }
}

const vector<list<Card>> Round::getState() {
  const vector<list<Card>> state{diamonds, clubs, hearts, spades};
  return state;
}


shared_ptr<Player> Round::getPlayer(int index) {
    return getPlayers()[index];
}

bool Round::isRoundOver() {
  for (int i = 0; i < 4; i++) {
    if (!getPlayer(i)->isemptyHand()) {
      return false;
    }
  }
  return true;
}

void Round::incrTurn() {
  if (whosTurn == 3) {
    whosTurn = 0;
  } else {
    whosTurn++;
  }
}

int Round::getTurn(bool increment) {
  int turn = whosTurn;
  if (increment) {
    incrTurn();
  }
  return turn;
}

void Round::deal() {
  for (int i = 0; i < 52; i++) {
    int j = i / 13;
    //cout << i << " " << j << " " << deckAt(i).getCard() << endl;
    getPlayer(j)->addCard(deckAt(i));
  }
}

int Round::findFirst() {
  int turn;
  for (int i = 0; i < 4; i++) {
    list<Card> hand = getPlayer(i)->getHand();
    for (auto it = hand.begin(); it != hand.end(); it++) {
        if (it->getCard() == "7S") {
            turn = i;
            break;
        } 
    }
  }
  return turn;
}

bool Round::isFirstMove() {
    vector<list<Card>> piles = getState();
    for (int i = 0; i < 4; i++) {
        if (!piles[i].empty()) {
            return false;
        }
    }
    return true;
};

list<Card> Round::legalMoves(int player) {
    const list<Card> hand = getPlayer(player)->getHand();
    list<Card> legalMoves;
    bool firstMove = isFirstMove();
    if (firstMove) {
        legalMoves.push_back(Card(7, 'S'));
        return legalMoves;
    } else {
        vector<char> suites = {'C', 'D', 'H'};
        // looking for 7s
        for (char suite: suites) {
            Card card = Card(7,suite);
            if (find(hand.begin(), hand.end(), card) != hand.end()) {
                legalMoves.push_back(card);
            }
        }
        // looking for bigger or smaller cards for a non-empty pile
        vector<list<Card>> piles = getState();
        for (auto pile: piles) {
            if (!pile.empty()) {
                Card next = ++Card::stringToCard(pile.back().getCard());
                Card prev = --Card::stringToCard(pile.front().getCard());
                if(!next.isNullCard() && find(hand.begin(), hand.end(), next) != hand.end()) {
                    legalMoves.push_back(next);
                }
                if(!prev.isNullCard() && find(hand.begin(), hand.end(), prev) != hand.end()) {
                    legalMoves.push_back(prev);
                }
            } 
        }
        // looking for specials

        /* commented out because no special cards currently in deck

        for (auto card: hand) {
            if (card.getSpecial() != "") {
                legalMoves.push_back(card);
            }
        }
        */
        return legalMoves;
    }
};

void Round::ragequit(int turn) {
    auto player = getPlayer(turn);
    cout << "Player" << turn + 1 << " ragequits. A computer will now take over." << endl;
    player->setBot();
    botMove(turn);
}

void Round::deck() {
    for (int i = 0; i < 52; i++) {
        int j = i / 13;
        cout << getDeck()[i].getCard() << " ";
        if (i == 12 || i == 25 || i == 38 || i == 51) {
            cout << endl;
        }
    }
}

void Round::botMove(int turn) {
    list<Card> legalPlays = legalMoves(turn);
    auto player = getPlayer(turn);
    if (!legalPlays.empty()) {
        play(legalPlays.front(), turn);
    } else {
        discard(player->getHand().front(), turn);
    }
}

bool Round::play(Card card, int turn) {
    auto player = getPlayer(turn);
    list<Card> legalPlays = legalMoves(turn);
    if (find(legalPlays.begin(), legalPlays.end(), card) != legalPlays.end()) {
        cout << "Player" << turn + 1 << " plays " << card.getCard() << "." << endl;
        setState(card);
        player->removeCard(card);
        return true;
    } else {
        cout << card.getCard() <<" is not a legal play." << endl;
        return false;
    }
    
}

bool Round::discard(Card card, int turn) {
    auto player = getPlayer(turn);
    list<Card> legalPlays = legalMoves(turn);
    const list<Card>& hand = player->getHand();
    if (!legalPlays.empty()) {
        cout << "You have a legal play. You may not discard." << endl;
        return false;
    } else {
        if (find(hand.begin(), hand.end(), card) != hand.end()) {
            player->addDiscard(card);
            player->removeCard(card);
            player->setRoundPoints(player->getRoundPoints() + card.getRank());
            cout << "Player" << turn + 1 << " discards " << card.getCard() << "." << endl;
            return true;
        } else {
            cout << "This is not a legal play. " << card.getCard() << " not in hand." << endl;
            return false;
        }
    }
}

bool Round::isBot(int turn) {
  return getPlayer(turn)->isPlayerBot();
}

void Round::handleRoundEnd() {
  for (int i = 0; i < 4; i++) {
    int pNum = i + 1;
    auto player = getPlayer(i);

    // print discards
    cout << "Player" << pNum << "'s discards:";
    player->printDiscards();

    // print score
    cout << "Player" << pNum << "'s score: ";
    cout << player->getGamePoints() << " + " << player->getRoundPoints();
    player->endRound();
    cout << " = " << player->getGamePoints() << endl;
    
    player->clearDiscards();
  }
}