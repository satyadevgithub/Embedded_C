#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef union idproof {
    char adhaar[20];
    char passport[20];
    char drivingl[20];
} IdProof;

typedef struct student {
    char name[50];
    char surname[25];
    char fathername[100];
    int age;
    int class; // Consider changing to a more descriptive name, like 'grade'
    int rollnum;
    IdProof ids;
    int id_type; // 0 for Adhaar, 1 for Passport, 2 for Driving License
} Student;

typedef struct teacher {
    char name[50];
    char surname[25];
    char subject[100];
    int age;
    int joiningyear;
    int regnum;
    IdProof idt;
    int id_type; // 0 for Adhaar, 1 for Passport, 2 for Driving License
} Teacher;

typedef struct college_portal {
    Student stu;
    Teacher tchr; // Renamed for clarity
} CollegePortal;

int st=0;
// Function prototypes for menu options
void Main_menu();
void Menu();
void Add();
void Display();
void Search();
void Modify();
void Return_Main_Menu();

// Create an array of function pointers to call menu functions
void (*func_ptr[6])() = {Menu, Add, Display, Search, Modify, Return_Main_Menu}; 

// Main function - entry point of the program
void main() {   
  printf("*****Welcome in College Portal*****\n");
  Main_menu();

}
void Main_menu()
{
  do{
  printf("*******Main Menu*******\n");
  printf("Who are you?\n1. Student\n2. Teacher\n3. Exit\nChoice-> ");
  scanf("%d",&st); 
  if(st<1 || st>3) 
  {
  printf("You are unauthorized person to access college portal!!\n\n");
  }
  } while(st<1 || st>3);
  if(st==3) { 
  printf("*****College Portal is Closed*****\n");
  exit(0); }
  func_ptr[0](); // Call the menu function
}
// Function to display the menu and get user choice
void Menu() {
    int choice;
    printf("*******Menu*******\n");
    printf("1.Add\n2.Display\n3.Search\n4.Modify\n5.Return in Main Menu\n");    
    printf("Your Choice: ");
    scanf("%d", &choice); // Get user choice

    // Validate user choice and call the corresponding function
    if (choice < 1 || choice > 5) {
      printf("Wrong choice!! Try again-->\n");
      func_ptr[0](); 
    } else {
      func_ptr[choice](); // Call the selected function
    }    
}

void Add() 
{
  CollegePortal cp;
  if(st==1) {
  printf("Name: ");
  getchar();
  scanf("%[^\n]s",cp.stu.name);
  printf("Surname: ");
  getchar();
  scanf("%[^\n]s",cp.stu.surname);
  printf("Father's Name: ");
  getchar();
  scanf("%[^\n]s",cp.stu.fathername);
  printf("Age: ");
  scanf("%d",&cp.stu.age);
  printf("Class: ");
  scanf("%d",&cp.stu.class);
  printf("Roll Number: ");
  scanf("%d",&cp.stu.rollnum);
  
  FILE *fp=fopen("student.txt","a+");
  if(fp==NULL){ printf("File is not opened!!\n"); exit(0);}
  fwrite(&cp.stu,sizeof(cp.stu),1,fp);
  fclose(fp);
  } else if(st==2) {
  printf("Name: ");
  getchar();
  scanf("%[^\n]s",cp.tchr.name);
  printf("Surname: ");
  getchar();
  scanf("%[^\n]s",cp.tchr.surname);
  printf("Subject: ");
  getchar();
  scanf("%[^\n]s",cp.tchr.subject);
  printf("Age: ");
  scanf("%d",&cp.tchr.age);
  printf("Joining year: ");
  scanf("%d",&cp.tchr.joiningyear);
  printf("Reg Number: ");
  scanf("%d",&cp.tchr.regnum);
  
  FILE *fp=fopen("teacher.txt","a+");
  if(fp==NULL){ printf("File is not opened!!\n"); exit(0);}
  fwrite(&cp.tchr,sizeof(cp.tchr),1,fp);
  fclose(fp);
  }
  func_ptr[0]();
}

void Display()
{
  CollegePortal cp;
  if(st==1) {
  int i=1;
  FILE *fp=fopen("student.txt","a+");
  if(fp==NULL){ printf("File is not opened!!\n"); exit(0);}
  

  while (fread(&cp.stu,sizeof(cp.stu),1,fp) == 1) {
  printf("*******Student-%d*******\n",i++);
  printf("Name: %s\n",cp.stu.name);
  printf("Surname: %s\n",cp.stu.surname);
  printf("Father's Name: %s\n",cp.stu.fathername);
  printf("Age: %d\n",cp.stu.age);
  printf("Class: %d\n",cp.stu.class);
  printf("Roll Number: %d\n",cp.stu.rollnum); }
  
  fclose(fp);
  } else if(st==2) {
  int i=1;
  FILE *fp=fopen("teacher.txt","a+");
  if(fp==NULL){ printf("File is not opened!!\n"); exit(0);}
  

  while (fread(&cp.tchr,sizeof(cp.tchr),1,fp) == 1) {
  printf("*******Teacher-%d*******\n",i++);
  printf("Name: %s\n",cp.tchr.name);
  printf("Surname: %s\n",cp.tchr.surname);
  printf("Subject: %s\n",cp.tchr.subject);
  printf("Age: %d\n",cp.tchr.age);
  printf("Joining year: %d\n",cp.tchr.joiningyear);
  printf("Reg Number: %d\n",cp.tchr.regnum); }
  
  fclose(fp);
  }
  func_ptr[0]();
}

void Search()
{
  CollegePortal cp;
  if(st==1) {
  int ID;
  printf("*****Search Student Details*****\n");
  printf("Search By-->Roll Number: ");
  scanf("%d", &ID); 
  
  
  FILE *fp=fopen("student.txt","a+");
  if(fp==NULL){ printf("File is not opened!!\n"); exit(0);}
  

  while (fread(&cp.stu,sizeof(cp.stu),1,fp) == 1) {
  if (cp.stu.rollnum == ID) {
  printf("*******Student is %s*******\n",cp.stu.name);
  printf("Name: %s\n",cp.stu.name);
  printf("Surname: %s\n",cp.stu.surname);
  printf("Father's Name: %s\n",cp.stu.fathername);
  printf("Age: %d\n",cp.stu.age);
  printf("Class: %d\n",cp.stu.class);
  printf("Roll Number: %d\n",cp.stu.rollnum); } }

  
  fclose(fp);
  } else if(st==2) {
  int ID;
  printf("*****Search Teacher Details*****\n");
  printf("Search By-->Reg Number: ");
  scanf("%d", &ID); 
  
  int i=1;
  FILE *fp=fopen("teacher.txt","a+");
  if(fp==NULL){ printf("File is not opened!!\n"); exit(0);}
  

  while (fread(&cp.tchr,sizeof(cp.tchr),1,fp) == 1) {
  if (cp.tchr.regnum == ID) {
  printf("*******Teacher is %s*******\n",cp.tchr.name);
  printf("Name: %s\n",cp.tchr.name);
  printf("Surname: %s\n",cp.tchr.surname);
  printf("Subject: %s\n",cp.tchr.subject);
  printf("Age: %d\n",cp.tchr.age);
  printf("Joining year: %d\n",cp.tchr.joiningyear);
  printf("Reg Number: %d\n",cp.tchr.regnum); } }
  
  fclose(fp);
  }
  func_ptr[0]();
}
void Modify()
{
CollegePortal cp;
  if(st==1) {
  int ID;
  printf("*****Modify Student Details*****\n");
  printf("Search By-->Roll Number: ");
  scanf("%d", &ID); 
  
  
  FILE *fp=fopen("student.txt","a+");
  FILE *fp1=fopen("student_M.txt","a+");
  if(fp==NULL || fp1==NULL){ printf("File is not opened!!\n"); exit(0);}
  

  while (fread(&cp.stu,sizeof(cp.stu),1,fp) == 1) {
  if (cp.stu.rollnum == ID) {
  printf("*******Student is %s*******\n",cp.stu.name);
  printf("Surname: ");
  getchar();
  scanf("%[^\n]s",cp.stu.surname);
  printf("Age: ");
  scanf("%d",&cp.stu.age);
  printf("Class: ");
  scanf("%d",&cp.stu.class); } 
  fwrite(&cp.stu,sizeof(cp.stu),1,fp1);
  }

  fclose(fp);
  fclose(fp1);
  
      // Remove the original file and rename the temp file
    remove("student.txt");
    rename("student_M.txt", "student.txt");
  } else if(st==2) {
  int ID;
  printf("*****Modify Teacher Details*****\n");
  printf("Search By-->Reg Number: ");
  scanf("%d", &ID); 
  
  int i=1;
  FILE *fp=fopen("teacher.txt","a+");
  FILE *fp1=fopen("teacher_m.txt","a+");
  if(fp==NULL||fp1==NULL){ printf("File is not opened!!\n"); exit(0);}
  

  while (fread(&cp.tchr,sizeof(cp.tchr),1,fp) == 1) {
  if (cp.tchr.regnum == ID) {
  printf("*******Teacher is %s*******\n",cp.tchr.name);
  printf("Surname: ");
  getchar();
  scanf("%[^\n]s",cp.tchr.surname);
  printf("Age: ");
  scanf("%d",&cp.tchr.age);
  printf("Joining year: ");
  scanf("%d",&cp.tchr.joiningyear); } 
  fwrite(&cp.tchr,sizeof(cp.tchr),1,fp1);
  }
  
  fclose(fp);
  fclose(fp1);
  
      // Remove the original file and rename the temp file
    remove("teacher.txt");
    rename("teacher_m.txt", "teacher.txt");
  }
  func_ptr[0]();
}
void Return_Main_Menu(){
Main_menu();
}
