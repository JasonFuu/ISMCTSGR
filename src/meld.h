//
// Created by Jason Fu on 7/20/17.
//

#ifndef UNTITLED_MELD_H
#define UNTITLED_MELD_H
#include "card.h"
#include <vector>

using namespace std;

bool compareByValue(const card &a, const card &b);
bool compareBySuit(const card &a, const card &b);

class meld {
public:

meld();
static int findDeadwood(std::vector<card> &hand);

private:
static int numbersDeadwood(std::vector<card> &subset);
    static int SFDeadwood(std::vector<card> &subset);
bool isNumberMeld(std::vector<card> &subset);
bool isSFMeld(std::vector<card> &subset);
};


#endif //UNTITLED_MELD_H
