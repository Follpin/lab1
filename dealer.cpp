#include "dealer.h"
#include <utility>
#include <stdexcept>

constexpr int SUIT_CNT = 4;

Dealer::Dealer(int cardsPerSuit)
    : cardsPerSuit(cardsPerSuit), currentIdx(0) {
    if (cardsPerSuit <= 0) {
        throw std::invalid_argument("cardsPerSuit must be a positive integer.");
    }

    std::random_device rd;
    rng.seed(rd());

    deck.reserve(static_cast<std::size_t>(SUIT_CNT * cardsPerSuit));
    for (int suit = 0; suit < SUIT_CNT; ++suit) {
        for (int rank = 1; rank <= cardsPerSuit; ++rank) {
            deck.push_back(Card{rank, suit});
        }
    }

    shuffleDeck();
}

void Dealer::shuffleDeck() {
    for (std::size_t i = deck.size(); i > 1; --i) {
        std::uniform_int_distribution<std::size_t> dist(0, i - 1);
        std::size_t j = dist(rng);
        std::swap(deck[i - 1], deck[j]);
    }
    currentIdx = 0;
}

Card Dealer::operator()() {
    if (currentIdx >= deck.size()) {
        shuffleDeck();
    }
    return deck[currentIdx++];
}