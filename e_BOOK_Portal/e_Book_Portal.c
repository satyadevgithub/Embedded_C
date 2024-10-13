#include<stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct structure {
    int Book_ID; 
    char Book_title[50]; 
    char Book_Author[50]; 
    char Book_ISBN[20]; 
    int Book_Cost; 
} structure;

void Menu(FILE *fp);
void Add(FILE *fp);
void Display_all(FILE *fp);
void Find(FILE *fp);
void Filter(FILE *fp);
void Modify(FILE *fp);
void Exit(FILE *fp);
int count(FILE *fp);
int unique_id(FILE *fp,int ID);
int Display(FILE *fp,structure book);

// Create an array of function pointers to call menu functions
void (*func_ptr[7])(FILE *fp) = {Menu, Add, Display_all, Find, Filter,Modify, Exit}; 

int main()
{
FILE *fp=fopen("file.txt","a+"); //"FILE *fp" is argument of each function
if(fp==NULL)
{
  printf("Error in opening file\n");
  exit (1);
} else {
  printf("File is opened successfully.\n");
}
/*****************code*********************/
  printf("*****Welcome in e Book Portal*****\n");
  printf("**We have %d Books in our Portal**\n", count(fp));
  func_ptr[0](fp); // Call the menu function
/******************************************/
return 0;
}

// Function to display the menu and get user choice
void Menu(FILE *fp) {
    int choice;
    printf("*******Menu*******\n");
    printf("1.Add\n2.Display all\n3.Find\n4.Filter\n5.Modify\n6.Exit\n");    
    printf("Your Choice: ");
    scanf("%d", &choice); // Get user choice

    // Validate user choice and call the corresponding function
    if (choice < 1 || choice > 6) {
      printf("Wrong choice!! Try again-->\n");
      func_ptr[0](fp); 
    } else {
      func_ptr[choice](fp); // Call the selected function
    }  
}

void Add(FILE *fp)
{
  structure book; 
  
  printf("*****Add Book Data*****\n");  
  printf("Book ID-> ");
  scanf("%d", &book.Book_ID); // Get book ID

  // Check for unique ID
  if (unique_id(fp,book.Book_ID) == 1) {
    printf("Book ID is already existing in our database. Try again->\n");
    func_ptr[0](fp);
  }
  // Validate book ID
  if (book.Book_ID < 100 || book.Book_ID > 999) {
    printf("Wrong ID!! Book ID should be 3 digits only. Try again->\n");
    func_ptr[0](fp);
  }

  // Get other book details
  printf("Book Title-> ");
  getchar(); // Clear newline character from buffer
  scanf("%[^\n]s", book.Book_title);  
  printf("Book Author-> ");
  getchar();
  scanf("%[^\n]s", book.Book_Author);  
  printf("Book ISBN-> ");
  getchar();
  scanf("%[^\n]s", book.Book_ISBN);  
  printf("Book Cost-> ");
  scanf("%d", &book.Book_Cost); 
  
  fseek(fp,0,2);
  fwrite(&book, sizeof(structure), 1, fp);
  func_ptr[0](fp);   
}

void Display_all(FILE *fp)
{
    int i=1;
    structure book;
    fseek(fp,0,0);
    while (fread(&book, sizeof(structure), 1, fp) == 1) {
        printf("******Book-%d*******\n", i++);
        Display(fp,book);
    }
    if(count(fp)==0)  { printf("Data Not Found!!\n"); }
    func_ptr[0](fp); 
}

// Function to find a book by its ID
void Find(FILE *fp) {
  int ID;
  int found=0;
  structure book;
  printf("*****Search Book*****\n");
  printf("Search By-->ID: ");
  scanf("%d", &ID); 
  fseek(fp,0,0);
    while (fread(&book, sizeof(structure), 1, fp) == 1) {
      if (book.Book_ID == ID) {
        printf("******Book of ID %d*******\n", ID);
        Display(fp,book);
        found=1;
      }
    }
    if(found==0) { printf("Data Not Found!!\n"); }
  func_ptr[0](fp); 
}

// Function to filter and display books by author
void Filter(FILE *fp) {
  int found=0;
  char Author[50];
  structure book; 
  printf("*****Search Book*****\n");
  printf("Search By-->Author: ");
  getchar(); // Clear newline character from buffer
  scanf("%[^\n]s", Author); 
  int i = 1; // Counter for book numbering
  fseek(fp,0,0);
    // Read books and display those matching the author
    while (fread(&book, sizeof(structure), 1, fp) == 1) {
      if (strcmp(book.Book_Author, Author) == 0) {
        printf("***Book Author: %s - Book%d***\n", book.Book_Author, i++);
        Display(fp,book);
        found=1;
      } 
    }
    if(found==0) { printf("Data Not Found!!\n"); }
  func_ptr[0](fp); // Return to menu
}

void Modify(FILE *fp) {
    int n;
    int ID;
    printf("*****Modify Book Details*****\n");
    printf("Search By-->Book ID: ");
    scanf("%d", &ID);
    structure book;
    FILE *fp1=fopen("file1.txt","a+");
    if(fp1==NULL){ printf("File is not opened!!\n"); exit(0);}
  
    fseek(fp,0,0);
    while (fread(&book,sizeof(structure),1,fp) == 1) {
    if (book.Book_ID == ID) {
    printf("Which option do you want to modify: ");
    printf("\n1. ID\n2. Title\n3. Author\n4. ISBN\n5. Cost\nYour choice is: ");
    scanf("%d", &n); // Read user's choice for modification
    switch(n) {
        case 1:
            printf("Sorry!! You can not change ID.\n");
            break;

        case 2:
           printf("Book Title-> ");
           getchar(); // Clear newline character from buffer
            scanf("%[^\n]s", book.Book_title); 
            break;

        case 3:
            printf("Book Author-> ");
            getchar();
            scanf("%[^\n]s", book.Book_Author);  
            break;

        case 4:
            printf("Book ISBN-> ");
            getchar();
            scanf("%[^\n]s", book.Book_ISBN); 
            break;

        case 5:
            printf("Book Cost-> ");
            scanf("%d", &book.Book_Cost); 
            break;
            
        default:
            printf("Wrong choice!! Try Again\n");
            func_ptr[0](fp);
            
    }
    }
    fwrite(&book,sizeof(structure),1,fp1) ;
    }
    fclose(fp);
    fclose(fp1);
          // Remove the original file and rename the temp file
    remove("file.txt");
    rename("file1.txt", "file.txt");
    fp=fopen("file.txt","a+"); //"FILE *fp" is argument of each function
if(fp==NULL)
{
  printf("Error in opening file\n");
  exit (1);
} else { printf("Book data is modified.\n"); }
  func_ptr[0](fp);
}
// Function to exit the program
void Exit(FILE *fp) {
  printf("***We have %d Books in our Portal***\n", count(fp));
  printf("**Thanks to visiting e Book Portal**\n");
  fclose(fp);
  printf("File is closed successfully.\n");
  exit (0); 
}

int unique_id(FILE *fp,int ID) // Check for unique ID
{
  structure book; //structure define
  fseek(fp,0,0);
  while (fread(&book, sizeof(structure), 1, fp) == 1) {
   if (book.Book_ID == ID) {
    return 1; // ID exists
   }
  }
  return 0; // ID is unique
}


int Display(FILE *fp,structure book)
{
        printf("Book_ID: %d\n", book.Book_ID);
        printf("Book_title: %s\n", book.Book_title);
        printf("Book_Author: %s\n", book.Book_Author);
        printf("Book_ISBN: %s\n", book.Book_ISBN);
        printf("Book_Cost: %d\n\n", book.Book_Cost);
        
        return 0;
}

// Function to count the total number of books in the database
int count(FILE *fp) {
  int count = 0; // Initialize counter
  structure book;  
  if (fp == NULL) {
    printf("FILE is not opened!! Try once more\n");
  } else {
    // Read all books and count them
    fseek(fp,0,0);
    while (fread(&book, sizeof(structure), 1, fp) == 1) {
      count++;
    }
  }
  return count; // Return the count of books
}



