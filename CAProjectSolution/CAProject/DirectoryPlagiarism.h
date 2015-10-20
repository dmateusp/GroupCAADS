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
	FilePlagiarism files[];
public:
	DirectoryPlagiarism();
	DirectoryPlagiarism(std::string dirName);
	virtual ~DirectoryPlagiarism();
};
#endif