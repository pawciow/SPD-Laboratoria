#include"SA_algorithm.h"
#include <random>
#include "math.h"
#include <ctime>
void SA::setExampleFromFile(std::string fileName)
{
	LoadFromFile(fileName);
}

void SA::getStartingState()
{
	DO();
}

double SA::getRandomDistribution()
{
	std::uniform_real_distribution<double> distr(0.0 , 1.1);
	std::default_random_engine generator;
	return distr(generator);
}
int SA::getRandomInt()
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(0, optimalTaskList.size()-1);
	return dis(gen);
}

double SA::getPossibility(std::vector<std::pair<int, int>> newInstance)
{
	int Pi = countTime(optimalTaskList);
	int newPi = countTime(newInstance);
	double possibility;
	if (newPi >= Pi)
		possibility = exp((Pi - newPi) / _temperature);
	else
		possibility = 1;
	return possibility;
}

void SA::StartComputing()
{
	getStartingState();
	int beginTime = countTime(optimalTaskList);
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
	}
	_endTime = countTime(optimalTaskList);
	std::cout << " \n \n " << "Porównianie czasów: na pocz¹tku:" << beginTime << " na koñcu: " << _endTime;
}

void SA::lowerTemperature()
{
	_temperature =  _temperature - (_temperature * _step);
}

std::vector<std::pair<int, int>> & SA::generateMovement()
{
	unsigned int a = getRandomInt();
	unsigned int b = getRandomInt();
	newInstance = optimalTaskList;
	std::swap(newInstance[a], newInstance[b]);
	return newInstance;
}
