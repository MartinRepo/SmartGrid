# Scheduling for Smart Grid
>Authored by: @[Martingale](https://github.com/MartinRepo)

Click [here](https://demo-smartgrid.tech) to visit demo site. Just try it :)
## Content
- [Algorithms Implementation](#algorithms-implementation)
  - [Feasible Graph](#feasible-graph)
  - [Fixed Parameter](#fixed-parameter)
  - [Greedy](#greedy)
  - [Genetic](#genetic)
- [Dataset Preview](#dataset-preview)
- [Simulation](#simulation)
- [Performance Comparison](#performance-comparison)
  - [Total cost](#total-cost)
  - [Peak cost](#peak-cost)
  - [Running time](#running-time)
- [References](#references)

## Algorithms Implementation
Core strategies for following algorithms
### Feasible Graph
  ![feasible graph](./readmeFig/feasiblegraph.jpg)
### Fixed Parameter
Pseudocode as following
```
Input: a set of job J 
Output: an optimal configuration of J 
{bi} i=1...τ/2+1 ← the boundaries {0, 2, 4, 6, ..., τ} 
{Di} i=1...τ/2 ← the windows where Di is bounded by bi (inclusively) and bi+1 (exclusively) 
{Ci} i=1...τ/2 ← the collection of job sets where Ci is the set of jobs in Di 
Tleft ← a configuration that labels all jobs j ∈ J to be not yet executed for i from 1 to τ/2 do 
Tright ← ListConfigurations(Di, Ci) 
Tleft ← ConcatenateTables(Tleft, Tright) 
Tleft ← FilterTable(Tleft) 
return any configuration in Tleft
```
### Greedy
Job is assigned to the machine with the smallest number of jobs currently assigned.
### Genetic
Through constant crossover mutations 

(crossover: crossing two schedules to generate a new schedule. 

Mutation: randomly changing the position or time of a task within a feasible interval.).

I use the fitness function to decide which scheduling scheme is kept and which is filtered out.
## Dataset Preview
There are 11 jobs, 6 windows, 7 boundaries.Their width(duration) and height(power cost) is adjusted

![jobs interval](./readmeFig/jobs.jpg)

## Simulation
![simulation](./readmeFig/simulation.jpg)

## Performance Comparison
Load function: Sum of jobs' height in per unit time t. 𝐿(𝑡) = ∑𝐽:𝑡 𝐻(𝑗)
### Total cost
Total cost function: Total cost of the entire scheduling solution S. 𝐶𝑜𝑠𝑡(𝑆) = ∑ 𝐿(𝑡)^𝛼
### Peak cost
Peak cost function: 𝐶𝑜𝑠𝑡(𝑆) = max(𝐿(𝑡))^𝛼
### Running time
Every algorithm's running time.

## References
