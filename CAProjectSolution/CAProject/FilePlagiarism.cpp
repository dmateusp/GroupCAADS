#include "./FilePlagiarism.h"
#include <ctype.h>
#include <regex>
#include <string>
#include <algorithm>
#include <fstream>
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
    next(nullptr),
    arrayUse(0)
{
    arrayPlagiarism = new std::string[ARRAYSIZE];
    getCleanContent();
	tokenizeContent();
	kGramGeneration(3);
}
FilePlagiarism::~FilePlagiarism()
{}
const int FilePlagiarism::ARRAYSIZE;
// LMD
void FilePlagiarism::getCleanContent() {
    std::ifstream read(pathToFile);
    std::string line;
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
            tokenizedContent += line;
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
                tokenizedContent += line;
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
            tokenizedContent += line;
            isComment = false;
        }
        /*
        If there are no comments on this line
        the line to keep will be the entire line
        */
        else if (!isComment) {
            tokenizedContent += line;
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

    tokenizedContent.erase(
        std::remove_if(
            tokenizedContent.begin(),
            tokenizedContent.end(),
            isspace),
            tokenizedContent.end());
}

/*
------------------------------------------------------------------
TOKENIZE
------------------------------------------------------------------
*/
void FilePlagiarism::tokenizeContent() {
    /*
    ---
    FUNCTIONS
    ---
    */
    // MAIN
    std::regex mainFunc("intmain\\([a-zA-Z0-9&*]*\\)\\{|voidmain\\([a-zA-Z0-9&*]*\\)\\{");
    tokenizedContent = std::regex_replace(tokenizedContent, mainFunc, "#MAIN$");

    // BOOLFUNC
    std::regex boolFunc("bool[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{");
    tokenizedContent = std::regex_replace(tokenizedContent, boolFunc, "#BOOLFUNC$");

    // CHARFUNC
    std::regex charFunc("signedchar[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|unsignedchar[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|char[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{");
    tokenizedContent = std::regex_replace(tokenizedContent, charFunc, "#CHARFUNC$");

    // INTFUNC
    std::regex intFunc("shortint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|signedshortint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|unsignedshortint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|int[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|signedint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|unsignedint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|longint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|signedlongint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|unsignedlongint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|longlongint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|signedlonglongint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|unsignedlonglongint[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{");
    tokenizedContent = std::regex_replace(tokenizedContent, intFunc, "#INTFUNC$");

    // FLOATFUNC
    std::regex floFunc("float[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|double[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{|long double[a-zA-Z0-9&*]*\\([a-zA-Z0-9&*]*\\)\\{");
    tokenizedContent = std::regex_replace(tokenizedContent, floFunc, "#FLOATFUNC$");

    /*
    ---
    FLOW CONTROL
    ---
    */

    // IF
    std::regex flowIf("if\\(");
    tokenizedContent = std::regex_replace(tokenizedContent, flowIf, "#IF$");

    // ELSE
    std::regex flowElse("else");
    tokenizedContent = std::regex_replace(tokenizedContent, flowElse, "#ELSE$");

    // FOR LOOP
    std::regex forLoop("for\\(");
    tokenizedContent = std::regex_replace(tokenizedContent, forLoop, "#FORLOOP$");

    // WHILE LOOP
    std::regex whileLoop("while\\(");
    tokenizedContent = std::regex_replace(tokenizedContent, whileLoop, "#WHILELOOP$");

    // DO
    std::regex flowDo("do\\{");
    tokenizedContent = std::regex_replace(tokenizedContent, flowDo, "#DO$");

    // BREAK
    std::regex flowBreak("break\\;");
    tokenizedContent = std::regex_replace(tokenizedContent, flowBreak, "#BREAK$");

    // CONTINUE
    std::regex flowContinue("continue\\;");
    tokenizedContent = std::regex_replace(tokenizedContent, flowContinue, "#CONTINUE$");

    // SWITCH
    std::regex flowSwitch("switch\\([a-zA-Z0-9]*\\)\\{");
    tokenizedContent = std::regex_replace(tokenizedContent, flowSwitch, "#SWITCH$");

    // CASE
    std::regex flowCase("case[a-zA-Z0-9]*\\:");
    tokenizedContent = std::regex_replace(tokenizedContent, flowCase, "#CASE$");

    /*
    ---
    IO
    ---
    */

    // No regex included. Does not affect logic.

    /*
    ---
    VARIABLES
    ---
    */    
    // VARBOOL
    std::regex boole("bool");
    tokenizedContent = std::regex_replace(tokenizedContent, boole, "#VARBOOL$");

    // VARCHAR
    std::regex varcha("signedchar|unsignedchar|char");
    tokenizedContent = std::regex_replace(tokenizedContent, varcha, "#VARCHAR$");

    // VARINT
    std::regex varint("shortint|signedshortint|unsignedshortint|int|signedint|unsignedint|longint|signedlongint|unsignedlongint|longlongint|signedlonglongint|unsignedlonglongint");
    tokenizedContent = std::regex_replace(tokenizedContent, varint, "#VARINT$");

    // VARFLOAT
    std::regex varflo("float|double|longdouble");
    tokenizedContent = std::regex_replace(tokenizedContent, varflo, "#VARFLOAT$");

    /*
    ---
    OPERATORS
    ---
    */
    // From more to less complex as first match is chosen

    // RELATIONAL OPERATORS
    std::regex relOp("\\==|\\!=|\\>=|\\<=|\\<|\\>");
    tokenizedContent = std::regex_replace(tokenizedContent, relOp, "#RELATIONALOP$");

    // COMPOUND ASSIGNMENT
    std::regex compAs("\\+=|\\-=|\\*=|\\/=|\\%=|\\>>=|\\<<=|\\&=");
    tokenizedContent = std::regex_replace(tokenizedContent, compAs, "#COMPOUNDASSIGN$");

    // INCREMENT
    std::regex increm("\\++");
    tokenizedContent = std::regex_replace(tokenizedContent, increm, "#INCREMENT$");

    // DECREMENT
    std::regex decrem("\\--");
    tokenizedContent = std::regex_replace(tokenizedContent, decrem, "#DECREMENT$");

    // LOGICAL OPERATORS
    /*
    std::regex log("\\!|\\&&|\\||");
    tokenizedContent = std::regex_replace(tokenizedContent, log, "LOGICALOP");
    */

    // ARITHMETIC OPERATORS
    std::regex ariOp("\\+|\\-|\\*|\\/|\\%");
    tokenizedContent = std::regex_replace(tokenizedContent, ariOp, "#ARITHMETICOP$");

    // ASSIGN
    std::regex assign("=");
    tokenizedContent = std::regex_replace(tokenizedContent, assign, "#ASSIGN$");

    // BEFORE RETURNING tokenizedContent REMOVE ANYTHING THAT IS not a regex
    /*
    std::regex rem("([^$]*)\\$(.*)[^#]*\\#");
    tokenizedContent = std::regex_replace(tokenizedContent, rem, "");
    
    std::regex rem("(?!\$)((.)+)(?=\#)");
    tokenizedContent = std::regex_replace(tokenizedContent, rem, "");
        
    std::regex rem("(?!\$)[a-zA-Z0-9](?=\#)");
    tokenizedContent = std::regex_replace(tokenizedContent, rem, "");
    
    std::regex rem("(?!\$).+(?=\#)");
    tokenizedContent = std::regex_replace(tokenizedContent, rem, "");

    std::regex rem2("$\W+#");
    tokenizedContent = std::regex_replace(tokenizedContent, rem2, "");	
    
    std::regex remSemiColon("[;]*");
    tokenizedContent = std::regex_replace(tokenizedContent, remSemiColon, "");
    std::regex remBrackets("[{]|[}]");
    tokenizedContent = std::regex_replace(tokenizedContent, remBrackets, "");
    std::regex rem("[']|[']");%
    tokenizedContent = std::regex_replace(tokenizedContent, remBrackets, "");
    */
}
void FilePlagiarism::kGramGeneration(const int k) {
    // kGram index
    int kGramIndex = 0;
    // number of tokens found
    int t = 0;
    // index of first token of this sequence
    int nextSequence = 0;
    // Finding all the tokens and adding them to the k-Gram array
    for (int j = tokenizedContent.find("#");
            j < tokenizedContent.length();
            j = tokenizedContent.find("#", j+1)) {
        if (t == k) {
            kGramIndex++;
            j = nextSequence;
            t = 0;
        } else {
            arrayPlagiarism[kGramIndex] = arrayPlagiarism[kGramIndex]
                        + tokenizedContent.substr(
                            j + 1,
                            (tokenizedContent.find('$', j) - j) - 1);
            if (t) {
                nextSequence = j;
            }
            t++;
        }
    }
    arrayUse = kGramIndex;
    /***************************************************
    * Gets a k-Gram,
    * if it occurs more than once in the array
    * deletes the other occurences
    * and keeps a track of the number of times
    * it occured. Then changes the array from
    * K-GRAMAK-GRAMBK-GRAMC to
    * K-GRAMAK-GRAMBK-GRAMC : [INT number of occurences]
    ***************************************************/
    for (int i = 0; arrayPlagiarism[i] != ""; i++) {
        // Counter for number of times a kGram occurs
        int n = 1;
        for (int j = 0; arrayPlagiarism[j] != ""; j++) {
            if (j != i) {
                if (!arrayPlagiarism[i].compare(arrayPlagiarism[j])) {
                    arrayPlagiarism[j] = arrayPlagiarism[arrayUse];
                    arrayPlagiarism[arrayUse] = "";
                    arrayUse--;
                    j--;
                    n++;
                }
            }
        }
        arrayPlagiarism[i] += " : " + std::to_string(n);
    }
}
std::string FilePlagiarism::getFileName() const {
    return fileName;
}
