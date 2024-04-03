#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

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
int getPeakLoad(const Solution & solution) {
    int peakLoad = 0;
    int lastEndTime = 0;
    for(auto&job : solution.schedule) {
        if(job.endTime>lastEndTime) lastEndTime = job.endTime;
    }
    int currentLoad = 0;
    for(int i = 0; i<lastEndTime; i++) {
        for(auto&job : solution.schedule) {
            if(job.startTime<=i && job.endTime>i) currentLoad += job.load;
        }
        if (currentLoad>peakLoad) peakLoad = currentLoad;
    }
    return peakLoad;
}

// Initialize your population
void initializePopulation(vector<Solution>& population, int num, Solution iniSolution) {
    // Generate random startTime
    srand(static_cast<unsigned int>(time(0)));
    // Generate { num } initial solutions
    for(int i = 0; i<num; i++){
        population.push_back(iniSolution);
    }
    for(auto & solution : population) {
        for(auto & job : solution.schedule) {
            job.startTime = job.releaseTime + rand() % (job.deadline - job.releaseTime - 1);
            job.endTime = job.startTime + 1; // assume they are unit jobs
        }
    }
}

void evaluateFitness(vector<Solution>& population) {
    // calculate total cost of each solution
    for(auto& solution : population) {
        int lastestEndTime =  0;
        for(auto & job : solution.schedule) {
            if(job.endTime > lastestEndTime) lastestEndTime = job.endTime;
        }
        for(int i = 0; i<lastestEndTime; i++) {
            vector<GeneticJob> jobSet;
            for(auto & job : solution.schedule) {
                if(job.startTime<=i && job.endTime>i) jobSet.push_back(job);
            }
            // sum and power
            int sum = 0;
            for (auto job : jobSet) {
                sum += job.load;
            }
            solution.fitness += pow(sum, 2);
        }
    }

}

// Selection
Solution selectParent(vector<Solution>& population) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    vector<Solution> parents;
    int fitnessSum = 0;
    for(auto & solution : population) {
        int fitness = getPeakLoad(solution);
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
void mutate(Solution& individual, double mutationRate) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    // some problem in mutation
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    std::uniform_int_distribution<int> geneDistribution(1, 2);
    for(auto& job : individual.schedule) {
        if(distribution(generator) < mutationRate) {
            job.startTime += geneDistribution(generator);
            job.endTime += geneDistribution(generator);
        }
    }

}

// Main GA loop
void geneticAlgorithm(vector<GeneticJob> jobs, int solutionNum) {
    vector<Solution> population;
    Solution iniSolution;
    iniSolution.schedule = std::move(jobs);
    initializePopulation(population, solutionNum, iniSolution);

    for (int generation = 0; generation < MAX_GENERATIONS; ++generation) {
        evaluateFitness(population);

        vector<Solution> newPopulation;
        while (newPopulation.size() < population.size()) {
            // Selection
            auto parent1 = selectParent(population);
            auto parent2 = selectParent(population);
            // Crossover
            Solution child1, child2;
            pair<Solution, Solution> children = crossover(parent1, parent2);
            child1 = children.first;
            child2 = children.second;
            // Mutation
            mutate(child1, 0.01);
            mutate(child2, 0.01);
            // Add to new population
            newPopulation.push_back(child1);
            newPopulation.push_back(child2);
        }
        population = newPopulation;
        // Optionally, include some logic to check for the termination condition
        Solution optimalSolution = population[0];
        for(auto& solution : population) {
            if(solution.fitness < optimalSolution.fitness) optimalSolution = solution;
        }
        cout<<"--- This is " <<generation+1<<" generation, optimal solution is: ---"<<endl;
        for(auto& job : optimalSolution.schedule) {
            cout<<"job "<<job.id<<", starts at time "<<job.startTime<<" and ends at time "<<job.endTime<<endl;
        }
    }
    // Output the best solution
}