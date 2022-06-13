#include<cstdio>
using namespace std;

/*
Food Class -> for each foods type it stores nutrients
Overloaded Operators:
+  -> Returns nutrients of two foods
*  -> Returns nutrients of C(constant) * the food
>= -> Returns true if Food A greater or equal than B in all nutrients
*/

class Food{
public:
	double protein;
	int vitaminC;
	double iron;
	int price;
	
	Food(double _protein = 0, int _vitaminC = 0, double _iron = 0, int _price = 0){
		protein = _protein;
		vitaminC = _vitaminC;
		iron = _iron;
		price = _price;
	}
	
	Food operator+(const Food &a){
		Food ret;
		ret.protein = protein + a.protein;
		ret.vitaminC = vitaminC + a.vitaminC;
		ret.iron = iron + a.iron;
		ret.price = price + a.price;
		return ret;	
	}
	
	bool operator>=(const Food &a){
		return protein >= a.protein && vitaminC >= a.vitaminC && iron >= a.iron;
	}
	
	Food operator*(const int x){
		Food ret;
		ret.protein = x * protein;
		ret.vitaminC = x * vitaminC;
		ret.iron = x * iron;
		ret.price = x * price;
		return ret;
	}
};

const int MAX = 1e9;
const int MinProtein = 70, MinVitaminC = 50, MinIron = 12;
int cnt[5];

int main(){
	
	/*
	Definition of foods
	*/
	Food A(0.4 , 6 , 0.4, 8);
	Food B(1.2 , 10, 0.6, 10);
	Food C(0.6 , 3 , 0.4, 3);
	Food D(0.6 , 1 , 0.2, 20);
	Food E(12.2, 0 , 2.6, 15);
	Food Req(MinProtein, MinVitaminC, MinIron, 0);
	
	const int n = 20;
	int minCost = MAX;
	Food Ans;
	
	/*
	The algorithm determines amount of each food. It tries all combinations. Then calculates nutrients of final meal.
	If its cost lower than current best answer, it updates the answer.
	Finally it prints minimum cost, amount of each food and amount of the nutrients in the meal. 
	It is a brute force approach. More efficent algorithms can solve the same problem.
	However, limits are low so there is no need of faster and complex algorithm.
	*/
	
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			for(int k = 0; k <= n; k++)
				for(int o = 0; o <= n; o++)
					for(int p = 0; p <= n; p++){
						Food cur = A*i + B*j + C*k + D*o + E*p;
						if(cur >= Req && cur.price < minCost){
							minCost = cur.price;
							Ans = cur;
							cnt[0] = i;
							cnt[1] = j;
							cnt[2] = k;
							cnt[3] = o;
							cnt[4] = p;
						}
					}
	
	if(minCost == MAX){
		printf("No Solution.\n");
		return 0;
	}
	
	printf("Minimim Cost: %d\n",minCost);
	
	printf("#apples : %d\n",cnt[0]);
	printf("#bananas: %d\n",cnt[1]);
	printf("#carrots: %d\n",cnt[2]);
	printf("#dates  : %d\n",cnt[3]);
	printf("#eggs   : %d\n",cnt[4]);
	
	printf("\n");
	printf("protein : %.1lf\n",Ans.protein);
	printf("vitaminC: %d\n",   Ans.vitaminC);
	printf("iron    : %.1lf\n",Ans.iron);
	
	return 0;
}
/*
Food Class -> for each foods type it stores nutrients
Overloaded Operators:
+  -> Returns nutrients of two foods
*  -> Returns nutrients of C(constant) * the food
>= -> Returns true if Food A greater or equal than B in all nutrients

The algorithm determines amount of each food. It tries all combinations. Then calculates nutrients of final meal.
If its cost lower than current best answer, it updates the answer.
Finally it prints minimum cost, amount of each food and amount of the nutrients in the meal. 
It is a brute force approach. More efficent algorithms can solve the same problem.
However, limits are low so there is no need of faster and complex algorithm.

The best solution is using two type of food -eggs and carrots-.
The best solution is on the edges of the convex region determined by inequalities.
*/
