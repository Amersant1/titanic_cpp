//
// Created by Сергей on 16.02.2024.
//
#include "titanic.h"

double WEIGHTS[3] = {0.5, 0.25, 0.25};

matrix getMatrix(const std::string &filePath) {
    std::ifstream input(filePath);
    matrix titanicMatrix;
    if (!input) {
        std::cout << "ERROR";

        return titanicMatrix;
    }
    std::string line;
    //    std::vector

    while (std::getline(input, line)) {
        //      std::cout<<line;
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string field;
        while (std::getline(ss, field, '\t')) {
            row.push_back(field);
        }
        titanicMatrix.push_back(row);
    }

    return titanicMatrix;
}

void fillNan(matrix &matrixTitanic, int column) {
    bool isNumber = false;
    try {
        std::stod(matrixTitanic[1][column]);
        isNumber = true;
    }
    catch (...) {
    }
    std::vector<std::string> columnaVec;
    for (int i = 1; i < matrixTitanic.size(); i++) {
        std::string cell = matrixTitanic[i][column];
        if (!cell.empty()) {
            columnaVec.push_back(cell); // работает для строк, поэтому сортировка работает некорректно
        }
    }
    std::string middleValue;
    if (!isNumber) {
        std::sort(columnaVec.begin(), columnaVec.end());
        middleValue = columnaVec[columnaVec.size() / 2];
    } else {
        std::vector<double> newColumnVec(columnaVec.size());
        std::transform(columnaVec.begin(), columnaVec.end(), newColumnVec.begin(),
                       [](const std::string &x) { return std::stod(x); });
        std::sort(newColumnVec.begin(), newColumnVec.end());
        middleValue = std::to_string(newColumnVec[newColumnVec.size() / 2]);
    }

    for (int i = 1; i < matrixTitanic.size(); i++) {
        std::string cell = matrixTitanic[i][column];
        if (cell.empty()) {
            matrixTitanic[i][column] = middleValue;
        }
    }
}

void printMatrix(const matrix &titanicMatrix) {
    for (const std::vector<std::string> &row: titanicMatrix) {
        for (const std::string &cell: row) {
            std::cout << cell << '\t';
        }
        std::cout << '\n';
    }
}

double judge(int age, int gender, int pClass) {
    return (WEIGHTS[0] * 1 / (age + 1) + WEIGHTS[1] * ((1 + gender) / 2) + WEIGHTS[2] / pClass);
}

void fillValue(matrix &matrixTitanic) {
    for (size_t i = 1; i < matrixTitanic.size(); i++) {
        int age = std::stoi(matrixTitanic[i][COLUMNS::Age]), gender = (matrixTitanic[i][COLUMNS::Sex] == "female" ? 1
                                                                                                                  : 0), pClass = std::stoi(
                matrixTitanic[i][COLUMNS::Pclass]);
        matrixTitanic[i].push_back(std::to_string(judge(age, gender, pClass)));
    }

}


std::ostream &operator<<(std::ostream &stream, const Passenger &p) {
    stream << p.id << '\t' << p.name << '\t' << p.value << '\n';
    return stream;
}


void Passenger::philValue() {
    value = judge(age, sex == "female" ? 1 : 0, pClass);
}


boats getBoats(const matrix &titanicMatrix) {
    boats bVector;
    std::vector<Passenger> passengers;
    for (size_t i = 1; i < titanicMatrix.size(); i++) {
        Passenger Ivan = {
                std::stoul(titanicMatrix[i][COLUMNS::PassengerId]),
                titanicMatrix[i][COLUMNS::Name],
                std::stoul(titanicMatrix[i][COLUMNS::Age]),
                titanicMatrix[i][COLUMNS::Sex],
                std::stoul(titanicMatrix[i][COLUMNS::Pclass])
        };
        Ivan.philValue();
        passengers.push_back(Ivan);
    }
    for (const Passenger &p: passengers) {
        std::cout << p;
    }
    return bVector;
}


personObesity personObesity::operator+(const personObesity &x) const {
    personObesity newpersonObesity{sex, age, weight + x.weight};
    return newpersonObesity;
}

std::map<size_t, double> processObesityData(const std::vector<personObesity> &data) {
    std::map<size_t, double> resultMap;

    for (size_t i = 0; i < 100; i++) {
        std::vector<personObesity> tempData;
        std::copy_if(data.begin(), data.end(), std::back_inserter(tempData),
                     [i](const personObesity &x) { return x.age == i; });

        if (!tempData.empty()) {
//            resultMap.insert({i, 70}); // это если в файле нет ничего (можно допилить и выставить среднее)
//        } else {
            personObesity sumOfWeights = std::reduce(tempData.begin(), tempData.end());
            resultMap.insert({i, (sumOfWeights.weight / tempData.size())});
        }
    }
    return resultMap;
}

obesityMapOfMaps workWithObesity(const std::string &filePath) {
    std::ifstream inputfile(filePath);
    if (!inputfile) {
        std::cout << "ПРОВЕРЬТЕ ФАЙЛ";
        obesityMapOfMaps map{{"Man",  {}},
                             {"Female", {}}};
        return map;
    }
    std::string line;
    std::vector<personObesity> vectorWomen, vectorMen;
    while (std::getline(inputfile, line)) {
        std::stringstream ss(line);
        std::string oneCellFromFile;
        std::vector<std::string> tokens;
        personObesity exectPerson;
//        std::getline(ss, oneCellFromFile, ',');
//        exectPerson.sex = oneCellFromFile;
//        std::getline(ss, oneCellFromFile, ',');
//        exectPerson.age = std::stoul(oneCellFromFile);
//        std::getline(ss, oneCellFromFile, ',');
//        exectPerson.weight = std::stod(oneCellFromFile);
        for (size_t i = 0; i < 4; ++i) {
            std::getline(ss, oneCellFromFile, ',');
            try {
                if (i == 0) {
                    exectPerson.sex = oneCellFromFile;
                } else if (i == 1) {
                    exectPerson.age = std::stoul(oneCellFromFile);
                } else if (i == 3) {
                    exectPerson.weight = std::stod(oneCellFromFile);
                }
            }
            catch (...) {}
        }

        if (exectPerson.sex == "Female")
            vectorWomen.push_back(exectPerson);
        else
            vectorMen.push_back(exectPerson);
    }
    std::map<size_t, double> tempMapMan = processObesityData(vectorMen);
    std::map<size_t, double> tempMapWomen = processObesityData(vectorWomen);
    obesityMapOfMaps map{{"Man",  tempMapMan},
                         {"Female", tempMapWomen}};


    for (const auto &x: map) {
        for (const auto &y: x.second) {
            std::cout << y.first << ':' << y.second << std::endl;
        }
        std::cout << '\n';
    }
    return map;
}

double genRand(double weight) {
//    10 -> 20 max weight
//    10 -> 5 min weight
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-weight*0.5, weight);
    return weight + dist(mt);
}

void phillWeights(matrix &matrix, const obesityMapOfMaps &map) {
    matrix[0].push_back("Weight");
    for (size_t i = 1; i < matrix.size(); i++) {
        try {
            size_t age = std::stoi(matrix[i][COLUMNS::Age]);
            std::string sex = (matrix[i][COLUMNS::Sex] == "male" ? "Man" : "Female");
//            std::map<std::string, std::map<size_t, double>>::const_iterator it = map.find(sex);
//            if (it != map.end()) {
//                const auto &ageMap = it->second;
//                auto it2 = ageMap.find(age);
//                if (it2 != ageMap.end()) {
//                    double weight = it2->second;
//                    matrix[i].push_back(std::to_string(weight));
//                }
//            }
            std::map<size_t, double> ageWeight = map.at(sex);

            std::map<size_t, double>::const_iterator ageWeightLower = ageWeight.lower_bound(age);
            double ageWeightVar = ageWeightLower->second;
            if (ageWeightLower == ageWeight.end()){
                ageWeightVar = (--ageWeight.upper_bound(age))->second;

            }
            matrix[i].push_back(std::to_string(genRand(ageWeightVar)));

        } catch (...) {}
    }
}
//template <class T>
//std::vector<T>

std::vector<int64_t> getCol(matrix &matrix, int col){
    std::vector<int64_t> newColVector;
    for (size_t i = 1; i < matrix.size(); i++) {

        std::cout << "done = "<<matrix[i][col] <<i <<"=i ; col = "<<col <<" - "<<(i==COLUMNS::Value?  std::stod(matrix[i][col])*100: std::stod(matrix[i][col]));
        newColVector.push_back(static_cast<int>(i==COLUMNS::Value?  std::stod(matrix[i][col])*100: std::stod(matrix[i][col])));
    }
    return newColVector;
}