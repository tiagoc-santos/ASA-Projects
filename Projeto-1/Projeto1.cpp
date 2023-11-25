#include <iostream>
#include <vector>

int maximizeValue(int plateColumn, int plateLine, std::vector<std::vector<int>> models,
                  std::vector<int> values, int numTypes){
    
    std::vector<std::vector<int>>calculatedValues(plateColumn + 1, std::vector<int>(plateLine + 1, 0));
    for(int c = 1; c <= plateColumn; c++){
        for(int l = 1; l <= plateLine; l++){
            calculatedValues[c][l] = calculatedValues[c-1][l-1];
            for(int m = 0; m < numTypes; m++){
                int value1 = 0, value2 = 0, value3 = 0, value4 = 0, value5 = 0,
                value6 = 0;
                if(models[m][0] <= c && models[m][1] <= l){
                    value3 = values[m] + calculatedValues[c - models[m][0]][models[m][1]] + calculatedValues[c][l - models[m][1]];
                    value4 = values[m] + calculatedValues[models[m][0]][l - models[m][1]] + calculatedValues[c - models[m][0]][l];
                    value6 = std::max(value3, value4);
                }
                if(models[m][1] <= c && models[m][0] <= l){
                    value1 = values[m] + calculatedValues[c - models[m][1]][models[m][0]] + calculatedValues[c][l-models[m][0]];
                    value2 = values[m] + calculatedValues[c - models[m][1]][l] + calculatedValues[models[m][1]][l - models[m][0]];
                    value5 = std::max(value1, value2);
                }
                calculatedValues[c][l] = std::max(calculatedValues[c][l], std::max(value5, value6));
            }
        }
    }
    return calculatedValues[plateColumn][plateLine];
}

int main(){
    int plateColumn = 0, plateLine = 0, numTypes = 0,
    value = 0, maxValue = 0, line = 0, column = 0;
    
    std::cin >> plateColumn;
    std::cin >> plateLine;
    std::cin >> numTypes;

    std::vector<std::vector<int>> models(numTypes, std::vector<int>(2, 0));
    std::vector<int> values = std::vector<int>(numTypes, 0);

    for(int i = 0; i < numTypes; i++){
        std::cin >> column;
        std::cin >> line;
        std::cin >> value;
        models[i][0] = column;
        models[i][1] = line;
        values[i] = value;
    }
    maxValue = maximizeValue(plateColumn, plateLine, models, values, numTypes);
    std::cout << maxValue << std::endl;
    return 0;
}