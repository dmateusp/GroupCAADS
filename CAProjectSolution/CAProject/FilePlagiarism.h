#pragma once
#ifndef FILEPLAGIARISM_H
#define FILEPLAGIARISM_H
#include <string>
class FilePlagiarism
{
	friend class DirectoryPlagiarism;
private:
	std::string fileName = "";
	std::string pathToFile;
	std::string content;
	int type = 0;
	// plagiarism %
	double plagiarism;
	// Reads the file and saves the content in the content member
	std::string getContent() const;
	// Gets the percentage of same lines in two files
	double percentageSameLines(FilePlagiarism otherFile);
public:
	FilePlagiarism();
	FilePlagiarism(std::string flName, int tp, std::string pathToDir);
	virtual ~FilePlagiarism();
	std::string getFileName() const;
	double getPlagiarism() const;
};
#endif