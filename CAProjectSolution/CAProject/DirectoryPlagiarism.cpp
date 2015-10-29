#include "DirectoryPlagiarism.h"
#include <sstream>
DirectoryPlagiarism::~DirectoryPlagiarism()
{
	FilePlagiarism *filePtr;
	// Since we delete the first pointer we loose the ->next, so we need to keep track
	// of the next pointer by using a second pointer
	FilePlagiarism *nextFilePtr;
	for (filePtr = head; filePtr; filePtr = nextFilePtr) {
		nextFilePtr = filePtr->next;
		delete filePtr;
	}
	filePtr, nextFilePtr = nullptr;
}
DirectoryPlagiarism::DirectoryPlagiarism()
{}
DirectoryPlagiarism::DirectoryPlagiarism(std::string dirName) 
	: directoryName(dirName)
{
	head = new FilePlagiarism;
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
			if (pent->d_type != 16384) {
				FilePlagiarism* filePtr = new FilePlagiarism;
				*filePtr = FilePlagiarism(pent->d_name, pent->d_type, directoryName);
				addFile(filePtr);
				filePtr = nullptr;
			}
		}
	}
	calculatePlagiarism();
}
FilePlagiarism * DirectoryPlagiarism::getFileAt(int index)
{
	int i = 0;
	FilePlagiarism* filePtr;
	for (filePtr = head; filePtr && i<index; filePtr = filePtr->next) {
		i++;
	}
	return filePtr;
}
void DirectoryPlagiarism::addFile(FilePlagiarism* fPtr)
{
	FilePlagiarism* filePtr;
	for (filePtr = head; filePtr->next; filePtr=filePtr->next);
	if (head->fileName=="")
		head = fPtr;
	else
		filePtr->next = fPtr;
}
void DirectoryPlagiarism::calculatePlagiarism() {
	int plagiarismIndexesCounter = 0;
	// The first pointer we'll use to grab a file
	FilePlagiarism* firstFilePtr;
	// The second pointer we'll use to compare the first file to another
	FilePlagiarism* secondFilePtr;
	// Takes a file
	for (firstFilePtr = head; firstFilePtr; firstFilePtr = firstFilePtr->next) {
		firstFilePtr->plagiarism = 0;
		// Takes all the other files
		for (secondFilePtr = head; secondFilePtr; secondFilePtr=secondFilePtr->next) {
			// Test if the file compared is not itself
			if (firstFilePtr != secondFilePtr) {
				// First function
				firstFilePtr->plagiarism += firstFilePtr->percentageSameLines(secondFilePtr);
				plagiarismIndexesCounter++;
			}
		}
		// TODO(anyone) we should do some average here
	}
	firstFilePtr, secondFilePtr = nullptr;
}
const std::string DirectoryPlagiarism::getDirectoryName() const {
	return directoryName;
}
std::ostream &operator<<(std::ostream &output,
	const DirectoryPlagiarism &Dir)
{
	output << "--------------------------------------" << std::endl;
	output << "- Path to directory : " << Dir.directoryName << std::endl;
	output << "- Files in directory : " << std::endl;
	FilePlagiarism *filePtr;
	for (filePtr = Dir.head; filePtr; filePtr = filePtr->next) {
		// This answer helped me figuring out how to convert a double to string :
		// http://stackoverflow.com/a/332132
		std::ostringstream stringStream;
		stringStream << filePtr->plagiarism;
		std::string plagiarismToString = stringStream.str();
		output << "- File : " << filePtr->fileName << "| Plagiarism (0 for original, 1 for plagiarized) : " << plagiarismToString << std::endl;
	}
	output << "--------------------------------------" << std::endl;
	output << "Plagiarism detector using a : " << std::endl;
	output << "- Same line detector " << std::endl;
	return output;
}