#include "DirectoryPlagiarism.h"
#include <iostream>
int main() {
	// The files are in ./files/[fileName]
	DirectoryPlagiarism dir("./files");
	std::cout << dir;
	/**************************************
	* this function (getFileAt) is actually
	* not used in our code but we thought
	* that it was the kind of generic
	* functionnality a developer would
	* expect if he used our code
	**************************************/
	//FilePlagiarism* fptr=dir.getFileAt(4);
	system("pause");
	return 0;
}