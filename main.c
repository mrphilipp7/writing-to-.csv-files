/*
  Authors: Zach Philipp, Alex Garza, Douglas Gray, Shane Hoock, Cody Kinney
  Date Due: 6 May 2020
  Purpose: A C program that allows users to input data about a person in a .csv file. Users can then compile the data into a linked list where they can search for users or delete them from the list
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function initializations
void load();
void search();
void del();
void printList();
void input();

// given structure
struct personNode {
  int id;
  char lastName[20];
  char firstName[20];
  int age;
  struct personNode *next;
};
struct personNode *head = NULL; // pointer synonym

int main(void) { // start main
  int choice = 0; // varaible for choice
  
  while (choice != 5){ // start while
    // output prompting for user input
    printf("Select which subset to use \n1: input 20 names\n2: load names\n3: search name\n4: delete name\nchoose 5 to exit\n");
    scanf("%d", &choice); // input for choice

    // if else if and else statements for choices
    if (choice == 1) {
      input();
    }
    //else if load function
    else if (choice == 2) {
      load();
      printList();
    }
    // else if search function
    else if (choice == 3) {
      search();
    }
    // else if del function
    else if (choice == 4) {
      del();
    }
    // else if statement ending loop
    else if (choice == 5)
    {
      printf("Program ended\n");
    }
    // else statement error
    else {
      printf("Wrong input\n");
    }
    //printData(linkedList);
  } // end while

  return 0;
} // end main

void input() {
  // initialization of local variables
  int idL, ageL;
  char lastNameL[20], firstNameL[20];

  // initialize file pointer and opening file
  FILE *fptr;
  fptr = fopen("person.csv", "w");
  // printing the header for the csv file
  fprintf(fptr, "Age > Last Name > First Name > ID");
  for(int x = 0; x < 20; x++) {
    // output and input statements prompting for id, last name, first name, and age
    printf("Enter the ID: ");
    scanf("%d", &idL);
    printf("Enter the Last Name: ");
    scanf("%s", lastNameL);
    printf("Enter the First Name: ");
    scanf("%s", firstNameL);
    printf("Enter the Age: ");
    scanf("%d", &ageL);
    fprintf(fptr, "\n%d>%s>%s>%d", idL, lastNameL, firstNameL,ageL);
  }

  fclose(fptr); // closing file
}

void load() {
  // initialize file pointer and opening file
  FILE *fptr;
  fptr = fopen("person.csv", "r");

  // variable initialization for counting and average
  int sum = 0;
  float average;
  float count = 0;

  //Initializing list variable
  char list[50];

  while (fgets(list, 50, fptr) != NULL) {
    //Allocation of space for personNode
    struct personNode *person = malloc(sizeof(struct personNode));
    // inputing the ID Last Name First Name into linked list
    int ID = atoi(strtok(list, ">"));
    person->id = ID;
    char *last = strtok(NULL, ">");
    strcpy(person->lastName, last);
    char *first = strtok(NULL, ">");
    strcpy(person->firstName, first);
    int ageLoad = atoi(strtok(NULL, ">"));
    person->age = ageLoad;
    person->next = head;
    head = person;
  }

  fclose(fptr); // close file

  struct personNode *loadPtr = head; // setting load pointer to head

  // while loop for finding sum of ages, using count for average
  while(loadPtr->next != NULL) {
    count++;
    sum = sum + loadPtr->age;
    loadPtr = loadPtr->next;
  }

  //Finds Average Age
  average = sum / count;
  // print statement for average age
  printf("Average Age: %.2f\n", average);
}

//Function to search Data
void search() {
  //Initiallizing Variables
  int idL, ageL;
  char lastNameL[20]; 
  char firstNameL[20];
  int count = 0;
  int choice;

  // initializing pointer search
  struct personNode *search = head;

  // output statement prompting user on which way to search
  printf("Select which section to search by: \n1. Age\n2. Last Name\n3. FirstName\n4. ID\n");
  scanf("%d", &choice);

  //Switch to test for Age, Last Name, First Name, or ID
  switch (choice) {
    //Switch Cases
    //Searches Age
    case 1:
      printf("Enter the Age of user: ");
      scanf("%d%*c", &ageL);
      while(search != NULL) {
        if(search->age == ageL) {   
          count++;
        }
        search = search->next; 
      }
      break;
    
    //Searches Last Name
    case 2:
      printf("Enter the Last Name of the user: ");
      scanf("%s%*c", lastNameL);
      while(search != NULL) {
        if(strcmp(search->lastName, lastNameL) == 0) {   
          count++;
        } 
        search = search->next;
      }
      break;
    
    //Searches First Name
    case 3:
      printf("Enter the First Name of the user: ");
      scanf("%s%*c", firstNameL);
      while(search != NULL) {
        if(strcmp(search->firstName, firstNameL) == 0) {   
          count++;
        }
        search = search->next;
      }
      break; 
    
    //Searches ID
    case 4:
      printf("Enter the ID of the user: ");
      scanf("%d%*c", &idL);
      while(search != NULL) {
        if(search->id == idL) {   
          count++;
        }
        search = search->next;
      }
      break; 
  }
  //If Else Statements for if records are found and how many
  if(count == 0) {
    printf("No Record(s) found\n");
  }
  else {
    printf("%d Record(s) found\n", count);
  }
}

//Function for record Deletion
void del() {
  struct personNode *del = head;
  struct personNode *previous = NULL;

  // variable initialization
  int idD;
  int sum = 0;
  float average;
  float count = 0;
  int x;
  
  // intitializing file pointer
  FILE *fptr;

  // prompting for user input of which ID to be deleted
  printf("Enter the ID of user: ");
  scanf("%d%*c", &idD);

  while(del->next != NULL) { // start while
    if(del->id == idD) { // if statement for if id matches with input
      x = 1;
      break; // break loop
    } 
    else { 
      previous = del;
      del = del->next; 
    }
  } // end while
  
  if (x == 0) { // if statement for if no records found
    printf("No record found \n");
  }
  //else statement that deletes the accound chosen by user 
  else {
    if(del == head) {
      head = head->next;
    }
    //else statement that searches the accound chosen by user for deletion
    else {
      previous->next = del->next;
    }
    
    printf("Record deleted\n");
    struct personNode *delPtr = head;
    fptr = fopen("person.csv", "w");
    //while loop that takes the average of age after deletion of an account
    while(delPtr->next != NULL) {
      count++;
      sum = sum + delPtr->age;
      fprintf(fptr,"\n%d>%s>%s>%d",delPtr->age, delPtr->firstName, delPtr->lastName, delPtr->id);
      delPtr = delPtr->next;
    }
    // count = count - 1;
    fclose(fptr);

    average = sum / count;

    printf("\nAverage of age after deletion: %.2f\n",average);
  }
}

//Function to Print List
void printList() {
  // pointer print referencing to personNode 
  struct personNode *print = head;
  // header statement 
  printf("ID   Last Name           First Name          Age\n");
  while(print != NULL) { // start while
    // print statement 
    printf("%-4d %-19s %-19s %d\n", print->id, print->lastName, print->firstName, print->age);
    print = print->next;
    // if statement ending if id is 0 (DNE)
    if (print->id == 0)
    {
      break;
    }
  } // end while
}