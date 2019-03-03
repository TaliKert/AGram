#include <sys/time.h>
#include <stdio.h>
#include <memory.h>


int main(int argc, char *argv[]) {

    // Timing:
    // https://stackoverflow.com/questions/12722904/how-to-use-struct-timeval-to-get-the-execution-time
    struct timeval tvalBefore, tvalAfter;
    gettimeofday (&tvalBefore, NULL);

    FILE *fp;


    long primeMap[1024];
    primeMap[0x61] = primeMap[0x41] = 2;
    primeMap[0x62] = primeMap[0x42] = 3;
    primeMap[0x63] = primeMap[0x43] = 5;
    primeMap[0x64] = primeMap[0x44] = 7;
    primeMap[0x65] = primeMap[0x45] = 11;
    primeMap[0x66] = primeMap[0x46] = 13;
    primeMap[0x67] = primeMap[0x47] = 17;
    primeMap[0x68] = primeMap[0x48] = 19;
    primeMap[0x69] = primeMap[0x49] = 23;
    primeMap[0x6A] = primeMap[0x4A] = 29;
    primeMap[0x6B] = primeMap[0x4B] = 31;
    primeMap[0x6C] = primeMap[0x4C] = 37;
    primeMap[0x6D] = primeMap[0x4D] = 41;
    primeMap[0x6E] = primeMap[0x4E] = 43;
    primeMap[0x6F] = primeMap[0x4F] = 47;
    primeMap[0x70] = primeMap[0x50] = 53;
    primeMap[0x71] = primeMap[0x51] = 59;
    primeMap[0x72] = primeMap[0x52] = 61;
    primeMap[0x73] = primeMap[0x53] = 67;
    primeMap[0x74] = primeMap[0x54] = 71;
    primeMap[0x75] = primeMap[0x55] = 73;
    primeMap[0x76] = primeMap[0x56] = 79;
    primeMap[0x77] = primeMap[0x57] = 83;
    primeMap[0x78] = primeMap[0x58] = 89;
    primeMap[0x79] = primeMap[0x59] = 97;
    primeMap[0x7A] = primeMap[0x5A] = 101;

    primeMap[0xD0] = primeMap[0xF0] = 103; // s katusega
    primeMap[0xF5] = primeMap[0xD5] = 107;
    primeMap[0xF6] = primeMap[0xD6] = 109; // ö
    primeMap[0xE4] = primeMap[0xC4] = 113; // ä
    primeMap[0xFC] = primeMap[0xDC] = 127; // ü
    primeMap[0xFE] = primeMap[0xDE] = 131; // z katusega

    primeMap[0x20] = 139; // b' '
    primeMap[0x21] = 149; // b'!'
    primeMap[0x27] = 151; // b"'"

    primeMap[0xE9] = primeMap[0xC9] = 137; // e katusega

    long long algneRasi = 1LL;
    int algsePikkus = strlen(argv[2]);
    for (int i = 0; i < algsePikkus; ++i) {
        algneRasi = algneRasi * primeMap[ argv[2][i] ];
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("Could not open file %s", argv[1]);
        return 1;
    }

    char tulemus[16][32];
    int tulemusCounter = 0;

    char kandidaat[32];
    int kandidaatCounter = 0;

    char buffer[256];
    long long kandidaadiRasi = 1LL;

    while (1) {
        int readBytes = fread(buffer, 8, 32, fp);
        for (int i = 0; i < readBytes; ++i) {
            if (buffer[i] == '\r') {
                if (kandidaadiRasi == algneRasi) {
                    for (int j = 0; j < kandidaatCounter; ++j) {
                        tulemus[tulemusCounter][j] = kandidaat[j];
                    }
                    tulemusCounter += 1;
                }
                kandidaatCounter = 0;
                kandidaadiRasi = 1LL;
                i++;
            } else {
                kandidaat[kandidaatCounter] = buffer[i];
                kandidaadiRasi = kandidaadiRasi * primeMap[buffer[i]];
                kandidaatCounter++;
            }
        }
        if (readBytes == 0) {
            break;
        }
    }



    gettimeofday (&tvalAfter, NULL);
    printf("%ld",
           ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
            +tvalAfter.tv_usec) - tvalBefore.tv_usec
    );

    for (int k = 0; k < tulemusCounter; ++k) {
        printf(",");
        for (int i = 0; i < 32; ++i) {
            if (tulemus[k][i] != 0) {
                printf("%c", tulemus[k][i]);
            }
        }
    }

}