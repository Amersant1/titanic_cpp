//
// Created by Сергей on 16.02.2024.
//

#ifndef TITANIC_CPP_TITANIC_H
#define TITANIC_CPP_TITANIC_H
#include <iostream>
#include <vector>
#include <string>
enum COLUMNS{PassengerId,Survived,Pclass,Name,Sex,Age,SibSp,Parch,Ticket,Fare,Cabin,Embarked,Value};
struct Passenger{
    size_t id; 
    std::string name;
    size_t age;
    std::string sex;
    size_t pClass;
    double value;
    void philValue ();
    };
typedef std::vector<std::vector<std::string>> matrix;
typedef std::vector<std::vector<Passenger>> boats;
matrix getMatrix(const std::string&);
void printMatrix(const matrix&);
double judge(int age,int gender,int pClass);
void fillNan(matrix& matrixTitanic,int);
void fillValue(matrix& matrixTitanic);
boats getBoats (const matrix&);
std::ostream& operator << (std::ostream&, const Passenger&);
#endif //TITANIC_CPP_TITANIC_H

