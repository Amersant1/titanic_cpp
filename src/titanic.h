#ifndef TITANIC_CPP_TITANIC_H
#define TITANIC_CPP_TITANIC_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <vector>

#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <numeric>

enum COLUMNS {
    PassengerId, Survived, Pclass, Name, Sex, Age, SibSp, Parch, Ticket, Fare, Cabin, Embarked, Value
};

struct Passenger {
    size_t id;
    std::string name;
    size_t age;
    std::string sex;
    size_t pClass;
    double value;

    void philValue();
};

typedef std::vector<std::vector<std::string>> matrix;
// новый тип данных
typedef std::map<std::string, std::map<size_t, double>> obesityMapOfMaps;
typedef std::vector<std::vector<Passenger>> boats;

matrix getMatrix(const std::string &);

void printMatrix(const matrix &);

double judge(int age, int gender, int pClass);

void fillNan(matrix &matrixTitanic, int);

void fillValue(matrix &matrixTitanic);

boats getBoats(const matrix &);

// новая функция для работы с obedity, возвращает словарь с разделением по gender:
obesityMapOfMaps workWithObesity(const std::string &filePath);

std::ostream &operator<<(std::ostream &, const Passenger &);

// новый struct для распределения веса людям:
struct personObesity {
    std::string sex;
    size_t age;
    double weight;

    personObesity operator+(const personObesity &x) const;
};

void phillWeights(matrix &matrix, const obesityMapOfMaps &map);

#endif //TITANIC_CPP_TITANIC_H

