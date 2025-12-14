#include "simulation.cpp"

int main(void)
{
    uint8_t board[] = {0, 0, 0, 0, 0, 15};
    uint8_t oppBoard[] = {0, 0, 15, 0, 0, 0};

    Results *results = simulate(new Board(board), 0);
    Results *oppResults = simulate(new Board(oppBoard), 0);
    
    cout << "========== SELF ==========" << endl;
    cout << "Sim Results: " << *results << endl;
    results->printProbPerTurn();
    cout << endl;
    cout << "========== OPP ==========" << endl;
    cout << "Sim Results: " << *oppResults << endl;
    oppResults->printProbPerTurn();
    cout << endl;

    cout << "========== RESULTS ==========" << endl;
    cout << "Win Chance: " << results->chanceWinAgainst(oppResults) * 100 << "%" << endl;
    cout << "=============================" << endl;

    cout << endl;
    cout << "Simulations: " << simulations << endl;
    cout << "Maxed out: " << maxed_out << endl;

    delete results;
    return 0;
}