/*
*Id: 202201548 
*Name: Zyad Mohamed Mahmoud Alsaeed
---------This Code is written by Zyad Alsaeed
---------Student at the October six University
---------Faculty of Computer Science
---------All Rights Reserved 2024------------
*/
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
pair<int, int> getIndexOfLeastElement(vector<vector<int>> matrix) {
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
void balanceProblem(vector<vector<int>>& costMatrix, vector<int>& supply, vector<int>& demand) {
    int totalSupply = getTotal(supply);
    int totalDemand = getTotal(demand);

    if (totalSupply > totalDemand) {
        
        for (auto& row : costMatrix) {
            row.push_back(0);
        }
        demand.push_back(totalSupply - totalDemand);
    }
    else if (totalDemand > totalSupply) {
        vector<int> dummyRow(demand.size(), 0); 
        costMatrix.push_back(dummyRow);
        supply.push_back(totalDemand - totalSupply);
    }
}

int leastCostMethod(vector<vector<int>> priceMatrix, vector<int> supply, vector<int> demand) {
    int minPrice = 0;
    int totalDemand = getTotal(demand);
    while (totalDemand != 0) {
        pair<int, int> index = getIndexOfLeastElement(priceMatrix);
        int i = index.first;
        int j = index.second;
        if (priceMatrix[i][j] == INT_MAX) {
            break;
        }
        int taken = min(supply[i], demand[j]);
        minPrice += taken * priceMatrix[i][j];
        cout << "price point: " << i + 1 << ", " << j + 1 << "\t supplied: " << taken << "\n";
        supply[i] -= taken;
        demand[j] -= taken;
        totalDemand -= taken;
        priceMatrix[i][j] = INT_MAX;
    }
    return minPrice;
}

int vogelMethod(vector<vector<int>> costMatrix, vector<int> supply, vector<int> demand) {
    int totalDemand = getTotal(demand);
    int minPrice = 0;

    vector<int> rowDiff(costMatrix.size(), 0);
    vector<int> colDiff(costMatrix[0].size(), 0);

    while (totalDemand > 0) {
        calculatePenalties(costMatrix, supply, demand, rowDiff, colDiff);
        pair<int, int> index = getIndexOfMaxDiff(costMatrix, rowDiff, colDiff);
        int i = index.first;
        int j = index.second;

        if (i == -1 || j == -1) {
            break; // No valid allocation
        }

        int allocation = min(supply[i], demand[j]);
        minPrice += allocation * costMatrix[i][j];
        cout << "Price point: (" << i + 1 << ", " << j + 1 << ") -> Allocated: " << allocation << "\n";

        supply[i] -= allocation;
        demand[j] -= allocation;
        totalDemand -= allocation;

        if (supply[i] == 0) {
            rowDiff[i] = INT_MAX;
        }
        if (demand[j] == 0) {
            colDiff[j] = INT_MAX;
        }

        costMatrix[i][j] = INT_MAX;
    }

    return minPrice;
}

int northWestMethod(vector<vector<int>> priceMatrix, vector<int> supply, vector<int> demand) {
    int minPrice = 0;
    int i = 0, j = 0;
    int totalDemand = getTotal(demand);
    while (i < supply.size() && j < demand.size()) {
        if (supply[i] == 0) {
            i++;
        }
        else if (demand[j] == 0) {
            j++;
        }
        else {
            int taken = min(supply[i], demand[j]);
            minPrice += taken * priceMatrix[i][j];
            cout << "price point: " << i + 1 << ", " << j + 1 << "\t supplied: " << taken << "\n";
            supply[i] -= taken;
            totalDemand -= taken;
            demand[j] -= taken;
        }
    }
    return minPrice;
}

int main() {
    std::vector<std::vector<int>> cost_matrix = {
    {16, 2, 3,7},
    {5, 13, 7,5},
    {8, 6, 5,9},
	{3, 4, 5,11}
    };

    try {

        std::cout << "Standard Hungarian Method:" << std::endl;
        std::vector<int> standard_assignment = solve_hungarian_method(cost_matrix);

        std::cout << "Optimal Assignment:" << std::endl;
        for (size_t i = 0; i < standard_assignment.size(); ++i) {
            if (standard_assignment[i] != -1) {
                std::cout << "Worker " << i << " assigned to Job "
                    << standard_assignment[i] << std::endl;
            }
        }

        int standard_total_cost = calculate_total_cost(cost_matrix, standard_assignment);
        std::cout << "Total Cost (Standard): " << standard_total_cost << std::endl;

        std::cout << "\nAdvanced Hungarian Method:" << std::endl;
        std::vector<int> advanced_assignment = advanced_hungarian_method(cost_matrix);

        std::cout << "Optimal Assignment:" << std::endl;
        for (size_t i = 0; i < advanced_assignment.size(); ++i) {
            if (advanced_assignment[i] != -1) {
                std::cout << "Worker " << i << " assigned to Job "
                    << advanced_assignment[i] << std::endl;
            }
        }

        int advanced_total_cost = calculate_total_cost(cost_matrix, advanced_assignment);
        std::cout << "Total Cost (Advanced): " << advanced_total_cost << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    int rows, cols;
    cout << "Enter the number of rows and columns\n";
    cin >> rows >> cols;

    cout << "Enter the price matrix (" << rows << "x" << cols << "):\n";
    vector<vector<int>> priceMatrix = readPriceMatrix(rows, cols);
    cout << "\nPrice Matrix:\n";
    printMatrix(priceMatrix);

    cout << "Enter the supply values (" << rows << "):\n";
    vector<int> supply(rows);
    readVector(supply);
    cout << "\nSupply Vector: ";
    printVector(supply);

    cout << "Enter the demand values (" << cols << "):\n";
    vector<int> demand(cols);
    readVector(demand);
    cout << "Demand Vector: ";
    printVector(demand);
    balanceProblem(priceMatrix, supply, demand);

    int minPrice = northWestMethod(priceMatrix, supply, demand);
    cout << "Minimum Transportation Cost (North West Method): " << minPrice << "\n";

    minPrice = leastCostMethod(priceMatrix, supply, demand);
    cout << "Minimum Transportation Cost (Least Cost Method): " << minPrice << "\n";

    minPrice = vogelMethod(priceMatrix, supply, demand);
    cout << "Minimum Transportation Cost (Vogel's Approximation Method): " << minPrice << "\n";
    return 0;
}