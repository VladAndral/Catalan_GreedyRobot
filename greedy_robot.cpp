#include "greedy_robot.h"
#include <iostream>

using namespace std;

/*
	IDEA:
	ONLY GO IN ONE DIRECTION, AND FOR EACH LIST ELEMENT, FLIP X-AXIS DIRECTION TO Y-AXIS DIRECTION

	^ NEVERMIND, ONLY WORKS FOR SQUARES, AND FRANKLY IS MORE WORK THEN BASIC RECURSION
*/

int main(int argc, char *argv[]) { // argv is a pointer to the first element in the array
	// for (int i = 0; i < 6; i++) {
	// 	cout << *(argv+i) << endl;
	// }
	GreedyRobot toReturn(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), stoi(argv[5])); // argv[0] is name of program; we don't need to dereference bc stoi() handles it for us
	toReturn.print_listof_shortestPaths();
}

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
	build();
}

void GreedyRobot::build() {
	_path_X_length = abs(_treasureCoordinates[0] - _startingCoordinates[0]);
	_path_Y_length = abs(_treasureCoordinates[1] - _startingCoordinates[1]);
	_path_length =  _path_X_length + _path_Y_length;
	_isShortestPathPossible = true;
	
	/*
		'f' TELLS US THAT THERE IS NO CHANGE IN X/Y, E.G. (1, 2) -> (1, 9)
	*/
	if (this->treasureX() > this->startingX()) {
		_directionsToGoIn[0] = 'E';
	} else if (this->treasureX() < this->startingX()) {
		_directionsToGoIn[0] = 'W';
	} else {
		_directionsToGoIn[0] = 'f';
	}

	if (this->treasureY() > this->startingY()) {
		_directionsToGoIn[1] = 'N';
	} else if (this->treasureY() < this->startingY()) {
		_directionsToGoIn[1] = 'S';
	} else {
		_directionsToGoIn[1] = 'f';
	}

	find_shortestPaths();
}

ostream& operator<<(ostream& stream, const GreedyRobot& greedyRobot) {
	// stream << "\nStarting X: " << greedyRobot.startingX()
	// 		<< "\nStarting Y: " << greedyRobot.startingY()
	// 		<< "\nTreasure X: " << greedyRobot.treasureX()
	// 		<< "\nTreasure Y: " << greedyRobot.treasureY()
	// 		<< "\nShortest Path Length: " << greedyRobot.path_length()
	// 		<< "\nMax Forward Moves: " << greedyRobot.max_movementDistance();
	greedyRobot.print_infoNoPaths();
	return stream;
}

istream& operator>>(istream& stream, GreedyRobot& greedyRobot) {
	int maximum_distance, startingX, startingY, treasureX, treasureY;
	stream >> maximum_distance >> startingX >> startingY >> treasureX >> treasureY;
	
	greedyRobot.set_max_movementDistance(maximum_distance, false);
	greedyRobot.set_startingX(startingX, false);
	greedyRobot.set_startingY(startingY, false);
	greedyRobot.set_treasureX(treasureX, false);
	greedyRobot.set_treasureY(treasureY, false);
	greedyRobot.build();

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

void GreedyRobot::set_max_movementDistance(int num, bool findPaths) {
	_max_movementDistance = num;
	if (findPaths) {
		find_shortestPaths();
	}
}

void GreedyRobot::set_startingX(int num, bool findPaths) {
	_startingCoordinates[0] = num;
	if (findPaths) {
		find_shortestPaths();
	}
}

void GreedyRobot::set_startingY(int num, bool findPaths) {
	_startingCoordinates[1] = num;
	if (findPaths) {
		find_shortestPaths();
	}
}

void GreedyRobot::set_treasureX(int num, bool findPaths) {
	_treasureCoordinates[0] = num;
	if (findPaths) {
		find_shortestPaths();
	}
}

void GreedyRobot::set_treasureY(int num, bool findPaths) {
	_treasureCoordinates[1] = num;
	if (findPaths) {
		find_shortestPaths();
	}
}


void GreedyRobot::print_listof_shortestPaths() const {
	// string toReturn = "";
	// for (string path : _list_of_shortestPaths) {
	// 	toReturn += path + "\n";
	// }
	// toReturn += "Number of paths: " + to_string(_numberOfPaths) + "\n";
	// cout << toReturn;
	for (string path : _list_of_shortestPaths) {
		cout << path << endl;
	}
	cout << "Number of paths: " << _numberOfPaths << endl;
}

void GreedyRobot::print_infoNoPaths() const {
	cout << "\nStarting X: " << startingX()
		<< "\nStarting Y: " << startingY()
		<< "\nTreasure X: " << treasureX()
		<< "\nTreasure Y: " << treasureY()
		<< "\nShortest Path Length: " << path_length()
		<< "\nMax Forward Moves: " << max_movementDistance();
	cout << "\nNumber of paths: " << _numberOfPaths << endl;
}

vector<string> GreedyRobot::list_of_shortestPaths() const {
	return _list_of_shortestPaths;
}

bool GreedyRobot::shortestPath_exists() const {
    return _isShortestPathPossible;
}


void GreedyRobot::find_shortestPaths() {

	if (_startingCoordinates == _treasureCoordinates) {
		_list_of_shortestPaths.push_back("Robot starts at treasure");
		_numberOfPaths = 0;
		return;
	} else if (_max_movementDistance == 0) {
		_list_of_shortestPaths.push_back("No paths exist for the coordinates and maximum foward movement.");
		_isShortestPathPossible = false;
		_numberOfPaths = 0;
		return;
	}

	array<int, 2> moves = {0, 0};
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
	@param pathString The path of the robot as a string combination of 'N', 'E', 'S', and/or 'W'
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
	/*
		AT TREASURE
	*/
	} else if ((currentCoordinates[0] == _treasureCoordinates[0]) && (currentCoordinates[1] == _treasureCoordinates[1])) { // if we are at the treasure
		_list_of_shortestPaths.push_back(pathString);
		return;
	/*
		MAXED OUT FORWARD MOVES
	*/
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
				default: // If we've moved max amount of times in a direction and we can't switch directions (if direction == 'f')...
					_isShortestPathPossible = false;
			}
		}
	/*
		AT BOUNDARY, X AXIS
	*/
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
	/*
		AT BOUNDARY, Y AXIS
	*/
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
	/*
		IF NONE OF THE ABOVE, SEND ROBOT IN BOTH DIRECTIONS (X AND Y AXIS) TOWARD TREASURE
	*/
	} else {
		if (direction == 'N') {
			currentCoordinates[1]++;
			moves[1]++;
			forwardMoves++;
			pathString += direction;
			recursive_find_shortestPaths(currentCoordinates, moves, forwardMoves, diretionSwitch, direction, pathString);
			
			/*
				DON'T SEND A ROBOT IN THE OTHER DIRECTION IF MOVES ARE MAXED OUT IN THAT DIRECTION
			*/
			if (moves[0] != _path_X_length) {
				pathString.pop_back(); // When recursing in another diretion, we need to remove the direction the other robot just went in
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