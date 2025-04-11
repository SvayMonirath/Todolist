#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_TASK_AMOUNT 30
#define MAX_WORD_LIMIT 201

// Setup enum for better readability
typedef enum {
    ADD_TASK,
    REMOVE_TASK,
    VIEW_TASK,
    EXIT
} OPTIONS;

// Function prototypes
OPTIONS DisplayChoice();
void AddTask(int *task_count, char **task_list);
void View_task(int task_count, char **task_list);
void Delete_task(int *task_count, char **task_list);

// System functions
void pauseScreen();
void clearScreen();

int main(void) {
    OPTIONS options;
    int task_count = 0;

    // Allocate memory for list of task pointers
    char **Task = (char **)malloc(MAX_TASK_AMOUNT * sizeof(char *)); 

    do {
        options = DisplayChoice();

        switch (options) {
            case ADD_TASK:
                AddTask(&task_count, Task);
                break;

            case REMOVE_TASK:
                View_task(task_count, Task);
                if (task_count > 0) {
                    Delete_task(&task_count, Task);
                } else {
                    pauseScreen();
                }
                break;

            case VIEW_TASK:
                View_task(task_count, Task);
                break;

            case EXIT:
                printf("Exiting.....\n");
                break;

            default:
                printf("Invalid Choice\n");
                break;
        }
        pauseScreen();
    } while (options != EXIT);

    // Free allocated memory
    for (int i = 0; i < task_count; i++) {
        free(Task[i]);
    }
    free(Task);

    return 0;
}

OPTIONS DisplayChoice() {
    int choice;
    clearScreen();
    printf("TODOLIST SYSTEM\n");
    printf("1. Add Task\n");
    printf("2. Delete Task\n");
    printf("3. View Task\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    // Return enum directly
    return (OPTIONS)(choice - 1);
}

void AddTask(int *task_count, char **task_list) {
    // Check if task limit has been reached 
    if (*task_count >= MAX_TASK_AMOUNT) { 
        printf("You've reached the maximum number of tasks\n");
    } else {
        // Allocate memory space for new task
        task_list[*task_count] = (char *)malloc(MAX_WORD_LIMIT * sizeof(char));
        if (!task_list[*task_count]) {
            printf("Memory allocation failed\n");
            pauseScreen();
            return;
        }

        // Clear input buffer before fgets
        getchar();

        clearScreen();

        // Prompt user for task
        printf("Enter task: ");
        fgets(task_list[*task_count], MAX_WORD_LIMIT, stdin);

        // Remove unwanted newline 
        task_list[*task_count][strcspn(task_list[*task_count], "\n")] = '\0';
        printf("Task added successfully\n");
        (*task_count)++;
    }
}

void View_task(int task_count, char **task_list) {
    clearScreen(); 
    if (task_count < 1) {
        printf("No task found\n");
    } else {
        printf("Tasks: \n");
        for (int i = 0; i < task_count; i++) {
            printf("%d. %s\n", i + 1, task_list[i]);
        }
    }
}

void Delete_task(int *task_count, char **task_list) {
    int delete_choice;
    
    // Check if there are any tasks to delete
    if (*task_count == 0) {
        printf("No tasks available to delete.\n");
        return;
    }

    // Display the task list and ask user to choose a task to delete
    printf("Choose a task number to remove: ");
    scanf("%d", &delete_choice);

    // Validate the input choice
    if (delete_choice < 1 || delete_choice > *task_count) {
        printf("Invalid choice. Please choose a valid task number.\n");
    } else {
        int index = delete_choice - 1;

        // Free memory of the task being deleted
        free(task_list[index]);

        // Shift remaining tasks left to fill the gap
        for (int i = index; i < *task_count - 1; i++) {
            task_list[i] = task_list[i + 1];
        }

        // Decrement the task count after deletion
        (*task_count)--;

        printf("Task deleted successfully.\n");
    }

}

void clearScreen() {
    system("cls"); // use "clear" for Linux/Mac
}

void pauseScreen() {
    printf("Press Enter to continue...");
    getchar();
    getchar();
}
