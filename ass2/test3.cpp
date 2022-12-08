#include <bits/stdc++.h>
using namespace std;

class name_grade {
	public:
		string student_name;
		int korean;
		int math;
		int english;
		int science;
		int social;
		int history;

		void set_grade(string tuple)
		{
			stringstream tuplestr(tuple);
			string tempstr;

			getline(tuplestr, student_name, ',');

			getline(tuplestr, tempstr, ',');
			korean = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			math = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			english = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			science = stoi(tempstr);
			
			getline(tuplestr, tempstr, ',');
			social = stoi(tempstr);
			
			getline(tuplestr, tempstr);
			history = stoi(tempstr);
		}
};

class name_number{
	public :
		string student_name;
		string student_number;

		void set_number(string tuple)
		{
			stringstream tuplestr(tuple);
			string tempstr;


			getline(tuplestr, student_name, ',');
			getline(tuplestr, student_number, ',');
		}
};

string make_tuple(string name, string number)
{
	string ret = "";

	ret += name+ "," + number +"\n";

	return ret;
}

int hashingName(string name) {
    int hashCode = 0;
    for (int i = 0; i < name.length(); i++) {
        hashCode += name[i] * pow(26, i);
    }
    return hashCode % 27;
}

int isValid(name_grade temp0, name_grade temp1) {
    int count = 0;
    if (temp0.student_name != temp1.student_name) return 0;

    if (temp0.korean > temp1.korean) count++;
    if (temp0.math > temp1.math) count++;
    if (temp0.english > temp1.english) count++;
    if (temp0.science > temp1.science) count++;
    if (temp0.history > temp1.history) count++;
    if (temp0.social > temp1.social) count++;

    if (count >= 2) return 1;
    else return 0;
}

int main(){

	string buffer[2];
	name_grade temp0;
	name_grade temp1;
	name_number temp2;
	fstream block[12];
	ofstream output;

	output.open("./output3.csv");

	if(output.fail())
	{
		cout << "output file opening fail.\n";
	}

	/*********************************************************************/

    // cleaning buckets files
    for (int i = 0; i < 27; i++) {
        output.close();
        output.open("..\\buckets1\\" + to_string(i) + ".csv");
        output.close();
        output.open("..\\buckets2\\" + to_string(i) + ".csv");
    }

    int nameGradeTwoCount = 0;
    int nameGradeOneCount = 0;
    int nameNumberCount = 0;
    int blockIndex, hashedNameThree, hashedNameTwo, hashedNameOne;

    while (nameGradeTwoCount < 1000) {
        for (blockIndex = 0; blockIndex < 10; blockIndex++) {
            block[blockIndex].close();
            block[blockIndex].open("..\\name_grade2\\" + to_string(nameGradeTwoCount++) + ".csv", ios::in);
        }
        blockIndex = 0;

        while (blockIndex < 10) {
            while(!block[blockIndex].eof()) {
                getline(block[blockIndex], buffer[1]);
                if (buffer[1].empty()) break;
                temp1.set_grade(buffer[1]);
                hashedNameTwo = hashingName(temp1.student_name);

                output.close();
                output.open("..\\buckets1\\" + to_string(hashedNameTwo) + ".csv", ofstream::out | ofstream::app);
                output << temp1.student_name << "," << temp1.korean << "," << temp1.math << "," << temp1.english
                << "," << temp1.science << "," << temp1.social << "," << temp1.history << endl;

            }
            blockIndex++;
        }
    }

    // hashing one finish
    // hashing two start

    const int blockOverIndex = 10;
    while (nameGradeOneCount < 1000) {
        for (blockIndex = 0; blockIndex < 10; blockIndex++) {
            block[blockIndex].close();
            block[blockIndex].open("..\\name_grade1\\" + to_string(nameGradeOneCount++) + ".csv", ios::in);
        }
        blockIndex = 0;

        while (blockIndex < 10) {
            while (!block[blockIndex].eof()) {
                getline(block[blockIndex], buffer[0]);
                if (buffer[0].empty()) break;
                temp0.set_grade(buffer[0]);
                hashedNameOne = hashingName(temp0.student_name);

                block[blockOverIndex].close();
                block[blockOverIndex].open("..\\buckets1\\" + to_string(hashedNameOne) + ".csv", ios::in);

                while (!block[blockOverIndex].eof()) {
                    getline(block[blockOverIndex], buffer[1]);
                    if (buffer[1].empty()) break;
                    temp1.set_grade(buffer[1]);
                    if (isValid(temp0, temp1)) {
                        output.close();
                        output.open("..\\buckets2\\" + to_string(hashedNameOne) + ".csv", ofstream::out | ofstream::app);
                        output << temp0.student_name << endl;
                    }
                }
            }
            blockIndex++;
        }
    }

    // second hashing finish
    // now, merge student_number and student_name
    // buffer[0] : name_number
    // buffer[1] : buckets2

    output.close();
    output.open("./output3.csv");

    while (nameNumberCount < 1000) {
        for (blockIndex = 0; blockIndex < 10; blockIndex++) {
            block[blockIndex].close();
            block[blockIndex].open("..\\name_number\\" + to_string(nameNumberCount++) + ".csv", ios::in);
        }
        blockIndex = 0;

        while (blockIndex < 10) {
            while (!block[blockIndex].eof()) {
                getline(block[blockIndex], buffer[0]);
                if (buffer[0].empty()) break;
                temp2.set_number(buffer[0]);
                hashedNameThree = hashingName(temp2.student_name);

                block[blockOverIndex].close();
                block[blockOverIndex].open("..\\buckets2\\" + to_string(hashedNameThree) + ".csv", ios::in);

                while (!block[blockOverIndex].eof()) {
                    getline(block[blockOverIndex], buffer[1]);
                    if (buffer[1].empty()) break;
                    if (buffer[1] == temp2.student_name) {
                        output << make_tuple(temp2.student_name, temp2.student_number);
                        break;
                    }
                }
            }
            blockIndex++;
        }
    }











	// write codes here.












	/*********************************************************************/


	output.close();

	
}
