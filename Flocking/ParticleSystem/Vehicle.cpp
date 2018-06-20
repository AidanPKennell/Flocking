//Aidan Kennell, 5/28/2018
#include "Vehicle.h";

Vehicle::Vehicle(sf::Vector2f Start_Pos) {
	pos = Start_Pos;

	max_speed = 200;
	max_force = 40;

	vel = Normalize(sf::Vector2f(rand(), rand())) * max_speed;
	accel = sf::Vector2f(0, 0);

	triangle = sf::VertexArray(sf::Triangles, 3);

	triangle[0].position = pos + sf::Vector2f(-4, -4);
	triangle[1].position = pos + sf::Vector2f(-4, 4);
	triangle[2].position = pos + sf::Vector2f(8, 0);

	teleport_distance = Mag2(pos - triangle[0].position);

	for (int i = 0; i < 3; i++)
		triangle[i].color = sf::Color::White;
}

Vehicle::~Vehicle() {

}


void Vehicle::Update(float dt) {
	if (Mag2(vel) < max_speed)
		vel += accel * dt;
	else
		vel = Normalize(vel + accel * dt) * max_speed;

	for (int i = 0; i < 3; i++)
		triangle[i].position += vel * dt;


	Update_Rotation();
	pos = Centroid(triangle[0].position, triangle[1].position, triangle[2].position);

	Check_Teleport();

	accel *= 0.f;
}

//calculates and adds all of the forces acting on the vehicle to acceleration
void Vehicle::Flock(vector<Vehicle*>& vehicles, int total_vehicles, byte forces) {
	float separation_dist = 30, cohesion_dist = separation_dist + 20;
	sf::Vector2f steer;
	sf::Vector2f sparate_sum = sf::Vector2f(0, 0);
	sf::Vector2f cohesion_sum = sf::Vector2f(0, 0);
	sf::Vector2f align_sum = sf::Vector2f(0, 0);
	bool separation = false;
	int cohesion_count = 0;

	for (int i = 0; i < total_vehicles; i++) {
		Vehicle* boid = vehicles[i];
		float distance = Mag2(pos - boid->Get_Pos());

		if (forces & ALI_MASK)
			align_sum += boid->Get_Vel();

		if (distance > 0 && distance < separation_dist && forces & SEP_MASK) {
			sparate_sum += Normalize(pos - boid->Get_Pos());
			separation = true;
		}

		if (distance > 0 && distance < cohesion_dist && forces & COH_MASK) {
			cohesion_sum += boid->Get_Pos();
			cohesion_count++;
		}

	}

	////////////////////////////////////
	//ALIGN//
	if (forces & ALI_MASK) {
		align_sum = Normalize(align_sum) * max_speed;

		steer = align_sum - vel;

		if (Mag2(steer) > max_speed) {
			steer = Normalize(steer) * max_speed;
		}

		Add_Force(steer * alignment_multiplier);
	}

	////////////////////////////////////
	//Cohesion//
	if (cohesion_count > 0 && forces & COH_MASK) {
		cohesion_sum /= (float)cohesion_count;
		Follow(cohesion_sum);
	}

	////////////////////////////////////
	//Separation//
	if (separation && forces & SEP_MASK) {
		sparate_sum = Normalize(sparate_sum) * max_speed;

		steer = sparate_sum - vel;

		if (Mag2(steer) > max_speed) {
			steer = Normalize(steer) * max_speed;
		}

		Add_Force(steer * separation_multiplier);
	}
}

//adds a force to acceleration that causes the vehicle to start turning towars the input vector
void Vehicle::Follow(sf::Vector2f target) {
	sf::Vector2f desired = target - pos;
	desired = Normalize(desired) * max_speed;

	sf::Vector2f steer = desired - vel;
	if (Mag2(steer) > max_force)
		Add_Force(Normalize(steer) * max_force);
	else
		Add_Force(steer * cohesion_multiplier);
}

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	states.texture = NULL;

	target.draw(triangle, states);
}


//will rotate the vehicles so that they are facing the direction of their velocity
void Vehicle::Update_Rotation() {


	Matrix2 rotation_matrix;
	float angle = Angle_Between(triangle[2].position - pos, vel);

	Get_Rotation_Matrix(rotation_matrix, angle);
	
	for (int i = 0; i < 3; i++) {
		triangle[i].position -= pos;
		triangle[i].position = Mult(rotation_matrix, triangle[i].position) + pos;
	}

}

void Vehicle::Add_Force(sf::Vector2f force) {
	accel += force;
}

//Wraps the vehicles around the edges of the screen
void Vehicle::Check_Teleport() {
	//check top
	if(pos.y + teleport_distance < 0){
		for (int i = 0; i < 3; i++)
			triangle[i].position.y += WINDOW_HEIGHT - teleport_distance * 2;
		
		pos = Centroid(triangle[0].position, triangle[1].position, triangle[2].position);
		return;
	}

	//check bottom
	if (pos.y - teleport_distance > WINDOW_HEIGHT) {
		for (int i = 0; i < 3; i++)
			triangle[i].position.y -= WINDOW_HEIGHT + teleport_distance * 2;

		pos = Centroid(triangle[0].position, triangle[1].position, triangle[2].position);
		return;
	}

	//check left
	if (pos.x + teleport_distance < 0) {
		for (int i = 0; i < 3; i++)
			triangle[i].position.x += WINDOW_WIDTH - teleport_distance * 2;

		pos = Centroid(triangle[0].position, triangle[1].position, triangle[2].position);
		return;
	}

	//check right
	if (pos.x - teleport_distance > WINDOW_WIDTH) {
		for (int i = 0; i < 3; i++)
			triangle[i].position.x -= WINDOW_WIDTH + teleport_distance * 2;

		pos = Centroid(triangle[0].position, triangle[1].position, triangle[2].position);
		return;
	}
}