#include<chrono>
#include<iostream>

class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
	Timer() : start(std::chrono::high_resolution_clock::now()) {}

	void reset()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	double elapsed() const
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);

		return duration.count() * 1e-6; //to seconds
	}
};