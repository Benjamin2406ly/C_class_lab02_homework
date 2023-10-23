#include "palindrome.h"
/*
**下面共有三种方法，前两种为课上给出的方法，第三种为Manacher算法，时间复杂度为O(n)
*/

void violent(char* arr, int len) {
    int longest_start_index = 0; // 最长回文字符串开始的索引
    int longest_length = 0; // 最长回文字符串的长度
    int current_length = 0;  // 当前判断的子串的长度
    
    for (int i = 0; i < len; i++){
        for (int j = i + 1; j <= len; j++) {
            current_length = j-i+1;
            char subarr[current_length];
            for (int c=i;c<=j;c++){
                subarr[c-i]=arr[c];
            }
            if (isPalindromic(subarr,current_length)){
               if(current_length>longest_length){
                    longest_length = current_length;
                    longest_start_index = i;
                } 
            }
        }
    }
    
    display_array(arr + longest_start_index * sizeof(char), longest_length);
    return;
}

void center_extension(char* arr, int len) {
    
    int longest_start_index = 0, longest_end_index = 0;

    for (int i = 0; i < len; i++) {
        // 字母本身为中心
        int len1 = expandAroundCenter(arr, len, i, i);

        // 字母间隙为中心
        int len2 = expandAroundCenter(arr, len, i, i + 1);

        int current_max_length = (len1 >= len2) ? len1 : len2;

        if (current_max_length > longest_end_index - longest_start_index) {
            longest_start_index = i - (current_max_length - 1) / 2;
            longest_end_index = i + current_max_length / 2;
        }
    }
    display_array(arr + longest_start_index * sizeof(char),  longest_end_index - longest_start_index + 1);
    return ;
}

void manacher(char* arr, int len) {
    // 预处理字符串，使用^作为标记,排除奇偶差异
    int newLen = 2 * len + 2;
    char *t = (char *)malloc(newLen);
    t[0] = '^';
    t[newLen - 1] = '\0';
    t[newLen - 2] = '^';
    for (int i = 0; i < len; ++i) {
        t[2 * i + 1] = arr[i];
        t[2 * i + 2] = '^';
    }

    // P:用于存储以每个字符为中心的最长回文子串的半径,C:中心,R:右边界
    int P[newLen];
    int C = 0, R = 0;

    // 遍历字符串，寻找最长回文子串
    for (int i = 1; i < newLen - 1; ++i) {
        int mirror = 2 * C - i;                                          // mirror:i关于C的镜像
        P[i] = (i < R) ? (R - i < P[mirror] ? R - i : P[mirror]) : 0;    // 选择R-i和P[mirror]中的较小者，原因如下
        //mirror的回文子串完全在C的最长回文子串内部：这种情况下，i的回文子串和mirror的回文子串是一样长的。我们可以直接将P[i]设置为P[mirror]，并且不需要进一步的检查，因为在C的最长回文子串内部，i和mirror是完全对称的。
        //mirror的回文子串延伸到了C的最长回文子串的左边界：这种情况下，i的回文子串可能会延伸到R之外。我们无法直接使用P[mirror]，因为这将导致i的回文子串越过R。在这种情况下，我们将P[i]初始化为R - i，然后再尝试进行中心扩展
        
        // 中心扩展
        while (t[i + 1 + P[i]] == t[i - 1 - P[i]]) {
            P[i]++;
        }

        // 更新C和R
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }

    // 找到最长回文子串
    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 1; i < newLen - 1; ++i) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    // 复原最长回文子串
    printf("\n The elements of the longest palindrome array are: ");
    for (int i = centerIndex - maxLen + 1; i <= centerIndex + maxLen - 1; i += 2) {
        printf("%c", arr[i / 2]);
    }
    printf("\n");

    free(t);
}

/*
**共用函数
*/
void read_array(char* arr, int len) {
    int ret;
    printf("Enter the elements into the array: ");
    for (int i = 0; i < len; i++) {
        ret = scanf("%c", &arr[i]);
    }
    fflush(stdin);
    return;
}

void display_array(char* arr, int len) {
    printf("\n The elements of the array are: ");
    for (int i = 0; i < len; i++) {
        printf("%c", arr[i]);
    }
    printf("\n");
    return;
}

int isPalindromic(char* arr, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (arr[i] != arr[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int expandAroundCenter(char* arr, int len, int left, int right) {
    int L = left, R = right;
    while (L >=0 && R<=len && arr[L]==arr[R])
    {
        L--;
        R++;
    }
    return R - L - 1;
}
