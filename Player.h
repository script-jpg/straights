#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <list>
#include <vector>

using namespace std;

class Card;

class Player {
  bool isBot;
  int gamePoints = 0;
  int roundPoints = 0;
  list<Card> hand;
  vector<Card> roundDiscards;

  public:
    Player(bool isBot = false);
    ~Player();

    // getters
    int getGamePoints();
    int getRoundPoints();
    bool isemptyHand();
    bool isPlayerBot();
    list<Card>& getHand();
    
    // setters
    bool removeCard(Card card);
    void setRoundPoints(int amount);
    void setBot();
    void addCard(Card card);
    void addDiscard(Card card);
    void clearDiscards();

    void printDiscards();
    void endRound();
};

#endif