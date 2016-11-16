#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <openssl/evp.h>

#define BUFLEN 256

int main(int argc, char* argv[]){
    struct passwd *pw = getpwuid(getuid());
    char orig_keyfile[BUFLEN], keyfile[BUFLEN], cmd[BUFLEN], abskey[BUFLEN];
    const char *homedir = pw->pw_dir;
    // Create path to keyfile config
    strncpy(orig_keyfile, homedir, BUFLEN);
    strncat(orig_keyfile, "/bin/encdec.key", BUFLEN);
    // Copy argument to local variable
    strncpy(keyfile, argv[1], BUFLEN);
    if(access(keyfile, F_OK) == -1) {
      printf("Error: specified keyfile <%s> does not exist\n", keyfile);
      return -1;
    }
    realpath(keyfile, abskey);
    // Create command to symlink keyfile config to new key
    strncpy(cmd, "ln -sf ", BUFLEN);
    strncat(cmd, abskey, BUFLEN);
    strncat(cmd, " ", BUFLEN);
    strncat(cmd, orig_keyfile, BUFLEN);
    printf("Running keyfile %s\n", keyfile);
    // Execute
    system(cmd);
    return 0;
}
