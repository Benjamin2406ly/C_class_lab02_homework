#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_LEN  10

#ifdef VIOLENT
//暴力解法
void violent(char* arr, int len);
#endif

//中心扩展法
void center_extension(char* arr, int len);

//Manacher算法
void manacher(char* arr, int len);

/*
**共用函数声明
*/
void read_array(char* arr, int len);
void display_array(char* arr, int len);
int isPalindromic(char* arr, int len); 
int expandAroundCenter(char* arr, int len, int left, int right);