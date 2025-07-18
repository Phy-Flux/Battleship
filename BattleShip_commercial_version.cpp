#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <utility> 
#include <tuple> 
#include <algorithm> 
#include <random> 

#include "BattleShip_fun.h"

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