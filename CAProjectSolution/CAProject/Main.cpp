/*****************************************************************
*                       Copyright 2015
* <Daniel Mateus Pires x00132886, Luke Michael Dickens x00132785>
*****************************************************************/
#include <iostream>
#include "./DirectoryPlagiarism.h"
int main() {
    // The files are in ./files/[fileName]
    DirectoryPlagiarism dir("./files");
    std::cout << dir;
    /**************************************
    * this function (getFileAt) is actually
    * not used in our code but we thought
    * that it was the kind of generic
    * functionnality a developer would
    * expect if he used our code
    **************************************/
    // FilePlagiarism* fptr=dir.getFileAt(4);
    system("pause");
    return 0;
}
