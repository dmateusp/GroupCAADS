#include "FilePlagiarism.h"
#include <fstream>
#include <algorithm>
#include <ctype.h>
FilePlagiarism::FilePlagiarism()
{}
FilePlagiarism::FilePlagiarism(std::string flName, int tp, std::string pathToDir)
    : fileName(flName) ,
    type(tp),
    pathToFile(pathToDir + '/' + flName),
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

// LMD
std::string FilePlagiarism::getCleanContent() const
{
    std::ifstream read(pathToFile);
    std::string line;
    std::string content;
    bool isComment = false;
    int posComment = 0;
    int posCommentEnd = 0;
    while (std::getline(read, line)) {
        /*
        ------------------------------------------------------------------
        CLEAN
        ------------------------------------------------------------------
        */

        /*
        ---
        Remove all comments
        ---
        */

        /*
        For single line comments
        Find position of the comment. If it returns a match (!= npos)
        Line to keep will be the substring from pos 0 to posComment
        */
        if (((posComment = line.find("//")) != std::string::npos) && isComment == false) {
            line = line.substr(0, posComment);
            content += line;
        }
        /*
        For multi line comments
        Find position of the start of the comment. If it returns a match (!= npos)
        Line to keep will be the substring from pos 0 to posComment
        isComment will remain true until end of comment is found
        */
        else if (((posComment = line.find("/*")) != std::string::npos)&& isComment==false) {
            //May be using multi line comment for single line comment		
            if ((posCommentEnd = line.find("*/")) != std::string::npos) {
                isComment = false;
            }
            // no code before comment
            else if (posComment == 0) {
                isComment = true;
            }
            // code before comment
            else{
                line = line.substr(0, posComment);
                content += line;
                isComment = true;
            }
        }
        /*
        For multi line comments
        Find position of the end of the comment. If it returns a match (!= npos)
        Line to keep will be the substring from posComment to end of string
        isComment is now false
        */
        else if (((posComment = line.find("*/")) != std::string::npos) && isComment == true) {
            line = line.substr(posComment+2); // from the position after the end comment indicator
            content += line;
            isComment = false;
        }
        /*
        If there are no comments on this line
        the line to keep will be the entire line
        */
        else if (isComment==false) {
            content += line;
            isComment = false;
        }
        /*
        In between start multi line comment and end of multi line comment
        isComment == true then read next line. Not added to comment. No further actions.
        */
    }

    read.close();

    /*
    ---
    Remove whitespace
    ---
    */

    content.erase(std::remove_if(content.begin(), content.end(), isspace), content.end());

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