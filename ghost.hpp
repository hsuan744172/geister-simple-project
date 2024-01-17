#ifndef GHOST_HPP
#define GHOST_HPP
#include <vector>
using namespace std;

#define BOARD_SIZE 6


class Ghost {
public:
    Ghost( char s, int id) :symbol(s), ghostID(id) {}
    Ghost():symbol(' '),ghostID(-1){}

    char getSymbol() const { return symbol; }
    int getID() const { return ghostID; }

private:
    char symbol;
    int ghostID;

};
#endif


