#include "titanic.h"

std::string PATH = "../data/tit_csv.txt";


int main() {
    matrix needed_matrix = getMatrix(PATH);

    for (int i: {COLUMNS::Sex, COLUMNS::Pclass, COLUMNS::Age}) {
        fillNan(needed_matrix, i);
    }
    fillValue(needed_matrix);
    //printMatrix(needed_matrix);
    getBoats(needed_matrix);
    obesityMapOfMaps map = workWithObesity("../data/obesity.csv");
    std::cout << "DONE with workWithObesity\n";
    phillWeights(needed_matrix, map);
    return 0;
}