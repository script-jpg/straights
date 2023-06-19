#ifndef ROUND_H
#define ROUND_H

#include <string>
#include <list>
#include <vector>
#include <memory>
#include "Game.h"

using namespace std;


class Player;
class Card;

class Round : public Game {
  list<Card> diamonds;
  list<Card> clubs;
  list<Card> hearts;
  list<Card> spades;
  int turn;

  private:
    void incrTurn();
    void deal();
    int findFirst();
    int whosTurn;
    void setState(Card card);
    bool isFirstMove();

  public:
    Round(vector<Card>& deck, vector<shared_ptr<Player>>& players, int seed = 0);
    ~Round();
    
    int getTurn(bool increment = true);
    const vector<list<Card>> getState();
    shared_ptr<Player> getPlayer(int index);
    list<Card> legalMoves(int player);


    // round player logic
    bool isRoundOver();
    void botMove(int turn);
    bool play(Card card, int turn);
    bool discard(Card card, int turn);
    void deck();
    void ragequit(int turn);
    void handleRoundEnd();
    bool isBot(int turn);

    

    

    
};

#endif
