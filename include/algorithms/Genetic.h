#ifndef SMARTGRID_GENETIC_H
#define SMARTGRID_GENETIC_H
#include <vector>

#define MAX_GENERATIONS 500
using namespace std;

struct GeneticJob {
    int id;
    int releaseTime;
    int deadline;
    int startTime;
    int endTime;
    int load;
};

// Define your solution structure here. For DSM, this might include a vector of power usages across time slots.
struct Solution {
    vector<GeneticJob> schedule;
    double fitness = 0.0;
};

// calculate peak load
int getPeakLoad(Solution & solution);

// initialize population
void initializePopulation(vector<Solution>& population, int num, Solution iniSolution);

void evaluateFitness(vector<Solution>& population);

vector<Solution> selectParents(const vector<Solution>& population);

void crossover(Solution& parent1, Solution& parent2, Solution& child1, Solution& child2);

void mutate(Solution& individual);

void geneticAlgorithm(vector<GeneticJob> jobs, int solutionNum);

#endif //SMARTGRID_GENETIC_H
