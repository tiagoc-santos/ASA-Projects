#include <iostream>
#include <vector>

int maximizeValue(std::vector<int> columns, std::vector<int> lines, std::vector<int> areas,
                  std::vector<int> values, int plateColumn, int plateLine, int plateArea, int numTypes){
    
    int i;
    std::vector<int> calculatedValues = std::vector<int>(plateArea + 1, 0);

    for(i = 1; i <= plateArea; i++){
        for(int j = 0; j < numTypes; j++){
            if(areas[j] <= i && columns[j] <= plateColumn && lines[j] <= plateLine){
                calculatedValues[i] = std::max(calculatedValues[i], 
                                               calculatedValues[i - areas[j]] + values[j]);
            }
        }
    }
    return calculatedValues[i-1];
}

int main(){
    int column = 0, line = 0, plateArea = 0, numTypes = 0,
    value = 0, maxValue = 0;
    
    std::cin >> column;
    std::cin >> line;
    std::cin >> numTypes;
    
    plateArea = column * line;
    std::vector<int> areas = std::vector<int>(numTypes, 0);
    std::vector<int> columns = std::vector<int>(numTypes, 0);
    std::vector<int> lines = std::vector<int>(numTypes, 0);
    std::vector<int> values = std::vector<int>(numTypes, 0);

    for(int i = 0; i < numTypes; i++){
        std::cin >> column;
        std::cin >> line;
        std::cin >> value;
        columns[i] = column;
        lines[i] = line;
        areas[i] = column * line;
        values[i] = value;
    }
    
    maxValue = maximizeValue(columns, lines, areas, values, column, line, plateArea, numTypes);
    std::cout << maxValue << std::endl;
    return 0;
}