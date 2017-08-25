//
// Created by Jason Fu on 8/17/17.
//

#include "GRGameState.h"
#include "deck.h"
#include <assert.h>

GRGameState::GRGameState() {
    deck current_deck{};
    Hand player_one{};
    Hand player_two{};
    DiscardPile discards{};
    hands.reserve(2);
    hands[0] = player_one;
    hands[1] = player_two;
    deal();
}

GRGameState::GRGameState(const GRGameState &determinize, int observer) {
    assert(observer == 0 || observer == 1);
    hands.reserve(2);

    hands[observer] = determinize.hands[observer];
    DiscardPile discards(*determinize.discards);

    int opponent;
    if (observer == 0) opponent = 1;
    else opponent = 0;

    std::vector<card> deck_copy = determinize.current_deck->allCards();
    std::vector<card> opponent_hand_copy = determinize.hands[opponent].cardsInHand();
    deck_copy.insert(deck_copy.end(), opponent_hand_copy.begin(), opponent_hand_copy.end());

    // unseenCards has contents of deck and opponents hand
    std::vector<card> unseenCards = deck_copy;

    // shuffle unseenCards

    // seeding
    srand (time(0));

    for (int k = 0; k < unseenCards.size(); k++)
    {
        // Pick a random index from 0 to i
        int i = rand() % 52;
        int j = rand() % 52;

        // Swap arr[i] with the element at random index
        card temp = unseenCards[i];
        unseenCards[i] = unseenCards[j];
        unseenCards[j] = temp;
    }

    deck current_deck(unseenCards);
    Hand player_two{};

    for (int i = 0; i < 10; i++) {
        player_two.addToHand(current_deck.draw());
    }
    hands[opponent] = player_two;
}


// shuffles deck and deals initial hand
void GRGameState::deal() {
    current_deck->shuffle();

    for (int i = 0; i < 10; i++) {
        player_one->addToHand(current_deck->draw());
        player_two->addToHand(current_deck->draw());
    }
    discards->discard(current_deck->draw());
}
