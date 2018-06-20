//Aidan Kennell, 5/28/2018
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <math.h>
#include <iostream>
using namespace std;

const float  PI = 3.14159265359;
const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 900;
const byte SEP_MASK = 1, ALI_MASK = 1 << 1, COH_MASK = 1 << 2;


struct Matrix2 {
	sf::Vector2f column1;
	sf::Vector2f column2;
};

struct Matrix3 {
	sf::Vector3f column1;
	sf::Vector3f column2;
	sf::Vector3f column3;
};


Matrix2 Inverse(Matrix2 matrix);
sf::Vector2f Normalize(sf::Vector2f inVec);
sf::Vector2f Mult(Matrix2 matrix, sf::Vector2f vector);
sf::Vector2f Centroid(sf::Vector2f vec1, sf::Vector2f vec2, sf::Vector2f vec3);
float Mag2(sf::Vector2f inVec);
float Dot(sf::Vector2f left, sf::Vector2f right);
float Determinant(Matrix2 matrix);
float Cross(sf::Vector2f left, sf::Vector2f right);
float Angle_Between(sf::Vector2f vec1, sf::Vector2f vec2);
void Get_Rotation_Matrix(Matrix2& rotation_matrix, float angle);

