//
// Created by Jason Fu on 7/20/17.
//

#ifndef UNTITLED_CARD_H
#define UNTITLED_CARD_H
#include <string>

using namespace std;
enum SUIT {HEARTS, SPADES, CLUBS, DIAMONDS};
enum VALUE {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

class card {
public:

    // check suit equality
    bool sameSuit(const card& that);

    // check value equality
    bool sameValue(const card& that);

    const std::string toString() const;

    card();

    card(SUIT suit, VALUE value);


private:
    SUIT suit;
    VALUE value;
};

std::ostream& operator<< (std::ostream &out, const card &card);



#endif //UNTITLED_CARD_H
