/*
*Id: 202201548 
*Name: Zyad Mohamed Mahmoud Alsaeed
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

    for (int i = 0; i < rows; i++) {
        if (supply[i] == 0) { 
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
            rowDiff[i] = costs[1] - costs[0];
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

const int MAX_SIZE = 100; 
void reduce_rows(std::vector<std::vector<int>>& cost_matrix) {
    for (auto& row : cost_matrix) {
        int min_val = *std::min_element(row.begin(), row.end());
        for (int& val : row) {
            val -= min_val;
        }
    }
}

void reduce_columns(std::vector<std::vector<int>>& cost_matrix) {
    int n = cost_matrix.size();
    for (int col = 0; col < n; ++col) {
        int min_val = std::numeric_limits<int>::max();
        for (int row = 0; row < n; ++row) {
            min_val = std::min(min_val, cost_matrix[row][col]);
        }

        for (int row = 0; row < n; ++row) {
            cost_matrix[row][col] -= min_val;
        }
    }
}

// Find optimal assignment
std::vector<int> find_optimal_assignment(const std::vector<std::vector<int>>& cost_matrix) {
    int n = cost_matrix.size();
    std::vector<int> assignment(n, -1);
    std::vector<bool> row_covered(n, false);
    std::vector<bool> col_covered(n, false);

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (cost_matrix[row][col] == 0 && !row_covered[row] && !col_covered[col]) {
                assignment[row] = col;
                row_covered[row] = true;
                col_covered[col] = true;
                break;
            }
        }
    }

    return assignment;
}

int calculate_total_cost(const std::vector<std::vector<int>>& cost_matrix,
    const std::vector<int>& assignment) {
    int total_cost = 0;
    for (size_t row = 0; row < assignment.size(); ++row) {
        if (assignment[row] != -1) {
            total_cost += cost_matrix[row][assignment[row]];
        }
    }
    return total_cost;
}

std::vector<int> solve_hungarian_method(std::vector<std::vector<int>> cost_matrix) {
    // Validate input matrix
    if (cost_matrix.empty() || cost_matrix.size() != cost_matrix[0].size()) {
        throw std::invalid_argument("Matrix must be square");
    }

    reduce_rows(cost_matrix);

    reduce_columns(cost_matrix);

    return find_optimal_assignment(cost_matrix);
}

// Advanced Hungarian Method with more complex assignment logic
std::vector<int> advanced_hungarian_method(std::vector<std::vector<int>> cost_matrix) {
    int n = cost_matrix.size();
    std::vector<int> row_cover(n, 0);
    std::vector<int> col_cover(n, 0);
    std::vector<std::vector<int>> mask(n, std::vector<int>(n, 0));
    reduce_rows(cost_matrix);

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (cost_matrix[r][c] == 0 && row_cover[r] == 0 && col_cover[c] == 0) {
                mask[r][c] = 1;
                row_cover[r] = 1;
                col_cover[c] = 1;
            }
        }
    }

    std::fill(row_cover.begin(), row_cover.end(), 0);
    std::fill(col_cover.begin(), col_cover.end(), 0);
    std::vector<int> assignment(n, -1);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (mask[r][c] == 1) {
                assignment[r] = c;
                break;
            }
        }
    }

    return assignment;
}