#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <openssl/evp.h>

#define BUFLEN 256

int main(int argc, char* argv[]){
    printf("Running keyfile\n");
    struct passwd *pw = getpwuid(getuid());
    char orig_keyfile[BUFLEN];
    char keyfile[BUFLEN];
    char cmd[BUFLEN];
    const char *homedir = pw->pw_dir;
    // Create path to keyfile config
    strncpy(orig_keyfile, homedir, BUFLEN);
    strncat(orig_keyfile, "/bin/encdec.key", BUFLEN);
    // Copy argument to local variable
    strncpy(keyfile, argv[1], BUFLEN);
    // Create command to symlink keyfile config to new key
    strncpy(cmd, "ln -sf ", BUFLEN);
    strncat(cmd, keyfile, BUFLEN);
    strncat(cmd, " ", BUFLEN);
    strncat(cmd, orig_keyfile, BUFLEN);
    // Execute
    system(cmd);
    return 0;
}
