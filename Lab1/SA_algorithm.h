#include "NEH.H"
#include <random>
#include <cstdlib>
class SA : public NEH
{
public:
	SA() = delete;
	SA(int startingTemperature, double iterationStep)
		:_temperature(startingTemperature), _step(iterationStep)
	{
		std::cout << "Utworzono obiekt SA z parametrami: " << _temperature << " , " << _step;
	}
	void getStartingState();
	void setExampleFromFile(std::string fileName);
	void StartComputing();
protected:
	int _temperature; 
	double _step;
	virtual std::vector<std::pair<int, int>> & generateMovement();
	double getRandomDistribution();
	double getPossibility(std::vector<std::pair<int, int>> newInstance);
	bool isBetterResult();
	void lowerTemperature();
};