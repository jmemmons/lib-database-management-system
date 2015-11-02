#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

void add_book(void);
void add_student(void);
void search_book(string [][3],int );
void search_student(string [][3],int);
void issue(string [][3],string[][3],int,int,int [],string,string, int []);
void retrn(string [][3],string[][3],int,int,int [],string,string, int []);
string due_date(void);
string date_format(void);
void check_due_date(string[],int,string[][3],int,string [][3],string [][5]);

int main () {
    string pass;

    //DEFINING LEVEL TOP
top:
    cout << "Welcome to The Library\n" << endl;
    cout << "Please Enter the Password to Gain Access to This Program : ";
    cin >> pass;
    
    if(pass == "project") {
        cin.ignore();

        string date;
        date = date_format();     //Calling function for date		

        //DEFINING LEVEL TOP
top2:

    int choice_section;           //Choice of section inside the library (admin/library)
    int choice_database;          //Choice of database in the admin section(seeing lists, adding books etc)
    int choice_lib;               //Choice of database in the library section
    int choice_issue;             //Choice for searching or entering code of the book while issuing it
    int count_book[100];          //number of books each user has issued
    int user_issue[100][5];       //student code and the code of the book that the user has issued
    int user_count[100] = {0};    //number of books issued by user
    int avail_book[100];          //book availability(1 when available and 0 when not available)

    // Setting The Book Availability of all books to 1 (available) and Book Count of Every Student to 1
    for (int i = 0; i < 100 ; i++) {
            avail_book[i] = 1;
            count_book[i] = 1;
    }

    string pass;                        //password for entering in the library
    string pass_admin;                  //password for entering in the admin section of the library
    string book[100][3];                //array for storing a book's code with its name, author and year of publication
    string student[100][3];             //array for storing a student's code with his name,batch and username
    string username;                    //username of student
    string date_book[100];              //date on which the book was issued
    string date_student[100][5];        //date on which a particular student issued a book
    string due_date[100];               //due date of book (date on which the book is to be returned)
    string due_date_student[100][5];    //date on which a particular student has to return a book

    int book_code = 1;                  //a unique book code for every book
    int student_code = 1;               //a unique student code for every student
    int book_code_enter;                //book code entered by the user while issuing/returning it
    int student_book_issue[100] = {0};  //code of the student who has issued the book

    //OPENING book.txt TO READ DATA OF BOOKS IN LIBRARY 
    ifstream InBook;
    InBook.open ("files/books.txt");
    do {
        //getting the date from the text file . Storing Book name in subscript [0]
        getline (InBook,book[book_code][0],'#');
        //storing author name in subscript [1]
        getline (InBook,book[book_code][1],'$');
        //storing year in subscript [2]
        getline (InBook,book[book_code][2]);		

        book_code++;

    } while (InBook.eof() == false);
    //getting the final value of book code
    book_code--;
    InBook.close();
    
    //OPENING student.txt TO READ DATA OF STUDENTS IN LIBRARY  
    ifstream InStudent;
    InStudent.open ("files/students.txt");
    do {
        //Name of Student is stored in Subscript [0]
        getline (InStudent,student[student_code][0],'#');
        //Batch is stored in subscript [1]
        getline (InStudent,student[student_code][1],'$');
        //user name is stored in subscript [2]
        getline (InStudent,student[student_code][2]);	

        cout << endl;
        student_code++;

    } while (InStudent.eof() == false);


    for (int i = 1; i < book_code; i++) {
        //using ostringstream to open a txt file by giving a variable name os
        //opening the individual txt files of all books to read the data of individual books
        ostringstream os;
        os << book[i][0] << ".txt";

        ifstream InBookAvail ( os.str().c_str() );
        do {
                // here i represents book code
                // storing 0 if book is not available and 1 if it is from file
                InBookAvail >> avail_book[i];
                // ignoring $ sign
                InBookAvail.ignore();
                // storing code of the student that has issued the book
                InBookAvail >> student_book_issue[i];
                //ignoring & sign
                InBookAvail.ignore();
                //storing the date when the book was issued
                getline (InBookAvail, date_book[i],'*');
                // storing the date when the book is to be returned (due date)
                getline (InBookAvail, due_date[i]);		

        } while (!InBookAvail.eof());
        
        InBookAvail.close();
    }

    for (int i = 1; i < student_code-1 ; i++) {
        int j = 0;
        //opening txt files of individual students to read data
        ostringstream zs;
        zs << student[i][0] << ".txt";

        ifstream InStudentStatus ( zs.str().c_str() );
        //storing code of the book issued by user
        // here i represents the users code and j represents the code of the book issued
        InStudentStatus >> user_issue[i][j];
        
        //ignoring $ sign
        InStudentStatus.ignore();
        do {
            //storing date when the book was issued
            getline (InStudentStatus, date_student[i][j],'*');
            //storing date when book is due
            getline (InStudentStatus,due_date_student[i][j]);		

            j++;

            InStudentStatus >> user_issue[i][j];
            InStudentStatus.ignore();

            //increasing the count (number of book issued by user) by 1 
            user_count[i]++;

        } while (!InStudentStatus.eof());
        
        InStudentStatus.close();
    }

    //main options
    cout << "\tTo Access the Admin Section Press 1\t\n\tTo Access The Library Section Press 2 \t\n\tTo Quit Program Press 3 \t\t" << endl;

    cout << "Enter your choice(1, 2 or 3): ";
    cin >> choice_section;
    cin.ignore();

    if (choice_section == 3)
            goto end;

    if (choice_section == 1) {
            cout << "Enter the Admin Password "; 
            cin >> pass_admin;
            cin.ignore();
            if (pass_admin == "admin") {
                    cout << endl;
                    cout << "" << setw(35) << "Welcome" << setw(29) << "" << endl;
                    cout << "\tTo Enter New Books in Database press 1\t\t\t\n\tTo Enter New Student in Student Database Press 2\t\n\tTo See The List of All Students press 3\t\t\t\n\tTo See The List of All Books Press 4\t\t\t\n\tTo Go Back To The Previous Menu Press 5:\t\t" << endl;
                    cout << endl;

                    cout << "Enter your choice(1-5): ";
                    cin >> choice_database;
                    cin.ignore();

                    if (choice_database == 1)
                        add_book();     //CALLING FUNCTION ADD BOOK

                    else if (choice_database == 2)
                        add_student();     //CALLING FUNCTION ADD STUDENT
                    

                    else if (choice_database == 3) {
                        // displaying names of all students
                        cout << "Student Name" << "\t\t\t" << "Batch" << "\t\t\t" << "UserName" << "\t" << endl;
                        for(int i = 0; i < student_code; i++) {
                            //here i represents respective student code
                            cout << student[i][0] << "\t\t\t" << student[i][1] << "\t\t\t" << student[i][2] << "\t" << endl;					

                            //the program will display 15 names and then wait for user to press any key before it continues
                            if (i == 15)
                                cin.get();
                        }
                        
                        cin.get();
                    }

                    else if (choice_database == 4) {
                        //showing all the books
                        cout << "Book Name" << "\t\t" << " Author Name" << "\t" << "Year Published" << "\t\t" << "code" << endl;
                        for(int i = 1; i < book_code; i++) {
                            //here i represents book code
                            cout << book[i][0] << "\t\t" << book[i][1] << "\t\t" << book[i][2] << "\t\t" << i << "\t" << endl;
                            //program will display 10 books and then wait for user to press any key before it continues
                            if(i == 10)
                                cin.get();
                        }			
                        cin.get();
                    }

                    else if (choice_database == 5)
                        goto top2;

                    else
                        cout << "Wrong Choice "<< endl;
                    goto top2;				
            }

            else {
                cout << "Wrong Password Entered ";
                cin.get();
                goto top2;
            }
    }

    else if(choice_section == 2) {
            cout << "\tTo Search For a Books Code Press 1\t\t\n\tTo Search For A Student Press 2\t\t\t\n\tTo Issue A Book Press 3\t\t\t\t\n\tTo Return a Book Press 4\t\t\t\n\tTo Check Status Of A Student Press 5\t\t\n\tTo Check Staus Of A Book Press 6\t\t\n\tTo Check If Any Book Is Due Today Press 7\t\n\tTo Go Back To The Previous Menue Press 8\t"<<endl;

            cout << "Enter your choice (1-8): ";
            cin >> choice_lib;
            cin.ignore();

            if (choice_lib == 1 || choice_lib == 2 || choice_lib == 3 || choice_lib == 4 || choice_lib == 5 || choice_lib == 6 || choice_lib == 7 || choice_lib == 8) {
                    if (choice_lib == 8)
                        goto top2;
                    
                    if (choice_lib == 1) {
                        search_book (book,book_code);   //CALIING SEARCH BOOK FUNCTION
                        goto top2;
                    }

            if (choice_lib == 2) {
                search_student (student,student_code);   //CALIING SEARCH STUDENT FUNCTION
                goto top2;
            }

            if (choice_lib == 3) {
                cout << "If You know the Code of the Book Press 1 to enter it\nIf You Want to Search for the book first press 2" << endl;
                cout << "Enter your choice (1-2): ";
                cin >> choice_issue;
                cin.ignore();

                if (choice_issue == 2)
                    search_book (book,book_code); 

                cout << "Enter The Username of The Student Who Wants to Issue the Book :";
                getline (cin, username);
                cout << "Enter the Book Code :";
                cin >> book_code_enter;
                cin.ignore();
                // if the code entered by the user is more than the total number of book codes in memory give an error
                if (book_code_enter > book_code-1)
                    cout << " Wrong Book Code Entered" << endl;

                //calling function to issue a book
                else
                    issue (book,student, book_code_enter, student_code, count_book, date, username, avail_book);

                cin.get();
                goto top2;
            }
                    
            if(choice_lib == 4) {
                cout << "If You Want to Enter The Code of the Book Press 1\nIf You Want to Search for the book First press 2" << endl;
                cin >> choice_issue;
                cin.ignore();

                // calling the function to search the book one used when issuing book
                if (choice_issue == 2)
                        search_book (book, book_code);

                cout << "Enter The Username of The Student Who Wants to Return the Book :";
                getline (cin,username);
                cout << "Enter the Book Code :";
                cin >> book_code_enter;
                cin.ignore();

                if (book_code_enter > book_code-1)
                    cout << " Wrong Book Code Entered" << endl;
                
                // calling function to return a book
                else
                    retrn (book, student, book_code_enter, student_code, count_book, date, username, avail_book);
                
                cin.get();
                goto top2;
            }

            if (choice_lib == 5) {
                int user_code_found, choice_student;
                cout << "To Enter username Of The Student You Want to Check Status Of Press 1\nTo Search For The Student Press 2:" << endl;
                cin >> choice_student;
                cin.ignore();
                if (choice_student == 2)
                        search_student (student, student_code);
                goto student;
                if (choice_student == 1) {
                    student:
                    cout << "Enter The username :";
                    getline (cin, username);
                    int check = 0;

                    //a small program to find the code of the student whose username has been entered
                    //starting from 1 and going to maximum amount of user code and comparing user name of each user code with the database to see which students username has been given
                    for (user_code_found = 1 ; user_code_found < student_code ; user_code_found++) {
                        //subscript [2] stores username . If The username of user code searching matches with the username given then that user code is the required code
                        if (student[user_code_found][2] == username) {
                            check = 1;
                            break;
                        }
                        else
                            check = 0;
                    }
                
                    //if the given username matches with none of the usernames in database
                    if (check == 0)
                        cout << " Wrong username " << endl;
                    
                    else {			
                        int i;
                        // if the count (number of books issued by user) are greater than1
                        if (user_count[user_code_found] > 1) {

                            // showing the full name of the user 
                            cout << student[user_code_found][0] << endl;
                            cout << "Book Name" << setw(25) << "Date Issued " << setw(25) << "Due Date" << endl; 
                            //running loop from 1 to the number of books user has issued (user_count)
                            
                            //displaying name of the book and date the book was issued
                            for (i = 1 ; i <= user_count[user_code_found]-1 ; i++)
                                    cout << book[user_issue[user_code_found][i]][0] << setw(20) << date_student[user_code_found][i] << setw(20) << due_date_student[user_code_found][i] << endl;
                            cin.get();
                            goto top2;
                        }
                        else
                            cout << " No Books Have Been Issued by " << student[user_code_found][0] << endl;
                        cin.get();
                        goto top2;
                    }
                }
                else
                    cout << "Wrong Choice Entered" << endl;
                cin.get();
                goto top2;
            }

            if (choice_lib == 6) {
                int choice_book_status;
                cout << "If You Want To Enter The Code of The Book Press 1\nIf You Want To Search For The Book Press 2" << endl;
                cin >> choice_book_status;
                cin.ignore();
                if (choice_book_status == 2)
                    search_book (book, book_code);
                else if(choice_book_status == 1) {
                            cout << "Enter The Code of The Book :";
                            cin >> book_code_enter;
                            //checking if the book code is valid
                            if (book_code_enter > book_code-1)
                                    cout << "Wrong Book_code entered ";
                            else {
                                    // 1 represents that book is available
                                    if (avail_book[book_code_enter] == 1)
                                    {
                                            // printing the name of the book (stored in subscript [0])
                                            cout << book[book_code_enter][0] << " is available" << endl; 

                            }
                                    //0 represents that book is not available
                                    else if (avail_book[book_code_enter] == 0)
                                    {
                                            //printing the name of the book and to whome it has been issued to and when
                                            cout << book[book_code_enter][0] << " Has Been Issued to " << student[student_book_issue[book_code_enter]][0] << " On " << date_book[book_code_enter] << " Till The Due Date :" << due_date[book_code_enter] << endl;
                                    }

            }
                    }
                    cin.get();
                    goto top2;

            }
            if (choice_lib == 7)
            {
             check_due_date (due_date, book_code, book, student_code, student, due_date_student);
                    goto top2;
            }
            }
            else
            {
                    cout << "Wrong Choice Entered " << endl;
                    cin.get();
                    goto top2;
                    }
            }

        else
        {
                cout << "Wrong Choice Entered :";
                cin.get();
                goto top2;
        }

    }
    else
            {
                    cout << "Wrong Password Entered" << endl << endl << endl;

                    goto top;
    }

    end:

    cin.get(); 
    return 0; 

    //end of main program

    }

void add_book (void)
{
	string book_name, author_name, year;
	char choice;
	ofstream OutBook;
	//opening the book txt file
	OutBook.open ("books.txt", ios::app);
	do
	{
	//inputing the info about the book
	
	cout << "Enter Book Name :";
	getline (cin, book_name);
	
	cout << "Enter Aurthors Name :";
	getline (cin, author_name);
	
	cout << "Enter Book Year :";
	getline (cin, year);
	//storing it in the file
	OutBook << book_name << "#" << author_name << "$" << year << endl;

	cout << "If You Want to Enter Another Book press Y else Press N :";
	cin >> choice;
	cin.ignore();
	choice = tolower(choice);
	//creating a seperate txt file for the book to store its data in
	ostringstream os;
	os << book_name << ".txt";

	ofstream OutBookAvail( os.str().c_str() );
	// 1 represents that its available . 0 is the code of the student that has issued it (by defualt 0 .. since no student has 0 code) and Year the book was issued on ( by defailt 1 January 2011 an old that on which book cant be issued) and Lastly due date which is also set to a date in the past by defualtwhich is not possible 
	OutBookAvail << 1 << "$" << 0 << "&" << "1/1/2010" << "*"<< "2/1/2010" << endl;
	OutBookAvail.close();
	} while (choice == 'y');

	OutBook.close();	
}


void add_student(void)
{
	char choice;
	string student_name, batch, user_name;
	ofstream OutStudent;
	//opening student txt file
	OutStudent.open ("students.txt",ios::app);
	do
	{
		cout << "Enter Students Name :";
		getline (cin, student_name);
		cout << "Enter Students Batch :";
		getline (cin, batch);
		cout << "Enter The Username :";
		getline (cin, user_name);
		//storing necessary data in it
		OutStudent << student_name << "#" << batch << "$" << user_name << endl;
		cout << "Enter Y if You want to Enter Data of Anotehr Student else Press N :";
		cin >> choice;
		cin.ignore();
		//creating a seperate txt file for the student 
		ostringstream ss;
	ss << student_name << ".txt";
	// 0 represents the book code of book issued by user ( 0 by default since no book has a 0 code) 
	//and 1/1/2010 as the default date the book was issued on (past date an arbitary value) 
	//and 2/1/2010 as default due date for the book issued
	ofstream OutStudentAvail ( ss.str().c_str(),ios::app );
	OutStudentAvail << 0 << "$" << "1/1/2010" << '*' << "2/2/2010" << endl;
	OutStudentAvail.close();	

	} while (choice == 'y');
}


void search_book(string book[][3], int book_code)
{
	int i, j, length1, length2, match = 0;
	string book_search, book_new;
	cout << "Enter The Name of The Book You Want to Search :";
	getline (cin, book_search);
	cout << " Following Are The Books That Matched Your Given Book Name" << endl;
	cout << "Book Name" << "\t\t" << " Author Name" << "\t" << "Year Published" << "\t\t" << "code" << endl;
	for ( i = 1 ; i <= book_code; i++)
	{		
            length2 = book_search.length();

            length1 = book[i][0].length();
            match = 0;

		// runs till the length of the book name entered for searching
		for (j = 0 ; j < length2-1 ; j++)		
		{
			// runs till the length of book name in database
			for (int k = 0 ; k < length1-1 ; k++)
			{
				//lowering all charecters for easy access 
			book[i][0][k] = tolower(book[i][0][k]);
			book_search[j] = tolower(book_search[j]);
			// if they are equal then counter match increases by 1
			if (book[i][0][k] == book_search[j])
		{
			match++;
			break;
		}
		}
		}
		//if match is greater than 1 less then the length of the name given by user .  
			if (match >= length2-1)
				{				
			    //printing the book name author year and code .. here i represents the book code						
				cout << book[i][0] << "\t\t" << book[i][1] << "\t\t" << book[i][2] << "\t\t" << i << "\t" << endl;
			}	
	}
	cin.get();
}


void search_student(string student[][3],int student_code)
{
	// searching student by same criteria aswell
	int i, j, length1, length2, match = 0;
	string student_search, student_new;
	cout << "Enter The Name of The Student You Want to Search :";
	getline (cin, student_search);
	cout << " Following Are The Students That Matched Your Given Book Name" << endl;
	cout << "Student Name" << "\t\t\t" << "Batch" << "\t\t\t" << "UserName" << "\t" << endl;
	for (i = 1 ; i <= student_code-1 ; i++)
	{
		length2 = student_search.length();
		
			length1 = student[i][0].length();
		match = 0;
		//runs till length of the name entered for search
		for (j = 0 ; j < length2-1 ; j++)		
		{
			// runs till length of the name in database
			for (int k = 0 ; k < length1-1 ; k++)
			{
			student[i][0][k] = tolower(student[i][0][k]);
			student_search[j] = tolower(student_search[j]);
			if (student[i][0][k] == student_search[j])
		{
			match++;
			break;
		}
		}
		}
			if (match >= length2-1)
				{   						
				cout << student[i][0] << "\t\t\t" << student[i][1] << "\t\t\t" << student[i][2] << "\t" << endl;
			}		
	}
	cin.get();
}


void issue(string book [][3], string student[][3], int book_code, int student_code, int count_book[], string date, string username, int avail_book[])
{
	int check = 0;
	// 0 represents that book isn't available. checking if it is or not
	if (avail_book[book_code] == 0)
	{
		cout << "Book Is Not Available " << endl;
	}
	else
	{
	int i;
	for (i = 1 ; i < student_code ; i++)
	{
		// searching for the user whose username has been entered
		if (student[i][2] == username)
			{				
				check = 1;
				break;
		}
		else
			check = 0;
	}

	if (check == 0)
	{
		cout << " Wrong User Name " << endl;
	}
	
	else
	{
		// here i represents student code . if that student has already issued 4 books i.e his counter is more than 4 it gives an error
	if (count_book[i] > 4)
		cout << " You Have Issued 4 Books Already, Please Return a Book to get More Books Issued" << endl;
	else
	{
		// setting the availbility status of that book to 0 (0 represents its not available)
	avail_book[book_code] = 0;
	//using due date function to store the due date
	string date_due = due_date();
	//displaying book name and who has issued it and other info
	cout << book[book_code][0] << " By " << book[book_code][1] << " Has Been Issued to " << student[i][0] << " on " << date << " Till The Due Date :" << date_due << endl;
	//increasing the count of the student by 1
	count_book[i]++;
	
	//opening the txt file of the respective book
	ostringstream os;
	os << book[book_code][0] << ".txt";

	ofstream OutBookAvail ( os.str().c_str() );
	//storing the new availbility status , the code of the user who has issued the book and the date when it was issued
	OutBookAvail << avail_book[book_code] << "$" << i << "&" << date << "*" << date_due << endl;
	OutBookAvail.close();
	// opening the text file of the respective user
	ostringstream ss;
	ss << student[i][0] << ".txt";

	ofstream OutStudentAvail ( ss.str().c_str(),ios::app );
	//storing the book code of the book issued and the date when it was issued
	OutStudentAvail << book_code << "$" << date << "*" << date_due << endl;
	OutStudentAvail.close();	
	}
	}
	}
}


void retrn(string book [][3], string student[][3], int book_code, int student_code, int count_book[], string date, string username, int avail_book[])
{	
		int check = 0;
		// if the status of book is 1 it means it hasent been issued yet
		if (avail_book[book_code] == 1)
	{
		cout << "The Book Hasent Been Issued yet" << endl;
	}
	else
	{
	int i;
	int check = 0;
	//searching for the student with the given username
	for (i = 1 ; i < student_code ; i++)
	{	
		if (student[i][2] == username)
			{				
				check = 1;
				break;
		}
		else
			check = 0;
		
	}
	if (check == 0)
	{
		cout << " Wrong User Name " << endl;
	}
	
	else
	{
		// opening the book file and storing the data in it temporary
		int temp_user, temp_avail;
		string temp_Date, temp_Due_Date;
		ostringstream os;
	os << book[book_code][0] << ".txt";

	ifstream InBookAvail( os.str().c_str() );
	while (!InBookAvail.eof())
	{
		InBookAvail >> temp_avail;
		InBookAvail.ignore();
		// code of the user who has issued the book
		InBookAvail >> temp_user;
		InBookAvail.ignore();
		getline (InBookAvail, temp_Date,'*');
		getline(InBookAvail, temp_Due_Date);

	}
	// if the username of the user wanting tor return the book matches with the user whose code is stored in the book's txt file then program continues
	if (temp_user == i)
	{
		//reducing the users counter of book issued by 1 (here i represents user code)
	count_book[i]--;
	//setting the availbility of the respective book to 1 ( 1 represents available)
	avail_book[book_code] = 1;
	// displaying the info
	cout << book[book_code][0] << " by " << book[book_code][1] << " Issued on : " << temp_Date << " has been returned by " << student[i][0] << " on  " << date << endl;
	
	//opening the text file of the book;
	ostringstream os;
	os << book[book_code][0] << ".txt";

	ofstream OutBookAvail( os.str().c_str() );
	//setting the values back to default as they were when we created the new text file
	OutBookAvail << 1 << "$" << 0 << "&" << "1/1/2010" << "*" << "2/1/2010" << endl;
	OutBookAvail.close();
	
	int temp_code, temp_count;
	string temp_date;
	//opening the students txt file.
	ostringstream ss;
	ss << student[i][0] << ".txt";

	ifstream InStudentAvail( ss.str().c_str(),ios::app );
	
	// reading the data 
	// storing book code
	InStudentAvail >> temp_code;
	InStudentAvail.ignore();
	//temp date
	getline (InStudentAvail, temp_date);
	
	while (!InStudentAvail.eof())
	{		
		// if the code of the book is equal to the code of the book returned then its not copied hence removing the code of the book that has been returned
		if (temp_code == book_code)
		{
		}
		else
		{
			// storing data of other books in a new temp txt file
		ostringstream ss;
		ss << student[i][0] << "_temp.txt";

		ofstream OutStudentAvail( ss.str().c_str(),ios::app);
		OutStudentAvail << temp_code << "$" << temp_date << endl;
		OutStudentAvail.close();	
		}
		InStudentAvail >> temp_code;
		InStudentAvail.ignore();
		getline (InStudentAvail, temp_date);
	}
	InStudentAvail.close();
	ostringstream ds;
	//removing the text file of the student
	ds << student[i][0] << ".txt";
	remove ( ds.str().c_str());
	
	ostringstream es;
	es << student[i][0] << "_temp.txt";
	
	ostringstream ps;
	ps << student[i][0] << ".txt";
	//renaming the temporary file to the original . in this way we have modified the txt file of the student removing data of the book returned and it only contain data of books that are still issed to him (if any)
	rename ( es.str().c_str(),ps.str().c_str());
	}
	// if the username given does not match with the username of student stored in the books txt file while issuing than it gives an error
	else
		cout << " The Book Has Not Been Issued By This User :" << endl;	
	}
}	
}


string due_date(void) {
	string due_date;
	int date = 0, month = 0 , year = 0;
	//calling date from computer
	char date_cal[9];
	ofstream OutFile;
	OutFile.open("date.txt");
	//storing it into date.txt
	OutFile << date_cal;
	OutFile.close();

	ifstream InFile;
	//reading date.txt and storing days months and year seperatly in different int
	InFile.open ("date.txt");
	InFile >> month;
	//to ignore /
	InFile.ignore();
	InFile >> date;
	// to ignore /
	InFile.ignore();
	InFile >> year;	

	
	
	// calculating for feburary
	if (month == 2)
	{
		//checking if leap year
		if (year%400 == 0 || (year%100 != 0 && year%4 == 0))
	{
		//making necesarry calculations
			if (date <= 8)
	date = date+21;
	else if(date > 8)
	{
		date = (date+21) - 29;
		month = month++;
		
	}
		}

		else if (date <= 7)
	date = date+21;
	else if (date > 7)
	{
		date = (date+21) - 28;
		month = month++;
		if (month > 12)	
		{
			//resetting month to 1 and increasing year  month is greater than 12
					month = 1;
			year++;
			}
	}
	}
	// for months with 31 days doing the necesary calculation
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (date <= 10)
				{
					date = date+21;
			}
			else if (date > 10)
				{
					date = (date+21) - 31;
					month = month++;
					if (month > 12)	
					{
					month = 1;
			year++;
			}
			}
	}
	// calculation for month with 30days
	else
	{
		if (date <= 9)
			date = date+21;
		else if (date > 9)
		{
			date = (date+21) - 30;
			month++;
			
		}
	}
	if(date > 9 && month > 9)
	{
	//storing the data into a txt file due_date
	
	ofstream outfile;
	outfile.open ("due_date.txt");
	outfile << date << "/" << month << "/" << year << endl;
	outfile.close();
	ifstream infile;
	// reading the txt file and storing the whole date in a single string
	infile.open ("due_date.txt");
	getline (infile, due_date);
	}
	else if (date <= 9 && month <= 9)
	{
			//storing the data into a txt file due_date
	
	ofstream outfile;
	outfile.open("due_date.txt");
	outfile << "0" << date << "/" << "0" << month << "/" << year << endl;
	outfile.close();
	ifstream infile;
	// reading the txt file and storing the whole date in a single string
	infile.open ("due_date.txt");
	getline (infile, due_date);
	
	}
	else if (date <= 9)
	{
			//storing the data into a txt file due_date
	
	ofstream outfile;
	outfile.open ("due_date.txt");
	outfile << "0" << date << "/" << month << "/" << year << endl;
	outfile.close();
	ifstream infile;
	// reading the txt file and storing the whole date in a single string
	infile.open ("due_date.txt");
	getline(infile, due_date);
	
	}
	else if (month <= 9)
	
	{
			//storing the data into a txt file due_date
	
	ofstream outfile;
	outfile.open ("due_date.txt");
	outfile << date << "/" << "0" << month << "/" << year << endl;
	outfile.close();
	ifstream infile;
	// reading the txt file and storing the whole date in a single string
	infile.open ("due_date.txt");
	getline (infile, due_date);
	
	}		
		//returning the due date
		return due_date;
}

/* Removed the '_strdate()' since it is depreciated. */
string date_format (void)
{
    char date_cal[9];
    /* Put something here..
       char cptime[50]; // char ptr
  
       time_t myTime = time(NULL);
       strftime (cptime, 50, "%B %d, %Y", localtime(&myTime));
       string strTime = cptime;
       cout << strTime << endl;
    */
    string date = "12345678";

    date[0] = date_cal[3];
    date[1] = date_cal[4];
    date[2] = '/';
    date[3] = date_cal[0];
    date[4] = date_cal[1];
    date[5] = '/';
    date[6] = date_cal[6];
    date[7] = date_cal[7];

    return date;
}


void check_due_date(string due_date[], int book_code, string book[][3], int student_code, string student [][3], string due_date_student [][5]) {
    int check=0;
    string date;
    date = date_format();
    cout << "Following Books are due today :" << endl;
    
    for (int i = 1; i < book_code; i++) {
            if (due_date[i] == date)
                cout << book[i][0];
    }
    
    for (int i = 1 ; i < student_code; i++) {
        for (int j = 0; j < 5; j++) {
            if (date == due_date_student [i][j]) {
                cout << " is To Be Returned By :" << student[i][0] << " " << endl;
                check=1;
            }
        }
    }
    
    if (check == 0)
        cout << "No Books Are Due Today " << endl;
    
}
