/*****************************************************************
*                       Copyright 2015
* <Daniel Mateus Pires x00132886, Luke Michael Dickens x00132785>
*****************************************************************/
#include "./DirectoryPlagiarism.h"
#include <sstream>
#include <string>
DirectoryPlagiarism::~DirectoryPlagiarism() {
    FilePlagiarism *filePtr;
    /******************************************************
    * Since we delete the first pointer we loose the ->next, 
    * so we need to keep track
    * of the next pointer by using a second pointer
    ******************************************************/ 
    FilePlagiarism *nextFilePtr;
    for (filePtr = head; filePtr; filePtr = nextFilePtr) {
        nextFilePtr = filePtr->next;
        delete[] filePtr->arrayPlagiarism;
        delete filePtr;
    }
    filePtr, nextFilePtr = nullptr;
}
DirectoryPlagiarism::DirectoryPlagiarism()
{}
DirectoryPlagiarism::DirectoryPlagiarism(std::string dirName, int kgr)
    : directoryName(dirName),
	kgram(kgr){
	if (kgram < 2)
		kgram = 2;
    head = new FilePlagiarism;
    // We need a pointer to the directory
    DIR *dirPtr = NULL;
    // Now something to read the directory
    struct dirent *pent = NULL;
    // We use c_str() to convert the string into a const char*
    dirPtr = opendir(dirName.c_str());
    // Test if the directory has been found
    if (!dirPtr) {
        // Directory not found
        throw 25;
    }
    while (pent = readdir(dirPtr)) {
        if (!pent) {
            // Reading error
            throw 26;
        } else {
            // Does not take the directory '.' and '..'
            if (pent->d_type != 16384) {
                FilePlagiarism* filePtr = new FilePlagiarism;
                *filePtr = FilePlagiarism(
                                pent->d_name,
                                pent->d_type,
                                directoryName,
								kgram);
                addFile(filePtr);
                filePtr = nullptr;
            }
        }
    }
}
FilePlagiarism * DirectoryPlagiarism::getFileAt(int index) {
    int i = 0;
    FilePlagiarism* filePtr;
    for (filePtr = head; filePtr && i < index; filePtr = filePtr->next) {
        i++;
    }
    return filePtr;
}
void DirectoryPlagiarism::addFile(FilePlagiarism* fPtr) {
    FilePlagiarism* filePtr;
    for (filePtr = head; filePtr->next; filePtr = filePtr->next) continue;
    if (head->fileName == "")
        head = fPtr;
    else
        filePtr->next = fPtr;
}
const std::string DirectoryPlagiarism::getDirectoryName() const {
    return directoryName;
}
std::ostream &operator<<(std::ostream &output,
    const DirectoryPlagiarism &Dir) {
    output << "--------------------------------------" << std::endl;
    output << "- Path to directory : " << Dir.directoryName << std::endl;
    output << "- Files in directory : " << std::endl;
    FilePlagiarism *filePtr;
    for (filePtr = Dir.head; filePtr; filePtr = filePtr->next) {
        output << "- File : "
            << filePtr->fileName
            << std::endl;
        for (int i = 0; i <= filePtr->arrayUse; i++) {
            output << filePtr->arrayPlagiarism[i];
            output << std::endl;
        }
        output << std::endl;
    }
    output << "--------------------------------------" << std::endl;
    output << "How the plagiarism detector works : " << std::endl;
    output << "- Gets the raw content from the file" << std::endl;
    output << "- Cleans the content" << std::endl;
    output << "- Tokenizes the content" << std::endl;
    output << "- Divides the content into k-Grams" << std::endl;
    output << "- Counts the occurences for each k-Gram" << std::endl;
    return output;
}
