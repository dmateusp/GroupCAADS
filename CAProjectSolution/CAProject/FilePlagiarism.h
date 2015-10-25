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
	/***************************************************************
	* Could not get rid of the '..' and '.' files so we created this
	* discriminating type variable to differentiate them
	****************************************************************/
	int type = 0;
	// plagiarism %
	double plagiarism;
	FilePlagiarism* next;
	// Reads the file and saves the content in the content member
	std::string getContent() const;
	// Gets the percentage of same lines in two files
	double percentageSameLines(FilePlagiarism* otherFile);
public:
	FilePlagiarism();
	FilePlagiarism(std::string flName, int tp, std::string pathToDir);
	/****************************************************
	* Actually the DirectoryPlagiarism acts like a list
	* and destructs all the nodes (FilePlagiarism)
	****************************************************/
	virtual ~FilePlagiarism();
	// returns the file name
	std::string getFileName() const;
	// returns the plagiarism index (between 0 and 1)
	double getPlagiarism() const;
};
#endif