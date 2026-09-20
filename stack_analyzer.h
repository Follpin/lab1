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

    // Calculates median stack length 
    double calculateMedian(const std::vector<std::size_t>& lenCnt, std::size_t totalStackCnt) const;

public:
    // Initialize analyzer with validation
    StackAnalyzer(int cardsPerSuit, int totalCards);

    //Executes dealing simulation and calculates metrics
    SimulationResult analyze() const;
};