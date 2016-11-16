#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CMDSIZE 1024
#define BUFSIZE 256

#define OK          0
#define ILLEGAL     1
#define NOT_ABS     1
#define NO_INPUT    1
#define BAD_Q       2
#define TOO_LONG    2
#define MID_Q       3
#define QUOTE       4

// Static method to check input for illegal characters or patterns
static int checkInput(char *in) {
    int quote = 0;
    // Searches for quoted strings and marks them as such
    if(in[0] == '"') {
        if(in[strlen(in)-1] == '"') quote = 1;
        else {
            printf("Error: if a filename begins with a quotation mark, it must end with one;\n\tArgument <%s> is invalid\n", in);
            return BAD_Q;
        }
    }
    else if(in[0] == '\'') {
        if(in[strlen(in)-1] == '\'') quote = 1;
        else {
            printf("Error: if a filename begins with a quotation mark, it must end with one;\n\tArgument <%s> is invalid\n", in);
            return BAD_Q;
        }
    }
    else if(strchr(in, ';')) {
        printf("Error: bad char;\n\tArgument <%s> is invalid\n", in);
    }
    if(quote) return QUOTE;
    return OK;
}

// Static method for getting lines from stdin
static int getLine (char *prmpt, char *buff, size_t sz) {
    int ch, extra;
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    if (fgets (buff, sz, stdin) == NULL) return NO_INPUT;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    buff[strlen(buff)-1] = '\0';
    return OK;
}

// Static method to open and execute commands in a file; also ensures commands
// have the correct number of arguments and checks the arguments
static int openAndExecuteFile(char *fname) {
    // Check if file exists!
    if( access( fname, R_OK ) != -1 ) {
        char orig_cmd[CMDSIZE], cmd[CMDSIZE], *cmd_tokens[3], total_cmd[CMDSIZE] = "";
        // Open the file
        FILE *file = fopen(fname, "r");
        if(file == NULL) {
            printf("Error: problem opening file\n");
            return -1;
        }
        // Read commands line-by-line
        while(fgets(cmd, CMDSIZE, file)) {
            int i = 0;
            strcpy(orig_cmd, cmd);
            // Tokenize the command; there should be 3 or less arguments
            cmd_tokens[i] = strtok(cmd, " ");
            i++;
            while((cmd_tokens[i] = strtok(NULL, " ")) != NULL) i++;
            cmd_tokens[i-1][strlen(cmd_tokens[i-1])-1] = 0;
            // Case: cmd is cd
            if(!strcmp(cmd_tokens[0],"cd")) {
                if(i == 2) {
                    int stat = checkInput(cmd_tokens[1]);
                    if(stat == OK) strcat(total_cmd, orig_cmd);
                    else if(stat == QUOTE) {
                        int j, k=0;
                        char new_cmd[CMDSIZE], new_arg[CMDSIZE];
                        strcpy(new_cmd, cmd_tokens[0]);
                        strcat(new_cmd, " ");
                        for(j=1; j < strlen(cmd_tokens[1])-1; j++) {
                            if(cmd_tokens[1][j] != '\\') {
                                new_arg[k] = cmd_tokens[1][j];
                                k++;
                            }
                        }
                        strcat(new_cmd, new_arg);
                        strcat(total_cmd, new_cmd);
                    }
                }
                else printf("Error: incorrect number of args for cd command\n");
            }
            // Case: cmd is mkdir
            else if(!strcmp(cmd_tokens[0],"mkdir")) {
                if(i == 2) {
                    int stat = checkInput(cmd_tokens[1]);
                    if(stat == OK) strcat(total_cmd, orig_cmd);
                    else if(stat == QUOTE) {
                        int j, k=0;
                        char new_cmd[CMDSIZE], new_arg[CMDSIZE];
                        strcpy(new_cmd, cmd_tokens[0]);
                        strcat(new_cmd, " ");
                        for(j=1; j < strlen(cmd_tokens[1])-1; j++) {
                            if(cmd_tokens[1][j] != '\\') {
                                new_arg[k] = cmd_tokens[1][j];
                                k++;
                            }
                        }
                        strcat(new_cmd, new_arg);
                        strcat(total_cmd, new_cmd);
                    }
                }
                else printf("Error: incorrect number of args for mkdir command\n");
            }
            // Case: cmd is keyfile
            else if(!strcmp(cmd_tokens[0],"keyfile")) {
                if(i == 2) {
                    int stat = checkInput(cmd_tokens[1]);
                    if(stat == OK) strcat(total_cmd, orig_cmd);
                    else if(stat == QUOTE) {
                        int j, k=0;
                        char new_cmd[CMDSIZE], new_arg[CMDSIZE];
                        strcpy(new_cmd, cmd_tokens[0]);
                        strcat(new_cmd, " ");
                        for(j=1; j < strlen(cmd_tokens[1])-1; j++) {
                            if(cmd_tokens[1][j] != '\\') {
                                new_arg[k] = cmd_tokens[1][j];
                                k++;
                            }
                        }
                        strcat(new_cmd, new_arg);
                        strcat(total_cmd, new_cmd);
                    }
                }
                else printf("Error: incorrect number of args for keyfile command\n");
            }
            // Case: cmd is password
            else if(!strcmp(cmd_tokens[0],"password")) {
                if(i == 3) {
                    int stat1 = checkInput(cmd_tokens[1]);
                    int stat2 = checkInput(cmd_tokens[2]);
                    if((stat1 == OK) && (stat2 == OK)) strcat(total_cmd, orig_cmd);
                    if(stat1 == QUOTE) {
                        int j, k=0;
                        char new_cmd[CMDSIZE], new_arg[CMDSIZE];
                        strcpy(new_cmd, cmd_tokens[0]);
                        strcat(new_cmd, " ");
                        for(j=1; j < strlen(cmd_tokens[1])-1; j++) {
                            if(cmd_tokens[1][j] != '\\') {
                                new_arg[k] = cmd_tokens[1][j];
                                k++;
                            }
                        }
                        strcat(new_cmd, new_arg);
                        strcat(total_cmd, new_cmd);
                    }
                    if(stat2 == QUOTE) {
                        int j, k=0;
                        char new_cmd[CMDSIZE], new_arg[CMDSIZE];
                        strcpy(new_cmd, cmd_tokens[0]);
                        strcat(new_cmd, " ");
                        for(j=1; j < strlen(cmd_tokens[2])-1; j++) {
                            if(cmd_tokens[2][j] != '\\') {
                                new_arg[k] = cmd_tokens[2][j];
                                k++;
                            }
                        }
                        strcat(new_cmd, new_arg);
                        strcat(total_cmd, new_cmd);
                    }
                }
                else printf("Error: incorrect number of args for password command\n");
            }
            // Case: cmd is encrypt
            else if(!strcmp(cmd_tokens[0],"encrypt")) {
                if(i == 3) {
                    int stat1 = checkInput(cmd_tokens[1]);
                    int stat2 = checkInput(cmd_tokens[2]);
                    if((stat1 == OK) && (stat2 == OK)) strcat(total_cmd, orig_cmd);
                    if(stat1 == QUOTE) {
                        int j, k=0;
                        char new_cmd[CMDSIZE], new_arg[CMDSIZE];
                        strcpy(new_cmd, cmd_tokens[0]);
                        strcat(new_cmd, " ");
                        for(j=1; j < strlen(cmd_tokens[1])-1; j++) {
                            if(cmd_tokens[1][j] != '\\') {
                                new_arg[k] = cmd_tokens[1][j];
                                k++;
                            }
                        }
                        strcat(new_cmd, new_arg);
                        strcat(total_cmd, new_cmd);
                    }
                    if(stat2 == QUOTE) {
                        int j, k=0;
                        char new_cmd[CMDSIZE], new_arg[CMDSIZE];
                        strcpy(new_cmd, cmd_tokens[0]);
                        strcat(new_cmd, " ");
                        for(j=1; j < strlen(cmd_tokens[2])-1; j++) {
                            if(cmd_tokens[2][j] != '\\') {
                                new_arg[k] = cmd_tokens[2][j];
                                k++;
                            }
                        }
                        strcat(new_cmd, new_arg);
                        strcat(total_cmd, new_cmd);
                    }
                }
                else printf("Error: incorrect number of args for encrypt command\n");
            }
            // Case: cmd is decrypt
            else if(!strcmp(cmd_tokens[0],"decrypt")) {
                if(i == 3) {
                    int stat1 = checkInput(cmd_tokens[1]);
                    int stat2 = checkInput(cmd_tokens[2]);
                    if((stat1 == OK) && (stat2 == OK)) strcat(total_cmd, orig_cmd);
                    if(stat1 == QUOTE) {
                        int j, k=0;
                        char new_cmd[CMDSIZE], new_arg[CMDSIZE];
                        strcpy(new_cmd, cmd_tokens[0]);
                        strcat(new_cmd, " ");
                        for(j=1; j < strlen(cmd_tokens[1])-1; j++) {
                            if(cmd_tokens[1][j] != '\\') {
                                new_arg[k] = cmd_tokens[1][j];
                                k++;
                            }
                        }
                        strcat(new_cmd, new_arg);
                        strcat(total_cmd, new_cmd);
                    }
                    if(stat2 == QUOTE) {
                        int j, k=0;
                        char new_cmd[CMDSIZE], new_arg[CMDSIZE];
                        strcpy(new_cmd, cmd_tokens[0]);
                        strcat(new_cmd, " ");
                        for(j=1; j < strlen(cmd_tokens[2])-1; j++) {
                            if(cmd_tokens[2][j] != '\\') {
                                new_arg[k] = cmd_tokens[2][j];
                                k++;
                            }
                        }
                        strcat(new_cmd, new_arg);
                        strcat(total_cmd, new_cmd);
                    }
                }
                else printf("Error: incorrect number of args for decrypt command\n");
            }
            else printf("Error: invalid command %s\n", cmd_tokens[0]);
        }
        printf("-----------------------------------------------------------------\nValid Commands in %s: {\n%s}\n-----------------------------------------------------------------\n", fname, total_cmd);
        sleep(0.1);
        system(total_cmd);
        fclose(file);
        return 0;
    }
    else {
        printf("Error: file %s does not exist\n", fname);
        return -1;
    }
}

int main(int argc, char* argv[]){
    int stat;
    printf("-----------------------------------------------------------------\n");
    // If there's only one argument ('encdec') read input from stdin
    if(argc == 1) {
        char fname[BUFSIZE];
        // Ask user for a file name and read it into fname
        while(!(stat = (getLine("Please enter a filename using an absolute paths:\n>", fname, BUFSIZE)))){
            printf("%s\n", fname);
            // If there's no input, exit w/ error
            if(stat == NO_INPUT){
                printf("Error: no input!\n");
                return stat;
            }
            // If input is too long, exit w/ error
            if(stat == TOO_LONG){
                printf("Error: input too long, please limit to %d characters\n", BUFSIZE);
                return stat;
            }
            // If we get past that, we need to check for sneaky sneaks
            if(checkInput(fname) == OK) openAndExecuteFile(fname);
            printf("-----------------------------------------------------------------\n");
        }
    }
    // Otherwise, read the arguments to get filenames
    else {
        int i;
        for(i=1; i<argc; i++){
            char fname[BUFSIZE];
            strcpy(fname, argv[i]);
            if(checkInput(fname) != OK) return -1;
            openAndExecuteFile(fname);
            printf("-----------------------------------------------------------------\n");
        }
    }
    printf("-----------------------------------------------------------------\n");
    return 0;
}
