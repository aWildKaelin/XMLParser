# XMLParser

Simple C++ based XML parser designed for a different project I'm working on, however I thought others might find my approach useful.
Still a work in progress, awaiting documentation, a couple of comfort features and a usage example

Just copy XMLReader.h and XMLReader.cpp to your project and everything should work. 
It currently has a tendency to run forever, so be extremely careful with usage.
Also be careful to only use tab spaces ('\t') when indenting branches.

**TODO:**
- make nextObject() part of accessObject()
- add reccursive reading of the XML tree
- make a buffer that reads and indexes all objects from current branch for more efficient selection
- automatically open root object upon opening a file
- accessBranch should automatically decide if the branch can be opened or if it should return data
- change everything to return parameters and use the return types for error signaling