Nicolas Corfmat<br>
CruzID: ncorfmat<br>
Assignment: pa8

```
DESCRIPTION
``` 
This program implements the Dictionary ADT to create a Red-Black Tree of corresponding keys and values.

```
FILES
```
+ `Dictionary.h` Header file containing the interface for the Dictionary ADT.
+ `Dictionary.cpp` C++ file containing the Dictionary ADT.
+ `DictionaryTest.cpp` C++ file containing code for testing the Dictionary ADT.
+ `Order.cpp` Contains the main() function that converts input from a file and converts it into a Red-Black Tree.
+ `WordFrequency.cpp` Contains the main() function that creates a dictionary with corresponding frequencies of each word.
+ `Makefile` Supports the compilation of all the .cpp programs in the pa8 directory.
+ `README.md` Contains information regarding the files in the pa8 directory and how to run them.

```
BUILD
``` 
To build, run `make` on the terminal command line within the pa8 assignment directory followed by `WordFrequency`, `Order`, and/or `DictionaryTest`. This creates respective executable files which can then be run.
```
CLEAN
```
Running `make clean` will remove all the executable (.o) files from the pa8 assignment directory as well as other compiler-generated files.
```
RUNNING
```
To run, type `./Order` or `./WordFrequency` followed by an input and output file.
