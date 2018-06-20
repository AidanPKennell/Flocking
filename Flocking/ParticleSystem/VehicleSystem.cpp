//Aidan Kennell, 5/28/2018
#include "VehicleSystem.h";


VehicleSystem::VehicleSystem() {
	total_vehicles = 0;
}

VehicleSystem::~VehicleSystem() {
	for (int i = 0; i < total_vehicles; i++)
		delete vehicles[i];
}

void VehicleSystem::Update(float dt, byte forces) {
	for (int i = 0; i < total_vehicles; i++) {
		vehicles[i]->Flock(vehicles, total_vehicles, forces);
		vehicles[i]->Update(dt);
	}
}

void VehicleSystem::Add_Vehicle(sf::Vector2f position) {
	vehicles.push_back(new Vehicle(position));
	total_vehicles++;

	cout << total_vehicles << endl << endl;
}

void VehicleSystem::Remove_Vehicle() {
	if (total_vehicles > 0) {
		Vehicle* temp = vehicles[total_vehicles - 1];
		vehicles.pop_back();
		delete temp;
		total_vehicles--;
	}
}

void VehicleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	states.texture = NULL;

	for (int i = 0; i < total_vehicles; i++) {
		target.draw(*vehicles[i], states);
	}
}

