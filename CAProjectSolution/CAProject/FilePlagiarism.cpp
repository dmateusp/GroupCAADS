#include "FilePlagiarism.h"
#include <fstream>
FilePlagiarism::FilePlagiarism()
{}
FilePlagiarism::FilePlagiarism(std::string flName, int tp, std::string pathToDir)
	: fileName(flName) ,
	type(tp),
	pathToFile(pathToDir + '/' + flName),
	content(getContent()),
	plagiarism(0)
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
	read.close();
	return content;
}
std::string FilePlagiarism::getFileName() const
{
	return fileName;
}
double FilePlagiarism::percentageSameLines(FilePlagiarism otherFile)
{
	int linesCounter = 0;
	int sameLinesCounter = 0;
	std::ifstream read(otherFile.pathToFile);
	std::string line;
	while (std::getline(read, line)) {
		linesCounter++;
		if (content.find(line)!=std::string::npos)
			sameLinesCounter++;
	}
	read.close();
	return sameLinesCounter / (double)linesCounter;
}
double FilePlagiarism::getPlagiarism() const
{
	return plagiarism;
}