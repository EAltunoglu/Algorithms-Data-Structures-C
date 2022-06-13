#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#define fi first
#define se second
#define mp make_pair
using namespace std;

const double eps = 1e-6;
 
typedef pair<double, double> dd;
/*
// (5x1-x2)^4 + (x1-2)^2 + x1 - 2x2 + 12
double f(const double x1, const double x2){
	return pow(5*x1-x2, 4.0) + pow(x1-2, 2.0) + x1 - 2*x2 + 12;
}

// 5*4*(5x1-x2)^3 + 2*(x1-2) + 1 
double f_x1(const double x1, const double x2){
	return 20*pow(5*x1-x2, 3.0) + 2*(x1-2) + 1;
}

// -4*(5x1-x2)^3 - 2
double f_x2(const double x1, const double x2){
	return -4*pow(5*x1-x2, 3.0) - 2;
}
*/
// (5x1-x2)^4 + (x1-2)^2 + x1 - 2x2 + 12
double f(const dd x){
	return pow(5*x.fi - x.se, 4.0) + pow(x.fi - 2, 2.0) + x.fi - 2*x.se + 12;
}

// 5*4*(5x1-x2)^3 + 2*(x1-2) + 1 
double f_x1(const dd x){
	return 20*pow(5*x.fi - x.se, 3.0) + 2*(x.fi - 2) + 1;
}

// -4*(5x1-x2)^3 - 2
double f_x2(const dd x){
	return -4*pow(5*x.fi - x.se, 3.0) - 2;
}

double calc_dist(const dd a, const dd b = dd(0,0)){
	return sqrt((a.fi-b.fi)*(a.fi-b.fi) + (a.se-b.se)*(a.se-b.se));
}

dd calculate_d(const dd x){
	double fg1 = f_x1(x);
	double fg2 = f_x2(x);
	double dist = calc_dist(dd(fg1, fg2));//sqrt(fg1*fg1 + fg2*fg2);
	//printf("Unit %lf %lf %lf\n",fg1/dist,fg2/dist, calc_dist(dd(fg1/dist, fg2/dist)));
	return dd(fg1/dist, fg2/dist);
	//return dd(-fg1/dist, -fg2/dist);
}

dd add(const dd p, const dd d){
	return dd(p.fi+d.fi, p.se+d.se);
}

dd mul(const dd p, const double a){
	return dd(p.fi*a, p.se*a);
}

// bisection method
double line_search(const dd p, const dd d){
	dd cur = p;
	double left = -1e4, right = 0;
	double mid;
	/*
	while(left + eps < right){
		mid = (left + right) / 2.0;
		if(f(cur) >= f(add(cur, mul(d, mid))))
			left = mid;
		else
			right = mid;
	}*/
	
	while(left + eps < right){
		mid = (left + right) / 2.0;
		//printf("%lf %lf %lf\n",mid,left,f(add(cur, mul(d, mid))));
		if(f(add(cur, mul(d, mid))) >= f(add(cur, mul(d, mid + eps))))
			left = mid;
		else
			right = mid;
	}
	/*
	dd cur = add(p, mul(d, -1e4));
	while(left + eps < right){
		mid = (left + right) / 2.0;
		if(f(add(cur, mul(d, mid))) >= f(add(cur, mul(d, mid + eps))))
			left = mid;
		else
			right = mid;
	}
	*/
	return (left+right) / 2.0;
	//return -1;
}

int main(){
	
	
	dd p(-1000, -1000), d;
	dd next = p;
	double a; 
	int cnt = 0;
	printf("Initial_Point: (%lf, %lf), Value_At_Point: %lf\n",p.fi,p.se,f(p));
	
	do{
		p = next;
		d = calculate_d(p);
		a = line_search(p, d);
		next = add(p, mul(d, a));
		//printf("Iteration: %d, Point: (%lf, %lf), Next_Point: (%lf %lf), Value_at_Point: %lf, Value_at_Next_Point: %lf\n",++cnt,p.fi,p.se,next.fi,next.se,f(p),f(next));
		printf("Iteration: %d, Next_Point: (%lf, %lf), Value_at_Next_Point: %lf\n",++cnt,next.fi,next.se,f(next));
		//printf("Iteration: %d, Next_Point: %lf %lf, Value_at_Next_Point: %lf, d: %lf %lf %lf\n",++cnt,next.fi,next.se,f(next),d.fi,d.se,f(p)-f(next));
	}while(f(p) - f(next) > eps && cnt < 100);
	if(f(p) > f(next)) p = next;
	printf("Minimum_Point: (%lf, %lf), Value_at_Point: %lf\n",p.fi,p.se,f(p));
	
	return 0;
}
