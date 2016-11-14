#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CMDSIZE 1024
#define BUFSIZE 256

#define OK       0
#define ILLEGAL  1
#define NO_INPUT 1
#define TOO_LONG 2

static int checkInput(char *in) {
    //for(int i=0; i<strlen(in); i++) printf("%c\n", in[i]);
    return OK;
}

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

static int openAndExecuteFile(char *fname) {
    // Check if file exists!
    if( access( fname, R_OK ) != -1 ) {
        char orig_cmd[CMDSIZE];
        char cmd[CMDSIZE];
        char *cmd_tokens[3];
        char total_cmd[CMDSIZE] = "";
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
            //system(cmd);
            // Tokenize the command; there should be 3 or less arguments
            cmd_tokens[i] = strtok(cmd, " ");
            i++;
            while((cmd_tokens[i] = strtok(NULL, " ")) != NULL) i++;
            cmd_tokens[i-1][strlen(cmd_tokens[i-1])-1] = 0;
            // Case: cmd is cd
            if(!strcmp(cmd_tokens[0],"cd")) {
                if(i == 2) {
                    if(checkInput(cmd_tokens[1]) == OK) strcat(total_cmd, orig_cmd);
                    printf("Okay cd commmand!\n");
                }
                else printf("Error: incorrect number of args for cd command\n");
            }
            // Case: cmd is mkdir
            else if(!strcmp(cmd_tokens[0],"mkdir")) {
                if(i == 2) {
                    if(checkInput(cmd_tokens[1]) == OK) strcat(total_cmd, orig_cmd);
                    printf("Okay mkdir commmand!\n");
                }
                else printf("Error: incorrect number of args for mkdir command\n");
            }
            // Case: cmd is keyfile
            else if(!strcmp(cmd_tokens[0],"keyfile")) {
                if(i == 2) {
                    if(checkInput(cmd_tokens[1]) == OK) strcat(total_cmd, orig_cmd);
                    printf("Okay keyfile commmand!\n");
                }
                else printf("Error: incorrect number of args for keyfile command\n");
            }
            // Case: cmd is password
            else if(!strcmp(cmd_tokens[0],"password")) {
                if(i == 3) {
                    if((checkInput(cmd_tokens[1]) == OK) && (checkInput(cmd_tokens[2]) == OK)) strcat(total_cmd, orig_cmd);
                    printf("Okay password commmand!\n");
                }
                else printf("Error: incorrect number of args for password command\n");
            }
            // Case: cmd is encrypt
            else if(!strcmp(cmd_tokens[0],"encrypt")) {
                if(i == 3) {
                    if((checkInput(cmd_tokens[1]) == OK) && (checkInput(cmd_tokens[2]) == OK)) strcat(total_cmd, orig_cmd);
                    printf("Okay encrypt commmand!\n");
                }
                else printf("Error: incorrect number of args for encrypt command\n");
            }
            // Case: cmd is decrypt
            else if(!strcmp(cmd_tokens[0],"decrypt")) {
                if(i == 3) {
                    if((checkInput(cmd_tokens[1]) == OK) && (checkInput(cmd_tokens[2]) == OK)) strcat(total_cmd, orig_cmd);
                    printf("Okay decrypt commmand!\n");
                }
                else printf("Error: incorrect number of args for decrypt command\n");
            }
            else printf("Error: invalid command %s\n", cmd_tokens[0]);
        }
        printf("-------------------------\nRunning: {\n%s}\n-------------------------\n", total_cmd);
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

void main(int argc, char* argv[]){
    int stat;
    // If there's only one argument ('encdec') read input from stdin
    if(argc == 1) {
        char fname[BUFSIZE];
        // Ask user for a file name and read it into fname
        if((stat = (getLine("Please enter a filename or list of filenames using absolute paths:\n>", fname, BUFSIZE)))){
            // If there's no input, exit w/ error
            if(stat == NO_INPUT){
                printf("Error: no input!\n");
                return;
            }
            // If input is too long, exit w/ error
            if(stat == TOO_LONG){
                printf("Error: input too long, please limit to %d characters\n", BUFSIZE);
                return;
            }
        }

        // If we get past that, we need to check for sneaky sneaks
        if(checkInput(fname) != OK) return -1;

        // If we get past all of that, we have a good filename! Open it and
        // execute commands
        openAndExecuteFile(fname);
    }
    // Otherwise, read the arguments to get filenames
    else {
        int i;
        for(i=1; i<argc; i++){
            char fname[BUFSIZE];
            strcpy(fname, argv[i]);
            if(checkInput(fname) != OK) return -1;
            openAndExecuteFile(fname);
        }
    }
}
