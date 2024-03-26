#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

typedef int           int32_t;
typedef long long int int64_t;

bool      is_prime(int64_t a);              /* Miller-Rabin���Բ��� */
int64_t   original_root(int64_t a);              /* �ҳ�ԭ�� */ 
bool      lucas(int64_t a, int64_t *b,int64_t c);        /* lucasԭ����� */
int64_t   quick_pow(int64_t a, int64_t b, int64_t c);    /* ����ƽ�����㷨 */

int64_t  sum;            /* ����sumΪȫ�ֱ��� */ 
int main() {
	srand((unsigned)time( NULL ) );          /* ��ʼ������������� */
	for (int i = 1; i <= 20; i++) {
	int64_t p, p_root, a, A, kab_alice, kab_bob, b, B;
	p = rand() % 4294967296;
	while (is_prime(p) == 0){
		p++;
	}
	p_root = original_root(p);         /*  Լ������p��p��һ��ԭ�� */ 
	a = rand() % (p - 4) + 2;          /* alice��2��p-2ѡ��˽Կa */ 
	A = quick_pow(p_root, a, p);       /* alice���㹫ԿA */ 
	b = rand() % (p - 4) + 2;          /* BObѡ��˽Կb */ 
	B = quick_pow(p_root, b, p);       /* bob���㹫ԿB */
	kab_alice = quick_pow(B, a, p);    /* alice����Ự��Կkab */ 
	kab_bob = quick_pow(A, b, p);      /* bob����Ự��Կkab */ 
	if (kab_alice == kab_bob) {        /* ��������Ự��Կ��ȣ���Կ�����ɹ� */ 
		cout<<i<<"."<<"��Կ�����ɹ�"<<endl; 
		cout<<"�Ự��ԿΪ��"<<kab_alice<<endl; 
	}
	else {
		cout<<"��Կ����ʧ��"<<endl; 
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
            if (v ==  - 1 && i != r - 1) /* �õ�-1��˵������������1�������˳��� */
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
    			c[sum] = p / i;
    			sum++;
    		}
    		}
	}
	
    root = rand()%p + 2;      /*�������2-p������lucas�ж��Ƿ�Ϊԭ�� */ 
    while (lucas(root, c, p) == 0) {    
    	root++;
	}                   /* ���lucas��ⲻ��ԭ��������ѡ��������������ҵ�һ��ԭ�� */ 
     //cout<<root<<" "<<endl;
	 
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
