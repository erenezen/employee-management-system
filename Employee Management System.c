#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee {
    char name[50];
    int employee_id;
    char position[50];
    float salary;
    struct employee* next;
};

// Functions going to be used
void addEmployee(struct employee** head);
void deleteEmployee(struct employee** head, const char* name);
void searchEmployee(struct employee* head, const char* name);
void displayEmployees(struct employee* head);
int checkDuplicate(struct employee* head, const char* name);
void displayMenu();

int main() {
    struct employee* head = NULL;

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        if (choice == 1) {
            addEmployee(&head);
        } else if (choice == 2) {
            char nameToDelete[50];
            printf("Enter the name of the employee to delete: ");
            scanf("%s", nameToDelete);
            deleteEmployee(&head, nameToDelete);
        } else if (choice == 3) {
            char nameToSearch[50];
            printf("Enter the name of the employee to search: ");
            scanf("%s", nameToSearch);
            searchEmployee(head, nameToSearch);
        } else if (choice == 4) {
            displayEmployees(head);
        } else if (choice == 5) {
            break;
            // Exit the program
        } else {
            printf("Invalid choice. Please try again.\n");}
    } while (choice != 5);

    // freeing memory
    while (head != NULL) {
        struct employee* temp = head;
        head = head->next;
        free(temp);
    }return 0;
}

void addEmployee(struct employee** head) {
    struct employee* newEmployee = (struct employee*)malloc(sizeof(struct employee));
    // Input employee information
    printf("Enter employee name: ");
    scanf("%s", newEmployee->name);
    // Check for duplicate names
    if (checkDuplicate(*head, newEmployee->name)) {
        printf("Error: Employee with the same name already exists.\n");
        free(newEmployee);
        return;}
    printf("Enter employee ID: ");
    scanf("%d", &newEmployee->employee_id);
    printf("Enter employee position: ");
    scanf("%s", newEmployee->position);
    printf("Enter employee salary: ");
    scanf("%f", &newEmployee->salary);
    newEmployee->next = *head;  // Adding the new employee to the beginning of the list
    *head = newEmployee;
    printf("Employee '%s' added successfully.\n", newEmployee->name);
}

void deleteEmployee(struct employee** head, const char* name) {
    struct employee* current = *head;
    struct employee* prev = NULL;
    printf("Deleting '%s':\n", name);
    // Searching the list
    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    // If the employee is found delete them
    if (current != NULL) {
        if (prev == NULL) {
            // If the employee is the head of the list
            *head = current->next;
        }else
            prev->next = current->next;
        free(current);
        printf("Employee '%s' deleted successfully.\n", name);
    }else{
        printf("No employee with the name '%s'.\n", name);
    }
}

void searchEmployee(struct employee* head, const char* name) {
    struct employee* current = head;
    // Search the list
    while (current != NULL && strcmp(current->name, name) != 0) {
        current = current->next;
    }
    //  display their information if the employee is found
    if (current != NULL) {
        printf("\nEmployee Information:\n");
        printf("Name: %s\n", current->name);
        printf("Employee ID: %d\n", current->employee_id);
        printf("Position: %s\n", current->position);
        printf("Salary: $%.2f\n", current->salary);
    } else {
        printf("No employee with the name '%s'.\n", name);
    }
}

void displayEmployees(struct employee* head) {
    // If the list is empty
    if (head == NULL) {
        printf("No employees to display.\n");
        return;}

    struct employee* current = head;

    printf("\nInitial Employee List:\n");
    // If the list not empty display the informationns of the employees
    while (current != NULL) {
        printf("Name: %s\nEmployee ID: %d\nPosition: %s\nSalary: $%.2f\n---------------\n", current->name, current->employee_id, current->position, current->salary);
        current = current->next;
    }
}

int checkDuplicate(struct employee* head, const char* name) {
    struct employee* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // Duplicate found
            return 1;}
        current = current->next;
    }
    return 0;
    // No duplicate
}

void displayMenu(){
    // Display menu
    printf("\nEmployee Management System Menu:\n");
    printf("1. Add Employee\n");
    printf("2. Delete Employee\n");
    printf("3. Search Employee\n");
    printf("4. Display Employees\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}
