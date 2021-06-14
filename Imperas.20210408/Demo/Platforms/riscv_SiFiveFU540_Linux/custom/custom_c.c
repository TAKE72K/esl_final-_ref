// Custom instruction test for Chacha20
#include <stdio.h>

int qr1_c(unsigned int a, unsigned int b) {
    return (a ^ b) << 16 | (a ^ b) >> 16;
}

int qr2_c(unsigned int a, unsigned int b) {
    return (a ^ b) << 12 | (a ^ b) >> 20;
}

int qr3_c(unsigned int a, unsigned int b) {
    return (a ^ b) << 8 | (a ^ b) >> 24;
}

int qr4_c(unsigned int a, unsigned int b) {
    return (a ^ b) << 7 | (a ^ b) >> 25;
}

int main(void) {

    FILE *fp = fopen("./custom.data", "r");
    if (fp) {
        unsigned int res = 0x84772366;
        unsigned int word;
        unsigned int cnt=0;
        unsigned int iter=0;
        while (iter++ < 16) {
            while (fread(&word,sizeof(unsigned int), 1, fp)) {
                res = qr1_c(res, word);
                res = qr2_c(res, word);
                res = qr3_c(res, word);
                res = qr4_c(res, word);
                res = qr1_c(res, word);
                res = qr2_c(res, word);
                res = qr3_c(res, word);
                res = qr4_c(res, word);
            }
            rewind(fp);
        }
        fclose(fp);
        printf("RES = %08X\n", res);
    } else {
        printf("Failed to open custom.data\n");
    }

    return 0;
}
