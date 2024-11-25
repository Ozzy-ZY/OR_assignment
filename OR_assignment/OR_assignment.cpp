/*
---------This Code is written by Zyad Alsaeed
---------Student at the October six University
---------Faculty of Computer Science
---------All Rights Reserved 2024------------
*/
#include "Helpers.h"
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