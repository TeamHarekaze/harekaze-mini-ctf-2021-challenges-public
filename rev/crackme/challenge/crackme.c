#include <stdio.h>
#include <string.h>

int a[32] = {122, 69, 62, 88, 61, 87, 53, 57, 108, 104, 95, 73, 58, 56, 84, 97, 52, 96, 56, 141, 86, 76, 133, 58, 64, 61, 59, 87, 115, 59, 48};
int b[32] = { -13968, -16102, -20064, -19089, -17976, -17848, -21350, -15958, -11725, -15792, -11550, -24108, -19323, -20241, -17557, -19700, -18924, -18721, -19952, -9310, -18315, -16245, -9384, -19323, -21177, -15326, -20300, -20160, -7824, -18590, -21625};

int calc(char x, int a, int b){
	int tmp = (x * x) + (a * x) + b;
	if(tmp == 0){
		return 1;
	}else{
		return 0;
	}
	
}
int main(int argc, char *argv[]){
	int result = 0;
	int i;
	int length;
	
	if(argc == 1){
		printf("Usage: crackme <flag>\n");
	}else{
		if(strlen(argv[1]) == 31){
			for(i=0; i < 31; i++){
				result = calc(argv[1][i] , a[i], b[i]);
				if(result == 0) break;
			}
			if(result == 1){
				printf("Conguratulations!! Flag is %s\n", argv[1]);
				return 1;
			}
		}else{
				printf("Oops, Try again.\n");	
		}
	}
	
	return 0;
}
