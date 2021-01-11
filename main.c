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
#include <stdio.h>
#include <math.h> 

int ltor(int, int, int[]);
int rtol(int, int, int[]);

int main(){
    int num;
    FILE *fptr;
    int i;
    if((fptr = fopen("test.txt", "r")) == NULL){
        printf("File could not be opened.\n");
    }else{
        int counter = 1;
        fscanf(fptr, "%d", &num);
        while(num != 0){
            int arr[num];
            fscanf(fptr, "%d", &arr[0]);
            //輸入
            for(i = 1; i < num; i++){
                fscanf(fptr, "%d", &arr[i]);
            }

            // bad code 0, bad C 1, bad K 2, good code 3;
            int ltor_result = ltor(num, counter, arr);
            int rtol_result = rtol(num, counter, arr);
            // 比較 ltor 和 rtol 兩函式何者有較佳的結果
			// 最佳 -------------------------> 最差
			// 有解答 -> Bad K -> Bad C -> Bad Code 
			// 因為有照最佳至最差的順序排序代號 (第49行) 故可以透過比大小比出應使用 ltor 或 rtol 
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
    // 判斷是否無法得出正確答案 
	int badC_check = 0;
    int badK_check = 0;
    int badCode_check = 0;
    int tmp, narrow, wide;
    tmp = arr[0];
    int i;
    //判斷寬與窄 (由於可能第一筆資料就是誤差資料，故我將誤差從 5% 提升至 10% )
    for(i = 0; i < num; i++){
    	 // 若新資料大於第零筆資料 * 1.1 && 約等於第零筆資料 * 2 
		 // -> 新資料為 wide bar, 第零筆資料為 narrow bar. 
        if(arr[i] > tmp * 1.1 && arr[i] >= tmp * 1.9){
            narrow = tmp;
            wide = arr[i];
            break;
        }
         // 若新資料小於第零筆資料 * 0.9 && 約等於第零筆資料 * 0.5 
		 // -> 新資料為 narrow bar, 第零筆資料為 wide bar. 
		else if(arr[i] < tmp * 0.9 && arr[i] <= tmp * 0.6){
            narrow = arr[i];
            wide = tmp;
            break;
        }
    }
    //將所有資料轉換為 wide 及 narrow  
    for(i = 0; i < num; i++){
        if(arr[i] > narrow * 0.9 && arr[i] < narrow * 1.1){
            arr[i] = 0;
        }else if(arr[i] > wide * 0.9 && arr[i] < wide * 1.1){
            arr[i] = 1;
        }
    }
    int word_num = (num + 1) / 6; // 每一組字為五個 0 或 1 加一個間隔用 0 (除了最後一組字) 
    int N = word_num - 4; // N為實際需顯式的字數(扣掉start/stop, code c 和 k) 
    int trans_ans[word_num];// 轉換後的數字存放的位置 
    int now = 0;
    int j;
    //五個一組分區段，並將二進位轉換成十進位碼。
    for(i = 0; i < num; i++){ // 這裡的 i++ 能跳過空格用的 0 (非常精妙 ! ) 
        int add = 0;
        for(j = 0; j < 5; j++, i++){  
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
    //start/stop check
    if(trans_ans[0] != -1 || trans_ans[word_num - 1] != -1){
        badCode_check = 1;
    }
    //Code C check
    int codeCchecker = 0;
    for(i = 1; i < word_num - 3; i++){
        codeCchecker += ((N - i) % 10 + 1) * trans_ans[i];
    }
    if(codeCchecker % 11 != trans_ans[word_num - 3]){
        badC_check = 1;
    }else{
        //code K check
        int codeKchecker = 0;
        for(i = 1; i < word_num - 2; i++){
            codeKchecker += ((N + 1 - i) % 9 + 1) * trans_ans[i];
        }
        if(codeKchecker % 11 != trans_ans[word_num - 2]){
            badK_check = 1;
        }
    }
    if(badCode_check){
        return 1;
    }else if(badC_check){
        return 2;
    }else if(badK_check){
        return 3;
    }else{
        printf("case %d : ", counter);
        for(i = 1; i < word_num - 3; i++){
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
    int i, j;
    //判斷寬與窄
    for(i = 0; i < num; i++){
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
    for(i = 0; i < num; i++){
        if(arr[i] > narrow * 0.9 && arr[i] < narrow * 1.1){
            arr[i] = 0;
        }else if(arr[i] > wide * 0.9 && arr[i] < wide * 1.1){
            arr[i] = 1;
        }
    }
    
    int word_num = (num + 1) / 6;
    int N = word_num - 4;
    int trans_ans[word_num];
    int now = 0;
    //五個一組分區段，並將二進位轉換成十進位碼。
    for(i = num - 1; i >= 0; i--){
        int add = 0;
        for(j = 0; j < 5; j++, i--){
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
    //start/stop check
    if(trans_ans[0] != -1 || trans_ans[word_num - 1] != -1){
        badCode_check = 1;
    }
    //Code C check
    int codeCchecker = 0;
    for(i = 1; i < word_num - 3; i++){
        codeCchecker += ((N - i) % 10 + 1) * trans_ans[i];
    }
    if(codeCchecker % 11 != trans_ans[word_num - 3]){
        badC_check = 1;
    }else{
        //code K check
        int codeKchecker = 0;
    	for(i = 1; i < word_num - 2; i++){
            codeKchecker += ((N + 1 - i) % 9 + 1) * trans_ans[i];
        }
        if(codeKchecker % 11 != trans_ans[word_num - 2]){
            badK_check = 1;
        }
    }
    if(badCode_check){
        return 1;
    }else if(badC_check){
        return 2;
    }else if(badK_check){
        return 3;
    }else{
        printf("case %d : ", counter);
        for(i = 1; i < word_num - 3; i++){
            if(trans_ans[i] == 10){
                printf("-");
            }else{
                printf("%d", trans_ans[i]);
            }
        }printf("\n");
        return 4;
    }
}
