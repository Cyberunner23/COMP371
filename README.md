
COMP 371: Computer Graphics
===========================

## Assignment 1

This repository contains my code for the first Computer Graphics assignment.
<br/>  In terms of feature and operation, the program is designed to follow
the requirements found in the Assignments/ProgrammingAssignment1.pdf file.
<br/>  In terms of usage there should be no deviations from the requirements.

### To compile

#### Requirements
 * cmake
 * A c++ compiler
 
#### Steps
 * `git clone https://github.com/Cyberunner23/COMP371.git`
 * `cd COMP371`
 * `mkdir build && cd build`
 * `cmake ..`
 * `cmake --build .`
 <br/>  **Note:** The first time you compile it will take rather long.
 This is because I'm using hunter for the dependencies. I do not assume
 that you have the libraries installed on your system and makes it 
 cross platform all while not having the need to redistribute the library
 files. 
 <br/>  **Other note:** If you're using GCC-7.3, don't. GLM currently has a bug
 with GCC-7.3 that breaks builds, I learned that the hard way...
 
#### To run
 * Simply execute the COMP371 executable that is generated once the build is complete

### Report

 The report highlighting the extra controls and the difficulties encountered 
 during the project is found in ```report.txt```