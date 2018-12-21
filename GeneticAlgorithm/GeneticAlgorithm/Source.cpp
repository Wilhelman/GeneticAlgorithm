#include <Windows.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

#include "Population.h"

#define MUTATION_RATE 100 // 1000 = 100% | 1 = 0.01%

int main() {

	srand(time(NULL));

	bool match_complete = false;
	unsigned int generation = 0;
	const std::string FINAL_DNA = "Guess what I'm thinking!";
	
	Population population(FINAL_DNA, 5000); // Create a population and initialize it with random DNA, also set the fitness to 0

	while (!match_complete) {

		generation++;

		for (int i = 0; i < population.members.size(); i++) {

			/*
			For each character of the string the fitness will increase 'X' points,
			to know if the match if complete we'll compare the fitness of the current
			member with the size of FINAL_DNA * 'X', if is equals the match is complete
			*/

			population.members.at(i).fitness = 0;

			for (int j = 0; j < population.members.at(i).dna.size(); j++) { 

				if (population.members.at(i).dna.at(j) == FINAL_DNA.at(j))
					population.members.at(i).fitness += 10; // Add points to the fitness when it match
				
			}
			if (population.members.at(i).fitness == FINAL_DNA.size() * 10) match_complete = true;
		}

		std::sort(population.members.begin(), population.members.end(), [](Population::Member const &a, Population::Member &b) {
			return a.fitness > b.fitness; 
		});

		std::vector<Population::Member> parents{population.members.at(0), population.members.at(1)};

		for (int i = 0; i < population.members.size(); i++) {

			for (int j = 0; j < population.members.at(i).dna.size(); j++) {

				int parent_random_gen = rand() % parents.size();
				population.members.at(i).dna.at(j) = parents.at(parent_random_gen).dna.at(j);

				if (rand() % 1000 < MUTATION_RATE) 
					population.members.at(i).dna.at(j) = (unsigned char)rand() % 96 + 32; // This character mutated!
				
			}

		}

		std::cout << "Gen. number: " << generation << " | Highest Fitness: " << parents.at(0).fitness << " | Sequence: " << parents.at(0).dna.c_str() << std::endl;
	}

	std::cout << "Gen. number: " << generation << " | Evolved to the full sequence!" << std::endl;

	Sleep(10000000);

	return 0;
}