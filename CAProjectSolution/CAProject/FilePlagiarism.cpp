#include "./FilePlagiarism.h"
#include <ctype.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>
/*****************************************************************
*                       Copyright 2015
* <Daniel Mateus Pires x00132886, Luke Michael Dickens x00132785>
*****************************************************************/
FilePlagiarism::FilePlagiarism()
{}
FilePlagiarism::FilePlagiarism(std::string flName,
                                int tp,
                                std::string pathToDir)
    : fileName(flName) ,
    type(tp),
    pathToFile(pathToDir + '/' + flName),
    content(getCleanContent()),
    plagiarism(0),
    next(nullptr)
{}
FilePlagiarism::~FilePlagiarism()
{}
std::string FilePlagiarism::getContent() const {
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
std::string FilePlagiarism::getCleanContent() const {
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
        if (
            (
                (posComment = line.find("//"))
                != std::string::npos
            )
            && !isComment) {
            line = line.substr(0, posComment);
            content += line;
        }
        /*
        For multi line comments
        Find position of the start of the comment. If it returns a match (!= npos)
        Line to keep will be the substring from pos 0 to posComment
        isComment will remain true until end of comment is found
        */
        else if (
            (
                (posComment = line.find("/*"))
                != std::string::npos
            )
                && !isComment
            ) {
            // May be using multi line comment for single line comment
            if ((posCommentEnd = line.find("*/")) != std::string::npos) {
                isComment = false;
            }
            // no code before comment
            else if (posComment == 0) {
                isComment = true;
            }
            // code before comment
            else {
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
        else if (((posComment = line.find("*/")) != std::string::npos)
                    && isComment) {
            // from the position after the end comment indicator
            line = line.substr(posComment+2);
            content += line;
            isComment = false;
        }
        /*
        If there are no comments on this line
        the line to keep will be the entire line
        */
        else if (!isComment) {
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

    content.erase(
        std::remove_if(
            content.begin(),
            content.end(),
            isspace),
            content.end());

	// Tokenize
	/*
	WE MAY NEED TO CHANGE THE WAY WE CALL THIS!!!
	*/
	content = tokenizeContent(content);
    return content;
}

std::string FilePlagiarism::tokenizeContent(std::string& content) const
{
	/*
	------------------------------------------------------------------
	TOKENIZE
	------------------------------------------------------------------
	*/

	/*
	---
	FUNCTIONS
	---
	*/

	/*
	---
	LOOPS
	---
	*/

	/*
	---
	DATA TYPES
	---
	*/

	// BOOLEAN
	std::regex boole("bool");
	content = std::regex_replace(content, boole, "BOOLEAN");

	// VARCHAR
	std::regex varcha("signedchar|unsignedchar|char");
	content = std::regex_replace(content, varcha, "VARCHAR");

	// VARINT
	std::regex varint("shortint|signedshortint|unsignedshortint|int|signedint|unsignedint|longint|signedlongint|unsignedlongint|longlongint|signedlonglongint|unsignedlonglongint");
	content = std::regex_replace(content, varint, "VARINT");

	// VARFLOAT
	std::regex varflo("float|double|long double");
	content = std::regex_replace(content, varflo, "VARFLOAT");	

	/*
	---
	OPERATORS
	---
	*/

	// Keep loose or strict token set?
	// From more to less complex as first match is chosen

	// RELATIONAL OPERATORS	
	std::regex relOp("==|!=|>=|<=|<|>");
	content = std::regex_replace(content, relOp, "RELATIONALOP");

	// COMPOUND ASSIGNMENT
	/*
	std::regex compAs("+=|-=|*=|/=|%=|>>=|<<=|&=");
	content = std::regex_replace(content, compAs, "COMPOUNDASSIGN");
	*/
	

	// INCREMENT
	/*
	std::regex increm("++");
	content = std::regex_replace(content, increm, "INCREMENT");
	*/

	// DECREMENT
	std::regex decrem("--");
	content = std::regex_replace(content, decrem, "DECREMENT");

	// LOGICAL OPERATORS
	/*
	std::regex log("!|&&|||");
	content = std::regex_replace(content, log, "LOGICALOP");
	*/

	// ARITHMETIC OPERATORS
	/*
	std::regex ariOp("+|-|*|/|%");
	content = std::regex_replace(content, ariOp, "ARITHMETICOP");
	*/

	// ASSIGN
	std::regex assign("=");
	content = std::regex_replace(content, assign, "ASSIGN");
	
	// BEFORE RETURNING CONTENT REMOVE ANYTHING THAT IS not a regex
	return content;
}

std::string FilePlagiarism::getFileName() const {
    return fileName;
}
double FilePlagiarism::percentageSameLines(FilePlagiarism* otherFile) {
    int linesCounter = 0;
    int sameLinesCounter = 0;
    std::ifstream read(otherFile->pathToFile);
    std::string line;
    while (std::getline(read, line)) {
        linesCounter++;
        if (content.find(line) != std::string::npos)
            sameLinesCounter++;
    }
    read.close();
    return sameLinesCounter / static_cast<double>(linesCounter);
}
double FilePlagiarism::getPlagiarism() const {
    return plagiarism;
}
