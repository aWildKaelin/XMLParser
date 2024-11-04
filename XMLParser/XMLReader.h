#pragma once
#ifndef XMLREADER_H_
#define XMLREADER_H_


#include <iostream>
/*
Copyright(c) 2024 , aWildKaelin
All rights reserved.

This source code is licensed under the BSD - style license found in the
LICENSE file in the root directory of this source tree.
*/

#include <fstream>
#include <list>

class XMLReader
{
public:
	//only works with properly indented XMLs
	XMLReader();
	~XMLReader();
	void fileOpen(std::string filename);
	void fileClose();

	//opens the first objectName object in the tree
	//returns 0 if successful, otherwise error
	int accessObject(std::string objectName);

	//exits current object
	void closeObject();

	//selects the next instance of the currently open object type
	//returns 0 if successful, otherwise error
	int nextObject();

	//returns a parameter of the object
	std::string returnParameter(std::string parameterName);

	//returns a parameter from the object declaration
	std::string returnObjectParameter(std::string parameterName);

	int parseInt(std::string a);
	float parseFloat(std::string a);

private:
	std::ifstream in;

	char buffer[1024] = { ' ' };
	uint32_t readHead = 0;

	int tabCount = 0;

	std::list<uint32_t> objectStack;
	std::list<std::string> objectNames;
};
#endif // !XMLREADER_H_


//filebuf is the internal class that actually does the reading, worth looking into

//get(dest, size, optional delimiter) places characetrs into dest until size is met or line end is encountered
//getline(dest, size, optional delimiter) does the same except it discards the '\0' line end
//read(dest, n) places n characters into dest without caring about line ends
//peek() gets the next character without advancing the read head

//unget() moves the read head back by one character
//seekg(int pos) moves the read head to the specified pos relative to beginning
//tellg() returns current read head pos
//gcount() returns number of characters extracted by last read operation


//void accessObject(string objectName) //opens next objectName object in the tree
//void closeObject() //exits current object object
//string returnParameter(string parameterName) //returns a parameter of the object
//string returnObjectParameter(string parameterName) //returns a parameter from the object declaration
