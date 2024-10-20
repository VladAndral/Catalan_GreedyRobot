#include "GreedyRobot.h"
#include <iostream>

using namespace std;

GreedyRobot::GreedyRobot() :
    _max_movementDistance(0),
    _startingCoordinates{0, 0},
    _treasureCoordinates{0, 0}
{    }

GreedyRobot::GreedyRobot(int max_movementDistance, int startingX, int startingY, int treasureX, int treasureY) :
	_max_movementDistance(max_movementDistance),
    _startingCoordinates{startingX, startingY},
    _treasureCoordinates{treasureX, treasureY}
{
	_path_X_length = abs(_treasureCoordinates[0] - _startingCoordinates[0]);
	_path_Y_length = abs(_treasureCoordinates[1] - _startingCoordinates[1]);
	_path_length =  _path_X_length + _path_Y_length;
	_isShortestPathPossible = true;
	
	if (this->treasureX() > this->startingX()) {
		_directionsToGoIn[0] = 'E';
	} else if (this->treasureX() > this->startingX()) {
		_directionsToGoIn[0] = 'W';
	} else {
		_directionsToGoIn[0] = 'f';
	}

	if (this->treasureY() > this->startingY()) {
		_directionsToGoIn[1] = 'N';
	} else if (this->treasureY() > this->startingY()) {
		_directionsToGoIn[1] = 'S';
	} else {
		_directionsToGoIn[1] = 'f';
	}

}

ostream& operator<<(ostream& stream, const GreedyRobot& greedyRobot) {
	greedyRobot.print_shortestPaths();
	return stream;
}

istream& operator>>(istream& stream, GreedyRobot& greedyRobot) {
	int maximum_distance, startingX, startingY, treasureX, treasureY;
	stream >> maximum_distance >> startingX >> startingY >> treasureX >> treasureY;
	
	greedyRobot.set_max_movementDistance(maximum_distance);
	greedyRobot.set_startingX(startingX);
	greedyRobot.set_startingY(startingY);
	greedyRobot.set_treasureY(treasureY);
	greedyRobot.set_treasureY(treasureY);

	return stream;
}



int GreedyRobot::max_movementDistance() const {
    return _max_movementDistance;
}

int GreedyRobot::numberOfPaths() const {
    return _numberOfPaths;
}

int GreedyRobot::path_length() const {
    return _path_length;
}

int GreedyRobot::startingX() const {
    return _startingCoordinates[0];
}

int GreedyRobot::startingY() const {
    return _startingCoordinates[1];
}

int GreedyRobot::treasureX() const {
    return _treasureCoordinates[0];
}

int GreedyRobot::treasureY() const {
    return _treasureCoordinates[1];
}

void GreedyRobot::set_max_movementDistance(int num) {
	_max_movementDistance = num;
}

void GreedyRobot::set_startingX(int num) {
	_startingCoordinates[0] = num;
}

void GreedyRobot::set_startingY(int num) {
	_startingCoordinates[1] = num;
}

void GreedyRobot::set_treasureX(int num) {
	_treasureCoordinates[0] = num;
}

void GreedyRobot::set_treasureY(int num) {
	_treasureCoordinates[1] = num;
}


void GreedyRobot::print_shortestPaths() const {
	for (string path : _list_of_shortestPaths) {
		cout << path << endl;
	}
	cout << "Number of paths: " << _numberOfPaths << endl;
}

bool GreedyRobot::shortestPath_exists() const {
    return _isShortestPathPossible;
}


void GreedyRobot::find_shortestPaths() {
	array<int, 2> moves = {0 , 0};
	recursive_find_shortestPaths(_startingCoordinates, moves, 0, 0, _directionsToGoIn[0], "");
	
	if (!_list_of_shortestPaths.size()) {
		_list_of_shortestPaths.push_back("No paths exist for the coordinates and maximum foward movement.");
		_isShortestPathPossible = false;
		_numberOfPaths = 0;
	} else {
		_numberOfPaths = _list_of_shortestPaths.size();
	}
	
}

/*
	@param currentCoordinates[2] The x and y coordinates of where the robot is currently at [x, y]
	@param forwardMoves How many moves the robot has made in the current direction; resets each direction change
	@param moves[2] The total moves of x and y [totalMoves_xDirection, totalMoves_yDirection]
	@param directionSwitch Used to switch direction with %2 math
	@param direction The current direction the robot is currently going in (N, E, S, W)
	@param pathString The path of the robot as a string of N, E, S, W
*/
void GreedyRobot::recursive_find_shortestPaths(array<int, 2> currentCoordinates, array<int, 2> moves, int forwardMoves, int diretionSwitch, char direction, string pathString) { // bool whether can continue or not
	bool foundPath;
	/*
		BASE CASE
	*/
	if (!_isShortestPathPossible) {
		if (!_list_of_shortestPaths.size()) {
			_list_of_shortestPaths.push_back("No paths exist for the coordinates and maximum foward movement.");
		}
		_isShortestPathPossible = false;
		return;
	} else if ((currentCoordinates[0] == _treasureCoordinates[0]) && (currentCoordinates[1] == _treasureCoordinates[1])) { // if we are at the treasure
		_list_of_shortestPaths.push_back(pathString);
		return;
	} else if (forwardMoves == _max_movementDistance) { // if we've moved max amount of times in a direction or...
	// } else if ((forwardMoves == _max_movementDistance)||((moves[0] == _path_X_length) || (moves[1] == _path_Y_length))) { // if we've moved max amount of times in a direction or...
		if ((moves[0] > _path_X_length) || (moves[1] > _path_Y_length)) { // ... and if we have passed the max shortest x/y distane length
			return;
		} else {
			switch((int(direction))) { // ...but if we haven't reached max shortest x/y distance
				case int('N'): // if we've been moving (n)orth
					diretionSwitch++;
					direction = _directionsToGoIn[diretionSwitch%2];
					if (direction == 'E') {
						currentCoordinates[0]++;
					} else {
						currentCoordinates[0]--;
					}
					moves[0]++;
					forwardMoves = 1;
					pathString += direction;
					recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
					break;
				case int('E'): // if we've been moving (e)ast
					diretionSwitch++;
					direction = _directionsToGoIn[diretionSwitch%2];
					if (direction == 'N') {
						currentCoordinates[1]++;
					} else {
						currentCoordinates[1]--;
					}
					moves[1]++;
					forwardMoves = 1;
					pathString += direction;
					recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
					break;
				case int('S'): // if we've been moving (s)outh
					diretionSwitch++;
					direction = _directionsToGoIn[diretionSwitch%2];
					if (direction == 'E') {
						currentCoordinates[0]++;
					} else {
						currentCoordinates[0]--;
					}
					moves[0]++;
					forwardMoves = 1;
					pathString += direction;
					recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
					break;
				case int('W'): // if we've been moving (w)est
					diretionSwitch++;
					direction = _directionsToGoIn[diretionSwitch%2];
					if (direction == 'N') {
						currentCoordinates[1]++;
					} else {
						currentCoordinates[1]--;
					}
					moves[1]++;
					forwardMoves = 1;
					pathString += direction;
					recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
					break;
				default:
					_isShortestPathPossible = false;
			}
		}
	// } else if ((currentCoordinates[0] == treasureX()) && ((direction == 'E')||(direction == 'W'))) { // If we have reached the limit of x movement
	} else if ((moves[0] == _path_X_length) && ((direction == 'E')||(direction == 'W'))) { // If we have reached the limit of x movement
		if (currentCoordinates[0] == treasureX()) {
			diretionSwitch++;
			direction = _directionsToGoIn[diretionSwitch%2];
			if (direction == 'N') {
				currentCoordinates[1]++;
			} else if (direction == 'S') {
				currentCoordinates[1]--;
			} else {
				_isShortestPathPossible = false;
				return;
			}
			moves[1]++;
			forwardMoves = 1;
			pathString += direction;
			recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
		}
	// } else if ((currentCoordinates[1] == treasureY()) && ((direction == 'N')||(direction == 'S'))) { // If we have reached the limit of y movement
	} else if ((moves[1] == _path_Y_length) && ((direction == 'N')||(direction == 'S'))) { // If we have reached the limit of y movement
		diretionSwitch++;
		direction = _directionsToGoIn[diretionSwitch%2];
		if (direction == 'E') {
			currentCoordinates[0]++;
		} else if (direction == 'W') {
			currentCoordinates[0]--;
		} else {
			_isShortestPathPossible = false;
			return;
		}
		moves[0]++;
		forwardMoves = 1;
		pathString += direction;
		recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
	} else {
		if (direction == 'N') {
			currentCoordinates[1]++;
			moves[1]++;
			forwardMoves++;
			pathString += direction;
			recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
			
			if (moves[0] != _path_X_length) {
				pathString.pop_back(); // When recursing in another diretion, we need to remove the direction the other robot went in
				currentCoordinates[1]--;
				moves[1]--;
				forwardMoves--;
				
				diretionSwitch++;
				direction = _directionsToGoIn[diretionSwitch%2];
				if (direction == 'E') {
					currentCoordinates[0]++;
				} else {
					currentCoordinates[0]--;
				}
				moves[0]++;
				forwardMoves = 1;
				pathString += direction;
				recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
			}
		} else if (direction == 'S'){
			currentCoordinates[1]--;
			moves[1]++;
			forwardMoves++;
			pathString += direction;
			recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
			
			if (moves[0] != _path_X_length) {
				pathString.pop_back(); // When recursing in another diretion, we need to remove the direction the other robot went in
				currentCoordinates[1]++;
				moves[1]--;
				forwardMoves--;

				diretionSwitch++;
				direction = _directionsToGoIn[diretionSwitch%2];
				if (direction == 'E') {
					currentCoordinates[0]++;
				} else {
					currentCoordinates[0]--;
				}
				moves[0]++;
				forwardMoves = 1;
				pathString += direction;
				recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
			}
		} else if (direction == 'E'){
			currentCoordinates[0]++;
			moves[0]++;
			forwardMoves++;
			pathString += direction;
			recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
			
			if (moves[1] != _path_Y_length) {
				pathString.pop_back(); // When recursing in another diretion, we need to remove the direction the other robot went in
				currentCoordinates[0]--;
				moves[0]--;
				forwardMoves--;

				diretionSwitch++;
				direction = _directionsToGoIn[diretionSwitch%2];
				if (direction == 'N') {
					currentCoordinates[1]++;
				} else {
					currentCoordinates[1]--;
				}
				moves[1]++;
				forwardMoves = 1;
				pathString += direction;
				recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
			}
		} else if (direction == 'W') {
			currentCoordinates[0]--;
			moves[0]++;
			forwardMoves++;
			pathString += direction;
			recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
			
			if (moves[1] != _path_Y_length) {
				pathString.pop_back(); // When recursing in another diretion, we need to remove the direction the other robot went in
				currentCoordinates[0]++;
				moves[0]--;
				forwardMoves--;
				
				diretionSwitch++;
				direction = _directionsToGoIn[diretionSwitch%2];
				if (direction == 'N') {
					currentCoordinates[1]++;
				} else {
					currentCoordinates[1]--;
				}
				moves[1]++;
				forwardMoves = 1;
				pathString += direction;
				recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
			}
		} else {
			_isShortestPathPossible = false;
			return;
		}
	}
} 