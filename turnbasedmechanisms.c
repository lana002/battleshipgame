#include <placeholderdata.h>

void playerswitch(Player *p1, Player *p2){
    if (p1->turn==1) //player one's turn
    {
        displayBoardOf(&p2,gamedifficulty);
    }
    
}

void HitOrMiss(Player *attacker, Player *defender, int x, int y, char movetype, char direction) {
    markAffectedArea(x, y, movetype, direction);
    int HitRegister=0;

    // Iterate over the affected area to check for hits
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (affectedArea[i][j] == 'X') {           // Affected
                char shipID = defender->board[i][j];   // Get the ship identifier
                if (shipID != '~') {                    // Check if there's a ship
                    // Check if the cell has already been hit
                    if (defender->hits[i][j] != '*') { //* means it was hit in a previous turn

                        // Find the ship using its ID directly
                        for (int k = 0; k < TOTALNUMBEROFSHIPS; k++) {
                            if (defender->ships[k].id == shipID) {
                                // update the hit status in occupiedCells
                                for (int m = 0; m < defender->ships[k].size; m++) {
                                    if (defender->ships[k].occupiedCells[m][0] == i &&
                                        defender->ships[k].occupiedCells[m][1] == j) {
                                        defender->ships[k].occupiedCells[m][2] = 1; // Mark as hit
                                        break;
                                    }
                                }
                                //update info 
                                defender->hits[i][j] = '*';
                                HitRegister++;
                                HitOrMissMessageDisplay(1);
                                
                                // Check if the ship is sunk
                                if (isShipSunk(&defender->ships[k]) == 1) {
                                    printf("%s has been sunk!\n", defender->ships[k].name);
                                    defender->numOfShipsSunken++;
                                }
                                break; //Exit
                            }
                        }
                    }
                } else {
                    // It's water, mark as miss
                    if (defender->hits[i][j] == '~') {
                        defender->hits[i][j] = 'o'; // Mark as miss
                    }
                }
            }
        }
    }
    if (HitRegister==0)
    {
        HitOrMissMessageDisplay(0);
    }
    
}

void HitOrMissMessageDisplay(int movesuccess){ //after any move is completed, 
    if (movesuccess==0) //MISS                 //pass the message success or not to display output 
    {                                          
       printf("Miss!");
    }
    if (movesuccess==1)//HIT
    {
        printf("Hit!");
    }
}

void markAffectedArea(int x, int y, char moveType, char direction) { //this function is ONLY for HITS so far.
                                                                     //validation of placement for a move is NOT accounted for as they are checked in each move's respective function.
    // Reset affected grid for new move incoming                     //radar sweep and smoke screen are NOT accounted for as they do not inflict direct hits.
    for (int i = 0; i <= GRID_SIZE; i++){                            //direction is only to account for the column/row move.
        for (int j = 0; j <= GRID_SIZE; j++)
            affectedArea[i][j] = '~';
    }
        
    // Mark the affected cells based on move type, Note that X is for affected
    if (moveType == 'F') { //sinle cell
        affectedArea[x][y]='X'; 
    }
    else if (moveType == 'A') { //2x2 area
        affectedArea[x][y] = 'X';
        affectedArea[x + 1][y] = 'X';
        affectedArea[x][y + 1] = 'X';
        affectedArea[x + 1][y + 1] = 'X';
    }
    else if (moveType == 'T') {
        if (direction == 'H') { //row move
            for (int i = 0; i < GRID_SIZE; i++) {
                affectedArea[x][i] = 'A';
            }
        } else if (direction == 'V') { //column move
            for (int i = 0; i < GRID_SIZE; i++) {
                affectedArea[i][y] = 'A';
            }
        }
    }
}

// Function to check if the ship is sunk. 0 is fail 1 is success
int isShipSunk(Ship *ship) { 
    for (int i = 0; i < ship->size ; i++) {
        if (ship->occupiedCells[i][2] == 0)
        {
            return 0;
        }
        
    }
    return 1; // All parts are hit
}
