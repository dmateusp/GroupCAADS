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
				addFile(FilePlagiarism(pent->d_name, pent->d_type, directoryName));
		}
	}
	calculatePlagiarism();
}
FilePlagiarism DirectoryPlagiarism::getFileAt(int index)
{
	if (index >= size)
		// Index out of bounds
		throw 28;
	return files[index];
}
DirectoryPlagiarism::~DirectoryPlagiarism()
{
}
void DirectoryPlagiarism::addFile(FilePlagiarism file)
{
	int i = 0;
	for (; i < size && files[i].fileName != ""; i++);
	if (i == size) // Means the array is full
		return;
	files[i] = file;
}
void DirectoryPlagiarism::calculatePlagiarism() {
	int plagiarismIndexesCounter = 0;
	for (int i = 0; i < size && files[i].fileName != ""; i++) {
		files[i].plagiarism = 0;
		for (int j = i+1; j < size && files[j].fileName != ""; j++) {
			files[i].plagiarism += files[i].percentageSameLines(files[j]);
			plagiarismIndexesCounter++;
		}
		files[i].plagiarism /= plagiarismIndexesCounter;
	}
}
std::ostream &operator<<(std::ostream &output,
	const DirectoryPlagiarism &Dir)
{
	output << "--------------------------------------" << std::endl;
	output << "- Path to directory : " << Dir.directoryName << std::endl;
	output << "- Files in directory : " << std::endl;
	for (int i = 0; Dir.files[i].getFileName() != ""; i++)
		output << "- File " << i + 1 << " : " << Dir.files[i].getFileName() << "| Plagiarism : " << Dir.files[i].getPlagiarism() << std::endl;
	output << "--------------------------------------" << std::endl;
	return output;
}