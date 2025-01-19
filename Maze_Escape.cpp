//these are the functionalities that allow the program to open a file, within which is contained the level map, count the rows and cols of said map.
//Then the program proceedes to dynamicly produce a 2-D array which contains the map 
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int startingPositionX = 1;
const int startingPositionY = 1;

bool key = false;
bool winCondition = false;

const int maxNameSize = 51;
const int startingCoins = 0;
const int startingLives = 3;

//Ch stands for character
const char playerCh = '@';
const char wallCh = '#';
const char portalCh = '%';
const char coinCH = 'C';
const char keyCh = '&';
const char chestCH = 'X';

struct Player {
	char name[maxNameSize];
	int coins = startingCoins;
	int lifes = startingLives;
	int currentStage = 0;
	int currentLevel = 0;
};

//Adds the .txt extension for the file;
void txtAddOn(char* fileName) {
	if (fileName == nullptr) {
		return ;
	}
	int i = 0;

	while (fileName[i] != '\0') {
		i++;
	}
	// Add the ".txt" extension
	fileName[i++] = '.';
	fileName[i++] = 't';
	fileName[i++] = 'x';
	fileName[i++] = 't';
	fileName[i] = '\0';
}

void leveltxtAddOn(char* fileName){
	if (fileName == nullptr) {
		return ;
	}
	int i = 0;

	while (fileName[i] != '\0') {
		i++;
	}
	// Add the ".txt" extension
	fileName[i++] = '_';
	fileName[i++] = 'L';
	fileName[i++] = 'e';
	fileName[i++] = 'v';
	fileName[i++] = 'e';
	fileName[i++] = 'l';
	fileName[i++] = '.';
	fileName[i++] = 't';
	fileName[i++] = 'x';
	fileName[i++] = 't';
	fileName[i] = '\0';

}

int countCols(ifstream& ifs) {
	char ch;

	int count = 0;

	while (true) {
		ch = ifs.get();

		if (ch == ' ') {
			count++;
		}

		if (ch == '\n') {
			count++;
			break;
		}
	}

	return count;
}

int getCharOccurance(ifstream& ifs, char target) {
	char current;

	int result = 0;

	while (true) {
		current = ifs.get();

		if (ifs.eof()) {
			break;
		}

		if (current == target) {
			result++;
		}
	}

	return result + 1;
}

int countRows(ifstream& ifs) {
	return getCharOccurance(ifs, '\n');
}

void calculateDimensions(const char* inputFile, int& rows, int& cols) {
	ifstream ifs(inputFile);

	if (!ifs.is_open()) {
		rows = cols = 0;
		return;
	}

	cols = countCols(ifs);
	ifs.clear();
	ifs.seekg(0);
	rows = countRows(ifs);
	ifs.close();
}

int** readMatrix(const char* file, int rows, int cols) {
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}

	ifstream ifs(file);

	if (!ifs.is_open()) {
		return nullptr;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			ifs >> matrix[i][j];
		}
	}

	ifs.close();
	return matrix;
}

void arrOutput(int** matix, int rows, int cols) {
	for (int i = 0; i < rows;i++) {
		cout << '\n' << '\n';
		for (int j = 0; j < cols; j++) {
			cout << (char)matix[i][j] << '\t';
		}
	}
}

void freeMatrix(int** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}

	delete[] matrix;
}

