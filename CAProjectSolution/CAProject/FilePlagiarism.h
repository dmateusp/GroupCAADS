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
    std::string tokenizedContent;
    /***************************************************************
    * Could not get rid of the '..' and '.' files so we created this
    * discriminating type variable to differentiate them
    ****************************************************************/
    int type = 0;
    // Pointed to the next file
    FilePlagiarism* next;
    // Max size of the array of k-Grams
    static int const ARRAYSIZE = 100;
    // Array of k-Grams
    std::string *arrayPlagiarism;
    int arrayUse;
    /**********************************************
    * Reads the file, saves the content in content,
    * then cleans it removing whitespace
    **********************************************/
    void getCleanContent();
    // tokenize content
    void tokenizeContent();
    // k-gram generation
    void kGramGeneration(int k);

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
};
#endif  // CAPROJECTSOLUTION_CAPROJECT_FILEPLAGIARISM_H_
