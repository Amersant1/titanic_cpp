//
// Created by Сергей on 16.02.2024.
//
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
enum COLUMNS{PassengerId,Survived,Pclass,Name,Sex,Age,SibSp,Parch,Ticket,Fare,Cabin,Embarked};
typedef std::vector<std::vector<std::string>> matrix;
double WEIGHTS[3] = {0.5, 0.25, 0.25};

matrix getMatrix(const std::string &filePath)
{
    std::ifstream input(filePath);
    matrix titanicMatrix;
    if (!input)
    {
        std::cout << "ERROR";

        return titanicMatrix;
    }
    std::string line;
    //    std::vector

    while (std::getline(input, line))
    {
        //      std::cout<<line;
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string field;
        while (std::getline(ss, field, '\t'))
        {
            row.push_back(field);
        }
        titanicMatrix.push_back(row);
    }

    return titanicMatrix;
}

void fillNan(matrix &matrixTitanic, int column)
{
    bool isNumber = false;
    try
    {
        std::stod(matrixTitanic[1][column]);
        isNumber = true;
    }
    catch (...)
    {
    }
    std::vector<std::string> columnaVec;
    for (int i = 1; i < matrixTitanic.size(); i++)
    {
        std::string cell = matrixTitanic[i][column];
        if (!cell.empty())
        {
            columnaVec.push_back(cell); // работает для строк, поэтому сортировка работает некорректно
        }
    }
    std::string middleValue;
    if (!isNumber)
    {
        std::sort(columnaVec.begin(), columnaVec.end());
        middleValue = columnaVec[columnaVec.size() / 2];
    }
    else
    {
        std::vector<double> newColumnVec(columnaVec.size());
        std::transform(columnaVec.begin(), columnaVec.end(), newColumnVec.begin(), [](const std::string &x)
                       { return std::stod(x); });
        std::sort(newColumnVec.begin(), newColumnVec.end());
        middleValue = std::to_string(newColumnVec[newColumnVec.size() / 2]);
    }

    for (int i = 1; i < matrixTitanic.size(); i++)
    {
        std::string cell = matrixTitanic[i][column];
        if (cell.empty())
        {
            matrixTitanic[i][column] = middleValue;
        }
    }
}

void printMatrix(const matrix &titanicMatrix)
{
    for (const std::vector<std::string> &row : titanicMatrix)
    {
        for (const std::string &cell : row)
        {
            std::cout << cell << '\t';
        }
        std::cout << '\n';
    }
}

double judge(int age, int gender, int pClass)
{
    return (WEIGHTS[0] * 1 / (age + 1) + WEIGHTS[1] * ((1 + gender) / 2) + WEIGHTS[2] / pClass);
}
void fillValue(matrix& matrixTitanic){
    for (size_t i=1;i<matrixTitanic.size();i++){
        int age =std::stoi(matrixTitanic[i][COLUMNS::Age]), gender=(matrixTitanic[i][COLUMNS::Sex]=="female"?1:0), pClass=std::stoi(matrixTitanic[i][COLUMNS::Pclass]);
        matrixTitanic[i].push_back(std::to_string(judge(age, gender,pClass)));
    }
    
}