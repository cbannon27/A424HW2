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
	 Plane(const string& from, const string& to) :
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
	virtual ~Plane() {
		
	}
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
			at_SCE = 1;
		}
		time_on_ground();
			//swap origin and destination
		std:: swap(origin, destination);
		pos = 0.0;
		return;
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
	void setvel(const double& v_mph) {
		vel = v_mph;

	}
	void setloiter_time(double& loiter_time) {
		loiter_time = loiter_time;
		if (loiter_time < 0) {
			loiter_time = 0;
		}
	}
	// uhhhh
	double distance_to_SCE() {
		if (destination == "SCE") {
			return distance - pos;
		}
	}
	virtual double time_on_ground() {
		return wait_time;
	}
	virtual string plane_type() {
		return "GA";
	}
	static double draw_from_normal_dist(double& m, double& sd) {
		std::random_device rd{};
		std::mt19937 gen{ rd() };
		std::normal_distribution<> d{ m, sd };
		return d(gen);
	}
};

//question 4 derived classes airliner and generaviation
class Airliner : public Plane {
private:
	string Airline;
public:
	//constructor
	Airliner(const string & Airline,const string& from, const string& to) :
		Airline(Airline),
		Plane(from,to)
	{}
	//deconstructor
	~Airliner() {}
	//overriding plane type
	string plane_type() override {
		return Airline;
	}
	//randomizing time on ground
	double time_on_ground() override {
		double m = 1800;
		double sd = 600;
		wait_time= draw_from_normal_dist(m, sd);
		return wait_time;
	}
};

class GeneralAviation : public Plane {
public:
	//constructor
	GeneralAviation(const string& from, const string& to) :
		Plane(from, to)
	{}
	//deconstructor
	~GeneralAviation() {}
	//randomizing time on ground
	double time_on_ground() override {
		double m = 600;
		double sd = 60;
		wait_time = draw_from_normal_dist(m, sd);
		return wait_time;
	}
};
int main()
{
	//instantiating objects
	Airliner AA1{"AA", "SCE", "PHL"};
	Airliner UA1("UA", "SCE", "ORD");
	Airliner UA2("UA", "SCE", "EWR");
	Airliner AA2("AA", "SCE", "ORD");
	GeneralAviation GA1 ("SCE", "PHL");
	GeneralAviation GA2("SCE", "EWR");
	GeneralAviation GA3("SCE", "ORD");

	// assigning velocities
	AA1.setvel(470 );
	UA1.setvel(515 );
	UA2.setvel(480 );
	AA2.setvel(500 );
	GA1.setvel(140 );
	GA2.setvel(160 );
	GA3.setvel(180 );

	//test time yay!
	//timestep
	double dt = 100;
	int i = 0;

			while (i<10) {
				//calling operate function for each plane
				AA1.operate(dt);
				UA1.operate(dt);
				UA2.operate(dt);
				AA2.operate(dt);
				GA1.operate(dt);
				GA2.operate(dt);
				GA3.operate(dt);

				//displaying each position
				cout << "AA1 Position: " << AA1.getpos() << endl;
				cout << "UA1 Position: " << UA1.getpos() << endl;
				cout << "UA2 Position: " << UA2.getpos() << endl;
				cout << "AA2 Position: " << AA2.getpos() << endl;
				cout << "GA1 Position: " << GA1.getpos() << endl;
				cout << "GA2 Position: " << GA2.getpos() << endl;
				cout << "GA3 Position: " << GA3.getpos() << endl;
				i++;
			}
			return 0;
		
}

