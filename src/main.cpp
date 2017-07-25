#include <iostream>
#include "card.h"
#include "deck.h"

int main() {
    card fuckyou(static_cast<SUIT>(2), static_cast<VALUE>(6));
    cout << "testing card is :" << fuckyou;
    deck test;
    test.print();
    test.shuffle();
    test.print();
}