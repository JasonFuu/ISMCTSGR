//
// Created by Jason Fu on 7/20/17.
//

#include "meld.h"
#include "card.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <bitset>
#include <math.h>
#include <iostream>


using namespace std;

namespace helpers {

    bool compareByValue(const card &a, const card &b) {
        return (a.getValue() < b.getValue());
    }

    bool compareBySuit(const card &a, const card &b) {
        return (a.getSuit() < b.getSuit());
    }
}

meld::meld() {};

// returns deadwood value of a hand by looking at all 2^(hand size) number/sf meld possibilities
// index 0 -> number meld, index 1 -> sf meld
meld::meld(std::vector<card> &hand) {

    best_deadwood = std::numeric_limits<int>::max();
    int const max_hand_size = 11;
    int deadwood_calc;

    std::vector<card> numberMelds;
    std::vector<card> SFMelds;

    for (int i = 0; i < pow(2.0, hand.size()); i++) {
        // issues with const, we just hard code max double hand size (20)
        std::bitset<max_hand_size> x(i);
        std::string s = x.to_string();
        std::reverse(s.begin(), s.end());

        //reset melds vectors
        numberMelds.reserve(max_hand_size);
        SFMelds.reserve(max_hand_size);
        numberMelds.clear();
        SFMelds.clear();

        // now we assign each card to the number or sf melds vector
        for (int j = 0; j < hand.size(); j++) {
            int temp = s[j] - '0';

            if (temp == 0) numberMelds.push_back(hand[j]);
            else SFMelds.push_back(hand[j]);
        }
        // shrink melds vectors to their size
        numberMelds.shrink_to_fit();
        SFMelds.shrink_to_fit();

        deadwood_calc = numbersDeadwood(numberMelds) + SFDeadwood(SFMelds);

        if (deadwood_calc < best_deadwood) {
            best_deadwood = deadwood_calc;
            bestNumberMeld = numberMelds;
            bestSFMeld = SFMelds;
        }
    }

    // clean up Number meld and SF meld vectors st they only contain meld members
    std::vector<int> toBeDeleted(max_hand_size);
    nonMeldMembers.reserve(max_hand_size);
    std::stable_sort(bestNumberMeld.begin(), bestNumberMeld.end(), helpers::compareByValue);
    int card_index = 0;
    int counter = 1;
    int current_index = 0;
    int current_value;

    // find cards in number melds vector that aren't meld members
    while (current_index < bestNumberMeld.size()) {
        card_index = current_index;
        current_value = bestNumberMeld[card_index].getValue();
        counter = 1;
        while (current_value == bestNumberMeld[++card_index].getValue()) {
            counter++;
        }

        // if no meld with current card, increment index and search
        if (counter < 3) {
            toBeDeleted.push_back(current_index);
            current_index++;
        }
            // if meld, increment index by size of meld
        else current_index += counter;

    }

    toBeDeleted.erase(unique(toBeDeleted.begin(), toBeDeleted.end()), toBeDeleted.end());

    // now clear melds vector of non meld elements and add them to nonmeld vector
    for (int i : toBeDeleted) {
        nonMeldMembers.push_back(bestNumberMeld[i]);
        bestNumberMeld[i] = bestNumberMeld.back();
        bestNumberMeld.pop_back();
    }

    // now clean up SF melds vector
    std::stable_sort(bestSFMeld.begin(), bestSFMeld.end(), helpers::compareByValue);
    std::stable_sort(bestSFMeld.begin(), bestSFMeld.end(), helpers::compareBySuit);

    // reset
    toBeDeleted.clear();
    toBeDeleted.reserve(11);
    card_index = 0;
    counter = 1;
    current_index = 0;
    int current_suit;

    // find cards in SF melds vector that aren't meld members
    while (current_index < bestSFMeld.size()) {

        card_index = current_index;
        current_value = bestSFMeld[card_index].getValue();
        current_suit = bestSFMeld[card_index].getSuit();
        counter = 1;

        // next card has to be one higher and the same suit
        while (++current_value == bestSFMeld[++card_index].getValue() && current_suit == bestSFMeld[card_index].getSuit()) {
            counter++;
        }

        // if it is not a meld
        if (counter < 3) {
            toBeDeleted.push_back(current_index);
            current_index++;
        }

        else current_index += counter;
    }


    // now clear melds vector of non meld elements and add them to nonmeld vector
    for (int i : toBeDeleted) {
        nonMeldMembers.push_back(bestNumberMeld[i]);
        bestSFMeld[i] = bestSFMeld.back();
        bestSFMeld.pop_back();
    }
}

// returns deadwood value of this hand
int meld::deadwoodValue() {
    return best_deadwood;
}

// returns true if input card can be played off the melds in this hand (for knocks)
bool meld::canPlayOffMeld(card &input) {

    // for the numbers meld vector, the card can be played if it has the same value as any of the other cards
    for (card next : bestNumberMeld) {
        if (input.getValue() == next.getValue()) return true;
    }

    // for the SF meld vector, the card can be played if it has the same suit and consecutive value of any of the cards
    for (card next : bestSFMeld) {
        if (input.getSuit() == next.getSuit() || input.getValue() + 1 == next.getValue() || input.getValue() - 1 == next.getValue())
            return true;
    }
    return false;
}

// final numbers meld members
std::vector<card> meld::numbersMeldCards() {
    return bestNumberMeld;
}

// final SF meld members
std::vector<card> meld::SFMeldCards() {
    return bestSFMeld;
}

// final non meld members
std::vector<card> meld::nonMeldCards() {
    return nonMeldMembers;
}

// returns deadwood value of "Numbers" melds vector
int meld::numbersDeadwood(std::vector<card> &subset) {
    std::stable_sort(subset.begin(), subset.end(), helpers::compareByValue);

    int total_sum = 0;

    // first get total potential deadwood sum, then subtract meld values
    for (card input : subset) {
        total_sum += input.getDeadwood();
    }

    if (subset.size() >= 3) {
        int cards_index = 0;
        int current_value = -1;
        int meld_size = 1;
        int deadwood_value = -1;

        while (cards_index < subset.size()) {
            current_value = subset[cards_index].getValue();
            deadwood_value = subset[cards_index].getDeadwood();
            meld_size = 1;
            while (current_value == subset[++cards_index].getValue()) {
                meld_size++;
            }
            if (meld_size >= 3) total_sum -= meld_size * deadwood_value;
        }
    }
    return total_sum;
}

// returns deadwood value of "straight flush" melds vector
int meld::SFDeadwood(std::vector<card> &subset) {
    // sort by value then suit
    std::stable_sort(subset.begin(), subset.end(), helpers::compareByValue);
    std::stable_sort(subset.begin(), subset.end(), helpers::compareBySuit);

    // first get total potential deadwood sum, then subtract meld values
    int total_sum = 0;

    for (card input : subset) {
        total_sum += input.getDeadwood();
    }

    //initialize meld checker vector
    std::vector<card> potential_meld;
    potential_meld.reserve(subset.size());

    // check input hand subset vector
    if (subset.size() >= 3) {

        int cards_index = 0;
        int current_value = -1;
        int current_suit = -1;

        while (cards_index < subset.size()) {
            potential_meld.clear();
            potential_meld.reserve(subset.size());

            current_value = subset[cards_index].getValue();
            current_suit = subset[cards_index].getSuit();
            potential_meld.push_back(subset[cards_index]);

            // next card has to be one higher and the same suit
            while (++current_value == subset[++cards_index].getValue() && current_suit == subset[cards_index].getSuit()) {
                potential_meld.push_back(subset[cards_index]);
            }
            // if it is a meld
            if (potential_meld.size() >= 3) {
                for (card input: potential_meld) {
                    total_sum -= input.getDeadwood();
                }
            }
        }
    }
    return total_sum;
}

// 3 of a kind, 4 of a kind
bool meld::isNumberMeld(std::vector<card> &subset) {
    if (subset.size() != 3 || subset.size() != 4) return false;

    int value = subset[0].getValue();

    for (card input : subset){
        if (input.getValue() != value) return false;
    }

    return true;
}

// tests for straight flush (sf) melds
bool meld::isSFMeld(std::vector<card> &subset) {
    std::stable_sort(subset.begin(), subset.end(), helpers::compareByValue);
    int suit = subset[0].getSuit();

    // all must be same suit
    for (card input : subset) {
        if (input.getSuit() != suit) return false;
    }

    int current_value = subset[0].getValue();

    // then check ascending order
    for (card input : subset) {
        if (input.getValue() != current_value) return false;
        current_value++;
    }

    return true;
}
