**Programming Assignment #4: Page Replacement Algorithms**

The purpose of this program is to show the different page replacement algorithms and how they interact in terms of page faults.
The three algorithms shown are the Least Recently Used, Optimal, and First In First Out. 
Least recently used gets rid of the pages that have not been used the longest. 
First In First Out gets rid of the page that was first loaded.
The optimal algorithm simulates future use and chooses pages based on that. 

The program was written using c++. The libraries needed to run the program are:
-iostream for input/output
- vector is used to store the frames that will be replaced
- unordered_map to store pages and when they were used
- sstream to convert the string to individual digits
- 
