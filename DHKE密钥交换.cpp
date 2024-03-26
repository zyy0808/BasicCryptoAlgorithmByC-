#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

typedef int           int32_t;
typedef long long int int64_t;

bool      is_prime(int64_t a);              /* Miller-Rabin素性测试 */
int64_t   original_root(int64_t a);              /* 找出原根 */ 
bool      lucas(int64_t a, int64_t *b,int64_t c);        /* lucas原根检测 */
int64_t   quick_pow(int64_t a, int64_t b, int64_t c);    /* 快速平方乘算法 */

int64_t  sum;            /* 定义sum为全局变量 */ 
int main() {
	srand((unsigned)time( NULL ) );          /* 初始化随机函数种子 */
	for (int i = 1; i <= 20; i++) {
	int64_t p, p_root, a, A, kab_alice, kab_bob, b, B;
	p = rand() % 4294967296;
	while (is_prime(p) == 0){
		p++;
	}
	p_root = original_root(p);         /*  约定素数p和p的一个原根 */ 
	a = rand() % (p - 4) + 2;          /* alice从2到p-2选择私钥a */ 
	A = quick_pow(p_root, a, p);       /* alice计算公钥A */ 
	b = rand() % (p - 4) + 2;          /* BOb选择私钥b */ 
	B = quick_pow(p_root, b, p);       /* bob计算公钥B */
	kab_alice = quick_pow(B, a, p);    /* alice计算会话密钥kab */ 
	kab_bob = quick_pow(A, b, p);      /* bob计算会话密钥kab */ 
	if (kab_alice == kab_bob) {        /* 如果两个会话密钥相等，密钥交换成功 */ 
		cout<<i<<"."<<"密钥交换成功"<<endl; 
		cout<<"会话密钥为："<<kab_alice<<endl; 
	}
	else {
		cout<<"密钥交换失败"<<endl; 
	}
	cout<<endl;
}
	return 0;
}
bool is_prime(int64_t a)
{
	int64_t d, r, witness;
	d=a-1;
	r=0;
    if (a < 3 && a != 2) /* 特判1，2 */
        return false;
    if (a % 2 == 0) /* 特判偶数 */
        return false;
    
    while (d % 2 == 0) {   /* 算出d，r */ 
        d = d / 2;
        r++;
    }
    for (int i = 0; i <= 50; i++) {      /* 见证51次 */ 
    	witness = rand()%a-3 + 2;       /* 见证人取2到n-2 */ 
        int64_t v = quick_pow(witness, d, a); 
        /* 如果witness^d≡0，说明是witness是a的倍数；如果witne^d≡1或-1，说明这串数接下来一定都是1，不用继续计算 */
        if (v <= 1 || v == a - 1) 
            continue;
        for (int i = 0; i < r; ++i)
        {
            v = v * v % a; 
            if (v ==  - 1 && i != r - 1) /* 得到-1，说明接下来都是1，可以退出了 */
            {
                v = 1;
                break;
            }
            /* 在中途而非开头得到1，却没有经过-1，说明存在其他数字y≠-1满足y^2≡1，则a一定不是奇素数 */
            if (v == 1)  
                return false;
        }
        if (v != 1)   /* 查看是不是以1结尾 */
            return false;
    }
    return true;
}
int64_t original_root(int64_t p) {
	int64_t c[p];         /* 定义一个数组 ，用来存放所有的φ(p) /φ(p)的素因子 */     
	int64_t i, root, sum;
	sum = 0;
    for (i = 2; i < p - 1; i++) {
    	if ((p - 1) % i == 0) {        /* 如果 i 是 p 的因子，则判断i是不是素数 */ 
    		if (is_prime(i) == 1) {         /* 如果 i 是素数，就把 i 加入 素因子数组，用于后面的lucas原根检测 */ 
    			c[sum] = p / i;
    			sum++;
    		}
    		}
	}
	
    root = rand()%p + 2;      /*随机生成2-p的数，lucas判断是否为原根 */ 
    while (lucas(root, c, p) == 0) {    
    	root++;
	}                   /* 如果lucas检测不是原根，就在选定的随机数附近找到一个原根 */ 
     //cout<<root<<" "<<endl;
	 
	return root;
}
bool lucas(int64_t a, int64_t *b,int64_t c){
	int64_t flag, t;      /* 设置一个标志，用于判断传进来的数是不是原根 */ 
	flag=1;
	for (int i = 0; i < sum; i++) {
     	t = quick_pow(a, b[i], c);        /* 计算所有素因子次方 */ 
     	if (t == 1) { 
     		flag = 0;                  /* 如果计算出素因子次方为1， 那么这个树就不是原根 */
		 }
	 }
	 if (flag == 0) {
	 	return false;
	 }
	 
	 return true;
}
int64_t quick_pow(int64_t a, int64_t b,int64_t c) {
    int64_t r, base;
    r = 1;
    base = a;
	while (b!=0)       /* 循环截止条件 */ 
	{
		if (b % 2 == 1) {
			r = (r * base) % c;     /* 如果此位二进制是1，就乘一下 */ 
		}
 
		base = (base * base) % c;   /* 不然就平方 */ 
 
		b = b / 2;     /* 移位运算，右移一位 */
	}
 
	return r;
}
