#include <openssl/rand.h>
#include <stdio.h>

int main() {
    unsigned char buffer[16];
    if (RAND_bytes(buffer, sizeof(buffer))) {
        printf("Random bytes generated successfully!\n");
    } else {
        printf("Failed to generate random bytes.\n");
    }
    return 0;
}
