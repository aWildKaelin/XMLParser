/*
Copyright(c) 2024 , aWildKaelin
All rights reserved.

This source code is licensed under the BSD - style license found in the
LICENSE file in the root directory of this source tree.
*/

#include "XMLReader.h"
#include <iostream>

//most of this will soon be deprecated, but while its here, might as well show it off
int main()
{
    XMLReader reader;
    reader.fileOpen("test.xml");
    
    //XML Trees must contain a root object which contains everything else
    reader.accessBranch("testfile");

    reader.accessBranch("note");

    //every action happens relative to the currently open branch
    //this one returns a value from inside the branch declaration
    std::string s = reader.returnBranchAttribute("index");

    //everything is returned as a string, so numbers must be converted
    std::cout << reader.parseInt(s) << std::endl;

    //this returns from the data from the next branches, will soon be deprecated
    std::cout 
        << reader.returnParameter("from") << '\n'
        << reader.returnParameter("text") << '\n';


    //open the next branch with the same name
    reader.nextBranch();
    std::cout << std::endl;

    //repeat steps from before, just with a different object
    s = reader.returnBranchAttribute("index");

    //this object's index is a float, so I'm using the parseFloat() function
    std::cout << reader.parseFloat(s) << std::endl;

    std::cout
        << reader.returnParameter("from") << '\n'
        << reader.returnParameter("text") << '\n' << '\n';

    //there are only two 'note' branches in this file, so this will error out
    reader.nextBranch();
    //this will place you back in the last successfully opened branch
    std::cout << reader.returnParameter("from") << std::endl;

    //exits the current branch
    //in this case, goes back to root
    reader.closeBranch();

    reader.fileClose();

    return 0;
}
