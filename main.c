#include <stdio.h>
#include <string.h>

#define BUFSIZE 256

#define OK       0
#define ILLEGAL  1
#define NO_INPUT 1
#define TOO_LONG 2

static int checkInput(char *in) {
    if(in[0] == '"') printf("quote!");
    for(int i=0; i<strlen(in); i++) printf("%c\n", in[i]);
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

int main(int argc, char* argv[]){
    int stat;
    if(argc == 1) {
        char input[BUFSIZE];
        if((stat = (getLine("Please enter a filename or list of filenames using absolute paths:\n>", input, BUFSIZE)))){
            if(stat == NO_INPUT){
                printf("Error: no input!\n");
                return stat;
            }
            if(stat == TOO_LONG){
                printf("Error: input too long, please limit to %d characters\n", BUFSIZE);
                return stat;
            }
        }
        printf("%s\n", input);
    }
    else {
        for(int i=1; i<argc; i++){
            char fname[BUFSIZE];
            strcpy(fname, argv[i]);
            checkInput(fname);
            printf("%s\n", fname);
        }
    }
}
