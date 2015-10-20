#pragma once
#ifndef FILEPLAGIARISM_H
#define FILEPLAGIARISM_H
#include <string>
class FilePlagiarism
{
private:
	std::string fileName;
public:
	FilePlagiarism();
	FilePlagiarism(std::string flName);
	virtual ~FilePlagiarism();
};
#endif