/* author: fpayan */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

void print_error(); /* Method to print the error message to the console */
/* Built-In Commands */
void updateDir(char* dir); /* Update the directory the user is in */

/* Non-Built-In Commands*/
int spawn (char* program, char** arg_list); /* Method to execute non-built-in command */

int main(int argc, char* argv[])
{
    /* Used for fork */
    pid_t pid;

    /* Input / Output file*/
    FILE *file;
    
    /* Logging variable */
    bool log_commands = false;

    /* Create a buffer to store the user's input */
    char *input = "";
    size_t length = 0;

    /* String to print out the current directory */
    char path_dir[] = "/bin";

    const char *path[200]; /* List of paths */
    path[0] = "/bin"; /* Default Directory */
    int num_paths = 1; /* Size of the path array */

    if (argc > 2) /* If more than two arguments are passed, throw an error */
    {
        print_error();
        exit(0);
    } 
    else if (argc == 2) /* BATCH MODE */
    {
        /* Checks if the file exists */
        FILE *input_file = fopen(argv[1], "r");

        /* If the file doesn't exist, exit the program */
        if (input_file == NULL)
        {
            fprintf(stderr,"File doesn't exist");
            exit(1);
        }

        /* Read each line in the file */
        while (getline(&input, &length, input_file) != -1)
        {
            /* If asked to do logging, then we will append each command entered */
            if (log_commands)
            {
                fprintf(file, "%s", input);
            }

            /* Parse the input */
            char *parsed_input[200]; /* Create an array to store all arguments passed */
            int num_args = 0;
            char *token = strtok(input, " \t\n");

            while (token != NULL) /* Iterates and parses the input, storing each token into an array */
            {
                /* Insert the token into the array of arguments */
                parsed_input[num_args] = token;
                num_args++;
                token = strtok(NULL, " \t\n");
            }
            parsed_input[num_args] = NULL;

            /* BUILT-IN COMMAND */
            if (strstr(parsed_input[0], "exit"))
            {
                if (num_args >= 2) /* It is an error to pass any arguments to exit */
                    print_error();
                else
                    exit(0);
            }
            else if (strstr(parsed_input[0], "cd"))
            {
                /* 0 or > 1 args is signaled as an error. Condition here is 1 and 2 because the command is in the argument list as well. */
                if (num_args == 1 || num_args > 2)
                    print_error();
                else
                    updateDir(parsed_input[1]);
            }
            else if (strstr(parsed_input[0], "path"))
            {
                if (num_args > 2) /* Display an error message */
                    print_error();
                else if (num_args == 1) /* If path was just entered, print the path */
                {
                    printf("The path is: %s\n", path_dir);
                }
                else /* Update the current path*/
                {
                    /* Overwrite the path directory */
                    char *temp = parsed_input[1];
                    strcpy(path_dir, temp);
                    
                    fprintf(stderr, "path is now %s\n", path_dir);

                    /* Overwrite the list of paths */
                    int index = 0;
                    num_paths = 0;
                    char* token = parsed_input[1];
                    token = strtok(parsed_input[1], ": \t\n");

                    while (token != NULL)
                    {
                        path[index] = token;
                        num_paths++;
                        index++;
                        token = strtok(NULL, ": \t\n");
                    }
                }
            }
            else if (strstr(parsed_input[0], "logging"))
            {
                if (num_args == 3 && strstr(parsed_input[1], "on")) /* Logging on*/
                {
                    /* Open the file for appending to file */
                    char* filename = parsed_input[2];
                    file = fopen(filename, "a");

                    /* Check if the file exists */
                    if (file == NULL)
                        print_error();
                    else
                    {
                        fprintf(stderr, "Writing to file\n");
                        log_commands = true;
                    }
                }
                else if (num_args == 2 && strstr(parsed_input[1], "off")) /* Logging off */
                {
                    fprintf(stderr, "Closing file\n");
                    fclose(file);
                    log_commands = false;
                }
                else /* Error */
                    print_error();
            }
            else /* NOT A BUILT-IN COMMAND */
            {
                int command_found = 0; /* Used to indicate if the command was found */
                char string[200]; /* Used to store the path the command is located in */

                /* Iterate through path and check if the command exists */
                for (int i = 0; i < num_paths; i++)
                {
                    /* Concatenate the string to the path */
                    strcpy(string, path[i]);
                    strcat(string, "/");
                    strcat(string, parsed_input[0]);
                    
                    printf("Checking: %s\n", string);
                    /* Check if the command exists */                
                    if (access(string, X_OK) == 0)
                    {
                        /* The command is now updated to have the path and set to index 0 */
                        parsed_input[0] = string;
                        command_found = 1;
                        break;
                    }
                }

                /* If the command is valid, we execute the command */
                if (command_found == 1)
                {
                    /* Execute command */
                    spawn(parsed_input[0], parsed_input);
                }
                else /* Command not found. Print an error */
                {
                    print_error();
                }
            }
        }

        /* Close the file and free up input */
        fclose(input_file);
    }
    else /* INTERACTIVE MODE */
    {
        /* While loop that repeatedly asks for input to tell it what command to execute */
        while (true)
        {
            /* Print the prompt and get user input */
            fprintf(stderr,"tsh> ");
            getline(&input, &length, stdin);

            /* If asked to do logging, then we will append each command entered */
            if (log_commands)
            {
                fprintf(file, "%s\n", input);
            }
            /* Parse the input */
            char *parsed_input[200]; /* Create an array to store all arguments passed */
            int num_args = 0;
            char *token = strtok(input, " \t\n");

            while (token != NULL) /* Iterates and parses the input, storing each token into an array */
            {
                /* Insert the token into the array of arguments */
                parsed_input[num_args] = token;
                num_args++;
                token = strtok(NULL, " \t\n");
            }
            parsed_input[num_args] = NULL;

            /* BUILT-IN COMMAND */
            if (strstr(parsed_input[0], "exit"))
            {
                if (num_args >= 2) /* It is an error to pass any arguments to exit */
                    print_error();
                else
                    exit(0);
            }
            else if (strstr(parsed_input[0], "cd"))
            {
                /* 0 or > 1 args is signaled as an error. Condition here is 1 and 2 because the command is in the argument list as well. */
                if (num_args == 1 || num_args > 2)
                    print_error();
                else
                    updateDir(parsed_input[1]);
            }
            else if (strstr(parsed_input[0], "path"))
            {
                if (num_args > 2) /* Display an error message */
                    print_error();
                else if (num_args == 1) /* If path was just entered, print the path */
                {
                    printf("The path is: %s\n", path_dir);
                }
                else /* Update the current path*/
                {
                    /* Overwrite the path directory */
                    char *temp = parsed_input[1];
                    strcpy(path_dir, temp);
                    
                    fprintf(stderr, "path is now %s\n", path_dir);

                    /* Overwrite the list of paths */
                    int index = 0;
                    num_paths = 0;
                    char* token = parsed_input[1];
                    token = strtok(parsed_input[1], ": \t\n");

                    while (token != NULL)
                    {
                        path[index] = (char*) malloc(sizeof(token));
                        path[index] = token;
                        printf("token = %s\n", path[index]);
                        num_paths++;
                        index++;
                        token = strtok(NULL, ": \t\n");
                    }
                }
            }
            else if (strstr(parsed_input[0], "logging"))
            {
                if (num_args == 3 && strstr(parsed_input[1], "on")) /* Logging on*/
                {
                    /* Open the file for appending to file */
                    char* filename = parsed_input[2];
                    file = fopen(filename, "a");

                    /* Check if the file exists */
                    if (file == NULL)
                        print_error();
                    else
                    {
                        fprintf(stderr, "Writing to file\n");
                        log_commands = true;
                    }
                }
                else if (num_args == 2 && strstr(parsed_input[1], "off")) /* Logging off */
                {
                    fprintf(stderr, "Closing file\n");
                    fclose(file);
                    log_commands = false;
                }
                else /* Error */
                    print_error();
            }
            else /* NOT A BUILT-IN COMMAND */
            {
                int command_found = 0; /* Used to indicate if the command was found */
                char string[200]; /* Used to store the path the command is located in */

                /* Iterate through path and check if the command exists */
                for (int i = 0; i < num_paths; i++)
                {
                    /* Concatenate the string to the path */
                    strcpy(string, path[i]);
                    strcat(string, "/");
                    strcat(string, parsed_input[0]);
                    
                    printf("Checking: %s\n", string);
                    /* Check if the command exists */                
                    if (access(string, X_OK) == 0)
                    {
                        /* The command is now updated to have the path and set to index 0 */
                        parsed_input[0] = string;
                        command_found = 1;
                        break;
                    }
                }

                /* If the command is valid, we execute the command */
                if (command_found == 1)
                {
                    /* Execute command */
                    spawn(parsed_input[0], parsed_input);
                }
                else /* Command not found. Print an error */
                {
                    print_error();
                }
            }            
        }
    }
    free(input);

    return 1;
}

void print_error()
{
    char error_message[] = "An error has occured (from FP)\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}

void updateDir(char* dir)
{
    char s[200];
                    
    /* Check if the path is valid */
    if (access(dir, X_OK) == 0)
    {
        chdir(dir);
        printf("Path updated.\nCurrent directory is now: %s\n", getcwd(s, 200));
    }
    else
        print_error();

}

int spawn (char* program, char** arg_list)
{
    pid_t child_pid;

    /* Create a child process to execute the command */
    child_pid = fork();

    if (child_pid < 0) /* Fork Failure */
    {
        fprintf(stderr,"\nFork Failed\n");
        return 1;
    }
    else if (child_pid == 0) /* CHILD PROCESS */
    {
        /* Execute the command */
        execvp (program, arg_list);

        /* If an error occurs, print an error message */
        print_error();
    }
    else /* PARENT PROCESS */
    {
        wait(NULL);
        return child_pid;
    }
}