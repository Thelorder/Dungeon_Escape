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
const char enemyCh = 'E';

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

bool fileExists(const char* fileName) {
	ifstream file(fileName);
	return file.good();
}

bool readingPlayerDataFromFile(const char* fileName, Player& player) {
	ifstream playerData(fileName);
	char buffer[maxNameSize * 2];

	if (playerData.is_open()) {
		while (playerData.getline(buffer, sizeof(buffer))) {
			int i = 0;
			int j = 0;
			while (buffer[i] != ':' && buffer[i] != '\0') {
				player.name[j++] = buffer[i++];
			}
			player.name[j] = '\0'; // Null-terminate the name
			i++; // Skip the comma

			// Extract coins (up to the next comma)
			int coins = 0;
			while (buffer[i] != ':' && buffer[i] != '\0') {
				coins = coins * 10 + (buffer[i] - '0'); // Convert char to int
				i++;
			}
			player.coins = coins;
			i++; // Skip the comma

			// Extract lives
			int lives = 0;
			while (buffer[i] != ':' && buffer[i] != '\0') {
				lives = lives * 10 + (buffer[i] - '0'); // Convert char to int
				i++;
			}
			player.lifes = lives;
			i++;

			int currentStage = 0;
			while (buffer[i] != ':' && buffer[i] != '\0') {
				currentStage = currentStage * 10 + (buffer[i] - '0'); // Convert char to int
				i++;
			}
			player.currentStage = currentStage;
			i++;

			int currentLevel = 0;
			while (buffer[i] != ':' && buffer[i] != '\0') {
				currentLevel = currentLevel * 10 + (buffer[i] - '0'); // Convert char to int
				i++;
			}
			player.currentLevel = currentLevel;

			if (strcmp(player.name, player.name) == 0) {
				playerData.close();
				return true; // Found the player and read their data
			}

		}
		playerData.close();
	}
	else {
		cout << "Error!!!";
	}

	return false;
}

//function to replace the spaces in the players name with _
void addingUnderscore(char* fileName) {
	for (int i = 0; fileName[i] != '\0'; ++i) {
		if (fileName[i] == ' ') {
			fileName[i] = '_';
		}
	}
}

void copyArray(char* destination, const char* source) {
	int i = 0;
	while (source[i] != '\0') {
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0'; // Null-terminate the string
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

void savePlayerDataToFile( Player& player,int Stage, int Level) {
	char fileName[maxNameSize + 10];
	copyArray(fileName, player.name);
	addingUnderscore(fileName);
	txtAddOn(fileName);

	player.currentLevel = Level;
	player.currentStage = Stage;

	ofstream playerData(fileName);
	if (playerData.is_open()) {
		playerData << player.name << ":"
			<< player.coins << ":"
			<< player.lifes << ":"
			<< player.currentStage<<":"
			<< player.currentLevel <<'\n';
		playerData.close();
	}
	else {
		cout << "Error saving player data!\n";
	}
}

void saveLevelState(const Player& player, int** level, int rows, int cols) {
	char fileName[maxNameSize*2];
	copyArray(fileName, player.name);
	addingUnderscore(fileName);
	leveltxtAddOn(fileName);


	ofstream saveFile(fileName);
	if (!saveFile.is_open()) {
		cout << "Error: Could not create save file.\n";
		return;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			saveFile << level[i][j];
			if (j < cols - 1) {
				saveFile << " "; // Add space only between elements
			}
		}
		if (i < rows - 1) {
			saveFile << '\n'; // Add newline only between rows, not after the last row
		}
	}

	saveFile.close();
}

bool loadSavedLevel(const char* playerName, int& currentStage, int& currentLevel, int**& level, int& rows, int& cols) {
	char fileName[maxNameSize*2];
	copyArray(fileName, playerName);
	addingUnderscore(fileName);
	leveltxtAddOn(fileName);

	ifstream saveFile(fileName); 
	if (!saveFile.is_open()) {
		return false;
	}

	calculateDimensions(fileName, rows, cols);

	if (rows == 0 || cols == 0) {
		return false;
	}

	// Allocate and read the level matrix
	level = readMatrix(fileName, rows, cols);
	saveFile.close();

	return true;

}

void newPlayerRegister(Player player) {
	cout << "Player Registration" << endl;
	

	cout << "Enter player name: ";
	std::cin.ignore();
	std::cin.getline(player.name, maxNameSize);

	player.coins = startingCoins;
	player.lifes = startingLives;
	player.currentStage = 0;
	player.currentLevel = 0;

	char playerInfo[maxNameSize + 20];
	copyArray(playerInfo, player.name);
	addingUnderscore(playerInfo);
	txtAddOn(playerInfo);

	if (fileExists(playerInfo)) {
		cout << "The Player name " << player.name << " already exists! " << endl;
		return;
	}

	savePlayerDataToFile(player,player.currentStage,player.currentLevel);
	cout << "Welcome to the Dungeons!!!"<<endl;
}

bool logInCredentials(Player& player) {

	char name[maxNameSize + 4];
	cout << "Enter player's name to log in: ";
	std::cin.ignore();
	std::cin.getline(name, maxNameSize);

	for (int i = 0; name[i] != '\0'; ++i) {
		player.name[i] = name[i];
	}

	txtAddOn(name);
	addingUnderscore(name);

	if (readingPlayerDataFromFile(name, player)) {
		cout << "Welcome back, " << player.name << "!\n";
		return true;
	}
	else {
		cout << "Player not found. Please register first.\n";
		return false;
	}
}

void clearConsole() {
	if (system("cls"))
	{
		system("clear");
	}
}

bool teleportaionToNextPortal(int** level, int rows, int cols, int& targetX, int& targetY) {
	bool found = false;

	// Search for the next portal after the current one
	for (int i = targetX; i < rows && !found; ++i) {
		for (int j = (i == targetX ? targetY + 1 : 0); j < cols; ++j) {
			if (level[i][j] == portalCh) { // Found another portal
				targetX = i;
				targetY = j+1;
				found = true;
				break;
			}
		}
	}

	// If no portal was found, wrap around and search from the beginning
	if (!found) {
		for (int i = 0; i < rows && !found; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (level[i][j] == '%') {
					targetX = i;
					targetY = j+1;
					found = true;
					break;
				}
			}
		}
	}

	return found; // Return whether a portal was found
}

bool collisionChech(int** level, int rows, int cols, int& targetX, int& targetY, Player& player) {

	if (targetX < 0 || targetX >= rows || targetY < 0 || targetY >= cols || level[targetX][targetY] == wallCh) {
		// Border collision or out-of-bounds
		player.lifes -= 1;
		return 0;
	}
	if (level[targetX][targetY] == coinCH){ // Pick up coin
		player.coins += 1;
		level[targetX][targetY] = ' ';
	}
	else if (level[targetX][targetY] == keyCh) { // Pick up key
		key = true;
		level[targetX][targetY] = ' ';
	}
	else if (level[targetX][targetY] == chestCH) { // Unlock Chest
		if (key) {
			winCondition = true;
			level[targetX][targetY] = ' ';
		}
		else {
			return 0; // Can't open without a key
		}
	}
	else if (level[targetX][targetY] == portalCh) { // Portal teleport
		teleportaionToNextPortal(level, rows, cols, targetX, targetY);
		return 1; // Portal transport successful
	}

	return 1; // No collision
}

void movementInLevel(int** level,int rows,int cols, char move, int& characterX, int& characterY, Player& player) {
	int offsetX = 0, offsetY = 0;

	switch (move) {
	case 'W': case 'w': offsetX = -1; break; // Move up
	case 'S': case 's': offsetX = 1; break;  // Move down
	case 'A': case 'a': offsetY = -1; break; // Move left
	case 'D': case 'd': offsetY = 1; break;  // Move right
	default:
		cout << "Incorrect Input!!!";
		return;
	}

	// Calculate the target position
	int targetX = characterX + offsetX;
	int targetY = characterY + offsetY;

	if (collisionChech(level, rows, cols, targetX, targetY, player)) {
		level[characterX][characterY] = ' '; // Clear previous position
		level[targetX][targetY] = playerCh;       // Move player to new position
		characterX = targetX;
		characterY = targetY;
	}
}

int characterXCordinates(int** matrix,int rows,int cols) {

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (matrix[i][j] == playerCh) {
				return i; // Return the row index of the player's position
			}
		}
	}
	return -1;

}

int characterYCordinates(int** matrix, int rows, int cols) {

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (matrix[i][j] == playerCh) {
				return j; // Return the column index of the player's position
			}
		}
	}
	return -1;

}

int enemyXCordinates(int** matrix, int rows, int cols) {

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (matrix[i][j] == enemyCh) {
				return i; // Return the row index of the player's position
			}
		}
	}
	return -1;

}

int enemyYCordinates(int** matrix, int rows, int cols) {

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (matrix[i][j] == enemyCh) {
				return j; // Return the column index of the player's position
			}
		}
	}
	return -1;

}

bool enemyCollisionChech(int** level, int rows, int cols, int& targetX, int& targetY) {

	if (targetX < 0 || targetX >= rows || targetY < 0 || targetY >= cols || level[targetX][targetY] == wallCh) {
		
		return 0;
	}
	if (level[targetX][targetY] == coinCH) { // Pick up coin
		
		level[targetX][targetY] = ' ';
	}
	else if (level[targetX][targetY] == keyCh) { 
	
		return 0;
	}
	else if (level[targetX][targetY] == chestCH) { 
		return 0;
	}
	else if (level[targetX][targetY] == portalCh) { // Portal teleport
		teleportaionToNextPortal(level, rows, cols, targetX, targetY);
		return 1; // Portal transport successful
	}

	return 1; // No collision
}

void enemyMovementInLevel(int** level, int rows, int cols, char move, int& enemyX, int& enemyY) {
	int offsetX = 0, offsetY = 0;

	switch (move) {
	case 'W': case 'w': offsetX = -1; break; // Move up
	case 'S': case 's': offsetX = 1; break;  // Move down
	case 'A': case 'a': offsetY = 1; break; // Move left
	case 'D': case 'd': offsetY = -1; break;  // Move right
	default:
		cout << "Incorrect Input!!!";
		return;
	}

	// Calculate the target position
	int targetX = enemyX + offsetX;
	int targetY = enemyY + offsetY;

	if (enemyCollisionChech(level, rows, cols, targetX, targetY)) {
		level[enemyX][enemyY] = ' '; // Clear previous position
		level[targetX][targetY] = enemyCh;       // Move enemy to new position
		enemyX = targetX;
		enemyY = targetY;
	}
}

bool findIfKeyHasBeenTaken(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (matrix[i][j] == keyCh) {
				return false;
			}
		}
	}
	return true;
}
