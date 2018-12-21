#pragma once

#include <string>
#include <vector>

class Population
{
public:

	struct Member {
		std::string dna;
		int fitness;
	};

public:

	Population(const std::string goal_dna, int population_size) {

		members = std::vector<Member>(population_size);

		for (int i = 0; i < members.size(); i++) {	// Generate all the population with random DNA (0 fitness)
			members.at(i).dna.resize(goal_dna.size());

			for (int j = 0; j < goal_dna.size(); j++)
				members.at(i).dna.at(j) = (unsigned char)rand() % 96 + 32; // random code ascii from 32 to 128

			members.at(i).fitness = 0;
		}

	}

public:

	std::vector<Member> members;

};