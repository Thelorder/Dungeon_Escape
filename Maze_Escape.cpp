//these are the functionalities that allow the program to open a file, within which is contained the level map, count the rows and cols of said map.
//Then the program proceedes to dynamicly produce a 2-D array which contains the map 

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


