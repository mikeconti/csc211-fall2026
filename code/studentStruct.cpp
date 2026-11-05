#include <iostream>

// Write a Student struct that contains
// Name
// StudentID
// Major

// Implement functions:
// void buildStudent(Student &someStudent)
       // Initialize member variables of student Struct
// void changeMajor(Student &someStudent, std::string newMajor);
       // Change the major of a student structure
// void printStudent(Student &someStudent);
       // Prints out all member variables of student structure

struct Student{

  std::string name, major;
  int studentID;

};

void buildStudent(Student &someStudent){

  std::cout << "enter a major: "  << std::endl;

  std::cin >> someStudent.major;

  std::cout << "enter a name: "  << std::endl;
  std::cin >> someStudent.name;

  std::cout << "enter a ID: "  << std::endl;
  std::cin >> someStudent.studentID;

}


void printStudent(Student &someStudent){
  std::cout << someStudent.major << std::endl;
  std::cout << someStudent.name << std::endl;
  std::cout << someStudent.studentID << std::endl;
}

void changeMajor(Student &someStudent, std::string newMajor){
  someStudent.major = newMajor;
}


int main(){

  Student mike, chloe, kayla;

  buildStudent(mike);

  std::cout << std::endl;

  printStudent(mike);
  std::cout << std::endl;

  changeMajor(mike, "CS");
  std::cout << std::endl;

  printStudent(mike);




}