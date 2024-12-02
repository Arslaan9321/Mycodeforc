/*Name:- Arslaan Naseem siddiqui 
Branch:- Comps
Roll No:- 11
UID:- 241P011
Aim: Write a program to maintain a simple employee 
database using a file handling */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Employee {
    int id;
    char name[100];
    float salary;
};


void addEmployee(FILE *file) {
    struct Employee emp;
    
    // Take employee details as input
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    getchar();  
    printf("Enter Employee Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = 0; 
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Employee added successfully!\n");
}


void displayEmployees(FILE *file) {
    struct Employee emp;
    rewind(file);  

    printf("\nEmployee List:\n");
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        printf("ID: %d\n", emp.id);
        printf("Name: %s\n", emp.name);
        printf("Salary: %.2f\n", emp.salary);
        printf("----------------------------\n");
    }
}


void searchEmployee(FILE *file, int searchID) {
    struct Employee emp;
    rewind(file);  
    int found = 0;

    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id == searchID) {
            printf("\nEmployee Found:\n");
            printf("ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Salary: %.2f\n", emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found!\n", searchID);
    }
}

// Main function
int main() {
    FILE *file;
    int choice, searchID;

    
    file = fopen("employee_db.dat", "ab+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (1) {
        printf("\nEmployee Database Management\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                displayEmployees(file);
                break;
            case 3:
                printf("Enter Employee ID to search: ");
                scanf("%d", &searchID);
                searchEmployee(file, searchID);
                break;
            case 4:
                fclose(file);
                printf("Exiting the program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    fclose(file);
    return 0;
}

/*output
Employee Database Management
1. Add Employee
2. Display All Employees
3. Search Employee by ID
4. Exit
Enter your choice: 1
Enter Employee ID: 1702
Enter Employee Name: Ab de villiers
Enter Employee Salary: $25,0000
Employee added successfully!

Employee Database Management
1. Add Employee
2. Display All Employees
3. Search Employee by ID
4. Exit
Enter your choice: Enter Employee ID:
 Enter Employee Name: Enter Employee Salary*/