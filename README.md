# XMLParser

Simple C++ based XML parser designed for a different project I'm working on, however I thought others might find my approach useful.
Still a work in progress. I swear I haven't forgotten about this repo, I've just haven't had time to focus on this

Just copy XMLReader.h and XMLReader.cpp to your project and everything should work. 
It currently has a tendency to run forever, so be extremely careful with usage.
Also be careful to only use tab spaces ('\t') when indenting branches inside the XML file.

**TODO:**
- add reccursive reading of the XML tree
- make a buffer that reads and indexes all objects from current branch for more efficient selection
- automatically open root object upon opening a file
- accessBranch should automatically decide if the branch can be opened or if it should return data
- change everything to return parameters and use the return types for error signaling
