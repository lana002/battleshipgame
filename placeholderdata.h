//TO BE CHANGED
#include <stdio.h>
#define GRID_SIZE 10 
#define TOTALNUMBEROFSHIPS 4

typedef struct {
    char *name;          // Ship name
    int size;           // Ship size
    char id;            // Ship identifier
    int occupiedCells[5][3];
    // (row, col, hit_status); 3rd column tracks hit status: 0 for not hit, 1 for hit max 5 cells for largest ship.              
    char direction;                        //could be 'H' or 'V'
} Ship;

typedef struct player {
    int turn;                               //1 its their turn, 0 its not their turn.
    char board[GRID_SIZE][GRID_SIZE];       //contains placement of ships across the 10x10 board //tentative could be removed.
    char hits[GRID_SIZE][GRID_SIZE];        // grid with ~ for water, o for miss, * for hit.This is for hits and misses done by the opponent on this player's board
    int numOfShipsSunken;                   //when initializing players, set to zero. Useful for victory checking.Ships sunken by the opponent of this player's ships.
    Ship ships[TOTALNUMBEROFSHIPS];         //array of their ships. to be initialized.
} Player; 



int movesuccess=0;                         //zero for fail , one for success
int gamedifficulty=0;                      //zero for easy, one for hard
char affectedArea[GRID_SIZE][GRID_SIZE];   // temporary grid for affected cells per each move.clears after every turn.
char MoveTypes[]={'F','R','S','A','T'};    //codename for fire,radar sweep,smoke screen, artillery,torpedo.
                                           //for now, not explicitly used anywhere, just referenced in function markAffectedArea