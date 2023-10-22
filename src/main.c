#include "palindrome.h"

int main() {
    char arr[ARRAY_LEN] = {0};

    read_array(arr, ARRAY_LEN);
    display_array(arr, ARRAY_LEN);
    manacher(arr,ARRAY_LEN);
    return 0;
}
