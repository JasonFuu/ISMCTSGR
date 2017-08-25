#include <iostream>
#include "card.h"
#include "deck.h"
#include "meld.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <bitset>
#include <math.h>

using namespace std;

int main() {

//    deck *b = new deck(*a);

//    cout << '\n';
//    b->print();
    deck a;
    deck b(a);
    a.shuffle();
    deck c(a);
    a.print();
    cout << "asdf + \n";
    c.print();
}





//    std::vector<card> testing;
//    testing.reserve(10);
//    card a(static_cast<SUIT>(1), static_cast<VALUE>(2));
//    card b(static_cast<SUIT>(2), static_cast<VALUE>(2));
//    card c(static_cast<SUIT>(3), static_cast<VALUE>(2));
//    card d(static_cast<SUIT>(3), static_cast<VALUE>(3));
//    card e(static_cast<SUIT>(3), static_cast<VALUE>(4));
//    card f(static_cast<SUIT>(2), static_cast<VALUE>(7));
//    card g(static_cast<SUIT>(0), static_cast<VALUE>(10));
//    card h(static_cast<SUIT>(1), static_cast<VALUE>(11));
//    card i(static_cast<SUIT>(2), static_cast<VALUE>(12));
//    card j(static_cast<SUIT>(3), static_cast<VALUE>(13));
//
//    /* cards as follows:
//    TWO of SPADES
//    TWO of CLUBS
//    TWO of DIAMONDS
//    FIVE of CLUBS
//    SIX of CLUBS
//    SEVEN of CLUBS
//    TEN of HEARTS
//    JACK of SPADES
//    QUEEN of CLUBS
//    KING of DIAMONDS*/
//
//
//
//    testing.push_back(a);
//    testing.push_back(b);
//    testing.push_back(c);
//    testing.push_back(d);
//    testing.push_back(e);
//    testing.push_back(f);
//    testing.push_back(g);
//    testing.push_back(h);
//    testing.push_back(i);
//    testing.push_back(j);
//
//    for (card input: testing) {
//
//        cout << input << "\n";
//    }
//
//    cout << "deadwood value is: " << "\n" << meld::findDeadwood(testing);
//    deck test;
//    test.print();
//    cout << "------------ \n";
//    test.shuffle();
//    test.print();
