#pragma once
#ifndef DIRECTORYPLAGIARISM_H
#define DIRECTORYPLAGIARISM_H
#include <string>
#include "dirent.h"
#include "FilePlagiarism.h"
class DirectoryPlagiarism
{
private:
	std::string directoryName;
	FilePlagiarism *head;
	// Adds a file
	void addFile(FilePlagiarism* filePtr);
	// Calculates the average plagiarism for every file
	void calculatePlagiarism();
	// Used in the << operator overriding
	std::string getOutput() const;
public:
	DirectoryPlagiarism();
	// The object created behaves as a list of files
	DirectoryPlagiarism(std::string dirName);
	// The destructor cleans up the memory by deleting the pointers for each node
	virtual ~DirectoryPlagiarism();
	// Returns a pointer to the file at the given index, if the index is outofbounds: returns a nullptr 
	FilePlagiarism* getFileAt(int index);
	/*****************************************************************************************
	* Learned @ http://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm
	* Operator << overloading
	* The code here is a little bit weird,
	* because the operator is not part of the DirectoryPlagiarism class so it could not
	* access the files of our directory because it was not a 'friend of' FilePlagiarism
	* so we are calling a function called 'getOutput()' to get all our information we want
	* to display and then we display it in a neat way using the operator overriding
	*****************************************************************************************/
	friend std::ostream &operator<<(std::ostream &output,
		const DirectoryPlagiarism &Dir);
};
#endif