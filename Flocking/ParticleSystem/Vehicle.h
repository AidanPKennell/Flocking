//Aidan Kennell, 5/28/2018
#pragma once
#include "MatrixFunctions.h";

class Vehicle : public sf::Drawable, public sf::Transformable{
public:
	Vehicle(sf::Vector2f Start_Pos);
	~Vehicle();
	void Update(float dt);
	void Flock(vector<Vehicle*>& vehicles, int total_vehicles, byte forces);

private:
	sf::VertexArray triangle;
	sf::Vector2f vel;
	sf::Vector2f accel;
	sf::Vector2f pos;
	float max_speed, max_force, teleport_distance;
	float separation_multiplier = 1, alignment_multiplier = 0.2, cohesion_multiplier = .5;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Follow(sf::Vector2f target);
	void Update_Rotation();
	void Add_Force(sf::Vector2f);
	void Check_Teleport();
	sf::Vector2f Get_Pos() { return pos; };
	sf::Vector2f Get_Vel() { return vel; };
};