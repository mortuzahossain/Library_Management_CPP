#include <iostream>
//other header files
#include <windows.h>
#include <cstdio>
// some header files from c to make this program more easy
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <time.h>

using namespace std;

/*
 sudo password
*/

char password[10]={"123"};


/*
List of function
 */
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void Password();
void issuerecord();

/*
List Of Global Variables which i will use in this program
 */


#define RETURNTIME 15
char catagories[][15]={"Computer","Electronics","Electrical","Civil","Mechanical","Architecture"};
FILE *fp,*ft,*fs;
int s;
char findbook;

COORD coord = {0, 0};
COORD max_res,cursor_size;


//Structure for books

struct meroDate
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    float Price;
    int count;
    int rackno;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books a;


//function t for time


int t(void)
{
    time_t t;
    time(&t);
    printf("Date and time:%s\n",ctime(&t));
    return 0 ;
}

void gotoxy (int x, int y)
{
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void loaderanim()
{
    int loader;
    system("cls");
    gotoxy(20,10);
    cout<<"LOADING........\n"<<endl;
    gotoxy(22,11);

    for(loader=1;loader<20;loader++)
    {
        delay(100);
        printf("%c",219);
    }
}

void mainmenu()
{
    system("cls");
    int i;
    gotoxy(20,3);
    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU";
    cout<<" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    gotoxy(20,5);
    cout<<"\xDB\xDB\xDB\xDB\xB2 1. Add Books   ";
    gotoxy(20,7);
    cout<<"\xDB\xDB\xDB\xDB\xB2 2. Delete books";
    gotoxy(20,9);
    cout<<"\xDB\xDB\xDB\xDB\xB2 3. Search Books";
    gotoxy(20,11);
    cout<<"\xDB\xDB\xDB\xDB\xB2 4. Issue Books";
    gotoxy(20,13);
    cout<<"\xDB\xDB\xDB\xDB\xB2 5. View Book list";
    gotoxy(20,15);
    cout<<"\xDB\xDB\xDB\xDB\xB2 6. Edit Book's Record";
    gotoxy(20,17);
    cout<<"\xDB\xDB\xDB\xDB\xB2 7. Close Application";
    gotoxy(20,19);
    cout<<"------------------------------------------";
    gotoxy(20,20);

    t();

    gotoxy(20,21);

    cout<<"Enter your choice:";

    switch(getch())
    {
        case '1':
            addbooks();
            break;
        case '2':
            deletebooks();
            break;
        case '3':
            searchbooks();
            break;
        case '4':
            issuebooks();
            break;
        case '5':
            viewbooks();
            break;
        case '6':
            editbooks();
            break;
        case '7':
            {
                system("cls");
                gotoxy(16,3);
                printf("Thanks for using the Program..");
                gotoxy(10,7);
                printf("Exiting in 5 second...........>");
                delay(5000);
                exit(0);
            }
        default:
        {
            gotoxy(10,23);
            printf("\aWrong Entry!!Please re-entered correct option");
            if(getch())
            mainmenu();
        }

    }
}

void addbooks(void)
{

    system("cls");
    int i;
    gotoxy(20,5);
    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SELECT CATEGOIES";
    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    gotoxy(20,7);
    cout<<"\xDB\xDB\xDB\xDB\xB2 1. Computer";
    gotoxy(20,9);
    cout<<"\xDB\xDB\xDB\xDB\xB2 2. Electronics";
    gotoxy(20,11);
    cout<<"\xDB\xDB\xDB\xDB\xB2 3. Electrical";
    gotoxy(20,13);
    cout<<"\xDB\xDB\xDB\xDB\xB2 4. Civil";
    gotoxy(20,15);
    cout<<"\xDB\xDB\xDB\xDB\xB2 5. Mechanical";
    gotoxy(20,17);
    cout<<"\xDB\xDB\xDB\xDB\xB2 6. Architecture";
    gotoxy(20,19);
    cout<<"\xDB\xDB\xDB\xDB\xB2 7. Back to main menu";
    gotoxy(20,21);
    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    gotoxy(20,22);


    cout<<"Enter your choice:";
    cin>>s;

    if(s==7)
    mainmenu() ;
    system("cls");

    fp=fopen("library.dat","ab+");

    if(getdata()==1)
    {
        a.cat=catagories[s-1];
        fseek(fp,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        gotoxy(21,14);
        cout<<"The record is successfully saved";
        gotoxy(21,15);
        cout<<"Save any more?(Y / N):";

        if(getch()=='n')
            mainmenu();
        else
            system("cls");
            addbooks();
    }
}

void deletebooks()
{
    system("cls");
    int d;
    char another='y';
    while(another=='y')

    {
        system("cls");
        gotoxy(10,5);

        cout<<"Enter the Book ID to  delete:";
        cin>>d;

        fp=fopen("library.dat","rb+");
        rewind(fp);

        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.id==d)
            {
                gotoxy(10,7);
                cout<<"The book record is available";
                gotoxy(10,8);
                cout<<"Book name is "<<a.name;
                gotoxy(10,9);
                cout<<"Rack No. is "<<a.rackno;
                findbook='t';
            }
        }

        if(findbook!='t')
        {
            gotoxy(10,10);
            cout<<"No record is found modify the search";
            if(getch())
                mainmenu();
        }

        if(findbook=='t' )
        {
            gotoxy(10,9);
            cout<<"Do you want to delete it?(Y/N):";

            if(getch()=='y')
            {
                ft=fopen("test.dat","wb+");
                rewind(fp);

                while(fread(&a,sizeof(a),1,fp)==1)
                {
                    if(a.id!=d)
                    {
                        fseek(ft,0,SEEK_CUR);
                        fwrite(&a,sizeof(a),1,ft);
                    }
                }

                fclose(ft);
                fclose(fp);
                remove("library.dat");
                rename("test.dat","library.dat");
                fp=fopen("library.dat","rb+");

                if(findbook=='t')
                {
                    gotoxy(10,10);
                    cout<<"The record is successfully deleted";
                    gotoxy(10,11);
                    cout<<"Delete another record?(Y/N)";
                }
            }

            else
                mainmenu();
                fflush(stdin);
                another=getch();
        }
    }

    gotoxy(10,15);
    mainmenu();
}

void searchbooks()
{
    system("cls");
    int d;
    cout<<"*****************************Search Books*********************************";
    gotoxy(20,10);
    cout<<"\xDB\xDB\xDB\xB2 1. Search By ID";
    gotoxy(20,14);
    cout<<"\xDB\xDB\xDB\xB2 2. Search By Name";
    gotoxy( 15,20);

    cout<<"Enter Your Choice";
    fp=fopen("library.dat","rb+");
    rewind(fp);

    switch(getch())
    {
        case '1':
        {
            system("cls");
            gotoxy(25,4);
            cout<<"****Search Books By Id****";
            gotoxy(20,5);
            cout<<"Enter the book id:";
            scanf("%d",&d);

            gotoxy(20,7);
            cout<<"Searching........";

            while(fread(&a,sizeof(a),1,fp)==1)
            {
                if(a.id==d)
                    {
                        delay(2);
                        gotoxy(20,7);
                        cout<<"The Book is available";
                        gotoxy(20,8);
                        cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                        cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                        gotoxy(20,9);
                        printf("\xB2 ID:%d",a.id);
                        gotoxy(47,9);
                        cout<<"\xB2";
                        gotoxy(20,10);
                        printf("\xB2 Name:%s",a.name);
                        gotoxy(47,10);
                        cout<<"\xB2";
                        gotoxy(20,11);
                        printf("\xB2 Author:%s ",a.Author);
                        gotoxy(47,11);
                        cout<<"\xB2";
                        gotoxy(20,12);
                        printf("\xB2 Qantity:%d ",a.quantity);
                        gotoxy(47,12);
                        cout<<"\xB2";
                        gotoxy(47,11);
                        cout<<"\xB2";
                        gotoxy(20,13);
                        printf("\xB2 Price:Rs.%.2f",a.Price);
                        gotoxy(47,13);
                        cout<<"\xB2";
                        gotoxy(20,14);
                        printf("\xB2 Rack No:%d ",a.rackno);
                        gotoxy(47,14);
                        cout<<"\xB2";
                        gotoxy(20,15);
                        cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                        cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                        findbook='t';
                    }
                }

                if(findbook!='t')
                {
                    gotoxy(20,8);
                    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                    gotoxy(20,9);
                    cout<<"\xB2";
                    gotoxy(38,9);
                    cout<<"\xB2";
                    gotoxy(20,10);
                    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                    gotoxy(22,9);
                    cout<<"\aNo Record Found";
                }

                gotoxy(20,17);
                cout<<"Try another search?(Y/N)";

                if(getch()=='y')
                    searchbooks();
                else
                    mainmenu();
            break;
        }

        case '2':
        {
            char s[15];
            system("cls");
            gotoxy(25,4);
            cout<<"****Search Books By Name****";
            gotoxy(20,5);
            cout<<"Enter Book Name:";
            scanf("%s",s);

            int d=0;
            while(fread(&a,sizeof(a),1,fp)==1)
            {
                if(strcmp(a.name,(s))==0)
                {
                    gotoxy(20,7);
                    cout<<"The Book is available";
                    gotoxy(20,8);

                    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";

                    gotoxy(20,9);
                    printf("\xB2 ID:%d",a.id);
                    gotoxy(47,9);
                    cout<<"\xB2";
                    gotoxy(20,10);
                    printf("\xB2 Name:%s",a.name);
                    gotoxy(47,10);
                    cout<<"\xB2";
                    gotoxy(20,11);
                    printf("\xB2 Author:%s",a.Author);
                    gotoxy(47,11);
                    cout<<"\xB2";
                    gotoxy(20,12);
                    printf("\xB2 Qantity:%d",a.quantity);
                    gotoxy(47,12);
                    cout<<"\xB2";
                    gotoxy(20,13);
                    printf("\xB2 Price:Rs.%.2f",a.Price);
                    gotoxy(47,13);
                    cout<<"\xB2";
                    gotoxy(20,14);
                    printf("\xB2 Rack No:%d ",a.rackno);
                    gotoxy(47,14);
                    cout<<"\xB2";
                    gotoxy(20,15);

                    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";

                    d++;
                }
            }

            if(d==0)
            {
                gotoxy(20,8);
                cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                gotoxy(20,9);
                cout<<"\xB2";
                gotoxy(38,9);
                cout<<"\xB2";
                gotoxy(20,10);
                cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
                gotoxy(22,9);
                cout<<"\aNo Record Found";
            }

            gotoxy(20,17);
            cout<<"Try another search?(Y/N)";

            if(getch()=='y')
                searchbooks();
            else
                mainmenu();
            break;
        }

        default :
            getch();
            searchbooks();
    }

    fclose(fp);
}

void viewbooks(void)
{
    int i=0,j;
    system("cls");
    gotoxy(1,1);

    cout<<"********************************* Book List *****************************";
    gotoxy(2,2);
    cout<<" CATEGORY     ID    BOOK NAME     AUTHOR       QTY     PRICE     RackNo ";

    j=4;
    fp=fopen("library.dat","rb");

    while(fread(&a,sizeof(a),1,fp)==1)
    {
        gotoxy(3,j);
        cout<<a.cat;
        gotoxy(16,j);
        cout<<a.id;
        gotoxy(22,j);
        cout<<a.name;
        gotoxy(36,j);
        cout<<a.Author;
        gotoxy(50,j);
        cout<<a.quantity;
        gotoxy(57,j);

        printf("%.2f",a.Price);
        gotoxy(69,j);
        cout<<a.rackno<<"\n"<<endl;

        j++;
        i=i+a.quantity;
    }

    gotoxy(3,25);
    printf("Total Books =%d",i);
    fclose(fp);
    gotoxy(35,25);
    returnfunc();
}

void issuerecord()
{
    system("cls");
    gotoxy(10,8);
    printf("The Book has taken by Mr. %s",a.stname);
    gotoxy(10,9);
    printf("Issued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
    gotoxy(10,10);
    printf("Returning Date:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}

void Password(void)
{
    system("cls");
    char d[25]=" Password Protected";
    char ch,pass[10];
    int i=0,j;
    gotoxy(10,4);

    for(j=0;j<20;j++)
    {
        delay(50);
        cout<<"*";
    }

    for(j=0;j<20;j++)
    {
        delay(50);
        cout<<d[j];
    }

    for(j=0;j<20;j++)
    {
       delay(50);
       cout<<"*";
    }
    gotoxy(10,10);
    gotoxy(15,7);

    cout<<"Enter Password:";

    while(ch!=13)
    {
        ch=getch();
        if(ch!=13 && ch!=8)
        {
            putch('*');
            pass[i] = ch;
            i++;
        }
    }

    pass[i] = '\0';

    if(strcmp(pass,password)==0)
    {
        gotoxy(15,9);
        cout<<"Password match";
        gotoxy(17,10);
        cout<<"Press any key to continue.....";
        getch();
        mainmenu();
    }

    else
    {
        gotoxy(15,16);
        cout<<"\aWarning!! Incorrect Password";
        getch();
        Password();
    }
}

int checkid(int t)
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)

    if(a.id==t)
        return 0;

    return 1;
}

void returnfunc(void)
{
    {
        cout<<" Press ENTER to return to main menu";
    }

    a:
    if(getch()==13)
        mainmenu();
    else
        goto a;
}

int getdata()
{
    int t;
    gotoxy(20,3);

    cout<<"Enter the Information Below";

    gotoxy(20,4);
    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    gotoxy(20,5);
    cout<<"\xB2";
    gotoxy(46,5);
    cout<<"\xB2";
    gotoxy(20,6);
    cout<<"\xB2";
    gotoxy(46,6);
    cout<<"\xB2";
    gotoxy(20,7);
    cout<<"\xB2";
    gotoxy(46,7);
    cout<<"\xB2";
    gotoxy(20,8);
    cout<<"\xB2";
    gotoxy(46,8);
    cout<<"\xB2";
    gotoxy(20,9);
    cout<<"\xB2";
    gotoxy(46,9);
    cout<<"\xB2";
    gotoxy(20,10);
    cout<<"\xB2";
    gotoxy(46,10);
    cout<<"\xB2";
    gotoxy(20,11);
    cout<<"\xB2";
    gotoxy(46,11);
    cout<<"\xB2";
    gotoxy(20,12);

    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";

    gotoxy(21,5);
    cout<<"Category:";
    gotoxy(31,5);

    cout<<catagories[s-1];

    gotoxy(21,6);
    cout<<"Book ID:\t";
    gotoxy(30,6);

    cin>>t;

    if(checkid(t) == 0)
    {
        gotoxy(21,13);
        cout<<"\aThe book id already exists\a";
        getch();
        mainmenu();
        return 0;
    }

    a.id=t;
    gotoxy(21,7);
    cout<<"Book Name:";
    gotoxy(33,7);
    cin>>a.name;
    gotoxy(21,8);
    cout<<"Author:";
    gotoxy(30,8);
    cin>>a.Author;
    gotoxy(21,9);
    cout<<"Quantity:";
    gotoxy(31,9);
    cin>>a.quantity;
    gotoxy(21,10);
    cout<<"Price:";
    gotoxy(28,10);
    cin>>a.Price;
    gotoxy(21,11);
    cout<<"Rack No:";
    gotoxy(30,11);
    cin>>a.rackno;

    return 1;
}

void editbooks(void)
{
    system("cls");
    int c=0;
    int d,e;
    gotoxy(20,4);
    cout<<"****Edit Books Section****";
    char another='y';
    while(another=='y')
    {
        system("cls");
        gotoxy(15,6);

        cout<<"Enter Book Id to be edited:";
        cin>>d;

        fp=fopen("library.dat","rb+");
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(checkid(d)==0)
            {
                gotoxy(15,7);

                cout<<"The book is available";
                gotoxy(15,8);
                cout<<"The Book ID: "<<a.id;
                gotoxy(15,9);
                cout<<"Enter new name:";
                cin>>a.name;
                gotoxy(15,10);
                cout<<"Enter new Author:";
                cin>>a.Author;
                gotoxy(15,11);
                cout<<"Enter new quantity:";
                cin>>a.quantity;
                gotoxy(15,12);
                cout<<"Enter new price:";
                cin>>a.Price;
                gotoxy(15,13);
                cout<<"Enter new rack-no:";
                cin>>a.rackno;
                gotoxy(15,14);
                cout<<"The record is modified";

                fseek(fp,ftell(fp)-sizeof(a),0);
                fwrite(&a,sizeof(a),1,fp);
                fclose(fp);
                c=1;
            }
            if(c==0)
            {
                gotoxy(15,9);
                cout<<"No record found";
            }
        }
        gotoxy(15,16);
        cout<<"Modify another Record?(Y/N)";
        fflush(stdin);
        another=getch() ;
    }
    returnfunc();
}

void issuebooks(void)
{
    int t;
    system("cls");

    cout<<"********************************ISSUE SECTION**************************";
    gotoxy(10,5);
    cout<<"\xDB\xDB\xDB\xDb\xB2 1. Issue a Book";
    gotoxy(10,7);
    cout<<"\xDB\xDB\xDB\xDb\xB2 2. View Issued Book";
    gotoxy(10,9);
    cout<<"\xDB\xDB\xDB\xDb\xB2 3. Search Issued Book";
    gotoxy(10,11);
    cout<<"\xDB\xDB\xDB\xDb\xB2 4. Remove Issued Book";
    gotoxy(10,14);
    cout<<"Enter a Choice:";

    switch(getch())
    {
    case '1':
    {
        system("cls");
        int c=0;
        char another='y';
        while(another=='y')
        {
            system("cls");
            gotoxy(15,4);

            cout<<"***Issue Book section***";
            gotoxy(10,6);
            cout<<"Enter the Book Id:";
            cin>>t;

            fp=fopen("library.dat","rb");
            fs=fopen("Issue.dat","ab+");

            if(checkid(t)==0)
            {
                gotoxy(10,8);
                cout<<"The book record is available";
                gotoxy(10,9);
                cout<<"There are "<<a.quantity<<" Unissued books in library";
                gotoxy(10,10);
                cout<<"The name of book is"<<a.name;
                gotoxy(10,11);
                cout<<"Enter student name:";
                cin>>a.stname;
                gotoxy(10,12);

                printf("Issued date=%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
                gotoxy(10,13);

                cout<<"The BOOK of ID "<<a.id<<" is issued";

                a.duedate.dd=a.issued.dd+RETURNTIME;
                a.duedate.mm=a.issued.mm;
                a.duedate.yy=a.issued.yy;

                if(a.duedate.dd>30)
                {
                    a.duedate.mm+=a.duedate.dd/30;
                    a.duedate.dd-=30;
                }

                if(a.duedate.mm>12)
                {
                    a.duedate.yy+=a.duedate.mm/12;
                    a.duedate.mm-=12;
                }

                gotoxy(10,14);

                printf("To be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);

                fseek(fs,sizeof(a),SEEK_END);
                fwrite(&a,sizeof(a),1,fs);
                fclose(fs);
                c=1;
            }

            if(c==0)
            {
                gotoxy(10,11);
                cout<<"No record found";
            }
            gotoxy(10,15);

            cout<<"Issue any more(Y/N):";

            fflush(stdin);
            another=getche();
            fclose(fp);
        }
        break;
    }

    case '2':
    {
        system("cls");
        int j=4;

        cout<<"*******************************Issued book list*******************************\n";
        gotoxy(2,2);

        cout<<"STUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE";

        fs=fopen("Issue.dat","rb");

        while(fread(&a,sizeof(a),1,fs)==1)
        {
            gotoxy(2,j);
            cout<<a.stname;
            gotoxy(18,j);
            cout<<a.cat;
            gotoxy(30,j);
            cout<<a.id;
            gotoxy(36,j);
            cout<<a.name;
            gotoxy(51,j);

            printf("%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
            gotoxy(65,j);
            printf("%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);

            gotoxy(50,25);
            j++;
        }

        fclose(fs);
        gotoxy(1,25);
        returnfunc();
    }
    break;

    case '3':
    {
        system("cls");
        gotoxy(10,6);

        cout<<"Enter Book ID:";

        int p,c=0;
        char another='y';

        while(another=='y')
        {
            cin>>p;

            fs=fopen("Issue.dat","rb");

            while(fread(&a,sizeof(a),1,fs)==1)
            {
                if(a.id==p)
                {
                    issuerecord();
                    gotoxy(10,12);

                    cout<<"Press any key.......";

                    getch();
                    issuerecord();
                    c=1;
                }

            }
            fflush(stdin);
            fclose(fs);
            if(c==0)
            {
                gotoxy(10,8);

                cout<<"No Record Found";

            }
            gotoxy(10,13);

            cout<<"Try Another Search?(Y/N)";

            another=getch();
        }
    }
    break;

    case '4':
    {
        system("cls");
        int b;
        FILE *fg;
        char another='y';
        while(another=='y')
        {
            gotoxy(10,5);

            cout<<"Enter book id to remove:";
            cin>>b;

            fs=fopen("Issue.dat","rb+");

            while(fread(&a,sizeof(a),1,fs)==1)
            {
                if(a.id==b)
                {
                    issuerecord();
                    findbook='t';
                }

                if(findbook=='t')
                {
                    gotoxy(10,12);

                    cout<<"Do You Want to Remove it?(Y/N)";

                    if(getch()=='y')
                    {
                        fg=fopen("record.dat","wb+");
                        rewind(fs);

                        while(fread(&a,sizeof(a),1,fs)==1)
                        {
                            if(a.id!=b)
                            {
                                fseek(fs,0,SEEK_CUR);
                                fwrite(&a,sizeof(a),1,fg);
                            }
                        }

                        fclose(fs);
                        fclose(fg);

                        remove("Issue.dat");
                        rename("record.dat","Issue.dat");

                        gotoxy(10,14);
                        cout<<"The issued book is removed from list";
                    }
                }

                if(findbook!='t')
                {
                    gotoxy(10,15);
                    cout<<"No Record Found";
                }
            }

            gotoxy(10,16);

            cout<<"Delete any more?(Y/N)";

            another=getch();
        }
    }

    default:
        gotoxy(10,18);

        cout<<"\aWrong Entry!!";

        getch();
        issuebooks();
        break;
    }

    gotoxy(1,30);
    returnfunc();

}



int main()

{
    Password();
    getch();
    return 0;
}


