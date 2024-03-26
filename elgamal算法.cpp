#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

typedef int                 int32_t;
typedef long long int       int64_t;

bool      is_prime(int64_t a);              /*Miller-Rabin���Բ���*/
int64_t   original_root(int64_t p);             /* �������ԭ���㷨 */
bool      lucas(int64_t a, int64_t *b,int64_t c);    /* lucasԭ����� */ 
int64_t   quick_pow(int64_t a, int64_t b, int64_t c);    /* ����ƽ���� */ 
int64_t   find_inverse(int64_t a, int64_t b);                /* ��չŷ������㷨����Ԫ*/
int64_t   quick_mul(int64_t a, int64_t b, int64_t c);        /* ���ٳ˷� */
int64_t   encrypt(int64_t p, int64_t a,int64_t b,int64_t plaintext);     /* ���ܺ��� */ 
int64_t   decrypt(int64_t ke, int64_t ciphertext, int64_t p, int64_t d);    /* ���ܺ��� */ 

int64_t  ke, sum;        /* ����ke,sumΪȫ�ֱ��� */ 
int main() {
	srand((unsigned)time( NULL ) );          /* ��ʼ������������� */  
	int64_t p, a, d, b, plaintext, i,  km, ciphertext;
	for (int i = 1; i<=20; i++) {

	p = rand() % 4294967296 ;     /* Ϊ֧��2��32λ�ļ��ܣ���4��4294967296���ȡһ����p */ 
	while (is_prime(p) == 0) {
		p++;
	}                           /* ��p��������������p�����ҵ�һ������ */ 
	a = original_root(p);       /* �ҵ���������p��һ��ԭ�� */ 
    d = rand()%(p-4) + 2;       /* ѡ��˽Կ������˽Կ����Ҫ��2 - p-2 ֮�� */ 
	b = quick_pow(a, d, p);           /* ���㹫Կ������*/  
	plaintext = rand() % p ;     /* ���ѡ�����ļ��� */ 
	cout<<i<<"."<<"������Ҫ���ܵ����ģ�"<<plaintext<<endl; 
	ciphertext = encrypt(p, a, b, plaintext);         /* ����Կp�� ���� �º����Ĵ���alice���� */ 
    cout<<"����Ϊ��";
    cout<<ciphertext<<" "<<endl;
    plaintext = decrypt(ke, ciphertext, p, d);        /* ��ke ������ ����bob ���� */ 
    cout<<"����Ϊ��";
    cout<<plaintext<<" "<<endl;
 }
    return 0;
}

bool is_prime(int64_t a)
{
	int64_t d, r, witness;
	d=a-1;
	r=0;
    if (a < 3 && a != 2) /* ����1��2 */
        return false;
    if (a % 2 == 0) /* ����ż�� */
        return false;
    
    while (d % 2 == 0) {   /* ���d��r */ 
        d = d / 2;
        r++;
    }
    for (int i = 0; i <= 50; i++) {      /* ��֤51�� */ 
    	witness = rand()%a-3 + 2;       /* ��֤��ȡ2��n-2 */ 
        int64_t v = quick_pow(witness, d, a); 
        /* ���witness^d��0��˵����witness��a�ı��������witne^d��1��-1��˵���⴮��������һ������1�����ü������� */
        if (v <= 1 || v == a - 1) 
            continue;
        for (int i = 0; i < r; ++i)
        {
            v = v * v % a; 
            if (v ==  - 1 && i != r - 1 ) /* �õ�-1��˵������������1�������˳��� */
            {
                v = 1;
                break;
            }
            /* ����;���ǿ�ͷ�õ�1��ȴû�о���-1��˵��������������y��-1����y^2��1����aһ������������ */
            if (v == 1)  
                return false;
        }
        if (v != 1)   /* �鿴�ǲ�����1��β */
            return false;
    }
    return true;
}

int64_t original_root(int64_t p) {
	int64_t c[p];         /* ����һ������ ������������еĦ�(p) /��(p)�������� */     
	int64_t i, root, sum;
	sum = 0;
    for (i = 2; i < p - 1; i++) {
    	if ((p - 1) % i == 0) {        /* ��� i �� p �����ӣ����ж�i�ǲ������� */ 
    		if (is_prime(i) == 1) {         /* ��� i ���������Ͱ� i ���� ���������飬���ں����lucasԭ����� */ 
    			c[sum] = (p-1) / i;
    			sum++;
    		}
    		}
	}
	
    root = rand()%p + 2;      /*�������2-p������lucas�ж��Ƿ�Ϊԭ�� */ 
    while (lucas(root, c, p) == 0) {    
    	root++;
	}                   /* ���lucas��ⲻ��ԭ��������ѡ��������������ҵ�һ��ԭ�� */ 
     
	 
	return root;
}

bool lucas(int64_t a, int64_t *b,int64_t c){
	int64_t flag, t;      /* ����һ����־�������жϴ����������ǲ���ԭ�� */ 
	flag=1;
	for (int i = 0; i < sum; i++) {
     	t = quick_pow(a, b[i], c);        /* �������������Ӵη� */ 
     	if (t == 1) { 
     		flag = 0;                  /* �������������Ӵη�Ϊ1�� ��ô������Ͳ���ԭ�� */
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
	while (b!=0)       /* ѭ����ֹ���� */ 
	{
		if (b % 2 == 1) {
			r = (r * base) % c;     /* �����λ��������1���ͳ�һ�� */ 
		}
 
		base = (base * base) % c;   /* ��Ȼ��ƽ�� */ 
 
		b = b / 2;     /* ��λ���㣬����һλ */
	}
 
	return r;
}

int64_t find_inverse(int64_t a,int64_t b) {
	
	int64_t ri[50], qi[50], si[50], ti[50];  /* �����ĸ����飬�γ�����ѧ������������� */ 
	
	ri[0] = b;
	ri[1] = a;                   /* ��p��ŷ������ֵ��r0���̶�ti����km mod p��ŷ����������Ԫ */ 
	si[0] = 1;
	si[1] = 0;
	ti[0] = 0;
	ti[1] = 1;
	qi[0] = 0;            /* �ȸ�����ֵ */  
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
	}                     /* һ��һ�м��㣬ֱ��riΪ0Ϊֹ */     
	if(ti[i_t - 2]<0){
		ti[i_t - 2] = ti[i_t - 2] + ri[0];
	}                     
	return ti[i_t - 2];    /* ������Ԫ */ 
}

int64_t quick_mul(int64_t a, int64_t  b, int64_t p) {
    int64_t r;
    r = 0;
    while (b != 0) {      /* �����λ���������� */ 
        if (b % 2 == 1){   /* �����λ��������1���Ͳ��ö���������ֵ */ 
        	r=(r+a)%p;         
		};
        a=(a*2)%p;         /* �����λ��0�� �ͳ�2 */ 
		b=b/2;      /* ��λ */ 
    }
    return r;
}

int64_t encrypt(int64_t p, int64_t a,int64_t b,int64_t plaintext){
	int64_t i,  km, y;
	i = rand()%p-4 + 2;            /*  aliceѡ��������� i */ 
 	ke = quick_pow(a, i, p);       /*  alice����ke */  
	km = quick_pow(b, i, p);       /*  ����km */ 
    y = quick_mul(km, plaintext, p);     /* ʹ�ÿ��ٳ��㷨�������ĵõ�����y */  
    return y;
} 

int64_t decrypt(int64_t ke, int64_t ciphertext, int64_t p, int64_t d) {
	int64_t km, km_inverse, x;
	km = quick_pow(ke, d, p);       /* bob����km */   
	km_inverse = find_inverse(km, p);     /* ʹ����չŷ������㷨�ҵ�km����Ԫ */ 
	x = quick_mul(km_inverse, ciphertext, p);     /* ʹ�ÿ���ƽ���˽�������x */ 
	return x;
}

