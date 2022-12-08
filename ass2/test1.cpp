#include <bits/stdc++.h>
using namespace std;

class name_age {
	public:
		string name;
		string age;
		
		void set_name_age(string tuple)
		{
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
		
		void set_name_salary(string tuple)
		{
			stringstream tuplestr(tuple);
			string salarystr;

			getline(tuplestr, name, ',');
			getline(tuplestr, salary);
		}
};

string make_tuple(string name, string age, string salary)
{
	return name+ ',' + age + ',' + salary + '\n';
}

int main(){

	string buffer[2];
	name_age temp0;
	name_salary temp1;
	int current_block[2] = {};
	fstream block[12];
	ofstream output;

	output.open("./output1.csv");

	if(output.fail())
	{
		cout << "output file opening fail.\n";
	}

	/*********************************************************************************/

    int nameAgeCount = 0;
    int nameSalaryCount = 0;

    int indexOfNameAge = 0;
    int indexOfNameSalary = 5;

    while (nameAgeCount <= 995 && nameSalaryCount <= 995) {
        if (nameAgeCount % 5 == 0) {
            // name_age block이 비어 있다면,
            for (int i = 0; i < 5; i++) {
                block[i].close();
                block[i].open("..\\name_age\\" + to_string(nameAgeCount++) + ".csv", ios::in);
            }
            indexOfNameAge = 0;
        }
        if (nameSalaryCount % 5 == 0) {
            // name_salary block이 비어 있다면,
            for (int i = 5; i < 10; i++) {
                block[i].close();
                block[i].open("..\\name_salary\\" + to_string(nameSalaryCount++) + ".csv", ios::in);
            }
            indexOfNameSalary = 5;
        }

        while (indexOfNameAge < 5 && indexOfNameSalary < 10) {
            if (indexOfNameAge % 5 == 0) getline(block[indexOfNameAge], buffer[0]);
            if (indexOfNameSalary % 5 == 0) getline(block[indexOfNameSalary], buffer[1]);

            while (true) {
                if (block[indexOfNameAge].eof()) {
                    indexOfNameAge++;
                    break;
                }
                if (block[indexOfNameSalary].eof()) {
                    indexOfNameSalary++;
                    break;
                }

                temp0.set_name_age(buffer[0]);
                temp1.set_name_salary(buffer[1]);

                if (temp0.name == temp1.name && !temp0.name.empty()) {
                    // 출력
                    output.write(make_tuple(temp0.name, temp0.age, temp1.salary).c_str(),make_tuple(temp0.name, temp0.age, temp1.salary).size());
                    getline(block[indexOfNameSalary], buffer[1]);
                } else if (temp0.name > temp1.name) {
                    getline(block[indexOfNameSalary], buffer[1]);
                } else {
                    getline(block[indexOfNameAge], buffer[0]);
                }
            }
        }
    }









	// write codes here.












	/*********************************************************************************/


	output.close();
}
