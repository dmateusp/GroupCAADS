/*****************************************************************
*                       Copyright 2015
* <Daniel Mateus Pires x00132886, Luke Michael Dickens x00132785>
*****************************************************************/
#include <iostream>
#include "./DirectoryPlagiarism.h"
int main() {
    // The files are in ./files/[fileName]
    unsigned int kgram = 0;
    do {
        std::cout << "/*****************************************************************************************/" << std::endl;
        std::cout << "* enter a k-Gram value" << std::endl;
        std::cout << "* k-Gram : ( from 2 to 50, the higher the value the more complex the sequences will be )" << std::endl;
        std::cout << "* -If you're not familiar with k-Grams enter 3-\n : ";
        std::cin >> kgram;
    } while(kgram < 2 || kgram > 50);
    DirectoryPlagiarism dir("./files",kgram);
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
