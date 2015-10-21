#include "FilePlagiarism.h"
#include <fstream>
FilePlagiarism::FilePlagiarism()
{}
FilePlagiarism::FilePlagiarism(std::string flName, int tp, std::string pathToDir)
	: fileName(flName) ,
	type(tp),
	pathToFile(pathToDir + '/' + flName)
{}
FilePlagiarism::~FilePlagiarism()
{}
std::string FilePlagiarism::getContent() const
{
	std::ifstream read(pathToFile);
	std::string line;
	std::string content;
	while (std::getline(read, line)) {
		content += line;
	}
	return content;
}
std::string FilePlagiarism::getFileName() const
{
	return fileName;
}