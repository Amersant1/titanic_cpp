//
// Created by Сергей on 16.02.2024.
//
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

typedef std::vector<std::vector<std::string>> matrix;
double WEIGHTS[3]={0.5,0.25,0.25};

matrix getMatrix(const std::string& filePath){
    std::ifstream input(filePath);
    matrix titanicMatrix;
    if(!input){
        std::cout<<"ERROR";

        return titanicMatrix;
    }
    std::string line;
//    std::vector

    while (std::getline(input,line)){
//      std::cout<<line;
      std::stringstream ss(line);
      std::vector<std::string> row;
      std::string field;
      while(std::getline(ss,field,'\t')){
          row.push_back(field);
      }
      titanicMatrix.push_back(row);
    }

    return titanicMatrix;
}

void fillNan(matrix& matrixTitanic,int column){
    std::vector<std::string> columnaVec;
    for(int i=1;i<matrixTitanic.size();i++){
        std::string cell = matrixTitanic[i][column];
        if (!cell.empty()){
            columnaVec.push_back(cell);//работает для строк, поэтому сортировка работает некорректно
        }
    }
    std::sort(columnaVec.begin(),columnaVec.end());
    std::string middleValue = columnaVec[columnaVec.size()/2];

    for(int i=1;i<matrixTitanic.size();i++){
        std::string cell = matrixTitanic[i][column];
        if (cell.empty()){
            matrixTitanic[i][column]=middleValue;
        }
    }

}


void printMatrix(const matrix& titanicMatrix){
    for (const std::vector<std::string>& row:titanicMatrix){
        for(const std::string& cell:row){
            std::cout<<cell<<'\t';
        }
        std::cout<<'\n';
    }
}


double judge(int age,int gender,int pClass){
    return (WEIGHTS[0]*1/(age+1)+WEIGHTS[1]*((1+gender)/2)+WEIGHTS[2]/pClass);
}