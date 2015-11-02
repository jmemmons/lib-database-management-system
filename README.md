# Library Database Management System

This program was designed as a first semester c++ project by a team of students from the National University of Science and Technology. The program functions as a database that stores students and books with the ability to issue, return, or check the status of books.

### About
---

This program was written originally on Windows using Visual Studio which created incompatible code on other platforms. The original code with no modifications in located in the `MS Visual Studio` folder named `lib new.cpp`. 

### Authors
---

hj576

John Emmons

### Usage
---

To enter the database you must provide `project` as the password. Alternatively, to access the admin panel, the password is simply `admin`.

For a detailed walkthrough with more information, please see the original author's video below. 

<a href="http://www.youtube.com/watch?feature=player_embedded&v=qAFLALyvLSs" target="_blank"><img src="http://img.youtube.com/vi/qAFLALyvLSs/0.jpg" 
alt="C++ First Semester Project" width="240" height="180" border="10" /></a>

### To run on Windows
---

Simply access the `MS Visual Studio` folder for all relevant project files. You will need to also include the `files` folder in the same directory you will be working in so the program can access necessary dependecies. The file that runs the entire program is named `lib new.cpp` and will use `files/` to access relevant data.

### To run on Linux
---

The file that runs the entire program is `library_DBMS.cpp` which uses the `/files/` folder for all relevant operations.

  project
  
    |
    
    +-- README.md
    
    |
    
    +-- library_DBMS.cpp
    
    |
    
    +-- files/
    
	    +-- Abdul Hannan.txt
	    
	    +-- Abdullah Nasim.txt
	    
	    +-- ...
