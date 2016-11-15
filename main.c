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

static int checkInput(char *in) {
    int quote = 0;
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
    else if(strchr(in, '"') != NULL) {
        int i, q=0;
        for(i=0; i<strlen(in); i++) {
            if(in[i] == '"') q++;
        }
        if(q>1){
            printf("Error: if a filename does not begin with a quotation mark, it may not contain more than one quotation mark;\n\tArgument <%s> is invalid\n", in);
            return MID_Q;
        }
    }
    else if(strchr(in, '\'') != NULL) {
        int i, q=0;
        for(i=0; i<strlen(in); i++) {
            if(in[i] == '\'') q++;
        }
        if(q>1){
            printf("Error: if a filename does not begin with a quotation mark, it may not contain more than one quotation mark;\n\tArgument <%s> is invalid\n", in);
            return MID_Q;
        }
    }
    /*else if(in[0] != '/') {
        printf("Error: all filenames must be absolute paths, %s is invalid\n", in);
        return NOT_ABS;
    }
    */
    if(quote) {

    }
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
                }
                else printf("Error: incorrect number of args for cd command\n");
            }
            // Case: cmd is mkdir
            else if(!strcmp(cmd_tokens[0],"mkdir")) {
                if(i == 2) {
                    if(checkInput(cmd_tokens[1]) == OK) strcat(total_cmd, orig_cmd);
                }
                else printf("Error: incorrect number of args for mkdir command\n");
            }
            // Case: cmd is keyfile
            else if(!strcmp(cmd_tokens[0],"keyfile")) {
                if(i == 2) {
                    if(checkInput(cmd_tokens[1]) == OK) strcat(total_cmd, orig_cmd);
                }
                else printf("Error: incorrect number of args for keyfile command\n");
            }
            // Case: cmd is password
            else if(!strcmp(cmd_tokens[0],"password")) {
                if(i == 3) {
                    if(checkInput(cmd_tokens[2]) == OK) strcat(total_cmd, orig_cmd);
                }
                else printf("Error: incorrect number of args for password command\n");
            }
            // Case: cmd is encrypt
            else if(!strcmp(cmd_tokens[0],"encrypt")) {
                if(i == 3) {
                    if((checkInput(cmd_tokens[1]) == OK) && (checkInput(cmd_tokens[2]) == OK)) strcat(total_cmd, orig_cmd);
                }
                else printf("Error: incorrect number of args for encrypt command\n");
            }
            // Case: cmd is decrypt
            else if(!strcmp(cmd_tokens[0],"decrypt")) {
                if(i == 3) {
                    if((checkInput(cmd_tokens[1]) == OK) && (checkInput(cmd_tokens[2]) == OK)) strcat(total_cmd, orig_cmd);
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

int main(int argc, char* argv[]){
    int stat;
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
        }
    }
    return 0;
}
