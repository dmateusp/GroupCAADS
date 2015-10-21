#include "DirectoryPlagiarism.h"
#include <iostream>
int main() {
	// The files are in ./files/[fileName]
	DirectoryPlagiarism dir("./files");
	std::cout << dir;
	system("pause");
	return 0;
}