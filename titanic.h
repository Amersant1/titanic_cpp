//
// Created by Сергей on 16.02.2024.
//

#ifndef TITANIC_CPP_TITANIC_H
#define TITANIC_CPP_TITANIC_H
#include <vector>
#include <string>
typedef std::vector<std::vector<std::string>> matrix;
matrix getMatrix(const std::string&);
void printMatrix(const matrix&);
double judge(int age,int gender,int pClass);
void fillNan(matrix& matrixTitanic,int);
void fillValue(matrix& matrixTitanic);
#endif //TITANIC_CPP_TITANIC_H

