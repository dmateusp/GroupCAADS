#pragma once
#ifndef FILEPLAGIARISM_H
#define FILEPLAGIARISM_H
#include <string>
class FilePlagiarism
{
	friend class DirectoryPlagiarism;
private:
	std::string fileName = "";
	int type = 0;
public:
	FilePlagiarism();
	FilePlagiarism(std::string flName, int tp);
	virtual ~FilePlagiarism();
};
#endif