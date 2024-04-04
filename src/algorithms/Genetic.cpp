#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include "../../include/algorithms/Genetic.h"

#define MAX_GENERATIONS 500
using namespace std;

// calculate peak load
int getPeakLoad(const Solution & solution, vector<Job> jobs) {
    int peakLoad = 0;
    int lastEndTime = 0;
    for(auto&job : solution.schedule) {
        if(job.endTime>lastEndTime) lastEndTime = job.endTime;
    }
    int currentLoad = 0;
    for(int i = 0; i<lastEndTime; i++) {
        for(auto&job : solution.schedule) {
            if(job.startTime<=i && job.endTime>i) currentLoad += jobs[job.id].width;
        }
        if (currentLoad>peakLoad) peakLoad = currentLoad;
    }
    return peakLoad;
}

// Initialize your population
void initializePopulation(vector<Job> jobs, vector<Solution>& population, int num, Solution iniSolution) {
    for(int i = 0; i<num; i++){
        population.push_back(iniSolution);
    }
    for(auto & solution : population) {
        for(auto & job : solution.schedule) {
            int timeRange = jobs[job.id].deadline - jobs[job.id].releaseTime - 1;
            if (timeRange > 0) {
                job.startTime = jobs[job.id].releaseTime + rand() % timeRange;
            } else {
                job.startTime = jobs[job.id].releaseTime;
            }
            job.endTime = job.startTime + jobs[job.id].width;
            if (job.endTime >= jobs[job.id].deadline) {
                job.endTime = jobs[job.id].deadline;
                job.startTime = job.endTime - jobs[job.id].width;
            }
        }
    }
}

void evaluateFitness(vector<Solution>& population, vector<Job>& jobs) {
    // calculate total cost of each solution
    for(auto& solution : population) {
        int lastestEndTime =  0;
        for(auto & job : solution.schedule) {
            if(job.endTime > lastestEndTime) lastestEndTime = job.endTime;
        }
        for(int i = 0; i<lastestEndTime; i++) {
            vector<Config> jobSet;
            for(auto & job : solution.schedule) {
                if(job.startTime<=i && job.endTime>i) jobSet.push_back(job);
            }
            // sum and power
            int sum = 0;
            for (auto job : jobSet) {
                sum += jobs[job.id].width;
            }
            solution.fitness += pow(sum, 2);
        }
    }

}

// Selection
Solution selectParent(vector<Solution>& population, vector<Job>& jobs) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    vector<Solution> parents;
    int fitnessSum = 0;
    for(auto & solution : population) {
        int fitness = getPeakLoad(solution, jobs);
        solution.fitness = fitness;
        fitnessSum += fitness;
    }
    double slice = distribution(generator) * fitnessSum;
    double partialSum = 0.0;
    for (auto & solution : population) {
        partialSum += solution.fitness;
        if (partialSum >= slice) {
            return solution;
        }
    }
    return population[population.size()-1];
}

// Crossover
pair<Solution, Solution> crossover(Solution& parent1, Solution& parent2) {
    if (parent1.schedule.size() != parent2.schedule.size()) {
        throw std::invalid_argument("Parents must have the same length.");
    }
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(1, static_cast<int>(parent1.schedule.size()) - 2);
    int crossoverPoint = distribution(generator);
    Solution child1, child2;
    for (int i = 0; i < parent1.schedule.size(); ++i) {
        if (i < crossoverPoint) {
            child1.schedule.push_back(parent1.schedule[i]);
            child2.schedule.push_back(parent2.schedule[i]);
        } else {
            child1.schedule.push_back(parent2.schedule[i]);
            child2.schedule.push_back(parent1.schedule[i]);
        }
    }
    return std::make_pair(child1, child2);
}

// Mutation
void mutate(Solution& individual, double mutationRate, vector<Job> jobs) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    // some problem in mutation
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    std::uniform_int_distribution<int> geneDistribution(1, 2);
    for(auto& job : individual.schedule) {
        if(distribution(generator) < mutationRate) {
            job.startTime += geneDistribution(generator);
            job.endTime += geneDistribution(generator);
            if (job.endTime >= jobs[job.id].deadline) {
                job.endTime = jobs[job.id].deadline;
                job.startTime = job.endTime - jobs[job.id].width;
            }
            else if (job.startTime <= jobs[job.id].releaseTime) {
                job.startTime = jobs[job.id].releaseTime;
                job.endTime = job.startTime + jobs[job.id].width;
            }
            if (job.startTime == job.endTime) {
                job.startTime = job.endTime - jobs[job.id].width;
            }
        }
    }

}

// Main GA loop
vector<Config> geneticAlgorithm(vector<Job> jobs, int solutionNum) {
    srand(static_cast<unsigned int>(time(0)));
    vector<Solution> population;
    Solution optimalSolution;
    Solution iniSolution;
    for(auto & job : jobs) {
        iniSolution.schedule.push_back({job.id, job.releaseTime, job.releaseTime+job.width});
    }
    initializePopulation(jobs, population, solutionNum, iniSolution);

    for (int generation = 0; generation < MAX_GENERATIONS; ++generation) {
        evaluateFitness(population, jobs);

        vector<Solution> newPopulation;
        while (newPopulation.size() < population.size()) {
            // Selection
            auto parent1 = selectParent(population, jobs);
            auto parent2 = selectParent(population, jobs);
            // Crossover
            Solution child1, child2;
            pair<Solution, Solution> children = crossover(parent1, parent2);
            child1 = children.first;
            child2 = children.second;
            // Mutation
            mutate(child1, 0.01, jobs);
            mutate(child2, 0.01, jobs);
            // Add to new population
            newPopulation.push_back(child1);
            newPopulation.push_back(child2);
        }
        population = newPopulation;
        // Optionally, include some logic to check for the termination condition
        optimalSolution = population[0];
        for(auto& solution : population) {
            if(solution.fitness < optimalSolution.fitness) optimalSolution = solution;
        }
    }
    return optimalSolution.schedule;
}