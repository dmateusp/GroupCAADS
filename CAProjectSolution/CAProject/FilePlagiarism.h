#pragma once
#ifndef CAPROJECTSOLUTION_CAPROJECT_FILEPLAGIARISM_H_
#define CAPROJECTSOLUTION_CAPROJECT_FILEPLAGIARISM_H_
/*****************************************************************
*                       Copyright 2015
* <Daniel Mateus Pires x00132886, Luke Michael Dickens x00132785>
*****************************************************************/
#include <string>
class FilePlagiarism {
    friend class DirectoryPlagiarism;
    /*****************************************************************************************
    * Learned @ http://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm
    * Operator << overloading
    * is friend of DirectoryPlagiarism and FilePlagiarism
    *****************************************************************************************/
    friend std::ostream &operator<<(std::ostream &output,
        const DirectoryPlagiarism &Dir);

 private:
    std::string fileName = "";
    std::string pathToFile;
    std::string content;
    /***************************************************************
    * Could not get rid of the '..' and '.' files so we created this
    * discriminating type variable to differentiate them
    ****************************************************************/
    int type = 0;
    // plagiarism %
    double plagiarism;
    FilePlagiarism* next;
    // Reads the file and saves the content in the content member
    std::string getContent() const;
    /**********************************************
	* Reads the file, saves the content in content,
	* then cleans it removing whitespace
	**********************************************/
    std::string getCleanContent() const;
	// tokenize content
	std::string tokenizeContent(std::string& content) const;	
    // Gets the percentage of same lines in two files
    double percentageSameLines(FilePlagiarism* otherFile);

 public:
    FilePlagiarism();
    FilePlagiarism(std::string flName, int tp, std::string pathToDir);
    /****************************************************
    * Actually the DirectoryPlagiarism acts like a list
    * and destructs all the nodes (FilePlagiarism)
    ****************************************************/
    virtual ~FilePlagiarism();
    // returns the file name
    std::string getFileName() const;
    // returns the plagiarism index (between 0 and 1)
    double getPlagiarism() const;
};
#endif  // CAPROJECTSOLUTION_CAPROJECT_FILEPLAGIARISM_H_
