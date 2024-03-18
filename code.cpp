#include<iostream>
using namespace std;
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<fstream>
const char password[8] = "object\r";
int success=0;

void gotoxy(short a, short b){
	COORD pos = {a,b};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

/// Menu FUNCTIONS
void regMenu();
void mainMenu();
void displayMenu();
void enquiryMenu();
void deletionMenu();
void performanceMenu();
void exitMenu();
void modificationMenu();
void loginScreen();


class College{
	unsigned int collegeId;
	char collegeName[50];
	char location[40];
	char stream[40];
	char degree[30];
	public:
		
		void addCollege() // For Registering New College
		{
			char string[] = "********COLLEGE REGISTRATION********";
			fstream file;
			int i,found;
			file.open("College.txt", ios::in|ios::app);
			gotoxy(25,6);
			for(i=0;string[i]!='\0';i++)
			{
				Sleep(40);
				cout << string[i];
			}
			gotoxy(30,9);
			cout<<"Enter the College ID:";
			cin >> collegeId;
			while(file) // To check whether College ID exists
			{
				College c2;
				found=0;
				file.read((char *)&c2, sizeof(c2));
				if(collegeId==c2.collegeId)
				{
					gotoxy(30,12);
					cout << "College ID already exists";
					found=1;
					break;
				}
			}
			if(found==1)
			{
				file.close();
				Sleep(100);
				system("CLS");
				regMenu();
			}
			else // if no Id found
			{
				char choice;
				gotoxy(30,10);
				cout<<"Enter the College Name:";
				cin >> collegeName;
				gotoxy(30,11);
				cout << "Enter the Location:";
				cin >> location;
				gotoxy(30,12);
				cout<<"Enter the Stream:";
				cin >> stream;
				gotoxy(30,13);
				cout<<"Enter the Degree:";
				cin >> degree;
				gotoxy(30,17);
				cout << "Do you wish to proceed?(Y/n):";
				cin >> choice;
				if(choice=='y' or choice=='Y') // Register College
				{
					file.write((char *)this,sizeof(College));
					gotoxy(30,19);
					cout<<"College Registered";
					Sleep(100);
					file.close();
					system("CLS");
					regMenu();
				}
				else
				{
					file.close();
					system("CLS");
					displayMenu();
				}
				
			}
		}
		
		void displayCollege() // Display College section of DisplayMenu
		{
			ifstream infile;
			infile.open("College.dat", ios::in|ios::binary);
			if(infile.fail())
			{
				cout << "File cannot be opened";
				infile.close();
				mainMenu();
			}
			else
			{
				gotoxy(8,10);
				cout<<"CollegeID";
				gotoxy(26,10);
				cout<<"Name";
				gotoxy(39,10);
				cout<<"Location";
				gotoxy(56,10);
				cout<<"Stream";
				gotoxy(71,10);
				cout<<"Degree";
				int i = 0;
				while(infile)
				{
					infile.read((char*)this, sizeof(College));
					gotoxy(8,13+i);
					cout<<collegeId;
					gotoxy(26,13+i);
					cout<<collegeName;
					gotoxy(39,13+i);
					cout << location;
					gotoxy(56,13+i);
					cout << stream;
					gotoxy(71,13+i);
					cout<< degree;
					i = i+2;
				}
				char choice;
				gotoxy(0,27);
				cout<<"Go Back to Display Menu?(Y/N):";
				cin >> choice;
				if(choice=='y' || choice=='Y')
				{
					system("CLS");
					infile.close();
					displayMenu();
				}
				else
				{
					infile.close();
					mainMenu();
				}
			}
		}
		
		void enquireCollege() // enquire about the college
		{
			ifstream infile;
			char string[] = "********COLLEGE ENQUIRY********";
			int id,i,found=0;
			gotoxy(25,6);
			for(i=0;string[i]!='\0';i++)
			{
				Sleep(40);
				cout << string[i];
			}
			gotoxy(30,9);
			cout << "Enter the College ID to enquire:";
			cin >> id;
			infile.open("College.dat", ios::in | ios::binary);
			if(infile.fail())
			{
				gotoxy(30,13);
				cout << "No datas Available";
				Sleep(100);
				infile.close();
				system("CLS");
				mainMenu();
			}
			else
			{
				while(!infile.eof())
				{
					infile.read((char *)this, sizeof(College));
					if(id==collegeId)
					{
						found=1;
						gotoxy(30,11);
						cout<<"----------------------------------";
						gotoxy(30,13);
						cout << "College ID:"<<collegeId;
						gotoxy(30,14);
						cout << "College Name:"<<collegeName;
						gotoxy(30,15);
						cout << "College Location:"<<location;
						gotoxy(30,16);
						cout << "Stream: "<<stream;
						gotoxy(30,17);
						cout << "Degree: "<<degree;
						break;
					}
				}
				if(found==0)
				{
					gotoxy(30,13);
					cout << "No college of that ID found";
				}
				char choice;
				gotoxy(30,21);
				cout << "Enquire Again?(Y/N):";
				cin >> choice;
				if(choice=='y' || choice=='Y')
				{
					infile.close();
					system("CLS");
					enquireCollege();
				}
				else
				{
					infile.close();
					system("CLS");
					mainMenu();
				}
			}	
		}
		
		void modifyCollege() // modify the college details
		{
			fstream file;
			int id,found=0;
			gotoxy(30,9);
			cout << "Enter the college ID to make changes to:";
			cin >> id;
			file.open("College.dat", ios::in|ios::out|ios::binary);
			if(file.fail())
			{
				gotoxy(30,20);
				cout << "File fail.";
				Sleep(100);
				file.close();
				system("CLS");
				mainMenu();
			}
			else
			{
				while(!file.eof())
				{
					int pos = file.tellg();
					 file.read((char*)this, sizeof(College));
					 if(id==collegeId)
					 {
					 		found=1;
					 		gotoxy(30,11);
					 		cout << "Enter the College Name:";
					 		cin >> collegeName;
					 		gotoxy(30,12);
							cout << "Enter the Location:";
							cin >> location;
							gotoxy(30,13);
							cout << "Enter the Stream";
							cin >> stream;
							gotoxy(30,14);
							cout << "Enter the Degree:";
							cin>>degree;
							gotoxy(30,16);
							char ch;
							cout << "Make changes?(Y/N):";
							cin >> ch;
							file.seekp(pos);
							if(ch=='y'||ch=='Y')
							{
							file.write((char*)this, sizeof(College));
							}
							else
							{
								file.close();
								system("CLS");
								modifyCollege();
							}
							break;
						}
					 }
				}
				if(found==0)
				{
					gotoxy(30,28);
					cout << "College not found"; 
				}
				file.close();
				char choice;
				gotoxy(30,30);
				cout << "Modify Again?(Y/N):";
				cin>>choice;
				if(choice=='y' || choice=='Y')
				{
					system("CLS");
					modifyCollege();
				}
				else
				{
					system("CLS");
					mainMenu();
				}
			}
		
		void deleteCollege() // delete the college details
		{
			fstream file;
			int id,i,found=0;
			char string[] = "********DELETE COLLEGE********";
			gotoxy(25,6);
			for(i=0;string[i]!='\0';i++)
			{
				Sleep(40);
				cout<<string[i];
			}
			file.open("College.dat", ios::in | ios::out|ios::binary);
			if(file.fail())
			{
				gotoxy(30,28);
				cout << "File not opened.";
				Sleep(100);
				file.close();
				system("CLS");
				mainMenu();
			}
			else
			{
				gotoxy(30,9);
				cout << "Enter the College Id to delete:";
				cin >> id;
				while(file)
				{
					file.read((char *)this, sizeof(College));
					if(id==collegeId)
					{
						found=1;
					}
					else
					{
						file.write((char *)this, sizeof(College));
					}
				}
				file.close();
				char choice;
				if(found==1)
				{
					gotoxy(30,18);
					cout << "College Deleted";
				}
				gotoxy(30,20);
				cout << "Delete Again?(Y/N):";
				cin >> choice;
				if(choice=='y' || choice=='Y')
				{
					system("CLS");
					deleteCollege();
				}
				else
				{
					system("CLS");
					mainMenu();
				}
			}	
		}
};


class Student{
	unsigned int studentId;
	char name[50];
	char fatherName[50];
	char city[40];
	char address[40];
	char stream[30];
	char degree[40];
	
	public:
		void addStudent()
		{
			fstream file;
			file.open("Students.txt",ios::in | ios::app);
			char string[] = "********STUDENT REGISTRATION********";
			int i,found;
			gotoxy(25,6);
			for(i=0;string[i]!='\0';i++)
			{
				cout << string[i];
			}
			gotoxy(30,9);
			cout << "Enter the student Id:";
			cin >> studentId;
			while(file)
			{
				Student s1;
				found = 0; 
				file.read((char*)&s1, sizeof(s1));
				if(studentId==s1.studentId)
				{
					found=1;
					break;
				}
			}
			if(found==1)
			{
				gotoxy(30,20);
				cout << "Id already exits";
				Sleep(150);
				file.close();
				system("CLS");
				regMenu();
			}
			else
			{
				gotoxy(30,10);
				cout << "Enter the Student Name:";
				cin >> name;
				gotoxy(30,11);
				cout << "Enter Father's Name:";
				cin >> fatherName;
			}
			
			
		}
};



int main(){
	loginScreen();
	if(success==1)
	{
		mainMenu();
	}
	else
	{
		exit(1);
	}
}

void mainMenu(){
	int ch,i;
	char string[] = "********MAIN MENU********";
	gotoxy(25,6);
	for(i=0;string[i]!='\0';i++)
	{
		Sleep(50);
		cout<<string[i];
	}
	gotoxy(30,9);
	cout<<"1. Registration";
	gotoxy(30,10);
	cout<<"2. Display";
	gotoxy(30,11);
	cout<<"3. Enquiry";
	gotoxy(30,12);
	cout<<"4. Modification";
	gotoxy(30,13);
	cout<<"5. Deletion";
	gotoxy(30,14);
	cout<<"6. Performance";
	gotoxy(30,15);
	cout<<"7. Exit";
	gotoxy(30,17);
	cout<<"Enter the choice.";
	cin>>ch;
	switch(ch){
		case 1:
			system("CLS");
			regMenu();
			break;
			
		case 2:
			system("CLS");
			displayMenu();
			break;
			
		case 3:
			system("CLS");
			enquiryMenu();
			break;
		
		case 4:
			system("CLS");
			modificationMenu();
			break;
			
		case 5:
			system("CLS");
			deletionMenu();
			break;
		
		case 6:
			system("CLS");
			performanceMenu();
			break;
		
		case 7:
			system("CLS");
			exitMenu();
			break;
		
		default:
			system("CLS");
			mainMenu();
	}
}


void regMenu(){
	int ch,i;
	char string[50] = "********REGISTRATION MENU********";
	gotoxy(25,6);
	for(i=0;string[i]!='\0';i++)
	{
		Sleep(50);
		cout<<string[i];
	}
	gotoxy(30,9);
	cout << "1. College";
	gotoxy(30,10);
	cout << "2. Student";
	gotoxy(30,11);
	cout << "3. Professor";
	gotoxy(30,12);
	cout << "4. Exam Form";
	gotoxy(30,13);
	cout << "5. Exam Schedule";
	gotoxy(30,14);
	cout << "6. Result";
	gotoxy(30,15);
	cout << "7. Back to Main Menu";
	gotoxy(30,17);
	cout << "Enter Choice:";
	cin >> ch;
	switch(ch)
	{
		case 1:
			system("CLS");
			College c;
			c.addCollege();
			break;
		case 7:
			system("CLS");
			mainMenu();
			break;
		default:
			system("CLS");
			regMenu();
	}
}

void displayMenu(){
	int i,ch;
	char string[] = "********DISPLAY MENU********";
	gotoxy(25,6);
	for(i=0;string[i]!='\0';i++)
	{
		Sleep(50);
		cout<<string[i];
	}
	gotoxy(30,9);
	cout << "1. College";
	gotoxy(30,10);
	cout << "2. Student";
	gotoxy(30,11);
	cout << "3. Professor";
	gotoxy(30,12);
	cout << "4. Exam Form";
	gotoxy(30,13);
	cout << "5. Exam Schedule";
	gotoxy(30,14);
	cout << "6. Result";
	gotoxy(30,15);
	cout << "7. Back to Main Menu";
	gotoxy(30,17);
	cout << "Enter Choice:";
	cin >> ch;
	switch(ch)
	{
		case 1:
			system("CLS");
			College c;
			c.displayCollege();
			break;
		
		case 7:
			system("CLS");
			mainMenu();
			break;
			
		default:
			system("CLS");
			displayMenu();
	}
}

void enquiryMenu(){
	int i,ch;
	char string[] = "********ENQUIRY MENU********";
	gotoxy(25,6);
	for(i=0;string[i]!='\0';i++)
	{
		Sleep(50);
		cout<<string[i];
	}
	gotoxy(30,9);
	cout << "1. College";
	gotoxy(30,10);
	cout << "2. Student";
	gotoxy(30, 11);
	cout << "3. Professor";
	gotoxy(30, 12);
	cout << "4. Back to Main Menu";
	gotoxy(30,14);
	cout << "Enter Choice:";
	cin >> ch;
	switch(ch)
	{
		case 1:
			system("CLS");
			College c;
			c.enquireCollege();
			break;
		
		case 4:
			system("CLS");
			mainMenu();
			break;
		
		default:
			system("CLS");
			enquiryMenu();
	}
}

void modificationMenu(){
	int ch,i;
	char string[] = "********MODIFICATION MENU********";
	gotoxy(25,6);
	for(i=0;string[i]!='\0';i++)
	{
		Sleep(50);
		cout<<string[i];
	}
	gotoxy(30,9);
	cout<<"1. College";
	gotoxy(30,10);
	cout<<"2. Student";
	gotoxy(30,11);
	cout << "3. Proffesor";
	gotoxy(30,12);
	cout << "4. Back to Main Menu";
	gotoxy(30,14);
	cout << "5. Enter Choice:";
	cin>>ch;
	switch(ch)
	{
		case 1:
			system("CLS");
			College c;
			c.modifyCollege();
			break;
		
		case 4:
			system("CLS");
			mainMenu();
			break;
			
		default:
			system("CLS");
			modificationMenu();
	}
}


void deletionMenu(){
	int ch,i;
	char string[] = "********DELETION MENU********";
	gotoxy(25,6);
	for(i=0;string[i]!='\0';i++)
	{
		Sleep(50);
		cout << string[i];
	 } 
	 gotoxy(30,9);
	 cout << "1. College";
	 gotoxy(30,10);
	 cout << "2. Student";
	 gotoxy(30,11);
	 cout << "3. Professor";
	 gotoxy(30,12);
	 cout << "4. Back to Main Menu";
	 gotoxy(30,14);
	 cout << "Enter Choice:";
	 cin >> ch;
	 switch(ch)
	 {
	 	case 1:
	 		system("CLS");
	 		College c;
	 		c.deleteCollege();
	 		break;
	 	
	 	case 4:
	 		system("CLS");
	 		mainMenu();
	 		
	 	default:
	 		system("CLS");
	 		deletionMenu();
	 }
}


void performanceMenu(){
	int ch,i;
	char string[] = "********PERFORMANCE MENU********";
	gotoxy(25,6);
	for(i=0;string[i]!='\0';i++)
	{
		Sleep(50);
		cout<<string[i];
	}
	gotoxy(30,9);
	cout << "1. Foundation";
	gotoxy(30,10);
	cout << "2. Back to Main Menu";
	gotoxy(30,12);
	cout << "Enter Choice:";
	cin >> ch;
}

void exitMenu(){
		int i;
		char string[50] = "Program ends in 3....2....1...";
		gotoxy(30,6);
		for(i=0;string[i]!='\0';i++);
		{
			Sleep(60);
			cout << string[i];
		}
}

void loginScreen(){
	char pass[7];
	char string[] = "WELCOME TO UNIVERSITY MANAGEMENT SYSTEM!!!!";
	int attempt = 0,i;
	gotoxy(30,4);
	for(i=0;string[i]!='\0';i++)
	{
		Sleep(70);
		cout<<string[i];	
	}
	gotoxy(30,8);
	cout << "Enter password to login:";
	while(attempt <= 3)
	{
		i=0;
		strcpy(pass,"");
		while(pass[i-1]!='\r')
		{
			pass[i] = getch();
			if(pass[i-1]!='\r')
			{
				cout<<"*";
			}
			i++;
		}
		cout<<endl;
		if(strcmp(pass, password)==0)
		{
				success=1;
				cout << "Password Correct";
				Sleep(1);
				break;
		}
		else
		{
				cout << "Incorrect Password. "<<3-attempt<<" login attempts remain:"<<endl;	
				attempt++;
		}
	}
	if(attempt>3)
	{
		cout << "You ran out of attempts";
		exit(2);
	}
	system("CLS");
}































































