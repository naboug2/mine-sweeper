/**------------------------------------------
MineSweeper
System: MacOS using VSCode
Author: Nuha Abougoash 
-------------------------------------------*/
#include <iostream> 
#include <string>

using namespace std;

const int width = 5;
const int height = 8;

const int UNFLAGGED_MINE = -1; //The cell is mine that has not been flagged yet
const int FLAGGED_MINE = -2; //The cell has been correctly flagged as a mine
const int INCORRECT_FLAGGED_MINE = -3; //The cell has been incorrectly flagged as a mine
const int UNKNOWN = -4; //The initial state of the cell. 
		       
//The number of mine in the field
const int num_mine = 10;

//We need one variable for each cell. The subscript of variables show the position of the cell in the field.
int c00, c01, c02, c03, c04, 
	c10, c11, c12, c13, c14,
	c20, c21, c22, c23, c24,
	c30, c31, c32, c33, c34,
	c40, c41, c42, c43, c44,
	c50, c51, c52, c53, c54,
	c60, c61, c62, c63, c64,
	c70, c71, c72, c73, c74 = UNKNOWN;

//These three variables shows the state of games. 
int num_incorrect_flagged_mine = 0; //number of incorrectly flagged cells
int num_correct_flagged_mine = 0;  //number of correctly flagged cells
bool explode = false; // if the field has exploded or not


string getTag(int c, bool explode);
void displayField(bool explode);
void setCell(int i, int j, int value);
int getCell(int i, int j);
void setMine(int num_of_mine);
void initField(int num_of_mine);
bool isMine(int i, int j);
void reveal(int i,int j); 
void executeCmd(string cmd);



//The helper getTag function returns the appropriate string (one character) to be shown in each cell depending on the state of the game
string getTag(int c, bool explode) {
	string tag;
	switch (c) {
		case UNKNOWN:
			tag = "-";
			break;
		case UNFLAGGED_MINE:
			if (explode) 
				tag = "*";
			else 
				tag = "-";
			break;
		case FLAGGED_MINE:
			tag = "!";
			break;
		case INCORRECT_FLAGGED_MINE:
			if (explode)
				tag = "&";
			else
				tag = "!";
			break;
		default:
			tag = to_string(c);
	};
	return tag;
}


//The displayField function displays the mine field (including the indices of the columns and rows)
void displayField(bool explode) {
	cout << "   0 1 2 3 4" <<endl << endl;
	cout << "0  " << getTag(c00, explode) << " " << getTag(c01, explode) << " " << getTag(c02, explode) << " " << getTag(c03, explode) << " " << getTag(c04, explode) << endl;
	cout << "1  " << getTag(c10, explode) << " " << getTag(c11, explode) << " " << getTag(c12, explode) << " " << getTag(c13, explode) << " " << getTag(c14, explode) << endl;
	cout << "2  " << getTag(c20, explode) << " " << getTag(c21, explode) << " " << getTag(c22, explode) << " " << getTag(c23, explode) << " " << getTag(c24, explode) << endl;
	cout << "3  " << getTag(c30, explode) << " " << getTag(c31, explode) << " " << getTag(c32, explode) << " " << getTag(c33, explode) << " " << getTag(c34, explode) << endl;
	cout << "4  " << getTag(c40, explode) << " " << getTag(c41, explode) << " " << getTag(c42, explode) << " " << getTag(c43, explode) << " " << getTag(c44, explode) << endl;
	cout << "5  " << getTag(c50, explode) << " " << getTag(c51, explode) << " " << getTag(c52, explode) << " " << getTag(c53, explode) << " " << getTag(c54, explode) << endl;
	cout << "6  " << getTag(c60, explode) << " " << getTag(c61, explode) << " " << getTag(c62, explode) << " " << getTag(c63, explode) << " " << getTag(c64, explode) << endl;
	cout << "7  " << getTag(c70, explode) << " " << getTag(c71, explode) << " " << getTag(c72, explode) << " " << getTag(c73, explode) << " " << getTag(c74, explode) << endl;
}


//The setCell functions assign a value to the cell specified by its position (row and column) in the field
void setCell(int i, int j, int value) {
	if (i == 0 && j == 0) 
		c00 = value;
	else if (i == 0 && j == 1)
		c01 = value;
	else if (i == 0 && j == 2)
		c02 = value;
	else if (i == 0 && j == 3)
		c03 = value;
	else if (i == 0 && j == 4)
		c04 = value;
	else if (i == 1 && j == 0)
		c10 = value;
	else if (i == 1 && j == 1)
		c11 = value;
	else if (i == 1 && j == 2)
		c12 = value;
	else if (i == 1 && j == 3)
		c13 = value;
	else if (i == 1 && j == 4)
		c14 = value;
	else if (i == 2 && j == 0)
		c20 = value;
	else if (i == 2 && j == 1)
		c21 = value;
	else if (i == 2 && j == 2)
		c22 = value;
	else if (i == 2 && j == 3)
		c23 = value;
	else if (i == 2 && j == 4)
		c24 = value;
	else if (i == 3 && j == 0)
		c30 = value;
	else if (i == 3 && j == 1)
		c31 = value;
	else if (i == 3 && j == 2)
		c32 = value;
	else if (i == 3 && j == 3)
		c33 = value;
	else if (i == 3 && j == 4)
		c34 = value;
	else if (i == 4 && j == 0)
		c40 = value;
	else if (i == 4 && j == 1)
		c41 = value;
	else if (i == 4 && j == 2)
		c42 = value;
	else if (i == 4 && j == 3)
		c43 = value;
	else if (i == 4 && j == 4)
		c44 = value;
	else if (i == 5 && j == 0)
		c50 = value;
	else if (i == 5 && j == 1)
		c51 = value;
	else if (i == 5 && j == 2)
		c52 = value;
	else if (i == 5 && j == 3)
		c53 = value;
	else if (i == 5 && j == 4)
		c54 = value;
	else if (i == 6 && j == 0)
		c60 = value;
	else if (i == 6 && j == 1)
		c61 = value;
	else if (i == 6 && j == 2)
		c62 = value;
	else if (i == 6 && j == 3)
		c63 = value;
	else if (i == 6 && j == 4)
		c64 = value;
	else if (i == 7 && j == 0)
		c70 = value;
	else if (i == 7 && j == 1)
		c71 = value;
	else if (i == 7 && j == 2)
		c72 = value;
	else if (i == 7 && j == 3)
		c73 = value;
	else if (i == 7 && j == 4)
		c74 = value;
}


//The getCell function return the value of the cell specified by its row and column index in the field.
int getCell(int i, int j) {
	int value;
	if (i == 0 && j == 0) 
		value = c00; 
	else if (i == 0 && j == 1)
		value = c01;
	else if (i == 0 && j == 2)
		value = c02;
	else if (i == 0 && j == 3)
		value = c03;
	else if (i == 0 && j == 4)
		value = c04;	
	else if (i == 1 && j == 0)
		value = c10;
	else if (i == 1 && j == 1)
		value = c11;
	else if (i == 1 && j == 2)
		value = c12;
	else if (i == 1 && j == 3)
		value = c13;
	else if (i == 1 && j == 4)
		value = c14;
	else if (i == 2 && j == 0)
		value = c20;
	else if (i == 2 && j == 1)
		value = c21;
	else if (i == 2 && j == 2)
		value = c22;
	else if (i == 2 && j == 3)
		value = c23;
	else if (i == 2 && j == 4)
		value = c24;
	else if (i == 3 && j == 0)
		value = c30;
	else if (i == 3 && j == 1)
		value = c31;
	else if (i == 3 && j == 2)
		value = c32;
	else if (i == 3 && j == 3)
		value = c33;
	else if (i == 3 && j == 4)
		value = c34;
	else if (i == 4 && j == 0)
		value = c40;
	else if (i == 4 && j == 1)
		value = c41;
	else if (i == 4 && j == 2)
		value = c42;
	else if (i == 4 && j == 3)
		value = c43;
	else if (i == 4 && j == 4)
		value = c44;
	else if (i == 5 && j == 0)
		value = c50;
	else if (i == 5 && j == 1)
		value = c51;
	else if (i == 5 && j == 2)
		value = c52;
	else if (i == 5 && j == 3)
		value = c53;
	else if (i == 5 && j == 4)
		value = c54;
	else if (i == 6 && j == 0)
		value = c60;
	else if (i == 6 && j == 1)
		value = c61;
	else if (i == 6 && j == 2)
		value = c62;
	else if (i == 6 && j == 3)
		value = c63;
	else if (i == 6 && j == 4)
		value = c64;
	else if (i == 7 && j == 0)
		value = c70;
	else if (i == 7 && j == 1)
		value = c71;
	else if (i == 7 && j == 2)
		value = c72;
	else if (i == 7 && j == 3)
		value = c73;
	else if (i == 7 && j == 4)
		value = c74;
	return value;
}


//The function setMine randomly assigns a predefined number of mines to the field
void setMine(int num_of_mine) {
	int current_mine = 0; // The number of assigned mines so far.
	while (current_mine < num_of_mine) {

		int i = rand() % height; 

		//We do the same for the column index
		int j = rand() % width;

		//If we have already selected the cell we should continue with another random cell
		//Otherwise we set the cell to be a mine 
		if ( getCell(i,j) != UNFLAGGED_MINE) {
			setCell(i,j, UNFLAGGED_MINE);
			current_mine++;
		}
	}
}


//The initField function initilizes the field with UNKOWN cells and then randomly sets some of the cells to be mine (using the setMin function)
void initField(int num_of_mine) {
    for (int i = 0; i < height; i++) {  // take every row and column in the field and set the cell to UNKNOWN
        for (int j = 0; j < width; j++){
            setCell(i,j, UNKNOWN);
        }
    }
    setMine(num_of_mine);  //call function to randomly set some cell to be a mine
}


//The isMine function checks whether a cell is a mine or not
//a cell is a mine if its state is FLAGGED_MINE or UNFLAGGED_MINE 
bool isMine(int i, int j) {
    if (getCell(i,j) == UNFLAGGED_MINE || getCell(i,j) == FLAGGED_MINE) {  // a cell is mine if it is UNFLAGGED or FLAGGED
        return true; 
    }
	return false;
}


//The reveal function set an appropriate values to each cell based on the player move.
//The function is called when the player decides that a cell is not a mine and wants to reveal it.
void reveal(int i,int j) {
    int count = 0;
    if (isMine(i,j)){ 
        explode = true;
    }
    else { //check if surround cells are with the field and increment count
        if (i-1 >= 0 && j-1 >= 0 && isMine(i-1,j-1)){ 
            count ++;
        }
        if (i-1 >= 0 && isMine(i-1,j)){ //
            count ++;
        }
        if (i-1 >= 0 && j+1 < width && isMine(i-1,j+1)){ 
            count ++;
        }
        if (j-1 >= 0 && isMine(i,j-1)){ 
            count ++;
        }
        if (j+1 < width && isMine(i,j+1)){ 
            count ++;
        }
        if (i+1 < height && j-1 >= 0 && isMine(i+1,j-1)){
            count ++;
        }
        if (i+1 < height && isMine(i+1,j)){ 
            count ++;
        }
        if (i+1 < height && j+1 < width && isMine(i+1,j+1) ){ 
            count ++;
        }
        setCell(i,j,count); //set corresponding cell with appropriae count number
    }
}


//The executeCmd function takes a command and change the state of game and the cells accordingly. 
void executeCmd(string cmd) {
    //when user wants to flag a cell, check first index of input for 'f' 
    //check which cell user wants flag by looking at index of input, with i as row and j as col    
    if (cmd[0] == 'f') {
        int i = cmd[1] - '0';
        int j = cmd[2] - '0';
        if (getCell(i,j) == UNFLAGGED_MINE) { //if UNFLAGGED cell was chosen, set cell as FLAGGED and increment correctly
            setCell(i,j, FLAGGED_MINE);
            num_correct_flagged_mine++ ;
        }
        else if (getCell(i,j) == UNKNOWN){ //if UNKNOW cell was chose, set cell as FLAGGED but increment incorrectly
            setCell(i,j, INCORRECT_FLAGGED_MINE);
            num_incorrect_flagged_mine++;
        }
    }

    //when user wants to reveal a cell, check first index of input for 'r' 
    //check which cell user wants flag by looking at index of input, with i as row and j as col
    else if (cmd[0] == 'r') {
        int i = cmd[1] - '0';
        int j = cmd[2] - '0';
        reveal(i,j);  //call reveal function at inputted cell
    }

    //when user wants to undo a cell, check first index of input for 'u' 
    //check which cell user wants flag by looking at index of input, with i as row and j as col
    else if (cmd[0] == 'u') {
        int i = cmd[1] - '0';
        int j = cmd[2] - '0';
        if (getCell(i,j) == FLAGGED_MINE) { //if chosen cell was FLAGGED, then to undo, set as UNFLAGGED and decrease correctly
            setCell(i,j, UNFLAGGED_MINE);
            num_correct_flagged_mine--;
        }
        else if (getCell(i,j) == INCORRECT_FLAGGED_MINE) { //if chosen cell was INCORRET FLAGGED, then to undo, revert it to be an UNKNOW cell and decrease incorrectly
            setCell(i,j, UNKNOWN);
            num_incorrect_flagged_mine--;
        }
    }
}


//The main function of the program
int main() {
	srand(0);
	initField(num_mine); //call function to initialize 10 random cells as a mine
	string cmd;	
	
	displayField(false); //call function to display field as in progress
    //while field does not explode AND (the num of correctly flagged cells is less than 10 OR the num of correctly flagged cells is greater than true)

	while (!explode && (num_correct_flagged_mine < num_mine || num_incorrect_flagged_mine > 0)) {

		cout << "Enter cmd:" << endl;
		cin >> cmd; //ask user to input cmd after each round for as long as game is in- progress
		
		executeCmd(cmd); // call function to change cell appropiatley based off user input

		displayField(explode); // call functio to set state of game as false (in prog)
		cout << "Number of mine left: " << num_mine - (num_correct_flagged_mine + num_incorrect_flagged_mine) << endl; // counter for number of mines left
	}

    // if does not explode then smiley face, else if explodes then lose game
	if (!explode) {
		cout << ":)" << endl;

	} else {
		cout << ":(" << endl;
	}
	return 0;
}
