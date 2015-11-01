//this file is the same as file 2
//Some code
/*
multi line
comment1 
*/
int main(a& s*){
	int i=10;
while (i>0) {
	i--;
}	
return 0;
}

int                     test1(){ // comment in same line as code
	int a = 2;
	int b = 3;
	int x = 2;
	bool isBo = true;	
	char c = 'a';
	float flo1 = 10.1;
	double do1 = 20.2;
	if (a == b){
		a++;
	}
	
	a++;
	a += b;
	a--;
	a = a*5;
	
	if ((a == 4) && (b==5) || !isBo){
		b++;
	}
	else {
		b--;
	}
	
	for (int j=0;j<10;j++){
		b++;
	}
	
	do {
		a++;
	}
	while (a>100);
	
	
	if (b==300){
		break;
	}
	
	for (int k=0; k<10; k++){
		b--;
		if (k==5) continue;
	}
	
	
	return 0; /*code before
	comment
	*/
}

bool testBooleanFuncion(){
	return true;
}

char testCharFunction(){
	return a;
}

double testDoubleFunction(){
	return 10.1;
}

switch (x){
	case 1: a=5;
	case 2: a=10;
	case 3: a=15;
	default: a =20;	
}
/*
multi line
comment2
*/
//line3
//line2
//code
//code
//if (/* condition */)
{
	/* code */
}
//code