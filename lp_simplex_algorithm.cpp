#include<cstdio>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<fstream>
#include<cassert>
using namespace std;

typedef vector<vector<double>> Mat;
const double eps = 1e-9;

/*
Matrix class
* operator -> performs matrix multiplication
- operator -> performs matrix subtraction
! operator -> returns inverse of matrix
get_columns(column ids) -> returns the only given columns as a matrix
price_out() -> returns the index of new variable which enters the basis (the biggest non-negative)
get_val() -> return the value of the matrix to find z (Optimal result) (only 1x1 matrices are valid)
ratio_test() -> performs the ratio test to find variable leaving the basis, returns -1 if none of the available, otherwise returns the index of variable
get_varibles(basic variables, total number of variables) -> returns the optimal vector

Utility functions
print_result() -> prints the result, if the problem is unbounded simply prints 'Unbounded', otherwise print the optimal variable vector and the optimal result
iterate() -> performs one iteration, returns true if a new variable enters basic, otherwise false
solve() -> reads the input and calls the iterate function. If the iterate function returns true, there is a new variable in the basis and calls the iterate function again. Otherwise, calls the print_result function.
*/
class Matrix {
	public:
		Mat ar;
		
		Matrix(const Mat &a){
			ar = a;
		}
		
		// returns multiplication of two matrices
		Matrix operator*(const Matrix &a){
			const Mat A = this -> ar;
			const Mat B = a.ar;
			
			assert(!A.empty() && !B.empty());
			assert(A[0].size() == B.size());
			
			const int n = A.size();
			const int m = A[0].size();
			const int k = B[0].size();
			
			Mat ret(n , vector<double> (k));
			
			for(int i = 0; i < n; i++)
				for(int j = 0; j < m; j++)
					for(int p = 0; p < k; p++)
						ret[i][p] += A[i][j] * B[j][p];
			
			return Matrix(ret);
		}
		
		// returns subtraction
		Matrix operator-(const Matrix &a){
			const Mat A = this -> ar;
			const Mat B = a.ar;
			
			assert(!A.empty() && !B.empty());
			assert(A.size() == B.size());
			assert(A[0].size() == B[0].size());
			
			const int n = A.size();
			const int m = A[0].size();
			
			Mat ret(n, vector<double> (m));
			
			for(int i = 0; i < n; i++)
				for(int j = 0; j < m; j++)
					ret[i][j] = A[i][j] - B[i][j];
			
			return Matrix(ret);
		}
		
		// returns inverse
		Matrix operator!(){
			Mat A = this -> ar;
			assert(A.size() == A[0].size());
			const int n = A.size();
			
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					A[i].push_back(i == j);
			
			vector<bool> used(n);
			
			for(int i = 0; i < n; i++){
				for(int j = 0; j < n; j++){
					if(used[j] || abs(A[i][j]) < eps) continue;
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
			
			Mat ans;
			
			for(int i = 0; i < n; i++){
				ans.push_back(vector<double> ());
				for(int j = 0; j < n; j++){
					ans[i].push_back(A[i][n+j]);
				}
			}
			
			return Matrix(ans);
		}
		
		Matrix get_columns(const vector<int> cols){
			const Mat A = this -> ar;
			const int n = A.size();
			Mat ret(n);
			for(int i = 0; i < cols.size(); i++){
				int col = cols[i];
				for(int j = 0; j < A.size(); j++)
					ret[j].push_back(A[j][col]);
			}
			return Matrix(ret);
		}
		
		int price_out(){
			const Mat A = this -> ar;
			assert(A.size() == 1);
			int index = -1;
			for(int i = 0; i < A[0].size(); i++)
				if(A[0][i] < 0.0){
					if(index == -1)
						index = i;
					else if(A[0][i] < A[0][index])
						index = i;
				}
			return index;
		}
		
		double get_val(){
			const Mat A = this -> ar;
			assert(A.size() == 1 && A[0].size() == 1);
			return A[0][0];
		}
		
		int ratio_test(const Matrix &a){
			Mat A = this -> ar;
			const Mat B = a.ar;
			assert(A[0].size() == 1);
			assert(A[0].size() == B[0].size());
			assert(A.size() == B.size());
			int index = -1;
			for(int i = 0; i < A.size(); i++)
				if(B[i][0] > 0.0){
					A[i][0] /= B[i][0];
					if(index == -1)
						index = i;
					else if(A[i][0] < A[index][0])
						index = i;
				}
			return index;
		}
		
		vector<double> get_variables(const vector<int> BV, const int size){
			const Mat A = this -> ar;
			assert(A[0].size() == 1);
			const int n = A.size();
			vector<double> ret(size, 0.0);
			for(int i = 0; i < n; i++)
				ret[BV[i]] = A[i][0];
			return ret;
		}
};


Mat A,b,c;
vector<int> BV, NBV;
bool unbounded;

// prints the result, if the problem is unbounded simply prints 'Unbounded', otherwise print the optimal variable vector and the optimal result
void print_result(){
	
	if(unbounded){
		puts("Unbounded");
		return;
	}
	
	Matrix B = Matrix(A).get_columns(BV);
	Matrix cb = Matrix(c).get_columns(BV);
	
	Matrix rhs = !B * Matrix(b);
	
	double z = (cb * rhs).get_val();
	
	printf("Optimal variable vector:\n");
	vector<double> ans = rhs.get_variables(BV, BV.size() + NBV.size());
	for(int i = 0; i < ans.size(); i++)
		printf("x%d = %.2lf\n",i+1,ans[i]);
	
	printf("Optimal result: %lf\n",z);
}

// Performs one iteration, returns true if a new variable enters basic, otherwise false
bool iterate(){
	Matrix B = Matrix(A).get_columns(BV);
	Matrix cb = Matrix(c).get_columns(BV);
	
	Matrix c_star = cb * !B * Matrix(A).get_columns(NBV);
	c_star = Matrix(c).get_columns(NBV) - c_star;
	
	int index = c_star.price_out();
	if(index == -1)	return false;
	
	Matrix A_star = !B * Matrix(A);
	Matrix b_star = !B * Matrix(b);
	
	vector<int> column;
	column.push_back(index);
	A_star = A_star.get_columns(column);
	
	// ratio test
	int outidx = b_star.ratio_test(A_star);
	
	if(outidx == -1){
		unbounded = true;
		return false;
	}
	
	// index enters basic variables, outidx leaves basic variables
	swap(NBV[index], BV[outidx]);
	
	return true;
}

// Reads the input and calls the iterate function. If the iterate function returns true, there is a new variable in the basis and calls the iterate function again. Otherwise, calls the print_result function.
bool solve(const string filename){
	ifstream myfile;
	myfile.open(filename);
	cout << "Solution of " << filename << ":" << endl;
	if(!myfile.is_open()){
		cout << "There is no file." << endl;
		return false;
	}
	
	int n,m;
	
	myfile >> m;
	myfile >> n;
	
	// clear everything
	A.clear();b.clear();c.clear();
	BV.clear();
	NBV.clear();
		
	A.resize(m, vector<double> (n)); // m x n coefficents in constraints
	b.resize(m, vector<double> (1)); // m x 1  RHS in constraints
	c.resize(1, vector<double> (n)); // 1 x n coefficents in objective function
	
	for(int i = 0; i < n; i++){
		double x;
		myfile >> x;
		c[0][i] = x;
		NBV.push_back(i); // non basic variables
	}
	
	for(int i = 0; i < m; i++){
		BV.push_back(n+i); // basic variables
		for(int j = 0; j < n+1; j++){
			double x;
			myfile >> x;
			if(j != n)
				A[i][j] = x;
			else
				b[i][0] = x;
		}
	}
	
	// add slack variables
	for(int i = 0; i < m; i++){
		for(int j = 0; j < m; j++)
			A[i].push_back(i == j); // to A
		c[0].push_back(0); // to c;
	}
	
	unbounded = false;
	int loop = m + n + m;
	while(iterate() && loop) loop--;
	
	print_result();
	
	return true;
}

int main(){
	
	int i = 1;
	bool rep = false;
	do{
		string filename = "Data" + to_string(i) + ".txt";
		rep = solve(filename);
		i++;
	}while(rep);
	
	return 0;
}
