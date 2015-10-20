#include "DirectoryPlagiarism.h"
DirectoryPlagiarism::DirectoryPlagiarism()
{}
DirectoryPlagiarism::DirectoryPlagiarism(std::string dirName) 
	: directoryName(dirName)
{
	// We need a pointer to the directory
	DIR *dirPtr = NULL;
	// Now something to read the directory
	struct dirent *pent;
	// We use c_str() to convert the string into a const char*
	dirPtr = opendir(dirName.c_str());
	// Test if the directory has been found
	if (!dirPtr) {
		// Directory not found
		throw 25;
	}
	while (pent == readdir(dirPtr)) {
		if (!pent) {
			// Reading error
			throw 26;
		}
	}
}
DirectoryPlagiarism::~DirectoryPlagiarism()
{}
