// A424HW2.cpp : Defines the entry point for the application.
//

#include "A424HW2.h"
#include <unordered_map>
#include <random>
#include <chrono>
using namespace std;


// question 1
class Flightdistances {
public:
	unordered_map<string, unordered_map<string, int>> distances{
		{"SCE", {{"PHL", 160}, {"ORD", 640}, {"EWR", 220}}},
	/*	{"PHL", {{"SCE", 160}}},
		{ "ORD", { {"SCE", 640} } },
		{ "EWR", { {"SCE", 220} } }
		*/
	};
	
};

//question 2
class Plane {
protected:
	double wait_time;
private:
	double pos;
	double vel;
	double distance;
	double loiter_time;
	bool at_SCE;
	string origin;
	string destination;
	Flightdistances flightdistances;
public:
	//constructor
	 Plane(string& from, string& to) :
		 // storing inputs and initializing vars
		origin(from),
		destination(to),
		pos(0),
		vel(0),
		wait_time(0),
		loiter_time(0),
		at_SCE(0)
	 {
		distance = flightdistances.distances[origin][destination];

	}
	//virtual deconstructor
	//operate function
	void operate(double& dt) {
		if (loiter_time != 0) {
			loiter_time -= dt;
			if (loiter_time < 0)
				loiter_time = 0;
			return;
		}
		if (wait_time != 0) {
			wait_time -= dt;
			if (wait_time < 0)
				wait_time = 0;
			return;
		}
		if (pos < distance) {
			pos += vel * dt;
			at_SCE = 0;
			return;
		}
		if (destination == "SCE") {

			return;
		}
	}
	//get fucntions
	double getpos() {
		return pos;
	}
	double getvel() {
		return vel;
	}
	double getloiter_time() {
		return loiter_time;
	}
	string getorigin() {
		return origin;
	}
	string getdestination() {
		return destination;
	}
	bool getat_SCE() {
		return at_SCE;
	}
	// set functions
	void setvel(double& vel) {
		vel = vel;

	}
	void setloiter_time(double& loiter_time) {
		loiter_time = loiter_time;
		
	}
	//
	double distance_to_SCE() {
		return 0;
	}
	virtual double time_on_ground() {

	}
	virtual string plane_type() {
	
	}
	static double draw_from_normal_dist(double& mean, double& sigma) {
		//seed to ensure random number is different each time
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		default_random_engine generator(seed);
		normal_distribution<double> distribution(mean, sigma);
		return distribution(generator);
	}
};
int main()
{
	Flightdistances flightdistances;
	cout << " Distance from SCE to PHL : " << flightdistances.distances["SCE"]["PHL"] << endl;

	return 0;
}
