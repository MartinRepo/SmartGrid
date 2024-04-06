#ifndef SMARTGRID_GENETIC_H
#define SMARTGRID_GENETIC_H
#include <vector>
#include "../structs/Job.h"
#include "../structs/Config.h"

#define MAX_GENERATIONS 500
using namespace std;

struct Solution {
    vector<Config> schedule;
    double fitness = 0.0;
};

int getPeakLoad(const Solution & solution, vector<Job> jobs);

void initializePopulation(vector<Job> jobs, vector<Solution>& population, int num, Solution iniSolution);

void evaluateFitness(vector<Solution>& population, vector<Job>& jobs);

Solution selectParent(vector<Solution>& population, vector<Job>& jobs);

pair<Solution, Solution> crossover(Solution& parent1, Solution& parent2);

void mutate(Solution& individual, double mutationRate, vector<Job> jobs);

int GeneticTotalCost(vector<Job> jobs, const vector<Config> &Solution, int boundary, int power);

vector<Config> geneticAlgorithm(vector<Job> jobs, int solutionNum);

#endif //SMARTGRID_GENETIC_H
