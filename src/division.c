jstatic int get_bit_width(int a){
	int w=0;
	while(a>0){
		a = a >> 2;
		w++;
	}
}
unsigned int __aeabi_uidiv(unsigned int a, unsigned int b){
	if(b>a || a==0)return 0;
	if(b==0)return -1;	//should call the exception, but we don't care
	int res = 0;
	while(1){
		if(a-b > a)break;
		a-=b;
		res++;
	}
	return res;
}
int __aeabi_idiv(int a, int b){
	unsigned int abs_a, abs_b;
	int res;
	abs_a = a>0? a : ~(a-1);
	abs_b = b>0? b : ~(b-1);

	res = __aeabi_uidiv(abs_a, abs_b);
	if(a <0 ^ b<0)res *= -1;
	return res;
}
int __aeabi_idivmod(int a, int b){
	return a - (b * __aeabi_idiv(a,b));
}
unsigned int __aeabi_uidivmod(unsigned int a, unsigned int b){
	return a - (b * __aeabi_uidiv(a,b));
}
