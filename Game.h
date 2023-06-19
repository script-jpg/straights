#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>
#include <vector>

class Player;
class Observer;
class Card;

using namespace std;

class Game {
  vector<Observer*> observers;
  vector<shared_ptr<Player>> players;
  vector<Card> deck;
  const int seed;
  
  private:
    // initialize members
    void fillPlayers();
    void fillDeck();

  protected:
    Game(vector<Card>& deck, vector<shared_ptr<Player>>& players, int seed = 0);
    Card deckAt(int index);

  public:
    vector<shared_ptr<Player>>& getPlayers();
    vector<Card>& getDeck();
    Game(int seed = 0);
    virtual ~Game();

    // facilitate observer pattern
    void notifyObservers();
    void attach(Observer* o);

    // gettors
    void shuffleDeck();
    bool gameOver();

    void resetBot();
};

#endif