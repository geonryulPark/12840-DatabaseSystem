#include <bits/stdc++.h>
using namespace std;

class name_age {
	public:
		string name;
		string age;
		
		void set_name_age(string tuple)
		{
			stringstream tuplestr(tuple);

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

			getline(tuplestr, name, ',');
			getline(tuplestr, salary);
		}
};

string make_tuple(string name, string age, string salary)
{
	return name+ ',' + age + ',' + salary + '\n';
}

int isSameName(name_age temp0, name_salary temp1) {
    // -1 : name_age 방향의 name이 더 크다.
    // 0 : 두 파일 간 name이 같다.
    // 1 : name_salary(temp1) 방향의 name이 더 크다.
    if (temp0.name > temp1.name)
        return -1;
    if (temp0.name == temp1.name)
        return 0;
    return 1;
}

int main(){

	string buffer[2];
	name_age temp0;
	name_salary temp1;
	int current_block[2] = {};  // 현재 block
	fstream block[12];          // memory에 올라올 수 있는 최대 block
	ofstream output;            // 쓰기

	output.open("./output1.csv");

	if(output.fail())
	{
		cout << "output file opening fail.\n";
	}

	/*********************************************************************************/

    int file1Count = 0; // 1000 / 10 = 100
    int file2Count = 0; // 100까지가 제한값



    while (file1Count < 100 && file2Count < 100) {
        for (int i = 0; i < 10; i++) {
            file1Index = file1Count + i;
            file2Index = file2Count + i;

        }


        file1Count++;
        file2Count++;
    }









	// write codes here.












	/*********************************************************************************/


	output.close();
}
