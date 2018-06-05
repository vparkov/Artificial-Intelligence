#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int values[10] = {92, 57, 49, 68, 60, 43, 67, 84, 87, 72};
const int weights[10] = {23, 31, 29, 44, 53, 38, 63, 85, 89, 82};
const int itemsNumber = 10;              //change if u will change the number of elements ^

const int maxWeight = 250;              //sets the max weight in the knapsack

//Settings (you can play with them and achieve better or worse results :D
const int populationSize = 10;          //the higher the better? :D
const int FITNESS_PENALTY = 10;         //used when the weight is exceeding the limit -> (fitness - (weight - maxWeight))/FITNESS_PENALTY
const double mutationProbability = 0.2; //percentage of the chromosomes that will be mutated

//helper functions
int randBetween(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int** generateChromosomes() {
    int** population = new int*[populationSize];

    for (int i=0; i<populationSize; i++)
    {
        population[i] = new int [itemsNumber];
    }

    for(int i = 0; i < populationSize; i++) {
        for(int j = 0; j < itemsNumber; j++) {
            population[i][j] = rand() % 2;
        }
    }

    return population;
}

int* fitness(int** population) {
    int* populationFitness = new int[populationSize];

    for (int i = 0; i < populationSize; i++) {
        int weight = 0;
        int fitness = 0;

        for(int j = 0; j < itemsNumber; j++) {
            weight += weights[j] * population[i][j];
            fitness += values[j] * population[i][j];
//            std::cout << population[i][j] << "(" << weights[j] << ") ";
        }

        std::cout << " weight: " << weight << " fitness: " << fitness << "\n\n";
        populationFitness[i] = weight > maxWeight ? (fitness - (weight - maxWeight))/FITNESS_PENALTY : fitness;
        //might be better
//        populationFitness[i] = weight > maxWeight ? fitness - ((weight - maxWeight) * 50) : fitness;
    }

//    for(int i = 0; i < populationSize; i++) {
//        std::cout << populationFitness[i] << " ";
//    }

    return populationFitness;
}

int** mateRandomChromosomes(int** population, int* fitness) {
    int** children = new int*[1];
    children[0] = new int [itemsNumber];
    children[1] = new int [itemsNumber];

    int chromosomeA = randBetween(0, populationSize - 1);
    int chromosomeB = randBetween(0, populationSize - 1);
    int pivot = randBetween(1, itemsNumber - 1);

    for(int i = 0; i < itemsNumber; i++) {
        if (i <= pivot) {
            children[0][i] = population[chromosomeA][i];
            children[1][i] = population[chromosomeB][i];
        } else {
            children[0][i] = population[chromosomeB][i];
            children[1][i] = population[chromosomeA][i];
        }
    }

    return children;
}

int** createNewGeneration(int** population, int* fitness) {
    int** newGeneration = new int*[populationSize];
    int** children = new int*[2];
    children[0] = new int [itemsNumber];
    children[1] = new int [itemsNumber];

    for (int i = 0; i < populationSize; i++)
    {
        newGeneration[i] = new int [itemsNumber];
    }

    for (int i = 0; i < populationSize;) {
        children = mateRandomChromosomes(population, fitness);

        for(int j = 0; j < itemsNumber; j++) {
            newGeneration[i][j] = children[0][j];
            newGeneration[i+1][j] = children[1][j];
        }
        i += 2;
    }

    return newGeneration;
}

int** mutate(int** population) {
    for(int i = 0; i < populationSize * mutationProbability; i++) {
        int randomChromosome = randBetween(0, populationSize - 1);
        int randomIndex = randBetween(0, itemsNumber - 1);
        population[randomChromosome][randomIndex] ^= 1;
    }

    return population;
}

int calculateBestFitness(int** population) {
    int *populationFitness;
    populationFitness = fitness(population);

    for(int i = 0; i < populationSize; i++) {
//        std::cout << populationFitness[i] << " ";
    }

    return 1;
}

int main()
{
    srand( (unsigned)time( NULL ) );

    int** population = generateChromosomes();

//================prints the population==================
//    for(int i = 0; i < populationSize; i++) {
//        for(int j = 0; j < itemsNumber; j++) {
//            std::cout << population[i][j] << " ";
//        }
//        std::cout << "\n";
//    }
//    std::cout << "\n";

    int *populationFitness;
    populationFitness = fitness(population);

    for(int i = 0; i < populationSize; i++) {
        std::cout << populationFitness[i] << " ";
    }

    population = createNewGeneration(population, populationFitness);

    population = mutate(population);
    std::cout << "\nNEWGEN\n";
    for(int i = 0; i < populationSize; i++) {
        for(int j = 0; j < itemsNumber; j++) {
            std::cout << population[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    calculateBestFitness(population);
}
