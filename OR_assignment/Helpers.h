/*
---------This Code is written by Zyad Alsaeed
---------Student at the October Six University
---------Faculty of Computer Science
---------All Rights Reserved 2024------------
*/

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void calculatePenalties(const vector<vector<int>>& costMatrix, const vector<int>& supply, const vector<int>& demand, vector<int>& rowDiff, vector<int>& colDiff) {
    int rows = costMatrix.size();
    int cols = costMatrix[0].size();

    // Calculate row penalties
    for (int i = 0; i < rows; i++) {
        if (supply[i] == 0) { // Skip rows with no supply
            rowDiff[i] = INT_MAX;
            continue;
        }
        vector<int> costs;
        for (int j = 0; j < cols; j++) {
            if (demand[j] != 0 && costMatrix[i][j] != INT_MAX) {
                costs.push_back(costMatrix[i][j]);
            }
        }
        if (costs.size() >= 2) {
            sort(costs.begin(), costs.end());
            rowDiff[i] = costs[1] - costs[0]; // Second smallest - smallest
        }
        else if (costs.size() == 1) {
            rowDiff[i] = costs[0];
        }
        else {
            rowDiff[i] = INT_MAX;
        }
    }

    for (int j = 0; j < cols; j++) {
        if (demand[j] == 0) {
            colDiff[j] = INT_MAX;
            continue;
        }
        vector<int> costs;
        for (int i = 0; i < rows; i++) {
            if (supply[i] != 0 && costMatrix[i][j] != INT_MAX) {
                costs.push_back(costMatrix[i][j]);
            }
        }
        if (costs.size() >= 2) {
            sort(costs.begin(), costs.end());
            colDiff[j] = costs[1] - costs[0];
        }
        else if (costs.size() == 1) {
            colDiff[j] = costs[0];
        }
        else {
            colDiff[j] = INT_MAX;
        }
    }
}

pair<int, int> getIndexOfMaxDiff(const vector<vector<int>>& costMatrix, const vector<int>& rowDiff, const vector<int>& colDiff) {
    int rows = costMatrix.size();
    int cols = costMatrix[0].size();

    int maxPenalty = -1;
    pair<int, int> index = { -1, -1 };

    for (int i = 0; i < rows; i++) {
        if (rowDiff[i] != INT_MAX) {
            for (int j = 0; j < cols; j++) {
                if (costMatrix[i][j] != INT_MAX && colDiff[j] != INT_MAX) {
                    int penalty = max(rowDiff[i], colDiff[j]);
                    if (penalty > maxPenalty || (penalty == maxPenalty && costMatrix[i][j] < costMatrix[index.first][index.second])) {
                        maxPenalty = penalty;
                        index = { i, j };
                    }
                }
            }
        }
    }

    return index;
}
vector<vector<int>> readPriceMatrix(int rows, int cols) {
	vector<vector<int>> priceMatrix(rows, vector<int>(cols));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> priceMatrix[i][j];
		}
	}
	return priceMatrix;
}

void printMatrix(const vector<vector<int>>& matrix) {
	for (const auto& row : matrix) {
		for (const auto& elem : row) {
			cout << elem << " ";
		}
		cout << endl;
	}
}

void readVector(vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		cin >> vec[i];
	}
}

void printVector(const vector<int>& vec) {
	for (const auto& elem : vec) {
		cout << elem << " ";
	}
	cout << endl;
}

int getTotal(const vector<int>& vec) {
	int total = 0;
	for (const auto& elem : vec) {
		total += elem;
	}
	return total;
} 
pair<int,int> getIndexOfLeastElement(vector<vector<int>> matrix) {
	int min = matrix[0][0];
	pair<int, int> index = { 0,0 };
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j] < min) {
				min = matrix[i][j];
				index = { i,j };
			}
		}
	}
	return index;
}