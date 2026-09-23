#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "priorityQ.h"
#include "lander.h"
using namespace std;

void printTop3(priorityQ<string, lander>& queue)
{
	string keys[3];
	lander landers[3];
	int count = 0;
	//print the top 3 in the queue
	for (int i = 0; i < 3 && !queue.isEmpty(); i++)
	{
		keys[i] = queue.get_front_key();
		landers[i] = queue.get_front_priority();

		//format it correctly
		cout << "(" << (i + 1) << ") Name: " << keys[i]
			 << " " << fixed << setprecision(6) << landers[i].get_altitude()
			 << " meters from the moon surface" << endl;
		cout << "traveling at " << fixed << setprecision(6) << landers[i].get_velocity() << " m/s" << endl;
		cout << "Fuel: " << fixed << setprecision(6) << landers[i].get_fuel_amount() << endl;
		cout << endl;

		count++;
		queue.pop_front();
	}
	//push them back in the queue
	for (int i = 0; i < count; i++)
	{
		queue.push_back(keys[i], landers[i]);
	}
}

int main()
{
	priorityQ<string, lander> raceToTheMoon;
	ifstream infile("LanderInput.txt");
	double mass, max_thrust, max_fuel, alt, fuel;
	string name;

	//read in the variables and push them in the queue
	while (infile >> name >> mass >> max_thrust >> max_fuel >> alt >> fuel)
	{
		lander l(name, mass, max_thrust, max_fuel, alt, fuel);
		raceToTheMoon.push_back(name, l);
	}
	infile.close();

	//print the top 3
	printTop3(raceToTheMoon);

	//loop while the queue is not empty
	while (!raceToTheMoon.isEmpty())
	{
		cout << "Enter lander name and throttle amount: " << endl;

		//get name and throttle
		string name;
		double throttle;
		//if fail, exit
		if (!(cin >> name >> throttle))
			break;
		//update and simulate
		lander l = raceToTheMoon.get_element(name);
		l.change_flow_rate(throttle);
		l.simulate();
		raceToTheMoon.update_element(name, l);
		//print the status of the landers
		while (!raceToTheMoon.isEmpty())
		{
			lander front = raceToTheMoon.get_front_priority();
			char status = front.get_status();
			if (status == 'c')
			{
				//c case
				cout << raceToTheMoon.get_front_key() << " crashed :(" << endl;
				raceToTheMoon.pop_front();
			} else if (status == 'l') {
				//l case
				cout << raceToTheMoon.get_front_key() << " landed :)" << endl;
				raceToTheMoon.pop_front();
			} else {
				break;
			}
		}
		//print top 3
		if (!raceToTheMoon.isEmpty())
		{
			printTop3(raceToTheMoon);
		}
	}

	return 0;
}