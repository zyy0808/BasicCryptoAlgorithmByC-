#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

typedef int               int32_t;
typedef long long int     int64_t;

bool      is_prime(int64_t a);              /* Miller-Rabin素性测试 */
int64_t   original_root(int64_t p);              /* 找出原根 */ 
bool      lucas(int64_t a, int64_t *b,int64_t c);        /* lucas原根检测 */ 
int64_t   quick_pow(int64_t a, int64_t b, int64_t c);    /* 快速平方乘算法 */ 
int64_t   quick_mul(int64_t a, int64_t b, int64_t c);    /* 快速乘算法 */ 
int64_t   find_inverse(int64_t a, int64_t b);           /* 找出原根 */ 

            
int main(){
	srand((unsigned)time( NULL ) );          /* 初始化随机函数种子 */ 
	int64_t p, a, d, b, ke, x, r, ke_inverse, s, t, b_r, r_s;
	for(int i = 1; i <= 20; i++){      /*  实验20次 */ 	
	p = rand()%4294967296;      /* 选择一个大素数 p */  
	while(is_prime(p) == 0){
		p++;
	}    
	a = original_root(p);    /* 随机选择一个p的原根 α */ 
	d = rand()%(p-4) + 2;    /* 在2到p-2中选择私钥 */ 
	b = quick_pow(a, d, p);   /* 计算公钥 β */ 
	ke = rand()%(p-4) + 2;    /* 在2到p-2中选择ke */ 
	while (is_prime(ke) == 0){        /* 若随机生成的ke不是素数，就再取一个，直到取到素数为止 */ 
		ke = rand()%(p-4) + 2;
	}                        /* 若ke是素数，则保证ke和p-1互素 */ 
	x =  rand() % p;            /* 随机生成签名消息x */ 
	r = quick_pow(a, ke, p);   /* 计算 r */ 
	ke_inverse = find_inverse(ke,p - 1);     /* 找到ke mod p-1 的逆元 */ 
	s = quick_mul((x-d*r)%(p - 1), ke_inverse, p - 1);     /* 计算s */ 
	if(s < 0){
		s = s + p-1;
	}
	cout<<i<<"."<<"签名值：（"<<r<<","<<s<<")"<<endl;
	b_r = quick_pow(b, r, p);      /* 计算 β的r次方（mod p） */ 
	r_s = quick_pow(r, s, p);      /* 计算r的s次方（mod p） */ 
	t = quick_mul(b_r, r_s, p);    /* 计算t */ 
	if (t == quick_pow(a, x, p)){         /* 验证，若t=a的x次方（mod p），则签名有效 */ 
	cout<<"签名有效！"<<endl;
    }
	else {
		cout<<"签名无效"<<endl; 
	}  
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
    			c[sum] = (p-1)/ i;
    			sum++; 
    		}
    		}
	}
	
    root = rand()%p + 2;      /*随机生成2-p的数，lucas判断是否为原根 */ 
    while (lucas(root, c, p) == 0) {    
    	root++;
	}                   /* 如果lucas检测不是原根，就在选定的随机数附近找到一个原根 */ 
   
	 
	return root;
}
bool lucas(int64_t a, int64_t *b,int64_t c){
	int64_t flag, t;      /* 设置一个标志，用于判断传进来的数是不是原根 */ 
	flag=1;
	for (int i = 0; b[i] != '\0'; i++) {
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

int64_t quick_mul(int64_t a, int64_t  b, int64_t c) {
    int64_t r;
    r = 0;
    while (b != 0) {      /* 计算此位二进制数字 */ 
        if (b % 2 == 1){   /* 如果此位二进制是1，就不用动，加入总值 */ 
        	r = (r + a) % c;         
		}
        a = (a * 2) % c;         /* 如果此位是0， 就乘2 */ 
		b = b / 2;      /* 移位 */ 
    }
    return r;
}

int64_t find_inverse(int64_t a,int64_t b) {
	
	int64_t ri[50], qi[50], si[50], ti[50];  /* 设置四个数组，形成密码学计算器里的四列 */ 
	
	ri[0] = b;
	ri[1] = a;                   /* 将p的欧拉函数值给r0，固定ti列是km mod p的欧拉函数的逆元 */ 
	si[0] = 1;
	si[1] = 0;
	ti[0] = 0;
	ti[1] = 1;
	qi[0] = 0;            /* 先给出初值 */  
	int x = 1;
	int i_r = 2,i_q = 1,i_s = 2,i_t = 2;
    for (int y = 1; x != 0; y++) {
		ri[i_r] = ri[i_r - 2] % ri[i_r - 1];
		qi[i_q] = ri[i_q - 1] / ri[i_q];
		si[i_s] = si[i_s - 2] - si[i_s - 1] * qi[i_s - 1];
		ti[i_t] = ti[i_t - 2] - ti[i_t - 1] * qi[i_t - 1];
		i_r++;
		i_q++;
		i_s++;
		i_t++;
		x = ri[i_r - 1];
	}                     /* 一行一行计算，直到ri为0为止 */     
	if(ti[i_t - 2]<=0){
		ti[i_t - 2] = ti[i_t - 2] + ri[0];
	}                     
	return ti[i_t - 2];    /* 返回逆元 */ 
}

