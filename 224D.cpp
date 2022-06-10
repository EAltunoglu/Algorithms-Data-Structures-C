#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 50, maxc = 26;

int sum[maxc+2][maxn],N,M,pre[maxn],suf[maxn];
char A[maxn],B[maxn];

int No(){
	return puts("No");
}

int get(int pos, int let){
	return sum[let][pos];
}

int calc(int l, int r, int let){
	if(l > r) return 0;
	return get(r, let) - get(l-1, let);
}

int main(){
	
	scanf("%s %s",A+1,B+1);
	N = strlen(A+1);
	M = strlen(B+1);
	
	for(int i = 1; i <= M; i++)
		for(int j = 0; j < maxc; j++)
			sum[j][i] = sum[j][i-1] + ('a'+j == B[i]);
	
	for(int i = 1; i <= N; i++)
		pre[i] = pre[i-1] + (A[i] == B[pre[i-1] + 1]);
	
	for(int i = N; i; i--)
		suf[i] = suf[i+1] + (A[i] == B[M-suf[i+1]]);
	
	for(int i = 1; i <= N; i++)
		if(!calc(M-suf[i]+1, pre[i], A[i]-'a'))
			return No();
	
	puts("Yes");
	
	return 0;
}
