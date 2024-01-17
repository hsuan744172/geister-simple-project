#include"ghost.hpp"
using namespace std;
#define BOARD_SIZE 6

class Player {
public:
    Player() {}

    void addGhost(Ghost ghost) { ghosts.push_back({ghost,playerID}); }
    const vector<pair<Ghost,int>>& getGhosts() const { return ghosts; }
    void set_Num(int g_num,int e_num){G_Num=g_num;E_Num=e_num;}
    int get_G_Num() const {return G_Num;}
    int get_E_Num() const {return E_Num;}
    void set_playerID(int id){playerID=id;}
    int get_playerID() const {return playerID;}

private:
    vector<pair<Ghost,int>> ghosts;
    int playerID=0;
    int G_Num=0;
    int E_Num=0;
};
