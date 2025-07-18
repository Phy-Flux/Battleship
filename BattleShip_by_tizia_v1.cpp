#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <utility> 
#include <tuple> 
#include <algorithm> 
#include <random> 

using Battlefield = std::vector<std::vector<int>>;

std::string elementGrid(int num){
    std::string symb;
    switch (num)
    {
    case 0:
        symb = "   ";// or sea symbol " ~ ";
        break;
    case 1:
        symb = " X ";
        break;
    case 2:
        symb = " O ";
        break;
    case 3:
        symb = " * ";
        break;    
    }
    return symb;
}

int string_converter(char letter){
    int level;
    letter = std::toupper(letter);

    if (letter == 'A'){ level =0; }
    else if (letter == 'B'){ level =1; }
    else if (letter == 'C'){ level =2; }
    else if (letter == 'D'){ level =3; }
    else if (letter == 'E'){ level =4; }
    else if (letter == 'F'){ level =5; }
    else if (letter == 'G'){ level =6; }
    else if (letter == 'H'){ level =7; }
    else if (letter == 'I'){ level =8; }
    else if (letter == 'J'){ level =9; }
 
    return level;
}

std::vector<std::pair<int, int>> generateCells() {
    std::vector<std::pair<int, int>> cells;
    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            cells.emplace_back(i, j);
        }
    }
    return cells;
}

int updateBattle(Battlefield m_opponent, int cell_r, int cell_c){

    int choice = m_opponent[cell_r][cell_c];
    int hit;
    if (choice == 3){ hit = 1; } 
    else if (choice == 0){hit = 2; } 
    else if (choice == 1){ hit = 1; } 
    else{ hit = 2; } 
    return hit;
}

bool checkShips(Battlefield m){

    for (int i = 0; i<10; i++){
        for (int j = 0; j < 10; j++){
                int cell = m[i][j];
                if (cell == 3){
                    return true;
                }
                }
            }        
    return false;
}

void printExampleGrid(){
    std::cout << "   | A | B | C | D | E | F | G | H | I | J |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << " 1 |   |   |   |   |   |   |   | * |   |   |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << " 2 | * | * |   |   |   |   |   | * |   |   |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << " 3 |   |   |   |   |   |   |   |   |   |   |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << " 4 |   |   | * | * | * | * |   |   |   |   |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << " 5 | * |   |   |   | * | * | * | * | * |   | * " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << " 6 |   |   |   |   |   |   |   |   |   |   |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << " 7 |   | * | * |   |   |   |   | * |   |   |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << " 8 |   |   |   |   |   |   |   | * |   |   |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << " 9 |   |   |   |   | * |   |   | * |   |   |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';
    std::cout << "10 | * | * | * |   |   |   |   |   |   |   |   " << '\n';
    std::cout << "-----------------------------------------------" << '\n';

}

void updateGrid2(Battlefield m, Battlefield m_op){
    
    int i,j,k;

    std::cout << "_____________________PLAYER___________________                      ___________________OPPONENT___________________" << '\n';
    std::cout << "   | A | B | C | D | E | F | G | H | I | J |                           | A | B | C | D | E | F | G | H | I | J |     " << '\n';
    std::cout << "----------------------------------------------                      ----------------------------------------------" << '\n';    
    for (i = 0; i<10; i++){
        std::cout << " " << i << " |";
        for (j = 0; j < 10; j++){
            if (j==9){
                std::cout << elementGrid(m[i][j]) << "|                         " << i << " |";
                for (k = 0; k < 10; k++){
                    std::cout << elementGrid(m_op[i][k]) << "|";
                }
            }
            else{
                std::cout << elementGrid(m[i][j]) << "|";
            }
        }
        std::cout << '\n' << "----------------------------------------------                      ----------------------------------------------" << '\n';
    }

}

std::tuple<Battlefield, Battlefield> round_player(Battlefield m11,Battlefield m12,Battlefield m22){
    std::cout << "Current situation: \n";

    updateGrid2(m11,m12);

    int row_player1, col_player1;
    std::string row_user;
    char col_letter;
    int userNumber = 0 ;
    std::cout << "Choose the cell to hit: \n";
    
    do{
    std::cout << "Input row (enter number 0-9):";
    std::cin >> row_user;
        try {
            // Try to do the conversion
            row_player1 = stoi(row_user);

        } catch (const std::invalid_argument& ia) { 
        // Catch the invalid argument exception if conversion cannot be performed
            std::cerr << "Input must be an integer." << '\n';
        }

    }while(row_player1 <0 || row_player1 >9); // avoid bad selection
    
    do{
    std::cout << "Input column (enter letter A-J):";
    std::cin >> col_letter;
    col_player1 = string_converter(col_letter);
    }while(col_player1 <0 || col_player1 >9 );

    std::cout << "You choose cell: (" << row_player1 << ',' << col_player1 << "). Let's see if it hits... \n";


    int hit_round = updateBattle(m22, row_player1, col_player1);
    if (hit_round == 1 ){ 
        m22[row_player1][col_player1] = 1;
        std::cout << "STRIKE! \n "; } 
    else{ 
        m22[row_player1][col_player1] = 2;
        std::cout << "No hit.\n"; }

    m12[row_player1][col_player1] = hit_round;

    return {m22, m12};
}

std::tuple<Battlefield, Battlefield,std::vector<std::pair<int, int>> , std::vector<std::pair<int, int>>, char > round_pc(Battlefield m22,Battlefield m21,Battlefield m11, std::vector<std::pair<int, int>> gridCells, std::vector<std::pair<int, int>> hits, char last_hit){
    
    int row, col ;
    int index;
    int found = 0;

    // select a random grid point or one close to a previously hitted ship
    if (last_hit == 'N'){
        //Random engine setup
        std::random_device rd;
        std::mt19937 gen(rd());  
        std::uniform_int_distribution<> dist(0, gridCells.size() - 1);

        //Draw a random index
        index = dist(gen);
        std::pair<int, int> target = gridCells[index];

        row = target.first;
        col = target.second;
    
    }
    else{
        int lenght_hits = hits.size();  // lenght of the vector
        index = rand()%lenght_hits; // choose a random index
        std::pair<int, int> target = hits[index];
        
        // change target
        int change_target = rand()%4;
        std::pair<int, int> new_target;
        switch (change_target)
        {
        case 0:
             new_target = {0,-1};
            break;
        case 1:
            new_target = {0,1};
            break;
        case 2:
            new_target = {1,0};
            break;
        case 3:
            new_target = {-1,0};
            break;
        }
        
        row = target.first + new_target.first;
        col = target.second + new_target.second;
    
        target = {row,col};
        
        bool inRangeRow = (row >= 0 && row <= 9);
        bool inRangeCol = (col >= 0 && col <= 9);  
        // check if the point is inside the appropriate range of value
        if (inRangeRow && inRangeCol){
            // of it is, we need to check if it is in the available grid points
            auto it = std::find(gridCells.begin(), gridCells.end(), target);            
                if (it != gridCells.end()) {
                    found = 1;
                } 
                else {
                    int avail_point_size = gridCells.size();
                    int rdn_index = rand()%avail_point_size;
                    std::pair<int, int> selected = gridCells[rdn_index];

                    // Assign to individual variables
                    int row = selected.first;
                    int col = selected.second;    
                    target = {row,col};   
                    }
        }
        else{

            int avail_point_size = gridCells.size();
            int rdn_index = rand()%avail_point_size;
            std::pair<int, int> selected = gridCells[rdn_index];

            // Assign to individual variables
            int row = selected.first;
            int col = selected.second;    
            target = {row,col};
        }

    }

    std::cout << "Player 2 select grid point: (" << row << ", " << col << ")\n";

    int hit_round = updateBattle(m11, row, col);
    
    if (hit_round == 1 ){ 
        m11[row][col] = 1;
        hits.emplace_back(row, col);
        last_hit = 'Y';

        std::cout << "STRIKE! \n "; } 
    else{ 
        m11[row][col] = 2;
        //hits.clear();  // empties the vector
        std::cout << "No hit.\n"; }
        last_hit = 'N';

    // Update opponent battlefield
    m21[row][col] = hit_round;


    //Remove the selected combination from the list
    gridCells.erase(gridCells.begin() + index);

    return {m11, m21, gridCells, hits, last_hit};
}

Battlefield init_BattleField(){
                    std::vector<Battlefield> init_battlefields = { 
                    {{3,0,3,0,0,0,0,3,0,0},
                    {0,0,3,0,0,3,0,0,0,3},
                    {0,0,3,0,0,3,0,0,0,3},
                    {0,0,3,0,0,0,0,0,0,3},
                    {0,0,3,0,0,0,0,0,0,0},
                    {0,0,0,0,0,3,3,3,0,0},
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,0,3,3,3,3,0,0,0,0},
                    {0,0,0,0,0,0,3,0,0,0},
                    {3,3,0,0,0,0,3,0,0,3}},

                    {{0,0,0,0,3,3,0,0,0,0},
                    {3,0,0,0,0,0,0,0,0,0},
                    {3,0,0,0,3,0,0,3,0,0},
                    {3,0,0,3,0,0,0,3,0,0},
                    {3,0,0,0,0,0,0,3,0,0},
                    {3,0,3,3,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,3,3,3,0,3,0},
                    {0,3,0,0,0,0,0,0,0,0},
                    {0,3,0,0,0,3,3,3,3,0}},

                    {{3,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,3,3,3,3,3,0,0},
                    {0,3,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,3,3,0,0,0},
                    {0,3,0,0,0,0,0,3,0,0},
                    {0,0,0,3,0,3,0,3,0,0},
                    {3,0,0,3,0,3,0,3,0,0},
                    {3,0,0,0,0,0,0,3,0,0},
                    {3,0,3,3,3,0,0,0,0,0}},

                    {{0,3,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,3,3,3,3},
                    {0,0,3,0,0,0,0,0,0,0},
                    {0,0,3,0,0,0,0,0,0,0},
                    {0,0,0,0,3,0,3,3,0,0},
                    {3,3,3,0,3,0,0,0,0,0},
                    {0,0,0,0,3,0,0,0,0,0},
                    {3,3,3,0,3,0,0,3,3,0},
                    {0,0,0,0,3,0,0,0,0,0},
                    {0,0,0,3,0,0,0,0,3,0}},
    
                    {{0,0,3,3,3,3,3,0,0,0},
                    {0,0,0,0,0,0,0,0,0,3},
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,0,3,0,0,0,3,0,0,0},
                    {0,3,3,0,0,0,3,0,0,0},
                    {0,3,0,3,0,0,3,0,3,3},
                    {0,3,0,0,3,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0},
                    {3,3,3,3,0,0,3,0,0,0},
                    {0,0,0,0,0,0,3,0,0,0}},

                    {{3,3,3,3,3,0,0,0,0,0},
                    {0,0,3,3,3,3,0,0,3,0},
                    {0,0,3,0,0,3,0,0,3,0},
                    {0,0,3,0,0,0,0,0,0,0},
                    {0,0,3,0,0,0,0,0,0,0},
                    {0,0,0,0,0,3,3,3,0,0},
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,0,3,3,0,3,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0},
                    {3,3,0,0,0,0,0,0,0,3}},
                    
                    {{0,0,0,0,3,0,0,0,0,0},
                    {0,0,3,0,0,0,0,3,3,0},
                    {0,0,3,0,0,3,0,0,0,0},
                    {0,0,0,0,0,3,0,0,0,0},
                    {0,0,3,0,0,3,3,3,0,0},
                    {0,3,0,0,0,3,0,0,0,0},
                    {0,3,0,0,0,0,0,0,0,0},
                    {0,3,0,3,0,0,3,0,0,0},
                    {0,3,0,3,0,0,0,0,0,0},
                    {0,3,0,3,0,0,3,3,3,0}},
                    
                    {{0,0,0,0,0,0,0,0,3,0},
                    {0,3,0,3,3,3,0,0,3,0},
                    {0,0,0,0,0,0,0,0,3,0},
                    {0,0,0,0,0,0,0,0,3,0},
                    {0,3,0,3,3,3,0,0,3,0},
                    {0,3,0,0,0,0,0,0,0,0},
                    {0,3,0,0,0,0,0,0,0,0},
                    {0,3,0,3,3,0,0,0,0,0},
                    {0,0,0,0,3,3,0,0,3,0},
                    {3,0,0,0,0,3,3,0,0,0}},

                    {{0,3,3,3,0,0,3,3,0,0},
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,3,0,0,0,0,3},
                    {0,0,0,0,3,0,0,0,0,3},
                    {3,0,0,0,3,0,3,0,0,3},
                    {0,0,0,0,3,0,0,0,0,0},
                    {3,0,0,0,3,0,0,0,0,0},
                    {3,0,0,0,0,0,3,0,0,3},
                    {0,0,0,0,0,0,0,0,0,3},
                    {0,0,3,3,3,3,0,0,0,0}},
                   
                    {{0,0,3,3,0,0,0,0,0,0},
                    {0,0,0,3,3,0,0,0,0,0},
                    {0,0,0,0,0,3,3,3,0,0},
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,3,3,3,3,3,0},
                    {0,0,3,3,3,3,0,0,0,0},
                    {0,3,0,0,0,0,0,0,0,0},
                    {0,0,0,3,3,3,0,0,0,0},
                    {0,0,0,0,0,0,0,3,3,0},
                    {0,0,3,0,0,3,0,0,0,0}},

                    {{0,0,0,0,3,0,0,0,0,0},
                    {0,0,0,0,3,0,0,0,0,0},
                    {0,0,3,0,3,0,0,0,0,0},
                    {0,0,3,0,3,0,3,0,3,0},
                    {3,0,3,0,3,0,3,0,0,3},
                    {3,0,0,0,0,0,3,0,0,3},
                    {0,0,3,0,0,0,3,0,3,0},
                    {0,0,3,0,0,0,0,0,3,0},
                    {3,0,3,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,3}},

                    {{3,0,0,0,3,0,0,3,0,0},
                    {3,0,0,3,0,0,0,3,0,0},
                    {3,0,0,0,3,0,0,0,0,0},
                    {3,0,0,0,0,3,3,3,3,0},
                    {3,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,3,3,0},
                    {0,0,0,0,0,0,3,0,0,0},
                    {0,0,0,0,0,0,3,0,0,0},
                    {0,0,0,0,0,0,3,0,3,0},
                    {0,3,3,3,0,0,0,0,3,0}},
                    
                    {{0,0,0,0,0,0,0,3,3,0},
                    {0,0,0,0,3,3,0,0,0,0},
                    {0,0,3,0,0,0,0,0,0,0},
                    {0,0,3,0,0,3,3,3,0,0},
                    {0,0,3,0,0,0,3,0,3,0},
                    {0,0,3,0,0,0,3,0,3,0},
                    {0,0,0,3,0,0,3,0,0,0},
                    {0,0,0,0,3,0,0,0,0,0},
                    {0,0,0,3,3,3,3,3,0,0},
                    {0,0,0,0,0,0,3,0,0,0}},

                    {{0,0,0,0,0,0,0,0,0,0},
                    {0,3,0,0,0,3,3,3,3,3},
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,3,0,0,0,0,0,0,3,0},
                    {0,0,3,3,3,3,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,0,3,0,3,0,3,0,3,0},
                    {0,0,3,0,3,0,3,0,3,0},
                    {0,0,3,0,3,0,0,3,0,0},
                    {0,0,0,0,0,0,0,3,0,0}},
                }; // end batterfield vector

    std::srand(std::time(NULL));

    int index_random = rand()%10;

    return init_battlefields[index_random];
}

using Battlefield = std::vector<std::vector<int>>;

int main(){

    std::cout << "********WELCOME TO BATTLESHIP*********** \n";

    std::cout << "Rules: \n" ;
    
    std::cout << "_________________________________________________________________________________________________________________________________________________________________________ \n"; 
    std::cout << "| The game is played on four grids, two for each player. \n";
    std::cout << "| The grids are squares of 10 by 10 cells, and the individual squares in the grid are identified by letter from (A-J) for the columns and number from (0-9) for the rows. \n";
    std::cout << "| On one grid the player can see its own battleground and records of the opponent's shots. \n";
    std::cout << "| On the other grid, the player's previous actions are stored.\n";
    std::cout << "| To each player is given a battle template. \n";
    std::cout << "| Each ship occupies a number of consecutive squares on the grid, arranged either horizontally or vertically.";
    std::cout << "| The number of squares for each ship is determined by the type of ship. \n";
    std::cout << "| The types and numbers of ships allowed are the same for each player.";
    std::cout << "| To win, you must discover the opponent's ship positions.";
    std::cout << "| The number and type of ships at your disposal are: \n";
    std::cout << "| Destroyer: ***** x1; "  "Battleship: **** x1; " << "Cruiser : *** x2; " << "Submarine: ** x3; " << "Patrol boat: * x3; \n";
    std::cout << "| Examples of a battlefield and ships placement: \n";
    std::cout << "|___________________________________________________________________________________________________________________________________________________________________________ \n"; 
    
    printExampleGrid();
    
    std::string play= "Yes";
    std::cout << "Would you like to play? (Enter Yes or No): ";
    std::cin >> play;
    
    if (play == "Yes" ){
        std::cout << "******************************** START *********************************** \n";

        std::vector<std::vector<int>> M11 = init_BattleField() ;
        std::vector<std::vector<int>> M12(10, std::vector<int>(10, 0));
        std::vector<std::vector<int>> M22 = init_BattleField() ;
        std::vector<std::vector<int>> M21(10, std::vector<int>(10, 0));

        std::vector<std::pair<int, int>> gridCells = generateCells(); 
        std::vector<std::pair<int, int>> hit_counts; 
        
        char last_hit = 'N';
        std::cout << "The 1st moove goes to.....";
        
        int starting_player = rand()%2 ;
        switch (starting_player)
        {
        case 0:
            std::cout << "Player 1 start!";
            break;
        case 1:
            std::cout << "Player 2 start!";
            break;    
        default:
            break;
        }
        int counter = 1;

        if (starting_player == 0){
        
            do{ std::cout << "................................................ ROUND: "<< counter <<" ................................................ \n";
                std::cout << "-----------------------------------------------> Player 1 TURN <----------------------------------------------- \n";
                
                std::tie(M22, M12) = round_player(M11,M12, M22);

                std::cout << "-----------------------------------------------> Player 2 TURN: <----------------------------------------------- \n";

                std::tie(M11, M21, gridCells, hit_counts, last_hit) = round_pc(M22,M21,M11, gridCells, hit_counts , last_hit) ;

                counter+=1;

            }while( checkShips(M11)==1 && checkShips(M22)==1 && counter < 99);
        }
        else{

            do{ std::cout << "................................................ ROUND: "<< counter <<" ................................................ \n";
                std::cout << "-----------------------------------------------> Player 1 TURN <----------------------------------------------- \n";
                
                std::tie(M11, M21, gridCells, hit_counts, last_hit) = round_pc(M22,M21,M11, gridCells, hit_counts , last_hit) ;
        
                std::cout << "-----------------------------------------------> Player 2 TURN: <----------------------------------------------- \n";

                std::tie(M22, M12) = round_player(M11,M12, M22);

                counter+=1;

            }while( checkShips(M11)==1 && checkShips(M22)==1 && counter < 99);

        }

        if (checkShips(M22)==0){
            std::cout << "RESULT: ................................... Player 1 WIN !!!!!!!!!!!!!!!!! \n";        
        }
        else if(checkShips(M11)==0){
            std::cout << "RESULT: ................................... Player 2 WIN !!!!!!!!!!!!!!!!! \n";   
        }
        else{
            std::cout << "RESULT: ................................... Tie :) \n";   
        }

    }
    return 0;
}
