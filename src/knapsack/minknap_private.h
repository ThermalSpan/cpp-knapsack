#include <stdlib.h>
#include <string>
#include <vector>


using namespace std;
long SYNC = 5; // When to switch to linear scan in bins
typedef vector <bool> SolVec;

struct Item {
    int id;
    long profit;
    long weight;
};

typedef vector <Item> ItemVec;
typedef vector <Item *> ItemPtrVec;

struct State {
    long valueSum;
    long weightSum;
    SolVec *solVec;
};

typedef vector <State> StateVec;

struct StateSet {
    long setSize;

};

class MinKnap {
private:
    ItemPtrVec m_ptrVec;

    long m_capacity; // Original capcity

    long m_currentBestValSum;
    long m_currentBestWeightSum;
    SolVec *m_currentBestSolVec;

    //
    // Find the state, l, such that l->weightSum <= wSum < (l+1)->weightSum
    //
    State *findState (long sSum, State *firstState, State *lastState);

    //
    // Update the current best solution's stats
    //
    void improveSolution (State *state);


};

void panic (string message);




