#include <iostream>
#include <ctime>
using namespace std;
int main(){
    srand(time(NULL));
    
    int num, i;
    cin >> num;
    int intArr[num + 2];
    for(i = 0; i < num; i++){
        int ask = rand() % 11;
        intArr[i] = ask;
    }
    for(i = 0; i < num; i++){
        if(intArr[i] == 10){
            cout << "-";
        }else{
            cout << intArr[i];
        }
    }cout << endl;
    intArr[num] = 0;
    intArr[num + 1] = 0;
    for(i = 0; i < num; i++){
        intArr[num] += ((num - i - 1) % 10 + 1) * intArr[i];
    }intArr[num] %= 11;

	for(i = 0; i < num + 1; i++){
        intArr[num + 1] += ((num - i) % 9 + 1) * intArr[i];
    }intArr[num + 1] %= 11;

    for(i = 0; i < num + 2; i++){
        cout << intArr[i] << " ";
        
    }cout << endl;

    int count = (num + 4) * 6 - 1;
    cout << count << endl;
    cout << "4 4 8 8 4 4 \n";
    for(int i = 0; i < num + 2; i++){
        switch(intArr[i]){
            case 0:
                cout << "4 4 4 8 8 4 \n";
                break;
            case 1:
                cout << "4 8 4 4 8 4 \n";
                break;
            case 2:
                cout << "8 4 4 4 4 4 \n";
                break;
            case 3:
                cout << "8 4 8 4 4 4 \n";
                break;
            case 4:
                cout << "8 8 4 4 4 4 \n";
                break;
            case 5:
                cout << "4 4 8 4 8 4 \n";
                break;
            case 6:
                cout << "4 8 8 4 4 4 \n";
                break;
            case 7:
                cout << "4 4 4 4 8 4 \n";
                break;
            case 8:
                cout << "8 4 4 8 4 4 \n";
                break;
            case 9:
                cout << "8 4 4 4 8 4 \n";
                break;
            case 10:
                cout << "4 4 8 4 4 4 \n";
                break;

        }

    }cout << "4 4 8 8 4";
}