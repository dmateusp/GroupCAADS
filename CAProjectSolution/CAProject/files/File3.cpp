/*
This is a copy of file 1 but with:
- modified datatypes and variables
- additional comments
- superfluous code
*/

/*
unnecessary comment
*/

int main() {
	short int yuio = 10;
	while (yuio>0) {
		yuio--;
	}
	return 0;
}

/*
unnecessary comment
*/

int funcNum1() { // comment in same line as code
	signed int qwe = 2;
	long int asd = 3;
	short int lkj = 2;
	bool test = true;
	/*
	unnecessary comment
	unnecessary comment
	unnecessary comment
	*/
	char character = 'a';
	double flo1 = 10.1;

	/*
	Superfluous code begin
	*/
	int i = 0;
	while (i < 1000) {
		i++;
	}
	/*
	Superfluous code end
	*/

	double do1 = 20.2;
	if (qwe == asd) {
		qwe++;
	}

	qwe++;
	qwe += asd;
	qwe--;//unnecessary comment

	qwe = qwe * 5;

	if ((asd == 5) && (qwe == 4) || !test) {
		asd++;
	}
	else {
		asd--;
	}

	/*
	unnecessary comment
	*/


	for (short int iop = 0; iop<10; iop++) {
		asd++;
	}

	do {
		qwe++;
	} while (qwe>100);

	/*
	unnecessary comment
	unnecessary comment
	unnecessary comment
	unnecessary comment
	*/

	if (asd == 300) {
		qwe = 5;
	}

	for (int k = 0; k<10; k++) {
		asd--;
		if (k == 5) continue;
	}


	return 0; /*code before
			  comment
			  */
}

bool funcNum2() {
	return true;
}

char funcNum3() {
	char characterTest = 'a';
	return characterTest;
}

double funcNum4() {
	int lkj = 1;
	int qwe = 0;

	/*
	Superfluous code begin
	*/
	int i = 0;
	while (i < 1000) {
		i++;
	}
	/*
	Superfluous code end
	*/

	switch (lkj) {
	case 1: { qwe = 5; break; }
	case 2: { qwe = 10; break; }
	case 3: {qwe = 15; break; }
	default: qwe = 20;
	}
	return 10.1*qwe;
}