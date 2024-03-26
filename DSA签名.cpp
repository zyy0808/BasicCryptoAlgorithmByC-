#include<iostream>

using namespace std;

typedef int             int32_t;
typedef long long int   int64_t;

int main() {
	srand((unsigned)time( NULL ) );          /* 初始化随机函数种子 */
	p = rand() % 4200000000;
	while (is_prime(p) == 0) {
		p++;
	}
	q = ramd() % 4200000000;
	while (is_prime(q) == 0) {
		q++;
	}
	
}
