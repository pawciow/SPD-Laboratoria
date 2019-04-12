#include "NEH.h"
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
		int _endTime;

	protected:
		int _temperature;
		double _step;
		std::vector<std::pair<int, int>> newInstance;

		void lowerTemperature();
		int getRandomInt();
		double getRandomDistribution();
		double getPossibility(std::vector<std::pair<int, int>> newInstance);

		virtual std::vector<std::pair<int, int>> & generateMovement();
		bool isBetterResult();
};
