/**
 * @endcode utf-8
 * @author merborn
 */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define true 1
#define false 0
#define malloc_error 100
#define param_error 200

typedef struct String {
    int len;
    char *ch;
} string, *String;

/**
 *  得到next数组的方法
 * @param str
 * @param next
 * @return
 */
int getNext(String str, int **next) {
    (*next) = (int *) malloc(sizeof(int) * str->len); //分配字符串长度的数组
    if ((*next) == NULL)return malloc_error;
    (*next)[0] = 0; //第一位为0号
    int i = 1; //数组后移指针（数组下标)
    int j = 0;

    while (i < str->len) {
        if (str->ch[i] == str->ch[j]) { //如果两个字符相等，就让next[i] = j+1; 然后 i，j往后移动,如果不相等,则往下继续判断
            (*next)[i] = ++j;  //j 自增1，然后赋值给next[i] 等同于   j += 1;    next[i] = j;
            ++i;
        } else if (j - 1 >= 0) {   //若 j -1 < 0 ,则j 已经到达 0 号位。此时i，j两个字符都不能相等的话，就执行else 语句块
            j = (*next)[j - 1];
        } else {
            (*next)[i] = 0;
            i++;
        }
    }
}
/**
 * KMP算法匹配模式串
 * @param str 目标串
 * @param pos 匹配开始的位置
 * @param target 模式串
 * @return 匹配位置的下标
 */
int indexStringByKMP(String str, int pos, String target) {

    int i = pos;  // i 为目标串 起始匹配点的下标
    int j = 0;   // j为 target 模式串 下标
    int *next;

    getNext(target, &next);

    while (i < str->len) {
        if (str->ch[i] == target->ch[j]) {
            if (j >= target->len - 1) return i - j; // 如果j是模式串最后一位，则匹配成功,返回下标
            i++;
            j++;
        } else if (j - 1 >= 0) { //如果匹配不成功，到就回溯
            j = next[j - 1];
        } else {   // 0号也匹配不成功,说明匹配失败,i++ 先后匹配，j = 0 从模式串第一位重新匹配
            j = 0;
            i++;
        }
    }

    printf("index false\n");
    return -1;
}

/**
 * 暴力算法进行字符串匹配
 * @param string 目标串
 * @param pos  匹配的起始位置
 * @param target 模式串
 * @return
 */
int indexString(String string, int pos, String target) {
    int i = pos;
    int j = 0;

    while (i <= string->len - 1 && j <= target->len - 1) {
        //printf("string->%c  ? target->%c  \n",string->ch[i],target->ch[j]);
        if (string->ch[i] == target->ch[j]) {
            ++i;
            ++j;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j > target->len - 1)return i - (target->len);
    else {
        printf("index string false 没有目标字符串\n");
        return 0;
    }
}

/**
 * 输入一个字符串
 * @param target  字符串的指针
 * @return  错误参数
 */
int scanf_string(String *target) {

    if ((*target) != NULL) return param_error;
    int init_size = 10;//初始10个字符
    const int increnment_size = 5; //每次增加5个字符
    char *str = (char *) malloc(sizeof(char) * init_size);//字符数组
    int index = 0; //输入指向的位置
    int char_arrary_len = init_size; //数组的真实长度
    int len = 0;//字符串长度
    char input = ' ';

    do {
        if (index >= char_arrary_len) {
            str = realloc(str, sizeof(char) * (char_arrary_len + increnment_size));
            if (str == NULL)return malloc_error;
            char_arrary_len += increnment_size;
        }

        scanf("%c", &input);

        if (input != '\n') {
            str[index++] = input;
            len++;
        } else break;

    } while (true);

    str[index] = '\0'; //字符串最后一位加入EOF
    (*target) = malloc(sizeof(struct String));
    if ((*target) == NULL) return malloc_error;
    (*target)->len = len;
    (*target)->ch = str;

    return true;
}

/**
 * 打印一行
 * @param string
 * @return
 */
int println_String(String string) {
    if (string == NULL)return param_error;
    for (int i = 0; i < string->len; i++) {
        printf("%c", string->ch[i]);
    }
    printf("\n"); //加入换行，进行区别
    return true;
}
/**
 * 输出字符串，不带换行
 * @param string
 * @return
 */
int print_String(String string) {
    if (string == NULL)return param_error;
    for (int i = 0; i < string->len; i++) {
        printf("%c", string->ch[i]);
    }
    return true;
}
/**
 * 带下标的打印一行字符串
 * @param string
 * @return
 */
int println_String_adv(String string) {
    if (string == NULL)return param_error;

    for (int i = 0; i < string->len; i++) {
        printf("%3d", i);
    }
    printf("\n");

    for (int i = 0; i < string->len; i++) {
        printf("%3c", string->ch[i]);
    }
    printf("\n");
    return true;
}

int main() {

    String str = NULL;
    String target = NULL;
    printf("请输入一个字符串：\n");
    scanf_string(&str);
    printf("请输入要匹配的目标字符串\n");
    scanf_string(&target);
    // int result = indexString(str,0,target);
    int result = indexStringByKMP(str, 0, target);

   // println_String_adv(str); //方便查看字符串下标

    printf("目标字符串从 %d 号开始\n", result);

/*
 *   测试next数组的代码，忽略
    int *next = NULL;
    getNext(str, &next);

    for (int i = 0; i < str->len; i++) {
        printf("%c", str->ch[i]);
    }
    printf("\n");

    for (int i = 0; i < str->len; i++) {
        printf("%d", next[i]);
    }
*/
}


