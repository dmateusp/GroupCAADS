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
public:
	DirectoryPlagiarism();
	DirectoryPlagiarism(std::string dirName);
	virtual ~DirectoryPlagiarism();
	void addFile(FilePlagiarism file);
};
#endif