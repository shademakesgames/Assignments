#include "lander.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

const int TIME = 1; //1 second of time for the simulation function

lander::lander(string name, double mass, double thrust, double max_fuel,
						double alt, double fuel)
{
	lander_mass = mass;
	max_thrust = thrust;
	max_fuel_consumption_rate = max_fuel;

	stillLanding = true;
	flow_rate = 0.0;
	velocity = 0.0;
	altitude = alt;
	fuel_amount = fuel;
	this->name = name;
}


char lander::get_status() const
{
	// 'a' case
	if (altitude > 0.0)
	{
		return 'a';
	} else if (velocity <= -2.0) { //'c' case
		return 'c';
	} else { //'l' case
		return 'l';
	}
}

bool lander::change_flow_rate(double r)
{
	//inclusive case
	if (r >= 0 && r <= 1)
	{
		if (fuel_amount > 0)
		{
			flow_rate = r;
		} else {
			flow_rate = 0.0;
		}
		return true;
	}
	return false;
}

void lander::simulate()
{
	if (!stillLanding) return;
	//1. Calculate the instantanues velocity
	double v = TIME * ((flow_rate * max_thrust) / (lander_mass + fuel_amount)) - 1.62;
	//2. Increment / update the velocity field by v
	velocity += v;
	//3. Increment / update altitude field by TIME * velocity
	altitude += TIME * velocity;
	//4. Update stillLanding if necessary
	switch (get_status())
	{
	case 'a':
		stillLanding = true;
		break;
	case 'c':
		stillLanding = false;
		break;
	case 'l':
		stillLanding = false;
		break;
	default:
		break;
	}
	//5. Decrement / update fuel_amount by TIME * max_fuel_rate * abs(v)
	if (flow_rate != 0)
		fuel_amount -= TIME * max_fuel_consumption_rate * abs(v);
	//6. set fuel_amount to 0 if fuel_amount is negative
	if (fuel_amount < 0)
		fuel_amount = 0;
}

bool lander::operator<(const lander& rhs) const
{
	//compare *this with rhs based on a priority
	//two priority counters
	int priority_this = 0;
	int priority_rhs = 0;
	//1. The object with the smallest altitude has the higher priority
	if (altitude < rhs.altitude)
	{
		return true;
	} else if (altitude > rhs.altitude){
		return false;
	}
	//2. the object with less fuel has the higher priority
	if (fuel_amount < rhs.fuel_amount)
	{
		return true;
	} else if (fuel_amount > rhs.fuel_amount){
		return false;
	}
	//3. The object with larger mass has the priority
	if (lander_mass > rhs.lander_mass)
	{
		return true;
	} else if (lander_mass < rhs.lander_mass){
		return false;
	}
	//4. Object earlier in alphabetical order
	//check which name is shorter
	string shorter;
	if (name.length() > rhs.name.length())
		shorter = rhs.name;
	else
		shorter = name;
	//convert both strings to lowercase
	string this_lower;
	string rhs_lower;
	bool rhs_alpha = true;
	//parse through the shorter lowercase strings
	for (int i = 0; i < shorter.length(); i++)
	{
		rhs_lower.push_back(tolower(rhs.name[i]));
		this_lower.push_back(tolower(name[i]));
		if (this_lower[i] < rhs_lower[i])
		{
			rhs_alpha = false;
		}
	}
	//decide which one gets priority
	if (rhs_alpha)
		return false;
	else
		return true;
}
