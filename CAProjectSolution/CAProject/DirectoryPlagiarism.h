#pragma once
#ifndef CAPROJECTSOLUTION_CAPROJECT_DIRECTORYPLAGIARISM_H_
#define CAPROJECTSOLUTION_CAPROJECT_DIRECTORYPLAGIARISM_H_
/*****************************************************************
*                       Copyright 2015
* <Daniel Mateus Pires x00132886, Luke Michael Dickens x00132785>
*****************************************************************/
#include <string>
#include "./dirent.h"
#include "./FilePlagiarism.h"
class DirectoryPlagiarism {
    /*****************************************************************************************
    * Learned @ http://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm
    * Operator << overloading
    * is friend of DirectoryPlagiarism and FilePlagiarism
    *****************************************************************************************/
    friend std::ostream &operator<<(std::ostream &output,
        const DirectoryPlagiarism &Dir);

 private:
    std::string directoryName;
    FilePlagiarism *head;
    // Adds a file
    void addFile(FilePlagiarism* filePtr);
	int kgram;

 public:
    DirectoryPlagiarism();
    // The object created behaves as a list of files
    DirectoryPlagiarism(std::string dirName, int kgram = 2);
    /****************************************
    * The destructor cleans up the memory
    * by deleting the pointers for each node
    ****************************************/
    virtual ~DirectoryPlagiarism();
    // Returns the directory name
    const std::string getDirectoryName() const;
    /**************************************************
    * Returns a pointer to the file at the given index,
    * if the index is outofbounds: returns a nullptr
    **************************************************/
    FilePlagiarism* getFileAt(int index);
};
#endif  // CAPROJECTSOLUTION_CAPROJECT_DIRECTORYPLAGIARISM_H_
