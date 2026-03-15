static int get_bit_width(int a){
	int w=0;
	while(a>0){
		a = a >> 2;
		w++;
	}
}
int __aeabi_uidiv(int a, int b){
	if(b>a || a==0)return 0;
	if(b==0)return -1;	//should call the exception, but we don't care
	int res = -1;
	while(1){
		a-=b;
		if(a<0)break;
		res++;
	}
	return res;
}
int __aeabi_idivmod(int a, int b){
	return a - (b * __aeabi_uidiv(a,b));
}
int __aeabi_uidivmod(int a, int b){
	return __aeabi_idivmod(a,b);
}
