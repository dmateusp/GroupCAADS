#include "DirectoryPlagiarism.h"
DirectoryPlagiarism::DirectoryPlagiarism()
{}
DirectoryPlagiarism::DirectoryPlagiarism(std::string dirName) 
	: directoryName(dirName)
{
	// We need a pointer to the directory
	DIR *dirPtr = NULL;
	// Now something to read the directory
	struct dirent *pent = NULL;
	// We use c_str() to convert the string into a const char*
	dirPtr = opendir(dirName.c_str());
	// Test if the directory has been found
	if (!dirPtr) {
		// Directory not found
		throw 25;
	}
	while (pent = readdir(dirPtr)) {
		if (!pent) {
			// Reading error
			throw 26;
		}
		else {
			// Does not take the directory '.' and '..'
			if(pent->d_type != 16384)
				addFile(FilePlagiarism(pent->d_name, pent->d_type));
		}
	}
}
DirectoryPlagiarism::~DirectoryPlagiarism()
{
	delete[] files;
}
void DirectoryPlagiarism::addFile(FilePlagiarism file)
{
	int i = 0;
	for (; i < size && files[i].fileName != ""; i++);
	if (i == size) // Means the array is full
		return;
	files[i] = file;
}