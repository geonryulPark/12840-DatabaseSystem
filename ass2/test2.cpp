#include <bits/stdc++.h>

using namespace std;

class name_age {
public:
    string name;
    string age;

    void set_name_age(string tuple) {
        stringstream tuplestr(tuple);
        string agestr;

        getline(tuplestr, name, ',');
        getline(tuplestr, age);
    }
};

class name_salary {
public:
    string name;
    string salary;

    void set_name_salary(string tuple) {
        stringstream tuplestr(tuple);
        string salarystr;

        getline(tuplestr, name, ',');
        getline(tuplestr, salary);
    }
};

string make_tuple(string name, string age, string salary) {
    return name + ',' + age + ',' + salary + '\n';
}

int hashingName(string name) {
    int hashCode = 0;
    for (int i = 0; i < name.length(); i++) {
        hashCode += name[i] * pow(26, i);
    }
    return hashCode % 1000;
}

int main() {

    string buffer[2];
    name_age temp0;
    name_salary temp1;
    fstream block[12];
    ofstream output;

    output.open("./output2.csv");

    if (output.fail()) {
        cout << "output file opening fail.\n";
    }


    /******************************************************************/

    // cleaning buckets files
    for (int i = 0; i < 27; i++) {
        output.close();
        output.open("..\\buckets\\" + to_string(i) + ".csv");
    }

    // Build Hash of name_salary
    int nameSalaryCount = 0;
    int nameAgeCount = 0;
    int blockIndex, hashedNameZero, hashedNameOne;

    while (nameSalaryCount < 1000) {
        for (blockIndex = 0; blockIndex < 10; blockIndex++) {
            block[blockIndex].close();
            block[blockIndex].open("..\\name_salary\\" + to_string(nameSalaryCount++) + ".csv", ios::in);
        }
        blockIndex = 0;

        while (blockIndex < 10) {
            while (!block[blockIndex].eof()) {
                getline(block[blockIndex], buffer[1]);
                temp1.set_name_salary(buffer[1]);
                if (temp1.name.empty()) break;
                hashedNameOne = hashingName(temp1.name);

                output.close();
                output.open("..\\buckets\\" + to_string(hashedNameOne) + ".csv", ofstream::out | ofstream::app);
                output << temp1.name << "," << temp1.salary << endl;
            }
            blockIndex++;
        }
    } // end of hashing

    output.close();
    output.open("./output2.csv");

    while (nameAgeCount < 1000) {
        for (blockIndex = 0; blockIndex < 10; blockIndex++) {
            block[blockIndex].close();
            block[blockIndex].open("..\\name_age\\" + to_string(nameAgeCount++) + ".csv", ios::in);
        }
        blockIndex = 0;

        const int blockOverIndex = 10;
        while (blockIndex < 10) {
            while (!block[blockIndex].eof()) {
                getline(block[blockIndex], buffer[0]);
                temp0.set_name_age(buffer[0]);
                if (temp0.name.empty()) break;
                hashedNameZero = hashingName(temp0.name);

                block[blockOverIndex].close();
                block[blockOverIndex].open("..\\buckets\\" + to_string(hashedNameZero) + ".csv", ios::in);

                while (!block[blockOverIndex].eof()) {
                    getline(block[blockOverIndex], buffer[1]);
                    temp1.set_name_salary(buffer[1]);
                    if (temp0.name == temp1.name) {
                        output << make_tuple(temp0.name, temp0.age, temp1.salary);
                        break;
                    }
                }
            }
            blockIndex++;
        }
    }












    // write codes here.















    /******************************************************************/

    output.close();


}
