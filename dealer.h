#pragma once

#include "card.h"
#include <vector>
#include <random>
#include <cstddef>

class Dealer {
private:
    int cardsPerSuit;
    std::vector<Card> deck;
    std::size_t currentIdx;
    std::mt19937 rng;

    //Shuffles deck (using Fisher-Yates algorithm)
    void shuffleDeck();

public:
    // Initializes dealer, allocates deck, and performs initial shuffle
    explicit Dealer(int cardsPerSuit);

    // Returns next card or reshuffles when deck is exhausted
    Card operator()();
};