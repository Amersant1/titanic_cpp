//
// Created by Сергей on 16.02.2024.
//
#include "titanic.h"
#include <map>
std::string PATH="../data/tit_csv.txt";



int main(){
//    std::map<std::string,int>{{}}
    matrix needed_matrix = getMatrix(PATH);

    for(int i:{COLUMNS::Sex,COLUMNS::Pclass,COLUMNS::Age}){
        fillNan(needed_matrix,i);
    }
    fillValue(needed_matrix);
    //printMatrix(needed_matrix);
    getBoats(needed_matrix);

    return 0;
}