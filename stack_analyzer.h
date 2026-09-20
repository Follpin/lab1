#pragma once

#include <vector>
#include <map>
#include <cstddef>

struct SimulationResult {
    std::size_t totalStackCnt;
    std::map<std::size_t, double> lenPctMap;
    std::size_t mostFreqLen;
    double avgLen;
    double medLen;
};

class StackAnalyzer {
private:
    int cardsPerSuit;
    int totalCards;

    double computeMedian(const std::vector<std::size_t>& lenCnt, std::size_t totalStackCnt) const;

public:
    StackAnalyzer(int cardsPerSuit, int totalCards);
    SimulationResult analyze() const;
};