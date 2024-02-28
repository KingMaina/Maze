#include "../include/init.h"

/**
* normaliseAngle - normalise the angle to be between 0 and 2*PI
* @angle: angle to normalise
* Return: normalised angle
*/
float normaliseAngle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

/**
* distanceBetweenPoints - calculate the distance between two points
* @x1: x-coordinate of the first point
* @y1: y-coordinate of the first point
* @x2: x-coordinate of the second point
* @y2: y-coordinate of the second point
*
* Return: distance between the two points
*/
float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
