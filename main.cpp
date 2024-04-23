#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>

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
    Student& operator=(Student&& moved) noexcept
    {
        if (this != &moved) {
            FIO = std::move(moved.FIO);
            group = std::move(moved.group);
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
        os << w.score[3]; // print the last score without a comma
        return os;
    }
    bool operator<(const Student& other) const {
        return FIO < other.FIO;
    }
};

int main() {
    vector<Student> students;
    ifstream inputFile("C:\\Games\\c++++\\untitled2\\input.txt");
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string fio, group;
        int ccnumber;
        int scores[4];
        getline(iss, fio, ',');
        getline(iss, group, ',');
        iss >> ccnumber;
        char comma; // add this to consume the comma after ccnumber
        iss >> comma;
        for (int i = 0; i < 4; i++) {
            iss >> scores[i];
        }
        Student student(fio, group, ccnumber, scores);
        students.push_back(student);
    }
    inputFile.close();

    // Output the source container to the output file
    ofstream outputFile("C:\\Games\\c++++\\untitled2\\output.txt");
    outputFile << "Source container:" << endl;
    for (const auto& student : students) {
        outputFile << student << endl;
    }

    // Sort the students vector by the FIO variable
    sort(students.begin(), students.end());

    // Output the sorted container to the output file
    outputFile << endl << "Sorted container:" << endl;
    for (const auto& student : students) {
        outputFile << student << endl;
    }

    // Copy the sorted container to a deque
    deque<Student> studentsDeque(students.begin(), students.end());

    // Output the deque container to the output file
    outputFile << endl << "Deque container:" << endl;
    for (const auto& student : studentsDeque) {
        outputFile << student << endl;
    }

    outputFile.close();

    return 0;
}