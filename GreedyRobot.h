#ifndef GREEDY_ROBOT_H_
#define GREEDY_ROBOT_H_
#include <iostream>

using namespace std;

class GreedyRobot {

    public:
        // CONSTRUCTOR
        GreedyRobot();
        GreedyRobot(int max_movementDistance, int startingX, int startingY, int treasureX, int tresureY);

        // GETS AND SETS
        int max_movementDistance() const;
        int numberOfPaths() const;
        int path_length() const;
        int startingX() const;
        int startingY() const;
        int treasureX() const;
        int treasureY() const;
        void print_listof_shortestPaths() const;
        void print_infoNoPaths() const;
        vector<string> list_of_shortestPaths() const;
        bool shortestPath_exists() const;
        void set_max_movementDistance(int num);
        void set_startingX(int num);
        void set_startingY(int num);
        void set_treasureX(int num);
        void set_treasureY(int num);
        void build();

        // RECURSIVE METHODS
        void find_shortestPaths();

        // OPERATOR OVERLOADS
        friend ostream& operator<<(ostream& stream, const GreedyRobot& greedyRobot);
        friend istream& operator>>(istream& stream, GreedyRobot& greedyRobot);


    private:
        int _max_movementDistance;
        int _numberOfPaths;
        array<int, 2> _startingCoordinates;
        array<int, 2> _treasureCoordinates;
        vector<string> _list_of_shortestPaths;
        int _path_length;
        int _path_X_length;
        int _path_Y_length;
        array<char, 2> _directionsToGoIn;

        bool _isShortestPathPossible;

        void recursive_find_shortestPaths(array<int, 2> currentCoordinates, array<int, 2> moves, int forwardMoves, int diretionSwitch, char direction, string pathString); // bool whether can continue or not

};



#endif