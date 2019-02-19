#include <iostream>
#include <string>
using namespace std;

class Student {
	private:
		int id;
		string name;
		int marks;
	public:
		/*Setter function declaration of private members*/
		bool setId(int id);
		bool setName(string name);
		bool setMarks(int marks);
		/*Getter function declarations of private members*/
		int getId(int id);
		string getName(string name);
		int getMarks(int marks);
		/*Constructor declaration*/
		Student(int id, string name, int marks);
		/*Destructor declaration*/
		~Student ();

};
/*Constructor of student class*/
Student::Student(int id, string name, int marks)
{
	cout <<"Constructing the student"<<endl;
	this->id = id;
	this->name = name;
	this->marks = marks;
}

/*Destructor of student class*/
Student::~Student()
{
	cout <<"Deleting the student object"<<endl;
}

/*Function definition of setter functions*/
bool Student::setId(int id)
{
	cout <<"Setting id of student"<<endl;
	this->id = id;
	return true;
}
bool Student::setName(string name)
{
	cout << "Setting the student name"<<endl;
	this->name = name;
	return true;
}

bool Student::setMarks(int marks)
{
	cout << "Setting marks of student"<<endl;
	this->marks = marks;
	return true;
}

/*Function definition of getter functions*/
int Student::getId(int id)
{
	cout <<"Returning id of student"<<endl;
	return this->id;
}
string Student::getName(string name)
{
	cout <<"Returning name of student"<<endl;
	return this->name;
}

int Student::getMarks(int marks)
{
	cout <<"Returning marks of student"<<endl;
	return this->marks;
}


int main()
{
	cout <<"Program starts..."<<endl;
	Student *s1 = new Student(101, "ABC", 400);
	Student s2(102, "DEF", 302);
	cout <<"Program ends..."<<endl;
}

