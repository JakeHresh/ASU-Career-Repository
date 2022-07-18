/**
* This program allows the user to create a schedule of their classes by inputting the type of course they are taking,
* the course number, the number of credits the course offers, and the instructor teaching the course.
 * Users can add, drop, and view courses. If the program ends after the user added some courses, the program
 * will create a text file containing information of the classes the student enrolled in. When the user uses
 * the program again, the course information is loaded back into the program for viewing and additional courses
 * can be added, or existing courses can be dropped.
 *
 * In attempting to implement a function that loads the file, I experienced difficulty with the fgets instruction.
 * When using fgets on the global file pointer in the main function, the information was loaded without issue.
 * However, when attempting to refactor the code by encapsulating the instructions in a function, fgets would
 * through a segmentation fault. I was forced to split up the implementation of the schedule_load() function between
 * the function and the main method for the file to be loaded correctly.
 *
* Completion time: 8 hours
* @author Jacob Hreshchyshyn, Professor Ruben Acuna
* @version 9/13/2020
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//MACROS: CONSTANTS
#define MAX_LENGTH 1024


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES
enum subject
{
    SER = 0, EGR, CSE, EEE
};
typedef enum subject Subject;

struct CourseNode
{
    Subject course;
    int courseNum;
    char instructor[MAX_LENGTH];
    int creditHours;

    struct CourseNode* next;
};


////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES

//place to store course information
struct CourseNode* course_collection = NULL;
FILE* file_pointer;
int creditCounter = 0;
////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS
void branching(char option);
void course_insert();// make sure elements are sorted properly. Lower numbers will be near head of list. Type of course id determined by function. COMPLETE
void schedule_print(); // possibly use switch statement to map from enum to printing statement
void course_drop(); // prompt user what course to drop, search for course, and, if it exists, delete it. If it doesn't exist, say so.

void deallocateFront(); // helper method that will be called to deallocate list before program is terminated.

void schedule_load()
{
    file_pointer = fopen("schedule.txt","r");
}
void schedule_save();

//main entry point. Starts the program by displaying a welcome and beginning an 
//input loop that displays a menu and processes user input. Pressing q quits.      
int main() {
    int totalCredits;
    char input_buffer;
    schedule_load();
    //reading file
    if(file_pointer != NULL)
    {
        while(!feof(file_pointer))
        {
            char* file_string;
            fgets(file_string, MAX_LENGTH * 2, file_pointer);
            if(file_string != "")
            {
                char delim[2] = ",";
                char* courseStr;
                char* courseNumStr;
                char* instructorStr;
                char* creditStr;
                courseStr = strtok(file_string, delim);
                courseNumStr = strtok(NULL, delim);
                instructorStr = strtok(NULL, delim);
                creditStr = strtok(NULL, delim);
                int course = atoi(courseStr);
                int courseNum = atoi(courseNumStr);
                int creditNum = atoi(creditStr);
                struct CourseNode* addedCourse = (struct CourseNode*) malloc(sizeof(struct CourseNode));
                addedCourse->course = course;
                addedCourse->courseNum = courseNum;
                strcpy(addedCourse->instructor, instructorStr);
                addedCourse->creditHours = creditNum;
                if(course_collection == NULL)
                {
                    course_collection = addedCourse;
                }
                else if(course_collection->courseNum >= addedCourse->courseNum)
                {
                    addedCourse->next = course_collection;
                    course_collection = addedCourse; // overwrites value of course_collection so that new node is head
                }
                else
                {
                    struct CourseNode* tmp = course_collection;
                    struct CourseNode* nextTmp = NULL;//course_collection;
                    while(tmp != NULL)
                    {
                        if(tmp->next == NULL)
                        {
                            tmp->next = addedCourse;
                            tmp = 0;
                            nextTmp = 0;
                            free(nextTmp);
                            free(tmp);
                            break;
                        }
                        else if(tmp->next->courseNum >= addedCourse->courseNum)
                        {
                            nextTmp = tmp->next;
                            tmp->next = addedCourse;
                            addedCourse->next = nextTmp;
                            tmp = 0;
                            nextTmp = 0;
                            free(tmp);
                            free(nextTmp);
                            break;
                        }
                        else
                        {
                            tmp = tmp->next;
                        }
                    }
                }
            }

        }
    }
    printf("\n\nWelcome to ASU Class Schedule\n");

    //TODO: stuff goes here...

    //menu and input loop
    do {
        printf("\nMenu Options\n");
        printf("------------------------------------------------------\n");
        printf("a: Add a class\n");
        printf("d: Drop a class\n");
        printf("s: Show your classes\n");
        printf("q: Quit\n");
        totalCredits = 0;
        struct CourseNode* tmp = course_collection;
        while(tmp != NULL)
        {
            totalCredits += tmp->creditHours;
            tmp = tmp->next;
        }
        creditCounter = totalCredits;
        tmp = 0;
        free(tmp);
        printf("\nTotal Credits: %d\n\n", totalCredits);
        printf("Please enter a choice ---> ");

        scanf(" %c", &input_buffer);

        branching(input_buffer);
    } while (input_buffer != 'q');

    //TODO: stuff goes here...
    // save list in text file
    schedule_save();// IMPLEMENT THIS!!!

    // deallocate list before program termination
    deallocateFront();
    return 0;
}

//takes a character representing an inputs menu choice and calls the appropriate
//function to fulfill that choice. display an error message if the character is
//not recognized.
void branching(char option) {
    switch (option) {
        case 'a':
            //TODO
            course_insert();
            break;

        case 'd':
            //TODO
            course_drop();
            break;

        case 's':
            //TODO
            schedule_print();
            break;

        case 'q':
            // main loop will take care of this.
            break;

        default:
            printf("\nError: Invalid Input.  Please try again...");
            break;
    }
}

void course_insert()
{
    struct CourseNode* addedCourse = (struct CourseNode*) malloc(sizeof(struct CourseNode));
    int courseSelection;
    printf("\nWhat is the subject? (SER=0, EGR=1, CSE=2, EEE=3)?\n");
    scanf("%d", &courseSelection);
    while(courseSelection != 0 && courseSelection != 1 && courseSelection != 2 && courseSelection != 3)
    {
        printf("\nPlease enter a valid subject selection. (SER=0, EGR=1, CSE=2, EEE=3).\n");
        scanf("%d", &courseSelection);
    }
    int courseNumber;
    printf("\nWhat is the number (e.g. 240)?\n");
    scanf("%d", &courseNumber);
    int creditNumber;
    printf("\nHow many credits is the class (e.g. 3)?\n");
    scanf("%d", &creditNumber);
    while(creditNumber <= 0)
    {
        printf("\nPlease insert a valid number for number of course credits.\n");
        scanf("%d", &creditNumber);
    }
    printf("\nWhat is the name of the teacher?\n");
    scanf("%s", addedCourse->instructor);
    addedCourse->course = courseSelection;
    addedCourse->courseNum = courseNumber;
    addedCourse->creditHours = creditNumber;
    if(course_collection == NULL)
    {
        course_collection = addedCourse;
    }
    else if(course_collection->courseNum >= addedCourse->courseNum)
    {
        addedCourse->next = course_collection;
        course_collection = addedCourse; // overwrites value of course_collection so that new node is head
    }
    else
    {
        struct CourseNode* tmp = course_collection;
        struct CourseNode* nextTmp = NULL;//course_collection;
        while(tmp != NULL)
        {
            if(tmp->next == NULL)
            {
                tmp->next = addedCourse;
                tmp = 0;
                nextTmp = 0;
                free(nextTmp);
                free(tmp);
                break;
            }
            else if(tmp->next->courseNum >= addedCourse->courseNum)
            {
                nextTmp = tmp->next;
                tmp->next = addedCourse;
                addedCourse->next = nextTmp;
                tmp = 0;
                nextTmp = 0;
                free(tmp);
                free(nextTmp);
                break;
            }
            else
            {
                tmp = tmp->next;
            }
        }
    }
}

void schedule_print()
{
    struct CourseNode* tmp = course_collection;
    printf("\nClass Schedule:");
    while(tmp != NULL)
    {
        Subject crse = tmp->course;
        switch (crse) {
            case 0: // SER
                //TODO
                printf("\nSER%d  %d  %s", tmp->courseNum, tmp->creditHours, tmp->instructor);
                break;

            case 1: // EGR
                //TODO
                printf("\nEGR%d  %d  %s", tmp->courseNum, tmp->creditHours, tmp->instructor);
                break;

            case 2: // CSE
                //TODO
                printf("\nCSE%d  %d  %s", tmp->courseNum, tmp->creditHours, tmp->instructor);
                break;

            case 3: // EEE
                printf("\nEEE%d  %d  %s", tmp->courseNum, tmp->creditHours, tmp->instructor);
                break;
        }
        tmp = tmp->next;
    }
    printf("\n");
    tmp = 0;
    free(tmp);
}

void course_drop()
{
    if(course_collection == NULL)
    {
        printf("\nError: Schedule is empty.");
        return;
    }
    int num;
    printf("Enter number:");
    scanf("%d", &num);
    struct CourseNode* tmp = course_collection;
    struct CourseNode* nextTmp = course_collection;
    if(tmp->courseNum == num)
    {
        course_collection = course_collection->next;
        tmp = 0;
        free(tmp);
        nextTmp = 0;
        free(nextTmp);
        return;
    }
    while(tmp != NULL)
    {
        if(tmp->next != NULL)
        {
            if(tmp->next->courseNum == num)
            {
                nextTmp = tmp->next;
                tmp->next = tmp->next->next;
                tmp = 0;//new change
                free(tmp);
                nextTmp = 0;
                free(nextTmp);
                return;
            }
        }
        tmp = tmp->next;
    }
    printf("Error: No course with that number was found.");
}

void schedule_save()
{
    //FILE* file_pointer;
    file_pointer = fopen("schedule.txt", "w");
    struct CourseNode* temp = course_collection;
    while(temp != NULL)
    {
        if(temp->next != NULL)
        {
            fprintf(file_pointer, "%d,%d,%s,%d,\n", temp->course, temp->courseNum, temp->instructor, temp->creditHours);
        }
        else
        {
            fprintf(file_pointer, "%d,%d,%s,%d,", temp->course, temp->courseNum, temp->instructor, temp->creditHours);
        }
        temp = temp->next;
    }
    temp = 0;
    free(temp);
    fclose(file_pointer);
    if(creditCounter == 0)
    {
        remove("schedule.txt");
    }
}

void deallocateFront()
{
    while(course_collection != NULL)
    {
        struct CourseNode* tmp = course_collection;
        course_collection = course_collection->next;
        free(tmp);
        tmp = NULL;
    }
}