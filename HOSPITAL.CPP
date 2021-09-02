#include<iostream.h>
#include<conio.h>
#include<iomanip.h>
#include<stdlib.h>
#include<fstream.h>
#include<string.h>
#include<process.h>
#include<stdio.h>

class Hospital
{ protected:
	   char choice;
  public:
	  void login();
	  void Menu();
};
class Patient: virtual public Hospital
{ int Pid;  //patient id
  char name[40];  //Patient Name
  char Fname[30]; //Father's Name
  char Address[50]; //Address of the paitent
  char BG[4];   //Blood Group of the paitent
  public:
	 void menu();
	 void search();
	 void search(int);
	 void search(char*);
	 void getvalues();
	 void printvalues();
	 int rid(){ return(Pid);};
	 char* retname(){ return(name);};
}pa;
void exitscreen()
{ clrscr();
  cout<<"\n\n\n\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@             THANKS FOR VISITING US                @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
  getch();
  exit(0);
}
void Patient :: menu()
{  clrscr();
   char choice;
   cout<<"\n\n\n\n\n\n\n\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@            1. ADD PAITENT RECORD                  @\n"
      <<"\t\t@            2. SEARCH PAITENT RECORD		 @\n"
      <<"\t\t@            3. DELETE THE PAITENT RECORD           @\n"
      <<"\t\t@            4. PRINT THE RECORD                    @\n"
      <<"\t\t@            5. EXIT                                @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
      cout<<"\n\n";
      cout<<" ENTER YOUR CHOICE : ";
      cin>>choice;
      switch(choice)
      { case '1' :	/*To Add new Patient in Database*/
		{
			Patient* P = new Patient;           //Implementation of new Operator
			ofstream add ("HOSPITAL.DAT",ios::binary|ios::app);
			(*P).getvalues ();
			add.write ((char *)&(*P),sizeof ((*P)));
			cout<<"\n\n\t\t\tRecord Added Successfully !!!";
			getch ();
			add.close ();
			delete P; menu();
			break;
		}
	case '2' :      search ();
			break;
	case '3' : {
			Patient P;
			int o=0,f=0,n;
			clrscr ();
			cout<<"\n\n\t\t***************************************";
			cout<<"\n\n\n\t\t\tEnter Patient ID to Delete : ";cin>>n;
			ifstream msearch ("HOSPITAL.DAT",ios::binary);
			while (msearch.read ((char *)&P,sizeof (P))) {
				if (P.rid () == n) {
					P.printvalues ();
					cout<<"\n\n\t\tARE you sure you want to delete this Patient (1/0) : ";cin>>o;
					if (o == 1) {
						ifstream search ("HOSPITAL.DAT",ios::binary);
						ofstream newfile ("TEMP.DAT",ios::binary);
						while (search.read ((char *)&P,sizeof (P)))
							if (P.rid () != n)
								newfile.write ((char *)&P,sizeof (P));
						cout<<"\n\n\t\tRecord Deleted Succesfull !!!";
						remove ("HOSPITAL.DAT");
						rename ("TEMP.DAT","HOSPITAL.DAT");
						search.close ();
						newfile.close ();
					}
					else {
						menu ();
					}
					getch ();
					f++;
				}
			}
			if (f==0) {
				cout<<"\n\n\n\t\t\tID NOT FOUND !!!";
				getch ();
				menu ();
			}
			cout<<"\n\n\t\t***************************************";
			menu();
			break;
		}
       case '4' : {     clrscr();
			Patient P;
			clrscr ();
			cout<<"\n\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			<<"\n\n\t\t----------------------------------------"
			<<"\n\n\t\t\t\tALL PAITENTS"
			<<"\n\n\t\t----------------------------------------"
			<<"\n\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
			ifstream print ("HOSPITAL.DAT",ios::binary);
			print.seekg (0,ios::end);
			if (print.tellg () == 0) {
			  cout<<"\n\n\t\t\tNo Record found !!!";
			  getch ();
			  menu ();
			 }
		 print.seekg (0,ios::beg);
		 cout<<"\n\n\n ID \t NAME \t\tFATHER NAME \tADDRESS \tBLOOD GROUP\n";
		 while (print.read ((char *)&P,sizeof (P))) {
		 cout<<"\n"<<P.Pid<<"\t"<<P.name<<"\t\t"<<P.Fname<<"\t\t"<<P.Address<<"\t\t"<<P.BG;
		}
		print.close ();
		getch ();
		menu();
		 break;
	       }
       case '5' :  clrscr();
		   cout<<"\n\n\n\n"
		   <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
		   <<"\t\t@                                                   @\n"
		   <<"\t\t@                                                   @\n"
		   <<"\t\t@             THANKS FOR VISITING US                @\n"
		   <<"\t\t@                                                   @\n"
		   <<"\t\t@                                                   @\n"
		   <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
		  getch();
		  exit(0);
		  break;
       default: menu();
     }
}
void Patient :: search () {
    clrscr ();
    char choice;
    cout<<"\n\n\t\t***************************************"
    <<"\n\n\t\t  SELECT SEARCH METHOD"
	<<"\n\n\t\t***************************************"
	<<"\n\n\t\t\t1.Search by ID"
	<<"\n\n\t\t\t2.Search by Departure"
	<<"\n\n\t\t\t0.Exit"
	<<"\n\n\t\t***************************************"
	<<"\n\n\t\t\tEnter choice:";
     cin>>choice;
     switch (choice) {
		   case '1' :
			int n;
			clrscr ();
			cout<<"\n\n\t\t***************************************"
			<<"\n\n\t\tEnter ID to Search : ";cin>>n;
			search (n);
			break;

		case '2' :
			char d [16];
			clrscr ();
			cout<<"\n\n\t\t***************************************"
			<<"\n\n\t\tEnter Name to Search : ";cin>>d;
			search (d);

		case '0' :
			exitscreen ();
			break;
	}
	search ();
}
void Patient :: search (int n) {
	Patient P;
	int f=0;
	ifstream search ("HOSPITAL.DAT",ios::binary);
	while (search.read ((char *)&P,sizeof (P))) {
		if (P.rid()==n) {
			clrscr ();
			P.printvalues ();
			getch ();
			f++;
		}
	}
	if (f==0) {
		cout<<"\n\n\n\t\t\tID NOT FOUND !!!";
		getch ();
		menu ();
	}
}

void Patient :: search (char *d) {
	Patient P;
	int f=0;
	ifstream search ("HOSPITAL.DAT",ios::binary);
	clrscr ();
	cout<<"\n\n\t\t***************************************"
		<<"\n\n\t\t\tPATIENT DETAILS : "<<d
		<<"\n\n\t\t***************************************"
		<<"\n\n\n ID \t NAME \t\tFATHER NAME \tADDRESS \tBLOOD GROUP\n";
	while (search.read ((char *)&P,sizeof (P))) {
		if (strcmp(d,P.retname())==0) {
			cout<<"\n"<<P.Pid<<"\t"<<P.name<<"\t\t"<<P.Fname<<"\t\t"<<P.Address<<"\t\t"<<P.BG;
			f++;
		}
	}
	cout<<"\n\n\t\t***************************************";
	if (f==0) {
		cout<<"\n\n\n\t\t\tNO SUCH PATIENT FOUND !!!";
		getch();
		menu();
	}
	getch ();
}

void Patient :: getvalues()
{ clrscr();
  cout<<"\n\n";
  cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
      <<"\t\t-------------------------------------------------\n"
      <<"\t\t              NEW PATIENT RECORD                 \n"
      <<"\t\t-------------------------------------------------\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
  cout<<"\n\t\t\t Enter the Patient ID :"; cin>>Pid;
  cout<<"\t\t\t Enter the Name of the Patient :"; cin>>name;
  cout<<"\t\t\t Enter the Father's Name of the Patient :"; cin>>Fname;
  cout<<"\t\t\t Enter the Address of the Paitent :"; cin>>Address;
  cout<<"\t\t\t Enter the Blood Group of the Paitent :"; cin>>BG;
  ifstream check ("HOSPITAL.DAT",ios::binary);
  while(check.read((char *)&pa, sizeof(pa)))
     if(pa.rid()==Pid)
     { cout<<"\n\n"
	   <<"\t\t ALREADY EXISTS!!!! "
	   <<"\n\n";
       getch();
       getvalues();
     }
}
void Patient :: printvalues()
{ clrscr();
  cout<<"\n\n";
  cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
      <<"\t\t-------------------------------------------------\n"
      <<"\t\t                   PATIENT RECORD                \n"
      <<"\t\t-------------------------------------------------\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
      cout<<"\n\t\t\t The Patient ID :"<<Pid<<"\n";
      cout<<"\t\t\t Name of the Patient :"<<name<<"\n";
      cout<<"\t\t\t Father's Name of the Patient :"<<Fname<<"\n";
      cout<<"\t\t\t Address of the Paitent :"<<Address<<"\n";
      cout<<"\t\t\t Blood Group of the Paitent :"<<BG<<"\n";
      cout<<"__________________________________________________\n";
}
class Diagnosis: virtual public Hospital
{ int Pid;  //patient id
  char name[40];  //Doc Name
  char Des[30]; //Desc of Doc
  char cause[50]; //cause of the paitent
  int Bno;   //Bed no. of the paitent
  public:
	 void search();
	 void search(int);
	 void search(char*);
	 void getvalues();
	 void printvalues();
	 int rid(){ return(Pid);};
}ps;
void Diagnosis :: getvalues()
{ cout<<"\n\n";
  cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
      <<"\t\t-------------------------------------------------\n"
      <<"\t\t              NEW DIAGNOSIS RECORD               \n"
      <<"\t\t-------------------------------------------------\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
  cout<<"\n\t\t\t Enter the Patient ID :"; cin>>Pid;
  cout<<"\t\t\t Enter the Name of the Doctor Assigned :"; cin>>name;
  cout<<"\t\t\t Enter the Description of the Doctor Assigned :"; cin>>Des;
  cout<<"\t\t\t Enter the Treatment of the paitent :"; cin>>cause;
  cout<<"\t\t\t Enter the Bed No. of the Paitent :"; cin>>Bno;
  ifstream check ("DIAGNOSIS.DAT",ios::binary);
  while(check.read((char *)&ps, sizeof(ps)))
     if(ps.rid()==Pid)
     { cout<<"\n\n"
	   <<"\t\t ALREADY EXISTS!!!! "
	   <<"\n\n";
       getch();
       getvalues();
     }
}
void Diagnosis :: printvalues()
{  cout<<"\n\n";
  cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
      <<"\t\t-------------------------------------------------\n"
      <<"\t\t                   DIAGNOSIS RECORD              \n"
      <<"\t\t-------------------------------------------------\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
      cout<<"\n\t\t\t The Patient ID :"<<Pid<<"\n";
      cout<<"\t\t\t Name of the Doctor Assigned :"<<name<<"\n";
      cout<<"\t\t\t Description of the Doctor :"<<Des<<"\n";
      cout<<"\t\t\t Treatment of the paitent :"<<cause<<"\n";
      cout<<"\t\t\t Bed No. of the Paitent :"<<Bno<<"\n";
      cout<<"__________________________________________________\n";
}

void Hospital :: login()
{ clrscr();
  char user[20], pass[20];
  int i=-1;
  static int attempt=0;
  cout<<"\n\n";
  cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
      <<"\t\t-------------------------------------------------\n"
      <<"\t\t             HOSPITAL MANAGEMENT SYSTEM          \n\n\n"
      <<"\t\t                    LOGIN PAGE                  \n"
      <<"\t\t-------------------------------------------------\n"
      <<"\n\n\t\t\t    USERNAME : ";
      cin>>user;
      cout<<"\n\t\t\t    PASSWORD : ";
      attempt++;
      do{ i++;
	  pass[i]=getch();
	  if(pass[i]!=13)
	     cout<<"*";
	}while(pass[i]!=13);
      if(strcmp(user,"Ayush")==0 && strcmp(pass,"Ashika@1407")==13)
	   Menu();
      else if(attempt<3)
	    { cout<<"\n\n\n\t\t\t INVALID PASSWORD OR USERNAME!!! ";
	      getch();
	      login();
	     }
	     else
	     { cout<<"\n\n\n\t\t\t YOU TIMED OUT!!!";
	       getch();
	       exitscreen();
	     }
}
void Hospital :: Menu()
{ clrscr();
   cout<<"\n\n\n\n\n\n\n\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@               1. PAITENT DETAILS                  @\n"
      <<"\t\t@               2. DIAGNOSIS DETAILS	         @\n"
      <<"\t\t@               3. EXIT                             @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
      cout<<"\n\n";
      cout<<"\t\t\t ENTER YOUR CHOICE : ";
      cin>>choice;
      switch(choice)
      {  case '1' : pa.menu();
	 case '2' : exitscreen(); //ps.menu();
         case '3' : exitscreen();
         default: Menu();
       }
}
void main()
{ clrscr();
   cout<<"\n\n\n\n\n\n\n\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@                 WELCOME TO THE                    @\n"
      <<"\t\t@           HOSPITAL MANAGEMENT SYSTEM              @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@                                                   @\n"
      <<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";

   cout<<"\n\n\n\n\n\n";
   system("pause");
   system("cls");
   pa.login();
   getch();
}