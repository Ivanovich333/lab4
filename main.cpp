#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
public:
    string FIO;
    string group;
    int ccnumber;
    int score[4];

    Student() {}
    Student(string f, string g, int c, int* s) : FIO(f), group(g), ccnumber(c) {
        for (int i = 0; i < 4; i++) {
            this->score[i] = s[i];
        }
    }
    Student(const Student& other) : FIO(other.FIO), group(other.group), ccnumber(other.ccnumber) {
        for (int i = 0; i < 4; i++) {
            this->score[i] = other.score[i];
        }
    }
    Student(Student&& move) {
        FIO = move.FIO;
        group = move.group;
        ccnumber = move.ccnumber;
        for (int i = 0; i < 4; i++) {
            this->score[i] = move.score[i];
        }
    }
    Student& operator=(Student&& moved) 
    {
        if (this != &moved) {
            FIO = move(moved.FIO);
            group = move(moved.group);
            ccnumber = moved.ccnumber;
            for (int i = 0; i < 4; i++) {
                this->score[i] = moved.score[i];
            }
        }
        return *this;
    }
    friend ostream& operator<<(ostream& os, const Student& w) {
        os << w.FIO << ": " << w.group << "," << w.ccnumber << ", Score: ";
        for(int i = 0; i < 3; i++) {
            os << w.score[i] << ", ";
        }
        os << w.score[3]; 
        return os;
    }
    bool operator<(const Student& other) const {
        return FIO < other.FIO;
    }
};

int main() {
    vector<Student> students;
    ifstream inputFile("input.txt");
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string fio, group;
        int ccnumber;
        int scores[4];
        getline(iss, fio, ',');
        getline(iss, group, ',');
        iss >> ccnumber;
        char comma; 
        iss >> comma;
        for (int i = 0; i < 4; i++) {
            iss >> scores[i];
        }
        Student student(fio, group, ccnumber, scores);
        students.push_back(student);
    }
    inputFile.close();
    ofstream outputFile("output.txt");
    outputFile << "Source container:" << endl;
    for (const auto& student : students) {
        outputFile << student << endl;
    }

    sort(students.begin(), students.end());

    outputFile << endl << "Sorted container:" << endl;
    for (const auto& student : students) {
        outputFile << student << endl;
    }

    vector<Student> studentsVector(students.begin(), students.end());

    outputFile << endl << "Copy container:" << endl;
    for (const auto& student : studentsVector) {
        outputFile << student << endl;
    }

    outputFile.close();

    return 0;
}
