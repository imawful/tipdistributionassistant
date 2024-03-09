#include<iostream>
#include<vector>
#include<fstream>
class Emp{
public:
	Emp()
	{
		name = "noname";
		hrsworked = 0.0;
		tipamt = 0.0;
	}
	Emp(std::string n)
	{
		name = n;
		hrsworked = 0.0;
	}
	void set_hours(int h)
	{
		hrsworked = h;
	}
	void set_name(std::string n)
	{
		name = n;
	}
	std::string name;
	double hrsworked;
	double tipamt;
private:
};
void skipLines()
{
	for(int i = 0; i < 50; i++)
		std::cout << std::endl;
	return;
}
void displayHeader(std::vector<Emp> empList, double totaltips)
{
	std::cout << "TIP DISTRIBUTION ASSISTANT!\n";
	std::cout << "--------LIST OF EMPLOYEES--------\n";
	std::cout << "NUM\tNAME\tHOURS\tDISTAMT\n";
	double totalhrs = 0.0;
	for(int i = 0; i < empList.size(); i++)
	{
		std::cout << "[" << i << "]" << "\t"
			  << empList[i].name << "\t" 
			  << empList[i].hrsworked << "\t"
			  << "$" << empList[i].tipamt
			  << std::endl;
		totalhrs += empList[i].hrsworked;
	}
	std::cout << "----------END OF LIST-----------\n";
	std::cout << "ALL HOURS WORKED: " << totalhrs << std::endl
		  << "WEEKLY TIP TOTAL: $" << totaltips << std::endl;
	return;
}
std::vector<Emp> parseRecord(std::string path)
{
	std::vector<Emp> record;
	std::fstream rec;
	std::string temp;
	rec.open(path);
	if(rec.is_open())
	{
		while(getline(rec, temp))
		{
			std::string name, hrs;
			bool namedone = false;
			for(int i = 0; i < temp.size(); i++)
			{
				if(temp[i] == ',')
					namedone = true;
				else if(!namedone)
					name += temp[i];
				else if(namedone)
					hrs += temp[i];
			}
			Emp emp;
			emp.set_name(name);
			emp.set_hours(stoi(hrs));
			record.push_back(emp);
		}
		rec.close();
		return record;
	}
	else
		std::cout << "Could not read list, make sure path is valid.\n";
	return record;
}
bool writeRecord(std::string path, std::vector<Emp> emps, int choice)
{
	std::fstream rec;
	if(choice == 1)
		rec.open(path + ".csv",std::ios::out);
	else if(choice == 2)
		rec.open(path + ".txt",std::ios::out);
	if(rec.is_open())
	{
		std::string temp;
		if(choice == 1)
		{
			temp = "Name,Hours,Distribution\n";
			rec << temp;
			temp = "";
			for(int i = 0; i < emps.size(); i++)
			{
				temp += emps[i].name;
				temp += ",";
				temp += std::to_string(emps[i].hrsworked);
				temp += ",";
				temp += std::to_string(emps[i].tipamt);
				temp += "\n";
				rec << temp;
				temp = "";
			}
		}
		else if(choice == 2)
		{
			temp = "Name\t\tHours\t\tDistribution\n";
			rec << temp;
			temp = "";
			for(int i = 0; i < emps.size(); i++)
			{
				temp += emps[i].name;
				temp += "\t\t";
				temp += std::to_string(emps[i].hrsworked);
				temp += "\t";
				temp += std::to_string(emps[i].tipamt);
				temp += "\n";
				rec << temp;
				temp = "";
			}
		}
		rec.close();
		return true;
	}
	else
		std::cout << "failed\n";
	return false;
}
void displayHelp()
{
	std::cout << "Hello! Welcome to tip distribution assisant!" << std::endl;
	std::cout << "Please ensure that all hours and the tip total are accurate before calculations."
		  << std::endl;
	std::cout << "Thank you for using Tip Distribution Assistant!" << std::endl; 
	return;
}
int main(int argc, char* argv[])
{
	std::vector<Emp> employees;
	char choice;
	double alltiptotal = 164.00;
	std::string message = "";
	while(1)
	{
		skipLines();
		displayHelp();
		std::cout << std::endl;
		displayHeader(employees, alltiptotal);
		std::cout << std::endl << "MSG:" << message << std::endl << std::endl;
		std::cout << "A) Add Employee.\n"
			  << "B) Remove Employee.\n"
			  << "C) Update Employee.\n"
			  << "T) Update Total Tips For The Week.\n"
			  << "D) Calculate Distribution\n"
			  << "L) Load New List.\n"
			  << "W) Write Current List to File.\n" 
			  << "Q) Exit" << std::endl;	  
		std::cout << "Make Selection: ";
		std::cin >> choice;
		switch (choice)
		{
			case 'a':
			case 'A':
			{
				skipLines();
				Emp employee;
				std::string tmple;
				double tmp2;	
				std::cout << "Enter employee name:";
				std::cin >> tmple;
				std::cout << "Enter hours worked:";
				std::cin >> tmp2;	
				employee.set_name(tmple);
				employee.set_hours(tmp2);
				employees.push_back(employee);
				message = "Added " + tmple + " as employee.";
				break;	
			}
			case 'b':
			case 'B':
			{
				int select;
				skipLines();
				displayHeader(employees, alltiptotal);
				std::cout << "Enter employee number to remove:";
				std::cin >> select;
				if(select >= employees.size() || select < 0)
					message = "DID NOT DELETE EMPLOYEE. OUT OF RANGE.";
				else
				{
					employees.erase(employees.begin() + select);
					message = "Successfully removed employee.";
				}
				break;
			}
			case 'c':
			case 'C':
			{
				int select;
				skipLines();
				displayHeader(employees, alltiptotal);
				std::cout << "Enter employee number to update:";
				std::cin >> select;
				if(select >= employees.size() || select < 0)
					message = "NO UPDATE PERFORMED. OUT OF RANGE.";
				else
				{
					int choice;
					std::cout << "[1] Name\n[2] Hours Worked\n"
						  << "Select info to update:";
					std::cin >> choice;
					if(choice == 1)
					{
						std::string temp;
						std::cout << "Enter new name:";
						std::cin >> temp;
						employees[select].set_name(temp);
						message = "Successfully updated name of Emp #" 
							+ std::to_string(select);
					}
					else if(choice == 2)
					{
						double hrs;
						std::cout << "Enter updated amt of hours worked:";
						std::cin >> hrs;
						employees[select].set_hours(hrs);
						message = "Successfully updated hours of Emp #"
							+ std::to_string(select);
					}
					else
						message = "No updates done...";
				}
				break;
			}
			case 't':
			case 'T':
			{
				skipLines();
				std::cout << "Enter total amount of tips to distribute:$";
				std::cin >> alltiptotal;
				message = "Successfully updated weekly tip total.";
				break;
			}
			case 'd':
			case 'D':
			{
				double allEmpHours = 0.0;
				for(int i = 0; i < employees.size(); i++)
					allEmpHours += employees[i].hrsworked;
				double rate = alltiptotal/allEmpHours;
				for(int i = 0; i < employees.size(); i++)
					employees[i].tipamt = (employees[i].hrsworked * rate);
				message = "Successfully calculated new distributions.";
				break;
			}
			case 'q':
			case 'Q':
			{
				std::cout << "exiting...\n";
				return 0;
			}
			case 'l':
			case 'L':
			{
				skipLines();
				std::string path;
				std::cout << "Enter path to list:";
				std::cin >> path;
				std::vector<Emp> loadedList = parseRecord(path);
				if(!loadedList.empty())
				{
					employees = loadedList;
					message = "Successfully loaded new list.";
				}
				else
					message = "Something went wrong reading list.";
				break;
			}
			case 'W':
			case 'w':
			{
				skipLines();
				std::string path;
				int choice;
				std::cout << "Enter name of new file:";
				std::cin >> path;
				std::cout << "[1] .CSV\n[2] .TXT\nmake choice:";
				std::cin >> choice;
				if(writeRecord(path, employees, choice))
					message = "Successfully wrote file to current directory.";
				else
					message = "Could not write to file!";
				break;
			}
			default:
			{
				std::cout << "invalid input! try again\n";
				break;
			}
		}
	}
	return 0;
}
