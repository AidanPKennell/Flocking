//Aidan Kennell, 5/28/2018
#include "MatrixFunctions.h"

//Calculates the magnitude of a 2D vector
float Mag2(sf::Vector2f inVec) {
	return  sqrt(inVec.x * inVec.x + inVec.y * inVec.y);
}

//normalizes a 2D vector
sf::Vector2f Normalize(sf::Vector2f inVec) {
	float mag = Mag2(inVec);

	if (mag <= 0)
		return sf::Vector2f(0, 0);

	return inVec  * (1 / mag);
}

//Multiplys a 2x2 matrix and a 2D vector, and returns the resulting 2D vector
sf::Vector2f Mult(Matrix2 matrix, sf::Vector2f vector) {
	sf::Vector2f newVec;
	newVec.x = matrix.column1.x * vector.x + matrix.column2.x * vector.y;
	newVec.y = matrix.column1.y * vector.x + matrix.column2.y * vector.y;
	return newVec;
}

//Performs the Dot Product on two 2D vectors
float Dot(sf::Vector2f left, sf::Vector2f right) {
	return left.x * right.x + left.y * right.y;
}

//Computes the Determinant of a matrix
float Determinant(Matrix2 matrix) {
	return matrix.column1.x * matrix.column2.y - matrix.column1.y * matrix.column2.x;
}

//Will return an Inverse matrix for the input matrix
Matrix2 Inverse(Matrix2 matrix) {
	Matrix2 outMatrix;
	float det = Determinant(matrix);

	if (det == 0) {
		outMatrix.column1.x = 0;
		outMatrix.column1.y = 0;
		outMatrix.column2.x = 0;
		outMatrix.column2.y = 0;
	}
	else {
		outMatrix.column1.x = matrix.column2.y / det;
		outMatrix.column2.y = matrix.column1.x / det;
		outMatrix.column1.y = -1 * matrix.column1.y / det;
		outMatrix.column2.x = -1 * matrix.column2.x / det;
	}

	return outMatrix;
}

//Performs the cross product on 2, 2D vectors
float Cross(sf::Vector2f left, sf::Vector2f right) {
	return left.x * right.y - left.y * right.x;
}

//Will compute the angle between two 2D vectors
float Angle_Between(sf::Vector2f vec1, sf::Vector2f vec2) {
	return atan2(vec2.y, vec2.x) - atan2(vec1.y, vec1.x);
}

//returns the center of mass for 3 2D vectors
sf::Vector2f Centroid(sf::Vector2f vec1, sf::Vector2f vec2, sf::Vector2f vec3) {
	return sf::Vector2f((vec1.x + vec2.x + vec3.x) / 3, (vec1.y + vec2.y + vec3.y) / 3);
}

//Computes a rotation matrix for a given angle
void Get_Rotation_Matrix(Matrix2& rotation_matrix, float angle) {
	rotation_matrix.column1 = sf::Vector2f(cos(angle), sin(angle));
	rotation_matrix.column2 = sf::Vector2f(-sin(angle), cos(angle));
}

