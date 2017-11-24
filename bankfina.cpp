#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>

void delay()
{
 for(long l=0; l<=99999999; ++l);
}

void align(int x, int y , char str[100])
{
 gotoxy(x,y);
 cout<<str;
}

void border(int x,int y,int l,int b)

{
	gotoxy(x,y);
	cout<<'$';
	for(int p=x+1; p<x+l-1; p++)			//creates the top horizontal rule
	{
		gotoxy(p,y);
		cout<<'$';
	}
	cout<<'$';

	gotoxy(x,y+b-1);
	cout<<'$';
	for(int q=x+1; q<x+l-1; q++)			//creates the bottom horizontal rule
	{
		gotoxy(q,y+b-1);
		cout<<'$';
	}

	//gotoxy(x,y);
	//cout<<'$';
	for(int r=y+1; r<y+b-1; r++)			//creates the left vertical rule
	{
		gotoxy(x,r);
		cout<<"$$";
	}
	//gotoxy(x,y+b);
	//cout<<'$';

	for(int s=y+1; s<y+b-1; s++)			//creates the right vertical rule
	{
		gotoxy(x+l-1,s);
		cout<<"$$";
	}
}

class account
{
	char username[20];
	char password[20];
	int acno;
	char name[50];
	int deposit;
public:
	void create_account();
	void show_account();
	void deposite(int);
	void withdraw(int);
	void report();
	int check_username(char user[20]);
	int check_password(char user[20], char pass[20]);
	int ret_acno();
	int ret_deposit();
};

void account::create_account()
{
	gotoxy(30,5);
	cout<<"Enter the username: ";
	gets(username);
	gotoxy(32,6);
	cout<<"Enter password: ";
	gets(password);
	gotoxy(29,8);
	cout<<"Enter The account No.: ";
	cin>>acno;
	gotoxy(21,9);
	cout<<"Enter The Name of The account Holder: ";
	gets(name);
	gotoxy(27,10);
	cout<<"Enter The Initial amount: ";
	cin>>deposit;
	gotoxy(32,20);
	cout<<"Account Created..";
	return;
}

void account::show_account()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nBalance amount : "<<deposit;
}
void account::deposite(int x)
{
	deposit+=x;
}

void account::withdraw(int x)
{
	deposit-=x;
}

void account::report()
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<deposit<<endl;
}

int account::check_username(char user[20])
{
	account ac;
	ifstream file;
	file.open("account.dat",ios::in|ios::binary);
	int i=0;
	while(file.read((char*)&ac,sizeof(ac)))
	{
		i=0;
		if(strcmpi(ac.username,user)==0)
		{
			i=1;
			break;
		}
	}
	file.close();
	return i;
}

int account::check_password(char user[20], char pass[20])
{
	account ac;
	ifstream file("account.dat", ios::in|ios::binary);
	int i=0;
	while(file.read((char*)&ac, sizeof(ac)))
	{
		i=0;
		if(strcmpi(ac.username,user)==0)
			if(strcmpi(ac.password,pass)==0)
			{
				i=1;
				break;
			}
	}
	file.close();
	return i;
}

int account::ret_acno()
{
	return acno;
}

int account::ret_deposit()
{
	return deposit;
}

void login();
void main_menu();
void transaction();
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit(int);
void withdraw(int);
void search_by_name();
void logo();
void display_all();


void main()
{
	login();
	main_menu();
}

void login()
{
	clrscr();
	border(0,0,80,26);
	logo();
	char ch;
	account ac;
	border(10,8,20,5);
	gotoxy(15,10);
	cout<<"1. Login";
	border(50,8,20,5);
	gotoxy(55,10);
	cout<<"2. Create";
	gotoxy(40,12);
	ch=getche();

	if(ch == '2')
	{
		clrscr();
		write_account();
		login();
	}

	else if(ch == '1')
	{
		clrscr();
		char tempu[20], tempp[20];

		get_user:
		gotoxy(30,11);
		cout<<"USERNAME: ";
		gets(tempu);
		gotoxy(31,13);
		cout<<"CHECKING.....";
		delay();
		if(ac.check_username(tempu)==0)
			{
				gotoxy(31,20);
				cout<<"INCORRECT USERNAME";
				getch();
				login();
			}
		else if(ac.check_username(tempu)==1)
			goto get_pass;
		else
			login();

		get_pass:
		gotoxy(29,15);
		cout<<"PASSWORD: ";

		for(int i=0; i<20; i++)
		{
			tempp[i]=getch();
			if(tempp[i] == 13)	//checks for enter
			{
				tempp[i]='\0';
				break;
			}
			else if((tempp[i] == 8) && i>0)		//checks for backspace
			{
				i--;
				gotoxy(39+i,15);
				cout<<' ';
				gotoxy(39+i,15);
				i--;
				continue;
			}
			cout<<'*';
		}

		if(ac.check_password(tempu,tempp)==0)
		{
			gotoxy(31,20);
			cout<<"INCORRECT PASSWORD";
			getch();
			goto get_pass;
		}
		else if(ac.check_password(tempu,tempp)==1)
			main_menu();
		else
			goto get_user;
	}
	else
		login();
}

void main_menu()
{
	char ch;
	int num;
	clrscr();
	do
	{
		clrscr();
		align(36,5,"MAIN MENU");
		align(9,10,"1.TRANSACTION");
		border(5,8,20,5);
		align(36,10,"2.BALANCE");
		align(36,11,"  ENQUIRY");
		border(31,8,20,5);
		align(59,10,"3.Report");
		border(56,8,20,5);
		align(10,17," 4. SEARCH");
		border(5,15,20,5);
		align(59,17," 5. EXIT");
		border(56,15,20,5);
		border(31,15,20,5);
		cout<<"\n\n\t\t\t Select Your Option";
		border(0,0,80,26);
		ch=getch();
		clrscr();
		switch(ch)
		{
		case '1':
			transaction();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '3':
			 display_all();
			 break;
		case '4':
			 search_by_name();
			 break;
		case '5':
			cout<<"\n\n\tThanks for using bank managemnt system";
			delay();
			exit(0);
			break;
		default :
			cout<<"\a";
		}
		getch();
	}while(ch!='6');
}

void transaction()
{
	clrscr();
	char ch;
	int num;
	clrscr();
	do
	{
		clrscr();
		cout<<"\n\n\t 1. DEPOSIT AMOUNT";
		cout<<"\n\n\t 2. WITHDRAW AMOUNT";
		cout<<"\n\n\t 3. EXIT";
		cout<<"\n\n\t Select Your Option:";
		cin>>ch;
		clrscr();
		switch(ch)
		{
		case '1':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit(num);
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			withdraw(num);
			break;
		case '3':
			main_menu();
			break;
		default :
			cout<<"\a";
		}
		getch();
	}while(ch!='4');
}
void write_account()
{
	account A;
	ofstream outfile;
	outfile.open("account.dat",ios::out|ios::binary);
	if(!outfile)
	{
		cout<<"account.dat does not exist"  ;
		getch();
		main_menu();
	}
	A.create_account();
	outfile.write((char*)&A,sizeof(A));
	outfile.close();
}

void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.ret_acno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
}

void deposit(int n)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)))
	{
		if(ac.ret_acno()==n)
		{
			ac.show_account();
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited:";
				cin>>amt;
				ac.deposite(amt);
				;
			}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
			 }
			 }
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}
void withdraw(int n)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)))
	{
		if(ac.ret_acno()==n)
		{
			ac.show_account();
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw:";
				cin>>amt;
				if(amt > ac.ret_deposit())
					{
					cout<<"Insufficience balance";
					found=1;
					break;
					}
				else
					ac.withdraw(amt);
			}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
			 }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}
void search_by_name()
{
 account A;
 char name[20];
 Start:
 cout<<"\n Enter the name of the user to be searched for:";
 gets(name);
 ifstream file;
 file.open("account.dat",ios::in|ios::binary);
 while(file.read((char*)&A,sizeof(A)))
  {
	if(A.check_username(name)==1)
	 {
	  A.show_account();
	  void main_manu();
	 }
	else
	 {
	  cout<<"\n Sorry. The username is invalid. please enter the username again";
	  goto Start;
	 }

  }
}
void logo()
{
gotoxy(17,3);
cout<<"____    ____ ____    ____     _   _         __";
gotoxy(17,4);
cout<<"|___| | |__| |__|    |___|   /_\\  |\\ | |/  |_";
gotoxy(17,5);
cout<<"|___| |  __|  __|    |___|  /   \\ | \\| |\\  __|"<<"  INC.";
gotoxy(0,13);
}
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME      Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

