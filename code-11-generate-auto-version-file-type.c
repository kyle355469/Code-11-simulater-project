#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
    srand(time(NULL));
    int times;
    scanf("%d", &times);
    FILE *test = fopen("/Users/kylekai/CppC/project/case.txt", "w");
    while(times--){
        printf("times %d : \n", times);
        int num = rand() % 33, i;
        int intArr[num + 2];
        for(i = 0; i < num; i++){
            int ask = rand() % 11;
            intArr[i] = ask;
        }
        for(i = 0; i < num; i++){
            if(intArr[i] == 10){
                printf("-");
            }else{
                printf("%d", intArr[i]);
            }
        }printf("\n");
        intArr[num] = 0;
        intArr[num + 1] = 0;
        for(i = 0; i < num; i++){
            intArr[num] += ((num - i - 1) % 10 + 1) * intArr[i];
        }intArr[num] %= 11;

        for(i = 0; i < num + 1; i++){
            intArr[num + 1] += ((num - i) % 9 + 1) * intArr[i];
        }intArr[num + 1] %= 11;

        int count = (num + 4) * 6 - 1;
        fprintf(test, "%d\n4 4 8 8 4 4\n", count);
        for(int i = 0; i < num + 2; i++){
            switch(intArr[i]){
                case 0:
                    fprintf(test ,"4 4 4 8 8 4 \n");
                    break;
                case 1:
                    fprintf(test ,"4 8 4 4 8 4 \n");
                    break;
                case 2:
                    fprintf(test ,"8 4 4 4 4 4 \n");
                    break;
                case 3:
                    fprintf(test ,"8 4 8 4 4 4 \n");
                    break;
                case 4:
                    fprintf(test ,"8 8 4 4 4 4 \n");
                    break;
                case 5:
                    fprintf(test ,"4 4 8 4 8 4 \n");
                    break;
                case 6:
                    fprintf(test ,"4 8 8 4 4 4 \n");
                    break;
                case 7:
                    fprintf(test ,"4 4 4 4 8 4 \n");
                    break;
                case 8:
                    fprintf(test ,"8 4 4 8 4 4 \n");
                    break;
                case 9:
                    fprintf(test ,"8 4 4 4 8 4 \n");
                    break;
                case 10:
                    fprintf(test ,"4 4 8 4 4 4 \n");
                    break;

            }

        }fprintf(test ,"4 4 8 8 4\n");
    }
    fprintf(test, "0");
    
}