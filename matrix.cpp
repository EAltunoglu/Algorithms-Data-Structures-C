#include<bits/stdc++.h>

int a = 5, n = 10, mat[5][5], size = 2;
int tmp[5][5],ans[5][5];

int calc(){
	int ans = 0;
	for(int i = 0, cur = 1; i <= n; i++){
		ans += cur;
		printf("%d %d\n",i,cur);
		cur *= a;
	}
	return ans;
}

void exp(){
	
	mat[1][1] = mat[2][1] = a;
	mat[1][2] = 0;
	mat[2][2] = 1;
	
	ans[1][1] = ans[2][2] = 1;
	puts("asfasdf");
	for(int pow = 1; pow <= n ; pow <<= 1){
		if(n & pow){
			memset(tmp,0,sizeof tmp);
			for(int i = 1; i <= size; i++)
				for(int j = 1; j <= size; j++)
					for(int k = 1; k <= size; k++){
						tmp[i][k] += ans[i][j] * mat[j][k];
					}
			memcpy(ans, tmp, sizeof ans);
		}
		puts("rrrrrr");
		memset(tmp,0,sizeof tmp);
		
		for(int i = 1; i <= size; i++)
			for(int j = 1; j <= size; j++)
				for(int k = 1; k <= size; k++)
					tmp[i][k] += mat[i][j] * mat[j][k];
		
		memcpy(mat, tmp, sizeof mat);
	}
	puts("qqqqqqqqqq");
}

int main(){
	
	printf("%d\n",calc());
	exp();
	
	for(int i = 1; i <= size; i++){
		for(int j = 1; j <= size; j++)
			printf("%d ",ans[i][j]);
		puts("");
	}
	
	return 0;
}
