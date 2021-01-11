#include <stdio.h>
#include <math.h> 

/*
ANS:
case 1 : 123-45
case 2 : Bad code.
case 3 : Bad K.
case 4 : 10932033 
*/
// 3 9 16 20 24 5 12 1 18 17 4 6
/*
Character Encoding
0 00011
1 01001
2 10000
3 10100
4 11000
5 00101
6 01100
7 00001
8 10010
9 10001
– 00100
Start/Stop 00110
*/

// bad code : bar 長度不對 沒有start/stop 沒有匹配的code
int ltor(int, int, int[]);
int rtol(int, int, int[]);

int main(){
    int num;
    FILE *fptr;
    if((fptr = fopen("test.txt", "r")) == NULL){
        printf("File could not be opened.\n");
    }else{
        int counter = 1;
        fscanf(fptr, "%d", &num);
        while(num != 0){
            int arr[num];
            fscanf(fptr, "%d", &arr[0]);
            //輸入
            for(int i = 1; i < num; i++){
                fscanf(fptr, "%d", &arr[i]);
            }

            // bad code 0, bad C 1, bad K 2, good code 3;
            int ltor_result = ltor(num, counter, arr);
            int rtol_result = rtol(num, counter, arr);
            if(ltor_result == 4 || rtol_result == 4){
                counter += 1;
            }else{
                if(ltor_result > rtol_result){
                    switch(ltor_result){
                        case 1:
                            printf("case %d : Bad code.\n", counter++);
                            break;
                        case 2:
                            printf("case %d : Bad C.\n", counter++);
                            break;
                        case 3:
                            printf("case %d : Bad K.\n", counter++);
                            break;
                    }
                }else{
                    switch(rtol_result){
                        case 1:
                            printf("case %d : Bad code.\n", counter++);
                            break;
                        case 2:
                            printf("case %d : Bad C.\n", counter++);
                            break;
                        case 3:
                            printf("case %d : Bad K.\n", counter++);
                            break;
                    }
                }
            }
            fscanf(fptr, "%d", &num);
        }
    }
}
int ltor(int num, int counter, int arr[]){
    //printf("ltor\n");
    int badC_check = 0;
    int badK_check = 0;
    int badCode_check = 0;
    int tmp, narrow, wide;
    tmp = arr[0];
    //判斷寬與窄
    for(int i = 0; i < num; i++){
        if(arr[i] > tmp * 1.1){
            narrow = tmp;
            wide = arr[i];
            break;
        }else if(arr[i] < tmp * 0.9){
            narrow = arr[i];
            wide = tmp;
            break;
        }
    }
    //寬與窄轉換
    for(int i = 0; i < num; i++){
        if(arr[i] > narrow * 0.9 && arr[i] < narrow * 1.1){
            arr[i] = 0;
        }else if(arr[i] > wide * 0.9 && arr[i] < wide * 1.1){
            arr[i] = 1;
        }
    }
    /*
    int dd = 0;
    for(int i = num - 1; i >= 0; i--){
        printf("%d ", arr[i]);
        dd++;
        if(dd == 6){
            printf("\n");
            dd = 0;
        }
    }printf("\n");
    */

    int word_num = (num + 1) / 6;
    int N = word_num - 4;
    int trans_ans[word_num];
    int now = 0;
    //五個一組分區段，並將二進位轉換成十進位碼。
    for(int i = 0; i < num; i++){
        int add = 0;
        for(int j = 0; j < 5; j++, i++){
            add += arr[i] * pow(2, 4 - j);
        }
        switch(add){
            case 3:
                trans_ans[now++] = 0;
                break;
            case 9:
                trans_ans[now++] = 1;
                break;
            case 16:
                trans_ans[now++] = 2;
                break;
            case 20:
                trans_ans[now++] = 3;
                break;
            case 24:
                trans_ans[now++] = 4;
                break;
            case 5:
                trans_ans[now++] = 5;
                break;
            case 12:
                trans_ans[now++] = 6;
                break;
            case 1:
                trans_ans[now++] = 7;
                break;
            case 18:
                trans_ans[now++] = 8;
                break;
            case 17:
                trans_ans[now++] = 9;
                break;
            case 4:
                trans_ans[now++] = 10;
                break;
            case 6:
                trans_ans[now++] = -1;
                break;
            default:
                badCode_check = 1;
                break;
        }
    }
    /*
    for(int i = 0; i < word_num; i++){
        printf("%d ", trans_ans[i]);
    }printf("\n");
    */
    //start/stop check
    if(trans_ans[0] != -1 || trans_ans[word_num - 1] != -1){
        badCode_check = 1;
    }
    //Code C check
    int codeCchecker = 0;
    for(int i = 1; i < word_num - 3; i++){
        codeCchecker += ((N - i) % 10 + 1) * trans_ans[i];
    }
    //printf("%d\n", codeCchecker % 11);
    if(codeCchecker % 11 != trans_ans[word_num - 3]){
        badC_check = 1;
    }else{
        //code K check
        int codeKchecker = 0;
        for(int i = 1; i < word_num - 2; i++){
            codeKchecker += ((N + 1 - i) % 9 + 1) * trans_ans[i];
        }
        //printf("%d\n", codeKchecker % 11);
        if(codeKchecker % 11 != trans_ans[word_num - 2]){
            badK_check = 1;
        }
    }
    //printf("%d %d %d\n", badCode_check, badC_check, badK_check);
    if(badCode_check){
        return 1;
    }else if(badC_check){
        return 2;
    }else if(badK_check){
        return 3;
    }else{
        printf("case %d : ", counter);
        for(int i = 1; i < word_num - 3; i++){
            if(trans_ans[i] == 10){
                printf("-");
            }else{
                printf("%d", trans_ans[i]);
            }
        }
        printf("\n");
        return 4;
    }
}
int rtol(int num, int counter, int arr[]){
    //printf("rtol\n");
    int badC_check = 0;
    int badK_check = 0;
    int badCode_check = 0;
    int tmp, narrow, wide;
    tmp = arr[0];
    //判斷寬與窄
    for(int i = 0; i < num; i++){
        if(arr[i] > tmp * 1.1){
            narrow = tmp;
            wide = arr[i];
            break;
        }else if(arr[i] < tmp * 0.9){
            narrow = arr[i];
            wide = tmp;
            break;
        }
    }
    //寬與窄轉換
    for(int i = 0; i < num; i++){
        if(arr[i] > narrow * 0.9 && arr[i] < narrow * 1.1){
            arr[i] = 0;
        }else if(arr[i] > wide * 0.9 && arr[i] < wide * 1.1){
            arr[i] = 1;
        }
    }
    /*
    int dd = 0;
    for(int i = num - 1; i >= 0; i--){
        printf("%d ", arr[i]);
        dd++;
        if(dd == 6){
            printf("\n");
            dd = 0;
        }
    }printf("\n");
    */
    int word_num = (num + 1) / 6;
    int N = word_num - 4;
    int trans_ans[word_num];
    int now = 0;
    //五個一組分區段，並將二進位轉換成十進位碼。
    for(int i = num - 1; i >= 0; i--){
        int add = 0;
        for(int j = 0; j < 5; j++, i--){
            add += arr[i] * pow(2, 4 - j);
        }
        switch(add){
            case 3:
                trans_ans[now++] = 0;
                break;
            case 9:
                trans_ans[now++] = 1;
                break;
            case 16:
                trans_ans[now++] = 2;
                break;
            case 20:
                trans_ans[now++] = 3;
                break;
            case 24:
                trans_ans[now++] = 4;
                break;
            case 5:
                trans_ans[now++] = 5;
                break;
            case 12:
                trans_ans[now++] = 6;
                break;
            case 1:
                trans_ans[now++] = 7;
                break;
            case 18:
                trans_ans[now++] = 8;
                break;
            case 17:
                trans_ans[now++] = 9;
                break;
            case 4:
                trans_ans[now++] = 10;
                break;
            case 6:
                trans_ans[now++] = -1;
                break;
            default:
                badCode_check = 1;
                break;
        }
    }
    /*
    for(int i = 0; i < word_num; i++){
        printf("%d ", trans_ans[i]);
    }printf("\n");
    */
    //start/stop check
    if(trans_ans[0] != -1 || trans_ans[word_num - 1] != -1){
        badCode_check = 1;
    }
    //Code C check
    int codeCchecker = 0;
    for(int i = 1; i < word_num - 3; i++){
        codeCchecker += ((N - i) % 10 + 1) * trans_ans[i];
    }
    //printf("%d\n", codeCchecker % 11);
    if(codeCchecker % 11 != trans_ans[word_num - 3]){
        badC_check = 1;
    }else{
        //code K check
        int codeKchecker = 0;
        for(int i = 1; i < word_num - 2; i++){
            codeKchecker += ((N + 1 - i) % 9 + 1) * trans_ans[i];
        }
        //printf("%d\n", codeKchecker % 11);
        if(codeKchecker % 11 != trans_ans[word_num - 2]){
            badK_check = 1;
        }
    }
    //printf("%d %d %d\n", badCode_check, badC_check, badK_check);
    if(badCode_check){
        return 1;
    }else if(badC_check){
        return 2;
    }else if(badK_check){
        return 3;
    }else{
        printf("case %d : ", counter);
        for(int i = 1; i < word_num - 3; i++){
            if(trans_ans[i] == 10){
                printf("-");
            }else{
                printf("%d", trans_ans[i]);
            }
        }printf("\n");
        return 4;
    }
}
