#include<cstdio>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const double eps = 1e-9;

int n;
vector<vector<double>> A,T;

// prints the given matrix

void print_matrix(const vector<vector<double>> A){
	if(A.empty()) return;
	const int n = A.size();
	const int m = A[0].size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++)
			printf("%lf ",A[i][j]);
		printf("\n");
	}
}


// Returns the rank of the given matrix
// Calculates with basic elementary row operations

int calc_rank(vector<vector<double>> A){
	if(A.empty()) return 0;
	int ret = 0;
	const int n = A.size();
	int m = A[0].size();
	for(int i = 0; i < n; i++){
		if(A[i][i] != 0){
			for(int j = i+1; j < n; j++){
				if(i == j)
					continue;
				double coef = A[j][i] / A[i][i];
				for(int k = 0; k < m; k++){
					A[j][k] -= coef * A[i][k];
				}
			}
			ret++;
		} else if(i == n-1){
			for(int k = i+1; k < m; k++)
				if(A[i][k] != 0){
					ret++;
					break;
				}
		} else {
			for(int j = i+1; j < n; j++){
				if(A[j][i] != 0){
					swap(A[j], A[i]);
					i--;
					break;
				}
			}
		}
	}
	return ret;
}

// Solves the given matrix by Gauss-Jordan Method
// With basic elementary row operations
// unless it has unique, then it prints arbitrary variables 

vector<double> elimination(vector<vector<double>> A, bool type){
	
	const int n = A.size();
	const int m = A[0].size(); // n+1
	vector<bool> used(n);
	vector<int> selected(n, -1);
	vector<double> ret(n);
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(used[j] || A[i][j] == 0 || abs(A[i][j]) < eps) continue;
			double temp = A[i][j];
			for(int k = 0; k < m; k++)
				A[i][k] /= temp;
			for(int row = 0; row < n; row++){
				if(row == i) continue;
				double coef = A[row][j];
				for(int k = 0; k < m; k++)
					A[row][k] -= coef * A[i][k];
			}
			selected[i] = j;
			used[j] = true;
			break;
		}
	}
	
	if(!type)
		printf("Arbitrary variables:");
	
	for(int i = 0; i < n; i++){
		if(selected[i] == -1){
			printf(" x%d",i);
			continue;
		}
		ret[selected[i]] = A[i][n];
	}
	if(!type) puts("");
	return ret;
}

// prints the solution depends on the type
// if type is true, then it is a unique solution
// otherwise it is arbitrary solution

void print_ans(const vector<double> ans, const bool type){
	if(type)	printf("Unique solution:");
	else		printf("Arbitrary solution:");
	
	for(int i = 0; i < n; i++)
		printf(" x%d=%.6lf",i,ans[i]);
	
	if(type)	printf("\nInverted A:");
	puts("");
}

// Finds the inverse of the given matrix
// Add an identity matrix create an augmented matrix
// With basic elementary row operations
// Make first matrix an identity matrix then
// The second matrix of the augmented matrix is inversed matrix of the given matrix
// Returns the inversed matrix

vector<vector<double>> find_inverse(vector<vector<double>> A){
	const int n = A.size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			A[i].push_back(i == j);
	}
	vector<bool> used(n);
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(used[j] || A[i][j] == 0 || abs(A[i][j]) < eps) continue;
			double temp = A[i][j];
			for(int k = 0; k < n+n; k++)
				A[i][k] /= temp;
			for(int row = 0; row < n; row++){
				if(row == i) continue;
				double coef = A[row][j];
				for(int k = 0; k < n+n; k++)
					A[row][k] -= coef * A[i][k];
			}
			used[j] = true;
			break;
		}
	}
	
	for(int i = 0; i < n; i++){
		if(abs(A[i][i] - 1) < eps) continue;
		for(int j = 0; j < n; j++)
			if(abs(A[j][i] - 1) < eps){
				swap(A[i], A[j]);
				break;
			}
	}
	
	vector<vector<double>> ans;
	
	for(int i = 0; i < n; i++){
		ans.push_back(vector<double> ());
		for(int j = 0; j < n; j++){
			ans[i].push_back(A[i][n+j]);
		}
	}
	
	return ans;
}

// Reads the matrix
// Finds the rank(A) and rank(A|b)
// By this values, it applies correct solution

void solve(){
	A.clear();
	T.clear();
	A.resize(n, vector<double> (n));
	T.resize(n, vector<double> (n+1));
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n+1; j++){
			double x;
			scanf("%lf",&x);
			T[i][j] = x;
			if(j != n)
				A[i][j] = x;
		}
	}
	
	const int rankA = calc_rank(A);
	const int rankT = calc_rank(T);

	if(rankA == n){ // if rank(A) = n then there is a unique solution
		vector<double> ans = elimination(T, true);
		print_ans(ans, true);
		vector<vector<double>> inv = find_inverse(A);
		print_matrix(inv);
	} else if(rankA == rankT){
		vector<double> ans = elimination(T, false);
		print_ans(ans, false);
	} else {
		puts("Inconsistent problem");
	}
	
}

int main(){
	
	freopen("Data.txt","r",stdin); // reads data from Data.txt file, all matrices in this file
	
	int cnt = 0;
	while(scanf("%d",&n) != -1){ // reads size of the matrix
		printf("Matrix #%d:\n",cnt);  // prints the number of the matrix
		solve();
		cnt++;
	}
	
	return 0;
}
