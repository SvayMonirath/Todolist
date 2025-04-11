#include<stdio.h>
#include <stdlib.h>
#include<string.h>

//define 
#define MAX_TASK_AMOUNT 30
#define MAX_WORD_LIMIT 201

//setup enum for better readability
typedef enum {
    ADD_TASK,
    REMOVE_TASK,
    VIEW_TASK,
    EXIT
} OPTIONS;

//function prototype 
void AddTask(int *task_count, char *task[]);
int DisplayChoice (int *choice);

//system function
void pauseScreen();
void clearScreen();

int main(void) {

    OPTIONS options;
    int task_count = 0, choice=0;//declare variables 

    char **Task = (char **)malloc(MAX_TASK_AMOUNT * sizeof(char *)); //allocate memory for list of pointers 

    while(choice != 4) {
        options = DisplayChoice(&choice);

        switch (options-1)
        {
        case ADD_TASK:
            AddTask(&task_count, Task);
            break;
            
        case REMOVE_TASK:

            break;
        case VIEW_TASK:

            break;
        case EXIT:

            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
    }

    return 0; //code success
}

int DisplayChoice (int *choice) {
    clearScreen();
    printf("TODOLIST SYSTEM\n");
    printf("1. Add Task\n");
    printf("2. Delete Task\n");
    printf("3. View Task\n");
    printf("4. Exit\n");
    printf("Choose an option: \n");
    scanf("%d", choice);

    return *choice;
}

void AddTask(int *task_count, char **task_list) {
    //check if task limit has been reached 
    if (*task_count>= MAX_TASK_AMOUNT) { 
        printf("You've reached the maximum number of task\n");
    } else {
        //allcate memory space
        task_list[*task_count] = (char*)malloc(MAX_WORD_LIMIT * sizeof(char));
        if(!task_list[*task_count]) {
            printf("Memory allocation failed\n");
            pauseScreen();
            return;
        }

        // Clear input buffer before fgets
        getchar();

        clearScreen();

        //prompt user for task
        printf("Enter task: ");
        fgets(task_list[*task_count], MAX_WORD_LIMIT, stdin);

        //remove unwanted newline 
         task_list[*task_count][strcspn( task_list[*task_count], "\n")] = '\0';
        printf("Task added: %s\n",  task_list[*task_count]);

        (*task_count)++;
        pauseScreen();
    }
}

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    // Portable pause screen
    printf("Press Enter to continue...");
    getchar();
    getchar();
}