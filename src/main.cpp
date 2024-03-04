#include "titanic.h"
#include "ortool.h"
std::string PATH = "../data/tit_csv.txt";



int main() {
    matrix needed_matrix = getMatrix(PATH);

    for (int i: {COLUMNS::Sex, COLUMNS::Pclass, COLUMNS::Age}) {
        fillNan(needed_matrix, i);
    }
    fillValue(needed_matrix);
    getBoats(needed_matrix);
    obesityMapOfMaps map = workWithObesity("../data/obesity.csv");
    phillWeights(needed_matrix, map);
    printMatrix(needed_matrix);
//    getCol(needed_matrix, COLUMNS::Weight);
    operations_research::RunKnapsackExample(needed_matrix);
    return 0;
}
