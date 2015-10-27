#include "FilePlagiarism.h"
#include <fstream>
#include <algorithm>
FilePlagiarism::FilePlagiarism()
{}
FilePlagiarism::FilePlagiarism(std::string flName, int tp, std::string pathToDir)
	: fileName(flName) ,
	type(tp),
	pathToFile(pathToDir + '/' + flName),
	//content(getContent()),
	content(getCleanContent()),
	plagiarism(0),
	next(nullptr)
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

// Clean. LMD
std::string FilePlagiarism::getCleanContent() const
{
	std::ifstream read(pathToFile);
	std::string line;
	std::string content;
	bool isComment = false;
	int posComment = 0;
	while (std::getline(read, line)) {
		// Read lines into content without reading 

		// First for comments // find position of the comment.
		// if it returns a match (!= npos) then isComment TRUE
		// line will be the substring from pos 0 to posComment
		if ((posComment = line.find("//")) != std::string::npos) {
			line = line.substr(0, posComment);
			//isComment = true;
			content += line;
		}
		else if ((posComment = line.find("/*")) != std::string::npos) {
			isComment = true;
		}
		else if ((posComment = line.find("*/")) != std::string::npos) {
			isComment = false;
		}
		else {
			isComment = false;
		}

		if (isComment == false) content += line;		
	}
	read.close();
	// Clean whitespace
	//content.erase(std::remove_if(content.begin(), content.end(), isspace), content.end());		
	return content;
	
}
std::string FilePlagiarism::getFileName() const
{
	return fileName;
}
double FilePlagiarism::percentageSameLines(FilePlagiarism* otherFile)
{
	int linesCounter = 0;
	int sameLinesCounter = 0;
	std::ifstream read(otherFile->pathToFile);
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