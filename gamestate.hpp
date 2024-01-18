#ifndef GameState_HPP
#define GameState_HPP
#define BOARD_SIZE 6
#include"ghost.hpp"
#include"player.hpp"
#include<iostream>
#include<vector>
using namespace std;

class GameState {
public:
    GameState() : gameOver(false) {}

    void initializeGame();
    void printBoard() const;
    bool isValidMove(int row, int col,Player &player) const;
    void makeMove(Player& player,int beforeRow,int beforeCol,int row, int col);
    void checkWin(Player &player1 ,Player &player2,int &winner,bool &gameOver) const;
    bool isBoardFull() const { return gameOver; }
    void playGame(GameState& game);

private:
    pair<Ghost,int> board[BOARD_SIZE][BOARD_SIZE];
    Player player1;
    Player player2;
    bool gameOver;
    int winner;
};

void GameState::initializeGame() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = make_pair(Ghost(' ', -1), 0);  // Initialize with empty ghost
        }
    }
    gameOver = false;
    winner = -1;
    player1.set_Num(0,0);
    player1.set_playerID(1);
    player2.set_Num(0,0);
    player2.set_playerID(2);

    // Player 1:
    cout << "Player 1, choose GOOD and EVIL ghost places (Input: row col): " << endl;
    for (int i = 0; i < 8; ++i) {
        int row, col;
        char type = (i < 4) ? 'G' : 'E';  // Determine the type based on i

        cout << (type == 'G' ? "GOOD " : "EVIL ") << i << ": ";
        cin >> row >> col;
        
        while(!isValidMove(row, col, player1) || board[col][row].first.getSymbol() != ' ' || !(row>=1 && row<=4 && col>=0 && col<=1)) {
            cout << "Invalid input, please input again." << endl;
            cout << (type == 'G' ? "GOOD " : "EVIL ") << i << ": ";
            cin >> row >> col;
        } 
        player1.addGhost(Ghost(type, i));  // Assign a unique ID to each ghost
        board[col][row] = player1.getGhosts()[i];
    }


    // Player 2:
    srand(static_cast<unsigned>(time(0)));  // Seed the random number generator
    for (int i = 0; i < 8; ++i) {
        int row, col;
        char type = (i < 4) ? 'G' : 'E';  // Determine the type based on i

        do {
            row = rand() % BOARD_SIZE;
            col = rand() % 2 + 4;
        } while (!isValidMove(row, col, player2) || board[col][row].first.getSymbol() != ' ' || !(row>=1 && row<=4 && col>=4 && col<=5));

        player2.addGhost(Ghost(type, i));  // Assign a unique ID to each ghost
        board[col][row] = player2.getGhosts()[i];
    }
    cout << "Player 2 is ready." << endl;
    gameOver = false;
}
void GameState::printBoard() const {
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if(board[i][j].second!=2)
                cout << board[i][j].first.getSymbol() << " ";
            else
                cout << "X"<< " ";
        }
        cout << endl;
    }
}

bool GameState::isValidMove(int row, int col, Player& player) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }

    // 確保這個位置是空的或上面的鬼不是自己的鬼
    if(board[col][row].second!=player.get_playerID()){
        return true;
    }


    return false;
}

void GameState::makeMove(Player& player,int beforeRow,int beforeCol,int row, int col) {
    if(isValidMove(row,col,player)){
        
        if(board[col][row].first.getSymbol()==' '){
            board[col][row]=board[beforeCol][beforeRow];
            board[beforeCol][beforeRow]=make_pair(Ghost(' ', -1), 0);
  
        }
        else{
            if(board[col][row].first.getSymbol()=='G'){
                player.set_Num(player.get_G_Num()+1,player.get_E_Num());
            }
            else{
                player.set_Num(player.get_G_Num(),player.get_E_Num()+1);
            }
            board[col][row]=board[beforeCol][beforeRow];
            board[beforeCol][beforeRow]=make_pair(Ghost(' ', -1), 0);
               
        }
        
    }
}
//判斷遊戲有沒有結束
void GameState::checkWin(Player &player1 ,Player &player2,int &winner,bool &gameOver) const {
    if(player1.get_G_Num()==4||player1.get_E_Num()==4){
        if(player1.get_G_Num()==4)
            winner=1;
        else
            winner=2;
        gameOver=true;
    }
    else if(player2.get_G_Num()==4||player2.get_E_Num()==4){
        if(player2.get_G_Num()==4)
            winner=2;
        else
            winner=1;
        gameOver=true;
    }
    else if((board[0][0].first.getSymbol()=='G' && board[0][0].second == 2) || (board[0][5].first.getSymbol()=='G' && board[0][5].second == 2)){
        winner=2;
        gameOver=true;
    }
    else if((board[5][0].first.getSymbol()=='G' && board[5][0].second == 1 )|| (board[5][5].first.getSymbol()=='G' && board[5][5].second == 1)){
        winner=1;
        gameOver=true;
    }
    else{
        gameOver=false;
    }
}


void GameState::playGame(GameState& game) {
    initializeGame();
    int player;
    cout<<"Who will play first?(Input 1 or 2):"<< endl;
    cin>>player;
    int playerTurn = player;
    int beforeRow=0,beforeCol=0;
    while (!game.isBoardFull()) {
        if(playerTurn==1){
            
            int row, col;
            cout << "Player " << playerTurn << ",choose the ghost you want to move(Input : row col): " << endl;
            do{
                cin >> row >> col;
                if(board[col][row].second!=1){
                    cout<<"Invalid input,please input again(Input : row col):"<<endl;
                    continue;
                }
            }
            while(board[col][row].second!=1);
            
            beforeRow=row;
            beforeCol=col;

            char direction;
            cout << "Player " << playerTurn << ",choose the direction(Input : w or a or s or d): " ;
            do{
                cin >> direction;
                if(direction=='w'){
                    col=col+1;
                }
                else if(direction=='a'){
                    row=row+1;
                }
                else if(direction=='s'){
                    col=col-1;
                }
                else if(direction=='d'){
                    row=row-1;
                }
                else{
                    cout << "Invalid input,please input again(Input : w or a or s or d):" << endl;
                    continue;
                }
            }while(!isValidMove(row, col,player1)) ;
            
            makeMove(player1,beforeRow,beforeCol,row,col);
            cout<<"Player "<<playerTurn<<" move ghost "<<board[col][row].first.getID()<<endl;
            printBoard();
            checkWin(player1,player2,winner,gameOver);
            if(gameOver){
                cout<<"Player "<<winner<<" wins!"<<endl;
                break;
            }
        }
        else{
            //換player2 他是隨機選擇移動的選自己有的ghost
            int row, col;
            do {
                row = rand() % BOARD_SIZE;
                col = rand() % BOARD_SIZE;
                
            } while (board[col][row].second!=2);
            beforeRow=row;
            beforeCol=col;
            //選擇方向
            char direction;
            do{
                int random=rand()%4;
                if(random==0){
                    direction='w';
                    col=col+1;
                }
                else if(random==1){
                    direction='a';
                    row=row+1;
                }
                else if(random==2){
                    direction='s';
                    col=col-1;
                }
                else if(random==3){
                    direction='d';
                    row=row-1;
                }
            }while(!isValidMove(row, col,player2)) ;
            makeMove(player2,beforeRow,beforeCol,row,col);
            cout<<"Player "<<playerTurn<<" move ghost "<<board[col][row].first.getID()<<endl;
            printBoard();

            checkWin(player1,player2,winner,gameOver);
            if(gameOver){
                cout<<"Player "<<winner<<" wins!"<<endl;
                break;
            }
        }
        playerTurn = playerTurn == 1 ? 2 : 1;
    }
}
#endif

