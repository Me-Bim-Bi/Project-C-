//
// Created by Chu Ha Thanh on 2024-12-25.
//

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<string>

using namespace std;

class Employee {
private:
  int id;
  string name;
  float salary;
  float salesCommission;

public:
  Employee(int id = 0, string name = "?", float salary = 0.0f, float salesCommission = 0.0f);
  ~Employee();

  int getId() const;
  string getName() const;
  float getSalary() const;
  float getsalesCommission() const;

  void setID(int id);
  void setName(const string& name);
  void setSalary(float salary);
  void setSalesCommission( float salesCommission);

  void totalIncome();

  void editInfoButNotID();
  string showInfo() const;
};



#endif //EMPLOYEE_H
