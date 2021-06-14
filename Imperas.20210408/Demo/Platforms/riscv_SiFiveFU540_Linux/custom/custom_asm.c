// Custom instruction test for Chacha20
#include <stdio.h>

int main(void) {

    FILE *fp = fopen("./custom.data", "r");
    if (fp) {
        unsigned int res = 0x84772366;
        unsigned int word;
        unsigned int cnt=0;
        unsigned int iter=0;

        while (iter++ < 16) {
            while (fread(&word,sizeof(unsigned int), 1, fp)) {
                asm __volatile__("mv x10, %0" :: "r"(res));
                asm __volatile__("mv x11, %0" :: "r"(word));
                asm __volatile__(".word 0x00B5050B\n" ::: "x10");     // QR1
                asm __volatile__(".word 0x00B5150B\n" ::: "x10");     // QR2
                asm __volatile__(".word 0x00B5250B\n" ::: "x10");     // QR3
                asm __volatile__(".word 0x00B5350B\n" ::: "x10");     // QR4
                asm __volatile__(".word 0x00B5050B\n" ::: "x10");     // QR1
                asm __volatile__(".word 0x00B5150B\n" ::: "x10");     // QR2
                asm __volatile__(".word 0x00B5250B\n" ::: "x10");     // QR3
                asm __volatile__(".word 0x00B5350B\n" ::: "x10");     // QR4
                asm __volatile__("mv %0,x10" : "=r"(res));
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
