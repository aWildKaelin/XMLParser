/*
Copyright(c) 2024 , aWildKaelin
All rights reserved.

This source code is licensed under the BSD - style license found in the
LICENSE file in the root directory of this source tree.
*/

#include "XMLReader.h"

//this will eventually become an example, for now I'm keeping it simple because I just wanted to get a repo up
int main()
{
    XMLReader reader;
    reader.fileOpen("test.xml");
    
    reader.accessObject("testfile");

    reader.fileClose();

    return 0;
}
