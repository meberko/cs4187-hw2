#include <stdio.h>
#include <openssl/evp.h>

int main(int argc, char* argv[]){
    printf("Running keyfile\n");
    //for(int i=0; i<argc; i++) printf("%s\n", argv[i]);
    /*PKCS5_PBKDF2_HMAC_SHA1(pass,
      passlen,
      salt,
      saltlen,
      iter,
      keylen,
      out)*/
    return 0;
}
