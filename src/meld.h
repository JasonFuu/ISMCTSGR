//
// Created by Jason Fu on 7/20/17.
//

#ifndef UNTITLED_MELD_H
#define UNTITLED_MELD_H
#include "card.h"
#include <vector>

using namespace std;
namespace helpers {
    bool compareByValue(const card &a, const card &b);

    bool compareBySuit(const card &a, const card &b);
}
class meld {
public:

meld();
    meld(std::vector<card> &hand);

    // returns deadwood value of hand
    int deadwoodValue();

    // returns true if input card can be played off the melds in this hand (for knocks)
    bool canPlayOffMeld(card &input);

    // returns non meld forming members of hand
    std::vector<card> nonMeldCards();

    // returns numbers meld members
    std::vector<card> numbersMeldCards();

    // returns straight flush meld members
    std::vector<card> SFMeldCards();


private:
static int numbersDeadwood(std::vector<card> &subset);
    static int SFDeadwood(std::vector<card> &subset);


bool isNumberMeld(std::vector<card> &subset);
bool isSFMeld(std::vector<card> &subset);

    std::vector<card> bestNumberMeld;
    std::vector<card> bestSFMeld;
    std::vector<card> nonMeldMembers;
    int best_deadwood;
};


#endif //UNTITLED_MELD_H
