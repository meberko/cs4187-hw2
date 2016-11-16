#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#define ITERS   1000
#define KEYLEN  32
#define PASSLEN 256

int main(int argc, char* argv[]){
    int i;
    char pass[PASSLEN], outfile[PASSLEN];
    unsigned char *out;
    unsigned char salt[] = {'s', 'a', 'l', 't'};
    // Get arguments into local variables
    strncpy(pass, argv[1], PASSLEN);
    strncpy(outfile, argv[2], PASSLEN);
    printf("Running password %s %s\n", pass, outfile);
    out = (unsigned char *) malloc(sizeof(unsigned char)*KEYLEN);
    // Perform keygen and save to specified output file
    if(PKCS5_PBKDF2_HMAC_SHA1(pass, strlen(pass), salt, sizeof(salt), ITERS, KEYLEN, out) != 0) {
      FILE *outfp = fopen(outfile, "wb");
      if(outfp != NULL) {
        for(i=0; i < KEYLEN; i++) fprintf(outfp, "%02x", out[i]);
        fprintf(outfp, "\n");
        fclose(outfp);
      }
      else printf("Error: problem creating keyfile\n");
    }
    free(out);
    return 0;
}
