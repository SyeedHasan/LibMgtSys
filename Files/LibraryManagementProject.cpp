#include<stdio.h>
#include<math.h>
#include<conio.h>
#include <graphics.h>
#include<string.h>
#include <unistd.h>
#include<time.h>
//Used for the time or month or date functions.
#include<stdlib.h>
//Used for sleep() and delay() functions
#include <dos.h>
//Used for declaring the gotoxy func.for modern compilers
#include <windows.h>
//Defines gotoxy() for ANSI C compilers.
void gotoxy(short x, short y)
{
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//Declaration for 'Time' function.
time_t t = time(NULL);
struct tm tm = *localtime(&t);
int pl=0; //ISSUED BOOKS

// Declaration of all functions used in our program
void mainmenu();	//Main menu of the program
void addbooks();	//Option to add books to the list (Librarian)
void deletebooks();	//Delete books (Librarian)
void issuebooks();  //for issue book records etc. (Student)
void editbooks();	//Modify book records (Librarian)
void searchbooks(); //Searching books (both modes)
void view();		//View books in the library (both modes)
void passcode();	//Password for the librarian
void student();		//Student Mode
void librarian();	//Librarian Mode
int checkid(int );	//Checking ID of the book and its existence
int information(int );//Used for input of information on every book
void bargraph();
void viewissuedbooks(int );
void returnbook();

int TimesRepeated=0;
int num; //For choices
int k=0, l=1, z=0,ij=0; //used in student menu
int cate[7];
FILE *fp, *fl, *fs, *fo, *fn, *fi;
//FS is used for issue books.
//FL is for the new book used in delete books.
char password[15]={"library"};
int i=0; //Used in the librarian function

char categories[][25]={"Programming", "Discrete Structres", "Islamiat", "Pakistan Studies", "Civil Engineering", "Architecture"};
//Structure declaration
struct type{
   // int pro=0, ds=0, isl=0, pst=0, ce=0, arch=0;
   int pro,ds,isl,pst,ce,arch;
};
struct type cat;
struct books{
	char title[30];
	char author[30];
	char subject[20];
	char stname[30];
	int stid,quantity,book_id,count;
	int issuecode;
	char *category;
	float price;
	int issuedate, issuemonth, issueyear;
	int returndate, returnmonth, returnyear;
};
struct books book;

main()
{
	mainmenu();
	getche();
}

void mainmenu()
{

	system("cls");
	int user;
	gotoxy(25,2);
		printf("Welcome to the Library");
	gotoxy(10,4);
		printf("Login as");
	gotoxy(10,6);
		printf("1. Student");
	gotoxy(10,8);
		printf("2. Librarian");
	gotoxy(10,10);
	printf("3. Graph");
	gotoxy(10,12);
	printf("4. Exit Application");
	gotoxy(10,14);
	printf("Enter your choice : ");
	scanf("%d", &user);
	switch(user)
	{
		case 1: student();
				break;
		case 2: librarian();
				break;
        case 3: bargraph();
                break;
        case 4:
				system("cls");
				gotoxy(25,2);
				printf("Exiting the application.  ");
				Sleep(2000);
				gotoxy(25,4);
				printf("Thankyou for running the program!");
				Sleep(2000);
				system("cls");
				exit(0);
                break;

		default:
				gotoxy(10,15);
				printf("Wrong choice!");
				gotoxy(10,17);
				printf("Press 'enter' to return");
				getche();
				mainmenu();
				break;

	}
}

void student()
{
	system("cls");
	z=0;
	gotoxy(23,3);
	printf("Welcome to the Student Menu");
	gotoxy(20,5);
	printf("Select from any of these choices:");
	gotoxy(20,7);
	printf("1.Issue a book");
	gotoxy(20,9);
	printf("2.Return issued book");
	gotoxy(20,11);
	printf("3.Search books");
	gotoxy(20,13);
	printf("4.View booklist");
	gotoxy(20,15);
	printf("5.Return to the Main Menu");
	gotoxy(20,17);
	printf("Enter your choice:");
	scanf("%d", &num);

	switch(num)
	{
		case 1: issuebooks();
				break;
		case 2: returnbook();
				break;
		case 3:	searchbooks();
				break;
		case 4:	view();
				break;
		case 5: mainmenu();
				break;
		default:
				 printf("No such entry. \n\n");
				 printf("Try again.\n\n");
				 getche();
				 student();
			     break;
	}


}

void librarian()
{
	//i is declared as a global variable for different calls every time.
	if(i==0){
	system("cls");}
	if(TimesRepeated==0)
	passcode();
	//setting time equals 1 so that next call would not call password!
	TimesRepeated=1;
	z=1; //to return to librarian menu
	system("cls");
	gotoxy(25,2);
	printf("Welcome to the Librarian Mode");
	gotoxy(20,4);
	printf("Select from any of these choices:");
	gotoxy(20,6);
	printf("1. Add Books ");
	gotoxy(20,8);
	printf("2. Delete Book Records");
	gotoxy(20,10);
	printf("3. Edit Book Records");
	gotoxy(20,12);
	printf("4. Search Books");
	gotoxy(20,14);
	printf("5. View Book Lists");
	gotoxy(20,16);
	printf("6. Issue Records");
	gotoxy(20,18);
	printf("7. Return to the Main Menu");
	gotoxy(20,20);
	printf("Enter your choice :  ");
	scanf("%d", &num);

	switch(num)
	{
		case 1:	addbooks();
				break;
		case 2:	deletebooks();
				break;
		case 3:	editbooks();
				break;
		case 4:	searchbooks();
				break;
		case 5:	view();
				break;
		case 6:     viewissuedbooks(1);
				break;
		case 7: mainmenu();
				break;
		default:
				 printf("No such entry. \n\n");
				 printf("Try again.\n\n");
				 i=1;
				 librarian();
			     break;
	}

}

void passcode()			//Password protection for users
{
	system("cls");
	char ch, pass[20], choice;
	int i=0,j=1;
	gotoxy(20,2);
	printf("Enter your password: ");
	while(ch!=13) //ASCII for Enter Key
	{
	    ch=getche();//Take input until ENTER is pressed.

        if(ch!=13&& ch!=8)
		//ASCII for Enter and Backspace
		{
		    printf("\b");
			putch('*');

			pass[i] = ch;

			//printf("*");
			i++;
		}
		//Close the password with a null character
		pass[i]='\0';
		//Comparison for entered pass with actual password
		j=strcmp(pass,password);
	}
		if(j==0)//Exact match.
		{
			gotoxy(20,5);
			printf("Password Matched!");
			gotoxy(20,7);
			printf("Press any key to continue.");
			getche();
			//Insert the page where the librarian will be leaded to
		}
		else
		{
			gotoxy(20,5);
			printf("Wrong Password!");
			gotoxy(20,7);
			printf("Enter any key to return to the main menu");
			getche();
			mainmenu();
		}
}

void addbooks()
{

	if(k==0)
	system("cls");
	int choice;
	printf("\n\n\t\t\tSELECT\t CATEGORY\n\n");
	printf("\n\n\t\t 1. Programming");
	printf("\n\n\t\t 2. Discrete Structures");
	printf("\n\n\t\t 3. Islamiat");
	printf("\n\n\t\t 4. Pakistan Studies");
	printf("\n\n\t\t 5. Civil Engineering");
	printf("\n\n\t\t 6. Architecture");
	printf("\n\n\t\t 7. Return to main menu");
	printf("\n\n\t\tEnter your choice:");
	scanf("%d", &choice);
	if(choice>=8 || choice==0)
	{
		printf("\n\n\t\tNo such category");
		k=1;
		addbooks();
	}
	if(choice==7)
	{
		mainmenu();
	}
	system("cls");
	fp=fopen("AllBooks.dat","ab+");
	//ab+ is for appending and reading in binary files
	if(information(choice)==1)
	/*Call the function 'information' which
	takes input for every book */
	{
		book.category=categories[choice-1];
		//End of the file. Starts writing at the end.
		//Currently the data is in the buffer, for writing
		//in the disk, seek to the end and then use fwrite.
		fseek(fp,0,SEEK_END);
		fwrite(&book,sizeof(book),1,fp);
		fclose(fp);
		printf("\n\n\t\tThe record has been saved!");
		printf("\n\n\t\tDo you wish to save any more? (Y / N ) ");
		if(getche()=='n' || getche()=='N')
		{
			librarian();
		}
		else
		{
		system("cls");
		addbooks();
		}
	}
}
//Part of addbooks
int information(int choice)
{
	if(i=0){
	system("cls");}
	int id;
	char ch;
	printf("\n\n\t\tComplete the following data of the book : ");
	printf("\n\n\n\n\t\tCategory: ");
	printf("%s", categories[choice-1]);
	//Categories is a globally define 2D array.
	printf("\n\n\t\tBook ID: ");
	scanf("%d", &id);
	while(l){
	if(checkid(id)==0)//For checking if any book by that ID exists.
	{
		gotoxy(21,13);
	printf("\aThe book id already exists\a");
	getche();
	mainmenu();
	return 0;
	}
	//removed \n\t
	book.book_id=id;
	printf("\n\t\tBook Name: ");
	fflush(stdin);
	gets(book.title);
	printf("\n\t\tAuthor: ");
	gets(book.author);
	fflush(stdin);
	printf("\n\t\tQuantity: ");
	scanf("%d",&book.quantity);
	printf("\n\t\tPrice: ");
	scanf("%f",&book.price);
	return 1;
	}


}
//Part of addbooks
int checkid(int id)
{
	//Check if the book exists in the library or not

	rewind(fp);
	while(fread(&book,sizeof(book),1,fp)==1)
    //Reads ID's from the file for matching with the input ID
	if((book.book_id)==id)
	{
		return 0;//0 if book exists
	}
	return 1;// 1 if it doesn't exist
}

void view()
{
	int line=4;
	system("cls");
	printf("---------------------------------BOOK LIST-------------------------------------");
	gotoxy(0,2);
	printf("Category");
	gotoxy(20,2);
	printf("Book ID");
	gotoxy(30,2);
	printf("Book Name");
	gotoxy(45,2);
	printf("Author");
	gotoxy(60,2);
	printf("Quantity");
	gotoxy(70,2);
	printf("Price");
	printf("\n\n");

	fp=fopen("AllBooks.dat", "rb");
	//Read mode because we won't be editing in this screen

	//1 means successful reading
	//0 means done or endoffile
	while(fread(&book,sizeof(book),1,fp)==1)
	{
	gotoxy(0,line);
	printf("%s",book.category);
	gotoxy(20,line);
	printf("%d",book.book_id);
	gotoxy(30,line);
	printf("%s",book.title);
	gotoxy(45,line);
	printf("%s",book.author);
	gotoxy(60,line);
	printf("%d",book.quantity);
	gotoxy(70,line);
	printf("%0.2f",book.price);
	line=line+2;
	}
	fclose(fp);
	gotoxy(20,line+1);
	printf(" Enter a key to return to main menu");
	getche();
	if(z==1)//Because view mode can be accessed from both the modes.
	librarian();
	else
	student();

}

void searchbooks()
{
	system("cls");
	int no,find=0,bk=1;
	//bk=No of books found
	//find=If the book is found or not
	char c;//Choice for exit/return
	int i=0;//No of repititions in the search by author
	char name[30]; //name is the book's name to be searched!
	gotoxy(25,2);
	int j=4;
	//Menu for the searching
	printf("Welcome to the Search Menu");
	gotoxy(20,4);
	printf("Enter your choice for the search");
	gotoxy(23,6);
	printf("1. Search by Name");
	gotoxy(23,8);
	printf("2. Search by Author");
	gotoxy(23,10);
	printf("3. Search by Category");
	gotoxy(23,12);
	printf("4. Return to the menu.");
	gotoxy(23,14);
	printf("Enter your choice : ");
	gotoxy(43,14);
	scanf("%d", &num);
	fp=fopen("AllBooks.dat","rb");
	rewind(fp);
	switch (num)
	{

		case 1:
		//Case 1 is SEARCH BY THE NAME
		system("cls");
		gotoxy(25,2);
		printf("Enter the name of the book  :  ");
		fflush(stdin);
		gets(name);
		while(fread(&book,sizeof(book),1,fp)==1)//Read from while until data exists
		{
			if(strstr(book.title,(name))!=0)//Checking string within a string
			{
				gotoxy(25,j+2);
				printf("-----Book No. %d----", bk);
				gotoxy(25,j+4);
				printf("Book Title: %s", book.title);
				gotoxy(25,j+6);
				printf("Authors name: %s", book.author);
				gotoxy(25,j+8);
				printf("Book ID: %d", book.book_id);
				gotoxy(25,j+10);
				printf("Book Quantity: %d", book.quantity);
				gotoxy(25,j+12);
				printf("Book Price: %.2f", book.price);
				j=j+12;
				find=1;
				bk++;
			}
		}

		if(find==0)//No book was found.
		{
			gotoxy(25,4);
			printf("No such book found!");
		}

		printf("\n\n\t\t\t Do you wish to return to the menu? (Y/N):  ");
		fflush(stdin);
		c=getche();
		if(c=='Y' || c=='y')
		{
			getche();
			librarian();
			break;
		}
		else if(c=='N'|| c=='n')
		{
			exit(0);
		}
		break;

		case 2:
		//Case 2 is SEARCH BY THE AUTHOR's NAME
		system("cls");
		gotoxy(25,2);
		printf("Enter the name of the Author : ");
		fflush(stdin);
		gets(name);
		while(fread(&book,sizeof(book),1,fp)==1)
		{
			if(strstr(book.author,(name))!=0)
			{
				gotoxy(25,j+2);
				printf("-----Book No. %d----", bk);
				gotoxy(25,j+4);
				printf("Book Title: %s", book.title);
				gotoxy(25,j+6);
				printf("Authors name: %s", book.author);
				gotoxy(25,j+8);
				printf("Book ID: %d", book.book_id);
				gotoxy(25,j+10);
				printf("Book Quantity: %d", book.quantity);
				gotoxy(25,j+12);
				printf("Book Price: %.2f", book.price);
				j=j+12;
				find=1;
				bk++;
			}
		}
		if(find==0)//No book was found.
		{
			gotoxy(25,4);
			printf("No book found of author : %s", name);
		}


		printf("\n\n\t\t\t Do you wish to return to the menu? (Y/N):  ");
		fflush(stdin);
		c=getche();
		if(c=='Y' || c=='y')
		{
			getche();
			librarian();
			break;
		}
		else if(c=='N'|| c=='n')
		{
			exit(0);
		}

		break;

		case 3:
		//Case 3 is SEARCH BY Category
		system("cls");
		gotoxy(25,2);
		printf("Enter the Category: ");
		fflush(stdin);
		gets(name);
		while(fread(&book,sizeof(book),1,fp)==1)
		{
			if(strstr(book.category,(name))!=0)
			{
				gotoxy(25,j+2);
				printf("-----Book No. %d----", bk);
				gotoxy(25,j+4);
				printf("Category: %s", book.category);
				gotoxy(25,j+6);
				printf("Book Title: %s", book.title);
				gotoxy(25,j+8);
				printf("Authors name: %s", book.author);
				gotoxy(25,j+10);
				printf("Book ID: %d", book.book_id);
				gotoxy(25,j+12);
				printf("Book Quantity: %d", book.quantity);
				gotoxy(25,j+14);
				printf("Book Price: %.2f", book.price);
				j=j+14;
				find=1;
				bk++;
			}
		}
		if(find==0)
		{
			gotoxy(25,4);
			printf("No book found in this category : %s", name);
		}


		printf("\n\n\t\t\t Do you wish to return to the menu? (Y/N):  ");
		fflush(stdin);
		c=getche();
		if(c=='Y' || c=='y')
		{
			getche();
			librarian();
			break;
		}
		else if(c=='N'|| c=='n')
		{
			exit(0);
		}

		break;

		case 4:
             librarian();
             break;

		default:
				gotoxy(21,17);
				printf("Wrong Choice!");
				gotoxy(21,19);
				printf("Press Y to restart or any key to return to the menu.");
				getche();
				searchbooks();

	}
	fclose(fp);
}

void editbooks()
{
	system("cls");
	int j=4,find=0,bk=1,o;
	char name[30],c,ch;
	fp=fopen("AllBooks.dat","rb+");
	gotoxy(30,2);
	printf("EDIT MODE");
	gotoxy(20,4);
	printf("Enter your choice to edit: ");
	gotoxy(20,6);
	printf("1.Search the book by name. ");
	gotoxy(20,8);
	printf("2.Search the book by the Author's name. ");
	gotoxy(20,10);
	printf("3. Return to the menu. ");
	gotoxy(20,12);
	printf("Enter your choice : ");
	scanf("%d", &o);
	switch(o)
	{
		case 1:
		//Search by title/edit
			system("cls");
			gotoxy(25,2);
			printf("Enter the books name : ");
			fflush(stdin);
			gets(name);
			while(fread(&book,sizeof(book),1,fp)==1)
			{
				//Search by the complete name only
				//Accessing the record was hard in keyword searching..
				if(strcmp(book.title,(name))==0)
				{
					gotoxy(25,j);
					printf("----BOOK DATA----");
					gotoxy(25,j+2);
					printf("Book ID: %d", book.book_id);
					gotoxy(25,j+4);
					printf("Book Title: %s", book.title);
					gotoxy(25,j+6);
					printf("Authors name: %s", book.author);
					gotoxy(25,j+8);
					printf("Book ID: %d", book.book_id);
					gotoxy(25,j+10);
					printf("Book Quantity: %d", book.quantity);
					gotoxy(25,j+12);
					printf("Book Price: %.2f", book.price);
					find=1;//A book is found.
				}
			}

			if(find==0)//No book was found of the name provided
			{
			gotoxy(25,4);
			printf("---No such book found!---");
			gotoxy(25,7);
			printf("Press 1 for Main Menu.");
			gotoxy(25,9);
			printf("Press 2 to exit. ");
			gotoxy(25,11);
			printf("Enter your choice : ");
			switch(getche())
			{
				case '1':
					librarian();
					break;

				case '2':
					exit(0);
			}

			}
			//If and only if a record/book is found, the editing option is visible.
			if(find==1)
			{
			gotoxy(25,18);
			printf("---------------");
			gotoxy(25,20);
			printf("Press 'enter' to enter edit mode.");
			if(getche()==13 )
			{
				//Could replace j with 4.
					system("cls");
					gotoxy(25,j);
					printf("----NEW BOOK DATA----");
					gotoxy(25,j+2);
					printf("New Book ID: ");
					scanf("%d", &book.book_id);
					gotoxy(25,j+4);
					printf("New Book Title: ");
					fflush(stdin);
					gets(book.title);
					gotoxy(25,j+6);
					printf("New Authors name: ");
					fflush(stdin);
					gets(book.author);
					gotoxy(25,j+8);
					printf("New Book Quantity: ");
					scanf("%d", &book.quantity);
					gotoxy(25,j+10);
					printf("New Book Price: ");
					scanf("%f", &book.price);

					fseek(fp,ftell(fp)-sizeof(book),0);
					/*To further understand the concept used above
					ftell(fp) recieves and outputs the current position or
					the position on which the record was found. sizeof(book) is the
					size of the data which is to be stored in the fp, which is 100
					for a single record. ftell(fp) - sizeof(book)
					long int p,q,r;
					q=ftell(fp);
					printf("%d", q);
					r=sizeof(book);
					printf("%d", r);
					p=ftell(fp)-sizeof(book);
					printf("%ld",p);
					Dont put anyhing in between the fseek function.
					It would shift the position in the fp.
					fseek(fp,0,SEEK_CUR); Doesnt work.*/
					fwrite(&book,sizeof(book),1,fp);
					fclose(fp);
			}
				gotoxy(25,16);
				printf("------------------");
				gotoxy(25,18);
				printf("Record Edited Successfully!");
				gotoxy(25,20);
				printf("Press enter to return to the main menu. ");
				getche();
				librarian();

			}
			break;

			case 2:

			//Search by author/edit
			system("cls");
			gotoxy(25,2);
			printf("Enter the authors name : ");
			fflush(stdin);
			gets(name);
			while(fread(&book,sizeof(book),1,fp)==1)
			{
				//Search by the complete name only.
				if(strcmp(book.author,(name))==0)
				{
					gotoxy(25,j);
					printf("----BOOK DATA----");
					gotoxy(25,j+2);
					printf("Book ID: %d", book.book_id);
					gotoxy(25,j+4);
					printf("Book Title: %s", book.title);
					gotoxy(25,j+6);
					printf("Authors name: %s", book.author);
					gotoxy(25,j+8);
					printf("Book ID: %d", book.book_id);
					gotoxy(25,j+10);
					printf("Book Quantity: %d", book.quantity);
					gotoxy(25,j+12);
					printf("Book Price: %.2f", book.price);
					find=1;//A book is found.
				}

			}

			if(find==0)//No book was found of the name provided
			{
			gotoxy(25,4);
			printf("---No such book found!---");
			gotoxy(25,7);
			printf("Press 1 for Main Menu.");
			gotoxy(25,9);
			printf("Press 2 to exit. ");
			gotoxy(25,11);
			printf("Enter your choice : ");
			switch(getche())
			{
				case '1':
					librarian();
					break;
				case '2':
					exit(0);
			}

			}
			//If and only if a record/book is found, the editing option is visible.
			if(find==1)
			{
			gotoxy(25,18);
			printf("---------------");
			gotoxy(25,20);
			printf("Press 'enter' to enter edit mode.");
			if(getche()==13 )
			{
				//Could replace j with 4.
				system("cls");
				gotoxy(25,j);
				printf("----NEW BOOK DATA----");
				gotoxy(25,j+2);
				printf("New Book ID: ");
				scanf("%d", &book.book_id);
				gotoxy(25,j+4);
				printf("New Book Title: ");
				fflush(stdin);
				gets(book.title);
				gotoxy(25,j+6);
				printf("New Authors name: ");
				fflush(stdin);
				gets(book.author);
				gotoxy(25,j+8);
				printf("New Book Quantity: ");
				scanf("%d", &book.quantity);
				gotoxy(25,j+10);
				printf("New Book Price: ");
				scanf("%f", &book.price);

				fseek(fp,ftell(fp)-sizeof(book),0);
					/*To further understand the concept used above
					ftell(fp) recieves and outputs the current position or
					the position on which the record was found. sizeof(book) is the
					size of the data which is to be stored in the fp, which is 100
					for a single record. ftell(fp) - sizeof(book)
					long int p,q,r;
					q=ftell(fp);
					printf("%d", q);
					r=sizeof(book);
					printf("%d", r);
					p=ftell(fp)-sizeof(book);
					printf("%ld",p);
					Dont put anyhing in between the fseek function.
					It would shift the position in the fp.
					fseek(fp,0,SEEK_CUR); Doesnt work.*/
				fwrite(&book,sizeof(book),1,fp);
				fclose(fp);
			}
				gotoxy(25,16);
				printf("------------------");
				gotoxy(25,18);
				printf("Record Successfully Edited!");
				gotoxy(25,20);
				printf("Press enter to return to the main menu. ");
				getche();
				librarian();

			}
            break;

            case 3: librarian();
                         break;
            default: gotoxy(20,15);
                        printf("Wrong input!");
                        getche();
                        gotoxy(20,17);
                        printf("Press Y to restart or any key to return to the menu.");
                        ch=getche();
                        if(ch=='y' || ch=='Y')
                            editbooks();
                        else
                            librarian();
                        break;
	}
}

void deletebooks()
{
	if(k==0)
	system("cls");
	int ch,j=4,find=0;
	char name[40],ch1;
	fp=fopen("AllBooks.dat","rb");//To read from
	fl=fopen("Deleted.dat", "wb+");
	//Temporary file for shifting records except the book to be deleted.
	rewind(fp);
	gotoxy(25,2);
	printf("-----DELETE BOOKS-----");
	gotoxy(25,4);
	printf("1. Search the book by name. ");
	gotoxy(25,6);
	printf("2. Search the book by the Author's name. ");
	gotoxy(25,8);
	printf("Enter your choice : ");
	scanf("%d", &ch);
	if(ch>3 || ch<=0)
	{
		gotoxy(17,12);
		printf("Wrong choice. Press enter to return to the main menu.");
		gotoxy(17,13);
		getche();
		librarian();

	}

	switch(ch)
	{
		case 1:
			//Search by title/edit
			system("cls");
			gotoxy(25,2);
			printf("Enter the name of the book : ");
			fflush(stdin);
			gets(name);
			while(fread(&book,sizeof(book),1,fp)==1)
			{
				//Search by the complete name only.
				if(strcmp(book.title,(name))==0)
				{
					gotoxy(25,j);
					printf("----BOOK DATA----");
					gotoxy(25,j+2);
					printf("Book ID: %d", book.book_id);
					gotoxy(25,j+4);
					printf("Book Title: %s", book.title);
					gotoxy(25,j+6);
					printf("Authors name: %s", book.author);
					gotoxy(25,j+8);
					printf("Book Category: %s", book.category);
					//Not working with -> the pointer structure
					gotoxy(25,j+10);
					printf("Book Quantity: %d", book.quantity);
					gotoxy(25,j+12);
					printf("Book Price: %.2f", book.price);
					find=1;//A book is found.
				}
			}

			if(find==0)//No book was found of the name provided
			{
				gotoxy(25,4);
				printf("---No such book found!---");
				gotoxy(25,7);
				printf("Press 1 for Main Menu.");
				gotoxy(25,9);
				printf("Press 2 to exit. ");
				gotoxy(25,11);
				printf("Enter your choice : ");
				switch(getche())
				{
					case '1':
						librarian();
						break;

					case '2':
						exit(0);
				}
			}
			while(find==1)
			{
				gotoxy(25,18);
				printf("---------------");
				gotoxy(25,20);
				printf("Do you wish to delete the book? (Y/N) ");
				ch1=getche();
				if(ch1=='Y' || ch1=='y')
				{
					//fl=fopen("Deleted.dat","ab+");
					rewind(fp);
					while(fread(&book,sizeof(book),1,fp)==1)
					{
						//if(book.title!=name)
					    if(strcmp(book.title,(name))!=0)
						{
							fseek(fl,0,0);//1 for current
							//0th position from seek_current.
							fwrite(&book,sizeof(book),1,fl);
						}
					}

					fclose(fl);
					fclose(fp);
					remove("AllBooks.dat");
					rename("Deleted.dat","AllBooks.dat");
				}
				find=0;
				gotoxy(25,22);
				printf("The record of the book has been deleted.");
				getche();
				librarian();

			}
		case 2://Search and delete by the author's name.
			system("cls");
			//fp=fopen("AllBooks.dat","rb");
			//fl=fopen("Deleted.dat", "wb+");
			//rewind(fp);
			gotoxy(25,2);
			printf("Enter the name of the author : ");
			fflush(stdin);
			gets(name);
			while(fread(&book,sizeof(book),1,fp)==1)
			{
				//Search by the complete name only.
				if(strcmp(book.author,(name))==0)
				{
					gotoxy(25,j);
					printf("----BOOK DATA----");
					gotoxy(25,j+2);
					printf("Book ID: %d", book.book_id);
					gotoxy(25,j+4);
					printf("Book Title: %s", book.title);
					gotoxy(25,j+6);
					printf("Authors name: %s", book.author);
					gotoxy(25,j+8);
					printf("Book Category: %s", book.category);
					//Not working with -> the pointer structure
					gotoxy(25,j+10);
					printf("Book Quantity: %d", book.quantity);
					gotoxy(25,j+12);
					printf("Book Price: %.2f", book.price);
					find=1;//A book is found.
				}
			}

			if(find==0)//No book was found of the name provided
			{
				gotoxy(25,4);
				printf("---No such book found!---");
				gotoxy(25,7);
				printf("Press 1 for Main Menu.");
				gotoxy(25,9);
				printf("Press 2 to exit. ");
				gotoxy(25,11);
				printf("Enter your choice : ");
				switch(getche())
				{
					case '1':
						librarian();
						break;

					case '2':
						exit(0);
				}
			}
			while(find==1)
			{
				gotoxy(25,18);
				printf("---------------");
				gotoxy(25,20);
				printf("Do you wish to delete the book? (Y/N) ");
				ch1=getche();
				if(ch1=='Y' || ch1=='y')
				{
					//fl=fopen("Deleted.dat","ab+");
					//rewind(fp);
					while(fread(&book,sizeof(book),1,fp)==1)
					{
						//if(book.title!=name)
					    if(strcmp(book.author,(name))!=0)
						{
							fseek(fl,0,0);//1 for current
							//0th position from seek_current.
							fwrite(&book,sizeof(book),1,fl);
						}
					}

					fclose(fl);
					fclose(fp);
					remove("AllBooks.dat");
					rename("Deleted.dat","AllBooks.dat");
				}
				find=0;
				gotoxy(25,22);
				printf("The record of the book has been deleted.");
				getche();
				librarian();
				}
		}
}

void issuebooks()
{
	if(k==0)
	system("cls");
	int comp=0,code;
	char ch;
	int choice, search,j=4,find=0;//stid is student's id
	char name[30],c;
	code=rand()%1000;

	rewind(fp);
	gotoxy(20,1);
	printf("ISSUE SECTION");
	gotoxy(10,5);
	printf(" 1. Issue a Book");
	gotoxy(10,7);
	printf(" 2. View Issued Book");
	gotoxy(10,10);
	printf("Enter your choice :  ");
	scanf("%d", &choice);

	switch(choice)
	{
		case 1:
				system("cls");
				gotoxy(25,2);
				printf("ISSUE BOOK");
				gotoxy(25,4);
				printf("1. Search the book by name");
				gotoxy(25,6);
				printf("2. Search the book by the Authors name");
				gotoxy(25,8);
				printf("Enter your choice : ");
				scanf(" %d", &search);
				switch(search)
				{
					case 1:
						//Case 1 is SEARCH BY THE NAME
						system("cls");
						gotoxy(25,2);
						printf("Enter the name of the book :  ");
						fflush(stdin);
						gets(name);
						fp=fopen("AllBooks.dat", "rb");
						//Contains the records of books
						fs=fopen("IssueRecords.dat", "ab+");
						//To store the data of the issued book.
						while(fread(&book,sizeof(book),1,fp)==1 && find==0)
						{
						if(strcmp(book.title,(name))==0)
						{
						gotoxy(25,j);
						printf("---------Book Data---------");
						gotoxy(25,j+2);
						printf("Book Title: %s", book.title);
						gotoxy(25,j+4);
						printf("Authors name: %s", book.author);
						gotoxy(25,j+6);
						printf("Book Category: %s", book.category);
						gotoxy(25,j+8);
						printf("Book ID: %d", book.book_id);
						gotoxy(25,j+10);
						printf("Book Price: %.2f", book.price);
						find=1;
						gotoxy(25,16);
						printf("Do you wish to issue this book? (Y/N) ");
						ch=getche();
						if(ch=='Y' || ch=='y')
						{
							gotoxy(25,18);
							printf("Enter your name : ");
							fflush(stdin);
							gets(book.stname);
							gotoxy(25,20);
							printf("Enter your ID : ");
							fflush(stdin);
							scanf("%d", &book.stid);

							system("cls");
							gotoxy(25,3);
							printf("-----Issued Book Data-----");
							gotoxy(25,5);
							printf("Issued To : %s", book.stname);
							gotoxy(25,7);
                            printf("Issue Code : %d", code);
                            book.issuecode=code;
                            gotoxy(25,9);
							printf("Issue Date : %d-%d-%d", tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900 );
							book.issuedate=tm.tm_mday;
							book.issuemonth=tm.tm_mon+1;

							//Issue Dates exceeding the last date of the month.
							if((tm.tm_mday+15)>31)
							{
							//(tm.tm_mday+15)>30
							//Days in a month
								tm.tm_mday=(tm.tm_mday+15)-31;
								tm.tm_mon+=2;
								comp=1;
							}
								book.returndate=tm.tm_mday;
								book.returnmonth=tm.tm_mon+1;

							if(comp==0){
							book.returndate=tm.tm_mday+15;
							book.returnmonth=tm.tm_mon+1;}

							gotoxy(25,11);
							printf("Return Date : %d-%d-%d",tm.tm_mday+15, tm.tm_mon + 1, tm.tm_year + 1900 );
                            fo=fopen("graph.dat", "rb+");
							if(strcmp(book.category,categories[0])==0)
                                cat.pro+=1;
                            else if(book.category==categories[1])
                                cat.ds+=1;
							else if(book.category==categories[2])
                                cat.isl+=1;
							else if(book.category==categories[3])
                                cat.pst+=1;
							else if(book.category==categories[4])
                                cat.ce=1+cat.ce;
							else if(book.category==categories[5])
                                cat.arch+=1;
                            fwrite(&cat,sizeof(cat),1,fo);
                            fclose(fo);
							fseek(fs,0,SEEK_END);
							fwrite(&book,sizeof(book),1,fs);
						}
						else if(ch=='N' || ch=='n')
						{
							librarian();
						}

						}

						}
						if(find==0)
						{
							gotoxy(25,4);
							printf("No such book found!");
						}


						fclose(fs);
						fclose(fp);
						gotoxy(25,18);
						printf("Press enter to return to the menu. ");
						getche();
						student();
						break;

					case 2://Search the book by author then issue it.
						system("cls");
						gotoxy(25,2);
						printf("Enter the name of the author :  ");
						fflush(stdin);
						gets(name);
						fp=fopen("AllBooks.dat", "rb");
						fs=fopen("IssueRecords.dat", "ab+");
						while(fread(&book,sizeof(book),1,fp)==1 && find==0)
						{
						if(strcmp(book.author,(name))==0)
						{
						gotoxy(25,j);
						printf("---------Book Data---------");
						gotoxy(25,j+2);
						printf("Book Title: %s", book.title);
						gotoxy(25,j+4);
						printf("Authors name: %s", book.author);
						gotoxy(25,j+6);
						printf("Book Category: %s", book.category);
						gotoxy(25,j+8);
						printf("Book ID: %d", book.book_id);
						gotoxy(25,j+10);
						printf("Book Price: %.2f", book.price);
						find=1;
						gotoxy(25,16);
						printf("Do you wish to issue this book? (Y/N) ");
						ch=getche();
						if(ch=='Y' || ch=='y')
						{
							gotoxy(25,18);
							printf("Enter your name : ");
							fflush(stdin);
							gets(book.stname);
							gotoxy(25,20);
							printf("Enter your ID : ");
							fflush(stdin);
							scanf("%d", &book.stid);

							system("cls");
							gotoxy(25,3);
							printf("-----Issued Book Data-----");
							gotoxy(25,5);
							printf("Issued To : %s", book.stname);
							gotoxy(25,7);
                            printf("Issue Code : %d", code);
                            book.issuecode=code;
                            gotoxy(25,9);
							printf("Issue Date : %d-%d-%d", tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900 );
							book.issuedate=tm.tm_mday;
							book.issuemonth=tm.tm_mon+1;

							//Issue Dates exceeding the last date of the month.
							if((tm.tm_mday+15)>31)
							{
							//(tm.tm_mday+15)>30
							//Days in a month
								tm.tm_mday=(tm.tm_mday+15)-31;
								tm.tm_mon+=2;
								comp=1;
							}
								book.returndate=tm.tm_mday;
								book.returnmonth=tm.tm_mon+1;

							if(comp==0){
							book.returndate=tm.tm_mday+15;
							book.returnmonth=tm.tm_mon+1;}

							gotoxy(25,11);
							printf("Return Date : %d-%d-%d",tm.tm_mday+15, tm.tm_mon + 1, tm.tm_year + 1900 );
                            fo=fopen("graph.dat", "rb+");
							if(strcmp(book.category,categories[0])==0)
                                cat.pro+=1;
                            else if(book.category==categories[1])
                                cat.ds+=1;
							else if(book.category==categories[2])
                                cat.isl+=1;
							else if(book.category==categories[3])
                                cat.pst+=1;
							else if(book.category==categories[4])
                                cat.ce=1+cat.ce;
							else if(book.category==categories[5])
                                cat.arch+=1;
                            fwrite(&cat,sizeof(cat),1,fo);
                            fclose(fo);
                            fseek(fs,0,SEEK_END);
							fwrite(&book,sizeof(book),1,fs);
						}
						else if(ch=='n' || ch=='N')//Use N or n condition if necessary
						{
							getche();
							librarian();
						}

						}
						}
						if(find==0)
						{
							gotoxy(25,4);
							printf("No such book found!");
						}

						}
						fclose(fs);
						fclose(fp);
						getche();
						student();
						break;

			//Closing of the inner switch.

			case 2: //View issued books.
				{
				    viewissuedbooks(0);
				}

				default:
				    gotoxy(25,20);
					printf("No such choice. Return to the menu.");
					student();
					break;

	}
}
/*
int t(void) //for time
{
/*time_t mytime;
mytime = time(NULL);
//time(&t);
printf("Date and time:%s\n",ctime(&mytime));
time_t timer;
char buffer[26];
struct tm* tm_info;

time(&timer);
tm_info = localtime(&timer);
//%H-%M-%S
strftime(buffer,26,"%Y-%m-%d",tm_info);
puts(buffer);

return 0;
}*/

void returnbook()
{
	if(k==0)
	system("cls");
	int ikk=0;
	int ch,j=4,find=0;
	char name[40],ch1;
	char bname[40];
	int code;
	fn=fopen("IssueRecords.dat","rb");
	fi=fopen("Returnbook.dat", "wb+");
	rewind(fn);
	gotoxy(25,2);
	printf("-----RETURN ISSUED BOOKS-----");
	gotoxy(25,4);
	printf("Enter your name: ");
	fflush(stdin);
	gets(name);
	gotoxy(25,6);
	printf("Enter the book you issued: ");
	fflush(stdin);
	gets(bname);
	gotoxy(25,8);
	printf("Enter the issue code: ");
	fflush(stdin);
	scanf("%d", &code);


	while(fread(&book,sizeof(book),1,fn)==1)
			{
				//Search by the complete name only.
				if((code==book.issuecode) && (strcmp(book.title,(bname))==0))
				{
					system("cls");
					gotoxy(25,j);
					printf("----BOOK DATA----");
					gotoxy(25,j+2);
					printf("Book ID: %d", book.book_id);
					gotoxy(25,j+4);
					printf("Book Title: %s", book.title);
					gotoxy(25,j+6);
					printf("Authors name: %s", book.author);
					gotoxy(25,j+8);
					printf("Book Category: %s", book.category);
					//Not working with -> the pointer structure
					gotoxy(25,j+10);
					printf("Book Quantity: %d", book.quantity);
					gotoxy(25,j+12);
					printf("Book Price: %.2f", book.price);
					find=1;//A book is found.
				}
			}

			if(find==0)//No book was found of the name provided
			{
				gotoxy(25,4);
				printf("---No book issued by this name!---");
				gotoxy(25,7);
				printf("Enter a key to return to main menu");
				getche();
				student();
			}

			while(find==1)
			{
				gotoxy(25,18);
				printf("---------------");
				gotoxy(25,20);
				printf("Do you wish to return this book? (Y/N) ");
				ch1=getche();
				if(ch1=='Y' || ch1=='y')
				{

					//fl=fopen("Returnbook.dat","ab+");
					rewind(fn);
					while(fread(&book,sizeof(book),1,fn)==1)
					{
						//if(book.title!=name)
					   if((code)!=(book.issuecode))
						{
							fseek(fi,0,SEEK_END);//1 for current
							//0th position from seek_current.
							fwrite(&book,sizeof(book),1,fi);
							//printf("%d", ikk);
						}

					}
				}
				else
				student();
                fclose(fi);
                fclose(fn);
                remove("IssueRecords.dat");
                rename("Returnbook.dat","IssueRecords.dat");


				find=0;
				gotoxy(25,22);
				printf("The issued book has been returned.");
				getche();
				student();

	}

}
void bargraph()
{
   fo=fopen("graph.dat","rb");
   rewind(fo);
    fread(&cat, sizeof(cat),1,fo);
    int gd=0,gm;
    initgraph(&gd,&gm,"C://TURBOC3//BGI");
    int y1=cat.pro, y2=cat.ds, y3=cat.isl, y4=cat.pst, y5=cat.ce, y6=cat.arch;
    setlinestyle(SOLID_LINE,0,2);
    line(100,100,100,400);//Shifting 400 to 600+ for new x-axis touch
    line(100,400,800,400);

    /*Y AXIS: Original
    line(90,100,100,100);
    outtextxy(70,100,"25");
    line(90,200,100,200);
    outtextxy(70,200,"10");
    line(90,300,100,300);
    outtextxy(70,300,"5");
    outtextxy(90,410,"0");*/
    /*Y AXIS: Mine*/

    line(90,150,100,150);
    outtextxy(70,150,"25");

    line(90,200,100,200); //COMP
    outtextxy(70,200,"20");

    line(90,250,100,250); //COMP
    outtextxy(70,250,"15");

    line(90,300,100,300); //COMP
    outtextxy(70,300,"10");

    line(90,350,100,350); //COMP
    outtextxy(70,350,"5");
    outtextxy(90,410,"0");

    //X-AXIS
    line(200,410,200,400);
    outtextxy(200,420,"1");
    outtextxy(170,440,"Programming");
    line(300,410,300,400);
    outtextxy(300,420,"2");
    outtextxy(285,440,"Discrete ");
    outtextxy(280,450,"Structures");
    line(400,410,400,400);
    outtextxy(400,420,"3");
    outtextxy(380,440,"Islamiat");
    line(500,410,500,400);
    outtextxy(500,420,"4");
    outtextxy(470,440,"Pak. Studies");
    line(600,410,600,400);
    outtextxy(600,420,"5");
    outtextxy(580,440,"Civil Eng.");
    line(700,410,700,400);
    outtextxy(700,420,"6");
    outtextxy(680,440,"Architecture");
    outtextxy(90,90,"Y-AXIS");
    outtextxy(810,400,"X-AXIS");

    setlinestyle(SOLID_LINE,0,3);
     bar(180,400-(y1*10),230,400);
     bar(280,400-(y2*10),330,400);
     bar(380,400-(y3*10),430,400);
     bar(480,400-(y4*10),530,400);
     bar(580,400-(y5*10),630,400);
     bar(680,400-(y6*10),730,400);


    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    outtextxy(450,50,"GRAPH");
    fclose(fo);
    getch();
    closegraph();



}

void viewissuedbooks(int z)
{
                    system("cls");
					int j=4;
					printf("*******************************ISSUED BOOKS*******************************\n");
					gotoxy(1,2);
					printf("Student Name      Category     IssueCode   Book Name  Issue Date  Return Date");
					fs=fopen("IssueRecords.dat","rb");
					while(fread(&book,sizeof(book),1,fs)==1)
					{

					gotoxy(2,j);
					printf("%s",book.stname);
					gotoxy(18,j);
					printf("%s",book.category);
					gotoxy(36,j);
					printf("%d",book.issuecode);
					gotoxy(45,j);
					printf("%s",book.title);
					gotoxy(59,j);
					printf("%d-%d",book.issuedate,book.issuemonth);
					gotoxy(71,j);
					printf("%d-%d",book.returndate,book.returnmonth);
					j=j+2;

					}
					fclose(fs);
					getche();
                    if(z==1)
                    librarian();
                    if(z==0)
                    student();
}
