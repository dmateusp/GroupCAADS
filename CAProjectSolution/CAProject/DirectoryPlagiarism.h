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
	FilePlagiarism files[10];
	int size = 10;
	// Adds a file
	void addFile(FilePlagiarism file);
	// Calculates the average plagiarism for every file
	void calculatePlagiarism();
public:
	DirectoryPlagiarism();
	DirectoryPlagiarism(std::string dirName);
	virtual ~DirectoryPlagiarism();
	// Return file at index
	FilePlagiarism getFileAt(int index);
	// Learned @ http://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm
	// Operator << overloading
	friend std::ostream &operator<<(std::ostream &output,
		const DirectoryPlagiarism &Dir);
};
#endif