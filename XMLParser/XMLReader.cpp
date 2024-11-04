/*
Copyright(c) 2024 , aWildKaelin
All rights reserved.

This source code is licensed under the BSD - style license found in the
LICENSE file in the root directory of this source tree.
*/

#include "XMLReader.h"

XMLReader::XMLReader()
{
	this->objectStack = std::list<uint32_t>();
	this->objectNames = std::list<std::string>();
}

XMLReader::~XMLReader()
{
	in.close();
}

void XMLReader::fileOpen(std::string filename)
{
	this->in.open(filename);
}

void XMLReader::fileClose()
{
	this->in.close();
}


int XMLReader::accessObject(std::string objectName)
{
	int readHead = 0;

	bool search = true;

	int currentTabCount = 0;
	while (search)
	{
		std::string returnString = "";

		//move read head to remove spaces
		char temp = in.get();
		if (temp == '<')
		{
			search = false;
			readHead = in.tellg();
		}
		else if(temp == '\t')
		{
			currentTabCount++;
		}

		if (!search)
		{
			//until end of string
			while (in.peek() != '>' && in.peek() != ' ')
			{
				returnString += in.get();
			}

			//just a safety check to avoid read access violation
			if (objectNames.size() > 0)
			{
				//if end of currently open object, error
				if (returnString == "/" + objectNames.back() && currentTabCount == tabCount)
				{
					std::cout << "XMLReader error: end of object" << std::endl;
					search = false;
					return -1;
				}
			}

			if (returnString == objectName)
			{
				objectStack.push_back(readHead);
				objectNames.push_back(objectName);
				in.seekg(objectStack.back());
				if (objectNames.size() != 1)
				{
					tabCount++;
				}
				return 0;
			}
			else
			{
				in.getline(buffer, 1024);
				search = true;
			}
		}
	}
}


void XMLReader::closeObject()
{
	objectStack.pop_back();
	objectNames.pop_back();
	in.seekg(objectStack.back());
	tabCount--;
}


int XMLReader::nextObject()
{
	std::string storage = this->objectNames.back();
	in.getline(buffer, 1024);

	objectStack.pop_back();
	objectNames.pop_back();

	int readHead = 0;

	bool search = true;

	int currentTabCount = 0;
	while (search)
	{
		std::string returnString = "";

		//move read head to remove spaces
		char temp = in.get();
		if (temp == '<')
		{
			search = false;
			readHead = in.tellg();
		}
		else if(temp == '\t')
		{
			currentTabCount++;
		}

		if (!search)
		{
			//until end of string
			while (in.peek() != '>' && in.peek() != ' ')
			{
				returnString += in.get();
			}

			//just a safety check to avoid read access violation
			if (objectNames.size() > 0)
			{
				//if end of currently open object, error
				if (returnString == "/" + objectNames.back() && currentTabCount == tabCount-1)
				{
					std::cout << "XMLReader error: end of object" << std::endl;
					search = false;
					objectStack.push_back(readHead);
					objectNames.push_back(storage);
					in.seekg(objectStack.back());
					return -1;
				}
			}
			//if the currently found string 
			if (returnString == storage && currentTabCount == tabCount)
			{
				objectStack.push_back(readHead);
				objectNames.push_back(storage);
				in.seekg(objectStack.back());
				return 0;
			}
			else
			{
				in.getline(buffer, 1024);
				currentTabCount = 0;
				search = true;
			}
		}
	}
}


std::string XMLReader::returnParameter(std::string parameterName)
{
	in.seekg(objectStack.back());

	bool search = true;
	while (search)
	{
		std::string returnString = "";

		//move read head to remove spaces
		if (in.get() == '<')
		{
			search = false;
		}

		if (!search)
		{
			//until end of string
			while (in.peek() != '>')
			{
				returnString += in.get();
			}

			if (returnString == "/" + objectNames.back())
			{
				return "error";
			}
			else if (returnString == parameterName)
			{
				returnString = "";
				in.get();
				while (in.peek() != '<')
				{
					returnString += in.get();
				}
				return returnString;
			}
			else
			{
				in.getline(buffer, 1024);
				search = true;
			}
		}
	}
}


std::string XMLReader::returnObjectParameter(std::string parameterName)
{
	in.seekg(objectStack.back());

	while (true)
	{
		char temp = in.get();
		while (temp != ' ') 
		{ temp = in.get(); };

		std::string returnString = "";

		while (in.peek() != '=' && in.peek() != ' ')
		{
			returnString += in.get();
		}

		if (returnString == parameterName)
		{
			returnString = "";

			in.get();
			if (in.peek() == '>') return "XMLReader error: parameter not found";
			in.get();
			if (in.peek() == '>') return "XMLReader error: parameter not found";
			while (in.peek() != '"')
			{
				if (in.peek() == '>') return "XMLReader error: parameter not found";
				returnString += in.get();
			}
			return returnString;
		}
	}
}


int XMLReader::parseInt(std::string a)
{
	int multiplier = 1;
	float num = 0;
	if (a[0] == '-')
	{
		multiplier = -1;
	}
	for (int i = multiplier > 0 ? 0 : 1; i < a.length(); i++)
	{
		if (a[i] == '.') i = a.length();
		else
		{
			num *= 10;
			num += a[i] - '0';
		}
	}
	return num * multiplier;
};

float XMLReader::parseFloat(std::string a)
{
	bool startFloat = false;
	float multiplier = 1;
	int num = 0;
	if (a[0] == '-')
	{
		multiplier = -1;
	}
	for (int i = multiplier > 0 ? 0 : 1; i < a.length(); i++)
	{
		if (startFloat)
		{
			multiplier *= 10;
		}
		if (!startFloat && a[i] == '.') startFloat = true;
		else
		{
			num *= 10;
			num += a[i] - '0';
		}
	}
	return num / multiplier;
}

