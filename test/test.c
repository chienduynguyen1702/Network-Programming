#include <stdio.h>

int main() {
    char *chuoi[2] = {"Chuoi A", "Chuoi B"};
    char *chuoi2[2] = {"Chuoi 2A", "Chuoi 2B"};

    printf("chuoi[0]: %s\n", chuoi[0]);
    printf("chuoi[1]: %s\n", chuoi[1]);

    char *conTroChuoiA = chuoi[0];
    char *conTroChuoiB = chuoi[1];

    printf("conTroChuoiA: %s\n", conTroChuoiA);
    printf("conTroChuoiB: %s\n", conTroChuoiB);

    chuoi2 = chuoi; // Gán địa chỉ của chuỗi B cho con trỏ chuỗi A

    printf("Sau khi gan:\n");
    printf("conTroChuoiA: %s\n", chuoi2[0]);
    printf("conTroChuoiB: %s\n", chuoi2[1]);

    return 0;
}