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
    bool sameSuit(const card& that) const;

    // check value equality
    bool sameValue(const card& that) const;

    // value comparison
    bool valueCmp(const card &that) const;

    // access suit
    int getSuit() const;

    // access value
    int getValue() const;

    // get deadwood value (different from value for face cards)
    int getDeadwood() const;

    const std::string toString() const;

    card();

    card(SUIT suit, VALUE value);

private:
    SUIT suit;
    VALUE value;
};

std::ostream& operator<< (std::ostream &out, const card &card);



#endif //UNTITLED_CARD_H
