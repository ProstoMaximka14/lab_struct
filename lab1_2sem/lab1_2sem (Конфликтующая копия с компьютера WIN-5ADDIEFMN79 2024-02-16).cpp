#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

struct Profile
{
	string fullName;
	char sex;
	int group;
	int id;
	int grades[8];
	int sr_zn;
	bool y;
};

int read(Profile mass[100], int h)
{
	string c;
	ifstream database;
	database.open("ved.txt");
	if (!database)
	{
		cout << "File does not open " << '\n';
	}
	else
	{
		while (getline(database, c))
		{
			istringstream ss(c);
			Profile t;
			getline(ss, t.fullName, ';');	
			ss >> t.sex;	
			ss.ignore();
			string p;
			getline(ss, p, ';');
			t.group = stoi(p);
			p = "";
			getline(ss, p, ';');
			t.id = stoi(p);
			p = "";
			int o = 0;
			for (int i = 0; i < 8; i++)
			{
				p = "";
				getline(ss, p, ';');
				t.grades[i] = stoi(p);
				o += t.grades[i];
			}
			t.sr_zn = o / 8;
			t.y = true;
			mass[h] = t;
			h += 1;
			p = "";
			c = "";
		}
	}
	return h;
}

int plus_student(Profile mass[100], int h)
{
	Profile student;
	cout << "Write full name ";
	cin >> student.fullName;
	cout << "Write the sex ";
	cin >> student.sex;
	cout << "Group Number ";
	cin >> student.group;
	cout << "Student id ";
	cin >> student.id;
	cout << "Exams ";
	for (int i = 0; i < 8; i++)
		cin >> student.grades[i];
	student.y = true;
	system("cls");
	int miss = 0;
	for (int i = 0; i < 8; i++)
	{
		if (student.grades[i] < 3 && student.grades[i] > 5)
			miss = miss + 1;
	}
	if (miss == 0)
	{
		mass[h]=student;
		h++;
	}
	else
	{
		cout << "2 can not be in stetment " << '\n';
	}
	cout << "Do you want to add one more student ? (1-yes, 0-no) ";
	int m;
	cin >> m;
	if (m)
	{
		plus_student(mass, h);
	}
	else
	{
		return h;
	}
}

void save(Profile mass[100], int p)
{
	ofstream ofs;
	ofs.open("ved.txt", ofstream::out | ofstream::trunc);
	ofs.close();
	for (int i =0; i<p-1; i++)
	{
		ofstream database;
		database.open("ved.txt", ios::app);
		if (!database.is_open())
		{
			cout << '\n' << "Saving error!";
		}
		else
		{
			database << mass[i].fullName << ';';
			database << mass[i].sex << ';' << mass[i].group << ';' << mass[i].id << ';';
			for (int o = 0; o < 8; o++)
				database << mass[i].grades[o] << ";";
			database << '\n';
			database.close();
		}
	}
}

void print(Profile mass[100], int p)
{
	cout << p;
	for (int i = 0; i < p; i++)
	{
		cout << "Fulname " << mass[i].fullName << " Sex " << mass[i].sex << " Group " << mass[i].group << " ID " << mass[i].id << " Grades";
		for (int k = 0; k < 8; k++)
		{
			cout << " " << mass[i].grades[k];
		}
		cout << '\n';
	}
}

void find_group(Profile mass[100], int p)
{
	int a;
	cout << "Write group number to print ";
	cin >> a;
	for (int i = 0; i < p; i++)
	{
		if (mass[i].group == a)
		{
			cout << "Fulname " << mass[i].fullName << " Sex " << mass[i].sex << " Group " << mass[i].group << " ID " << mass[i].id << " Grades";
			for (int k = 0; k < 8; k++)
			{
				cout << " " << mass[i].grades[k];
			}
			cout << '\n';
		}
	}
}

void edit(Profile mass[100], int p)
{

}

void find_id(Profile mass[100], int p)
{
	int a;
	cout << "Write id to print ";
	cin >> a;
	for (int i = 0; i < p; i++)
	{
		if (mass[i].id == a)
		{
			cout << "Fulname " << mass[i].fullName << " Sex " << mass[i].sex << " Group " << mass[i].group << " ID " << mass[i].id << " Grades";
			for (int k = 0; k < 8; k++)
			{
				cout << " " << mass[i].grades[k];
			}
			cout << '\n';
		}
	}
}

void menu()
{
	Profile mass[100];
	int p;
	p = 0;
	bool d = true;
	p=read(mass, p);
	while (d)
	{
		cout << "0)Exit" << '\n';
		cout << "1)Create a new student record. " << '\n';
		cout << "2)Making changes to an existing record." << '\n';
		cout << "3)Displays all student data." << '\n';
		cout << "4)Displays information about all students in group N. N – initialized by the user." << '\n';
		cout << "5)Displaying the top most successful students with the highest rated average score for the last session." << '\n';
		cout << "6)Displaying the number of male and female students." << '\n';
		cout << "7)Displaying data about students who do not receive a scholarship; they study only for “good” and “excellent” grades; they study only “excellently”" << '\n';
		cout << "8)Displaying data about students with list number – k." << '\n';
		int a;
		cout << "Chouse task" << '\n';
		cin >> a;
		switch (a)
		{
		case 1:
			p = plus_student(mass, p);
			break;
		case 2:
			edit(mass, p);
			break;
		case 3:
			print(mass, p);
			break;
		case 4:
			find_group(mass, p);
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			find_id(mass, p);
			break;
		default:
			d = false;
			break;
		}
	}
	save(mass, p);
}

int main()
{
	menu();
}