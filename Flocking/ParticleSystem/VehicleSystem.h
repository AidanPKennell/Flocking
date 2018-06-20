//Aidan Kennell, 5/28/2018
#pragma once
#include "Vehicle.h";

class VehicleSystem : public sf::Drawable, public sf::Transformable {
public:
	VehicleSystem();
	~VehicleSystem();
	void Add_Vehicle(sf::Vector2f position);
	void Remove_Vehicle();
	void Update(float dt, byte forces);

private:
	vector<Vehicle*> vehicles;
	float separation = 100, alignment, cohesion;
	int total_vehicles;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};