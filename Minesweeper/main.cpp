//Created by Selim Gul 29200
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>     // for setw
#include <vector>

using namespace std;

int maxRow, maxCol; //these are global variables to prevent user inputs go out of matrix's range.

void readColsRows(int& rows, int& cols, ifstream& input) {
	string fileName, line;
	cout << "Enter the input file name: ";
	cin >> fileName;
	input.open(fileName.c_str());
	while (!input) { // if the file cannot be opened successfully get input until it can be opened
		cout << "Problem occurred while reading the file!!!" << endl;
		cout << "Enter the input file name: ";
		cin >> fileName;
		input.open(fileName.c_str());
	}
	if (input) {  // if the file opened sucessfully
		cout << "Welcome to the Minesweeper Game!" << endl;
		getline(input, line); // parse file line by line
		istringstream iss(line);
		iss >> rows >> cols; //read the first line to define rows and columns
	}
}


void readMatrix(ifstream& input, vector<vector<char> >& ansMat, int rows, int cols) { /*the function here reads the matrix using the ifstream, it doesn't read the first line because we used getline at the first function. */
	for (int i = 0; i < rows; i++) { //this matrix will be used as our answer matrix
		for (int j = 0; j < cols; j++) {
			input >> ansMat[i][j];
		}
	}
}


void printMatrix(vector<vector<char> >& mat) { //function to print the matrix, used a reference parameter here because it will be modified each time
	int rows = (int)mat.size();
	if (rows != 0) {
		int cols = (int)mat[0].size();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << setw(4) << mat[i][j];
			}
			cout << endl;
		}
	}
	cout << endl; //these endlines are required in the sample runs
	cout << endl;
}

void getChoice(string& choice, int& selectedRow, int& selectedCol) { // get the users choice as required
	string line;
	cout << "Please enter your choice: ";
	cin >> line; //define choice, rows and cols of the user input.
	choice = line;
	getline(cin, line);
	stringstream iss;
	iss << line;
	iss >> selectedRow >> selectedCol;
}


/*
void getChoice(string& choice, int& selectedRow, int& selectedCol) { // get the users choice as required
	cout << "Please enter your choice: ";
	cin >> choice >> selectedRow >> selectedCol;//define choice, rows and cols of the user input.
}*/


bool isMine(int row, int col, vector<vector<char> > ansMat, string choice) { //check if the selected cell is mine
	if (ansMat[row][col] == 'x' && choice == "-o") {
		return true; //returns true if the choice is opening the bomb and cell contains bomb. choice check doesn't affect our program because it won't check if it's mine if the input is -b or -h.
	}
	else {
		return false; //returns false if it's not bomb
	}
}


bool checkMatrix(vector<vector<char> >& mat, int maxRow, int maxCol) { // return true if matrix is completed
	for (int i = 0; i < maxRow + 1; i++) {
		for (int j = 0; j < maxCol + 1; j++) {
			if (mat[i][j] == '.') {
				return false;
			}
		}
	}
	return true;
}

bool checkBombs(vector<vector<char> >& mat, int maxRow, int maxCol, vector<vector<char> > ansMat) { //returns false if bombs are placed correctly
	for (int i = 0; i < maxRow + 1; i++) {
		for (int j = 0; j < maxCol + 1; j++) {
			if (ansMat[i][j] == '-') {
				if (mat[i][j] == 'B') {
					return true;
				}
			}
		}
	}
	return true;
}

bool checkValid(int row, int col) { //check if a cell exists (should be used to check the adjacent mines)
	return (row >= 0) && (row <= maxRow) && (col >= 0) && (col <= maxCol);
}


int countMines(int row	, int col, vector<vector<char> >& ansMat, string choice) {
	int count = 0;
	if (checkValid(row - 1, col) == true) { //upper cell
		if (isMine(row - 1, col, ansMat, choice) == true) {
			count++;
		}
	}
	if (checkValid(row + 1, col) == true) { //bottom cell
		if (isMine(row + 1, col, ansMat, choice) == true) {
			count++;
		}
	}
	if (checkValid(row, col -1) == true) { //left cell
		if (isMine(row, col -1, ansMat, choice) == true) {
			count++;
		}
	}
	if (checkValid(row, col + 1) == true) { //right cell
		if (isMine(row, col + 1, ansMat, choice) == true) {
			count++;
		}
	}
	if (checkValid(row - 1, col + 1) == true) { //upper right cell
		if (isMine(row - 1, col + 1, ansMat, choice) == true) {
			count++;
		}
	}
	if (checkValid(row + 1, col - 1) == true) { //bottom left cell
		if (isMine(row + 1, col - 1, ansMat, choice) == true) {
			count++;
		}
	}
	if (checkValid(row - 1, col - 1) == true) { //upper left cell
		if (isMine(row - 1, col - 1, ansMat, choice) == true) {
			count++;
		}
	}
	if (checkValid(row + 1, col + 1) == true) { //bottom right cell
		if (isMine(row + 1, col + 1, ansMat, choice) == true) {
			count++;
		}
	}
	return count;
}

bool checkHelp(vector<vector<char> >& mat, int rows, int cols) { //returns true if all cells are closed
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (mat[i][j] != '.' || mat[i][j] < '1') {
				return false;
			}
		}
	}
	return true;
}

bool checkNeighbor(vector<vector<char> > mat, int selectedRow, int selectedCol) {
	if (mat[selectedRow - 1][selectedCol] != '.' || mat[selectedRow - 1][selectedCol] != 'B') {
		return true;
	}
	else if (mat[selectedRow - 1][selectedCol - 1] != '.' || mat[selectedRow - 1][selectedCol - 1] != 'B') {
		return true;
	}
	else if (mat[selectedRow + 1][selectedCol + 1] != '.' || mat[selectedRow + 1][selectedCol + 1] != 'B') {
		return true;
	}
	else if (mat[selectedRow][selectedCol - 1] != '.' || mat[selectedRow][selectedCol - 1] != 'B') {
		return true;
	}
	else if (mat[selectedRow + 1][selectedCol] != '.' || mat[selectedRow + 1][selectedCol] != 'B') {
		return true;
	}
	else if (mat[selectedRow][selectedCol + 1] != '.' || mat[selectedRow][selectedCol + 1] != 'B') {
		return true;
	}
	else if (mat[selectedRow - 1][selectedCol + 1] != '.' || mat[selectedRow - 1][selectedCol + 1] != 'B') {
		return true;
	}
	else if (mat[selectedRow + 1][selectedCol - 1] != '.' || mat[selectedRow + 1][selectedCol - 1] != 'B') {
		return true;
	}
	else {
		return false;
	}
	
}

void giveHelp(vector<vector<char> >& mat, int rows, int cols, int & helpCounter, int selectedRow, int selectedCol, vector<vector<char> > ansMat) {
	int ref = 0;
	if (helpCounter < 3) {
		for (int i = 0; i < rows; i++) { //searching the matrix
			for (int j = 0; j < cols; j++) {
				if (mat[i][j] != 'B') { //if not flagged as bomb
					if (checkNeighbor(mat, selectedRow, selectedCol) == true) { //if neighbors fulfill the requirements
						if (ansMat[i][j] == 'x' && mat[i][j] != 'x') {
							mat[i][j] = 'x'; //give the help
							helpCounter++;
							ref++;
							if (ref == 1) {
								return;
							}
						}
					}
				}
			}
		}
	}
	else {
		cout << "Your help chances are over. :(" << endl;
	}
}

void executeAction(string choice, int selectedRow, int selectedCol, vector<vector<char> >& mat, vector<vector<char> > ansMat, int & ref, int & helpCounter) {
	if (choice == "-o") { //if the user selects to open a cell
		if (isMine(selectedRow, selectedCol, ansMat, choice) == false){ //if the cell doesn't include a mine
			int count = countMines(selectedRow, selectedCol, ansMat, choice);
			mat[selectedRow][selectedCol] = count + '0';
			if (mat[selectedRow][selectedCol] == '0') {
				if (checkValid(selectedRow - 1, selectedCol) == true) {
					int count1 = countMines(selectedRow - 1, selectedCol, ansMat, choice); //count of upper cell
					mat[selectedRow - 1][selectedCol] = count1 + '0';
				}
				if (checkValid(selectedRow + 1, selectedCol) == true) {
					int count2 = countMines(selectedRow + 1, selectedCol, ansMat, choice); //count of bottom cell
					mat[selectedRow + 1][selectedCol] = count2 + '0';
				}
				if (checkValid(selectedRow, selectedCol - 1) == true) {
					int count3 = countMines(selectedRow, selectedCol - 1, ansMat, choice); //count of left cell
					mat[selectedRow][selectedCol - 1] = count3 + '0';
				}
				if (checkValid(selectedRow, selectedCol + 1) == true) {
					int count4 = countMines(selectedRow, selectedCol + 1, ansMat, choice); //count of right cell
					mat[selectedRow][selectedCol + 1] = count4 + '0';
				}
				if (checkValid(selectedRow - 1, selectedCol - 1) == true) {
					int count5 = countMines(selectedRow - 1, selectedCol - 1, ansMat, choice); //count of upper left cell
					mat[selectedRow - 1][selectedCol - 1] = count5 + '0';
				}
				if (checkValid(selectedRow - 1, selectedCol + 1) == true) {
					int count6 = countMines(selectedRow - 1, selectedCol + 1, ansMat, choice); // count of upper right cell
					mat[selectedRow - 1][selectedCol + 1] = count6 + '0';
				}
				if (checkValid(selectedRow + 1, selectedCol - 1) == true) {
					int count7 = countMines(selectedRow + 1, selectedCol - 1, ansMat, choice); //count of bottom left cell
					mat[selectedRow + 1][selectedCol - 1] = count7 + '0';
				}
				if (checkValid(selectedRow + 1, selectedCol + 1) == true) {
					int count8 = countMines(selectedRow + 1, selectedCol + 1, ansMat, choice); //count of bottom right cell
					mat[selectedRow + 1][selectedCol + 1] = count8 + '0';
				}
			}
		}
	}
	else if (choice == "-h") { // I wasn't able to successfully implement the help option.
		if (checkHelp(mat, maxRow, maxCol)) {
			cout << "I can't help you." << endl;
		}
		else {
			giveHelp(mat, maxRow, maxCol, helpCounter, selectedRow, selectedCol, ansMat);
		}
	}
	else if (choice == "-b") { //if the user selects to flag a cell
		if (mat[selectedRow][selectedCol] == '.') { //if it's not flagged, it flags
			mat[selectedRow][selectedCol] = 'B';
		}
		else if (mat[selectedRow][selectedCol] == 'B') { //if it's already flagged, it removes the flag
			mat[selectedRow][selectedCol] = '.';
		}
		else if (mat[selectedRow][selectedCol] != '.') { //if it can't be flagged because it's already opened
			cout << "Can't mark that cell as a bomb." << endl;
			ref = 1;
		}
	}
}

int main() {
	int rows, cols, selectedRow = 0, selectedCol = 0, ref = 0, helpCounter = 0;
	string choice, action;
	ifstream input;
	readColsRows(rows, cols, input); //first we start to read the desired rows and columns.
	vector<vector<char> > ansMat(rows, vector<char>(cols));
	readMatrix(input, ansMat, rows, cols); //we read the matrix in the text file as answer key
	maxRow = rows - 1; //using global variables here to prevent inputs out of matrix borders
	maxCol = cols - 1;
	vector<vector<char> > mat(rows, vector<char>(cols, '.'));
	cout << "You may choose a cell to open (-o), get help (-h) or mark/unmark bomb (-b)!!" << endl;
	printMatrix(mat);
	getChoice(choice, selectedRow, selectedCol);
	while (!isMine(selectedRow, selectedCol, ansMat, choice) && (!checkMatrix(mat, maxRow, maxCol)) && (checkValid(selectedRow, selectedCol))) { //if the input is to open a cell and the cell doesn't represent a bomb, the matrix is not fully opened and the input is valid, continue
		executeAction(choice, selectedRow, selectedCol, mat, ansMat, ref, helpCounter);
		int count = countMines(selectedRow, selectedCol, ansMat, choice);
		if (ref != 1) { //the ref value here prevents printing the matrix if the call cannot be marked as bomb.
			printMatrix(mat);
		}
		if (!checkMatrix(mat, maxRow, maxCol)) {
			getChoice(choice, selectedRow, selectedCol);
		}

		while (!checkValid(selectedRow, selectedCol)) { // check if the coordinate is correct
			cout << "Please enter a valid coordinate! " << endl;
			getChoice(choice, selectedRow, selectedCol);
		}
		while ((choice == "-o") && (mat[selectedRow][selectedCol] == 'B')) { // if the cell is already marked as bomb and the user is trying to open that cell
			cout << "It seems like this cell is a bomb." << endl;
			getChoice(choice, selectedRow, selectedCol);
		}
		ref = 0;
	}
	if (isMine(selectedRow, selectedCol, ansMat, choice)) { //if the user selects a mine, this terminates the game.
		cout << "You opened a mine! Game over:(" << endl;
	}
	else if (checkMatrix(mat, maxRow, maxCol)) { //check if the matrix is full
		if (!checkBombs(mat, maxRow, maxCol, ansMat)) { //check if bombs are correctly placed
			cout << "Congrats!You won!" << endl;
		}
		else {
			cout << "You put bombs in the wrong places! Game over:(" << endl;
		}
	}



	return 0;
}
