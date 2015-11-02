/*
This code does not do anything it is purely designed to test the plagarism detector
*/
//Some code
/*
multi line
comment1
*/
int main() {
	int i = 10;
	while (i>0) {
		i--;
	}
	return 0;
}

int                     test1() { // comment in same line as code
	int a = 2;
	int b = 3;
	int x = 2;
	bool isBo = true;
	char c = 'a';
	float flo1 = 10.1;
	double do1 = 20.2;
	if (a == b) {
		a++;
	}

	a++;
	a += b;
	a--;
	a = a * 5;

	if ((a == 4) && (b == 5) || !isBo) {
		b++;
	}
	else {
		b--;
	}

	for (int j = 0; j<10; j++) {
		b++;
	}

	do {
		a++;
	} while (a>100);


	if (b == 300) {
		a = 5;
	}

	for (int k = 0; k<10; k++) {
		b--;
		if (k == 5) continue;
	}


	return 0; /*code before
			  comment
			  */
}

bool testBooleanFuncion() {
	return true;
}

char testCharFunction() {
	char c = 'a';
	return c;
}

double testDoubleFunction() {
	int x = 1;
	int a = 0;

	switch (x) {
	case 1: { a = 5; break; }
	case 2: { a = 10; break; }
	case 3: {a = 15; break; }
	default: a = 20;
	}
	return 10.1*a;
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

/* code */
//code