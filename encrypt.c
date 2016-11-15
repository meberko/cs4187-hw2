#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define BUFLEN 256

int main(int argc, char* argv[]){
    printf("Running encrypt\n");
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    char keyfile[BUFLEN];
    char in[BUFLEN];
    char out[BUFLEN];
    char cmd[BUFLEN];
    // Create keyfile string
    strncpy(keyfile, homedir, BUFLEN);
    strncat(keyfile, "/bin/encdec.key", BUFLEN);
    // Copy arguments to local variables
    strncpy(in, argv[1], BUFLEN);
    strncpy(out, argv[2], BUFLEN);
    // Construct command
    strncpy(cmd, "openssl enc -aes-128-cbc -e -in ", BUFLEN);
    strncat(cmd, in, BUFLEN);
    strncat(cmd, " -out ", BUFLEN);
    strncat(cmd, out, BUFLEN);
    strncat(cmd, " -pass file:", BUFLEN);
    strncat(cmd, keyfile, BUFLEN);
    // Execute
    system(cmd);
    return 0;
}
