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
	int type = 0;
	// 0 to 10
	int indexOfPlagiarism = 0;
public:
	FilePlagiarism();
	FilePlagiarism(std::string flName, int tp, std::string pathToDir);
	virtual ~FilePlagiarism();
	std::string getContent() const;
	std::string getFileName() const;
};
#endif