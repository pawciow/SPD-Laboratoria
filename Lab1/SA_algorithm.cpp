#include"SA_algorithm.h"
#include <random>
#include "math.h"
#include <ctime>
void SA::setExampleFromFile(std::string fileName)
{
	NEH::LoadFromFile(fileName);
}

void SA::getStartingState()
{
	NEH::DO();
}
/*
std::vector<std::pair<int, int>> SA::generateMovement() // TODO : wymyœliæ coœ xd
{
	std::cout << "NOWA MO¯LIWOŒÆ \n";
	return std::vector<std::pair<int, int>>{}; 
}*/

double SA::getRandomDistribution()
{
	std::uniform_real_distribution<> distr;
	std::default_random_engine generator;
	return distr(generator);
}

double SA::getPossibility(std::vector<std::pair<int, int>> newInstance)
{
	int Pi = countTime(optimalTaskList);
	int newPi = countTime(newInstance);
	double possibility;
	if (newPi > Pi)
		possibility = exp((Pi - newPi) / _temperature);
	else
		possibility = 1;
	return possibility;
}

void SA::StartComputing()
{
	getStartingState();
	int beginTime = countTime(optimalTaskList);
	int endTime;
	while (_temperature > 0)
	{
		auto newInstance = generateMovement();
		double possibility = getPossibility(newInstance);
		if (possibility > getRandomDistribution())
			optimalTaskList = newInstance;
		lowerTemperature();
		std::cout <<std::endl << "At temperature : " << _temperature << " OptimalTaskList: ";
		for (auto e : optimalTaskList)
			std::cout << e.first << "," << e.second << " ";
		//std::cout << "time : " << countTime(optimalTaskList);
		endTime = countTime(optimalTaskList);
	}

	std::cout << " \n \n " << "Porównianie czasów: na pocz¹tku:" << beginTime << " na koñcu: " << endTime;
}

void SA::lowerTemperature()
{
	_temperature =  _temperature - (_temperature * _step);
}

std::vector<std::pair<int, int>> & SA::generateMovement()
{
	std::srand(std::time(nullptr));
	unsigned int a = (std::rand() % optimalTaskList.size()) - 1;
	unsigned int b = std::rand() % optimalTaskList.size() - 1;
	if (a == b)
		return generateMovement(); /*To prevent from not swaping anything*/
	else
	{
		std::vector<std::pair<int, int>> newInstance = optimalTaskList;
		std::swap(newInstance[a], newInstance[b]);
		return newInstance;
	}
}
