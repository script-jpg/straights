#ifndef VIEW_H
#define VIEW_H

#include <list>
#include <string>
#include "Observer.h"
#include "Round.h"

using namespace std;

class Card;

class View : public Observer{
  Round* round;
  int turn;
  public:
    View(Round* round);
    ~View() = default;
    void update() override;
    bool controller(int turn);
};

#endif