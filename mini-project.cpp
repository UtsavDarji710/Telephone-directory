#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<string.h>
using namespace std;
class telephone
{
    char name;
    long long number;
    char email_id[20];
    char work[20];
public:
    void creat_record();
    void show_record();
    void reset_record();
    void Search_record();
    char retacna()
    {

        return name;
    }
};
void telephone::creat_record()
{
    cout<<"******************************";
    cout<<"\ncontact name : ";
    cin>>name;
    cout<<"\ncontact number : ";
    cin>>number;
    cout<<"\nEmail ID : ";
    cin>>email_id;
    cout<<"\nwork : ";
    cin>>work;
    cout<<"\n******************************";
}
void telephone::show_record()
{
    cout<<"******************************";
    cout<<"\ncontact name : ";
    cout<<name;
    cout<<"\ncontact number : ";
    cout<<number;
    cout<<"\nEmail ID : ";
    cout<<email_id;
    cout<<"\nwork : ";
    cout<<work;
    cout<<"\n******************************";
}
void telephone::reset_record()
{
    cout<<"\ncontact name : ";
    cin>>name;
    cout<<"\ncontact number : ";
    cin>>number;
    cout<<"\nEmail ID : ";
    cin>>email_id;
    cout<<"\nwork : ";
    cin>>work;
}
/*char telephone::retacna()
{
	return name;
}*/

///////////////////////////////////////////////////////////////////////
void telephone_record();
void display_sp(char na);
void modify_record(char na);
void delete_record(char na);
void intro();
///////////////////////////////////////////////////////////////////////
int main()
{
    char ch;
    char name;
    intro();
    do
    {
            cout<<"\n\n\tMAIN MENU";
            cout<<"\n\n 1. Create record: ";
            cout<<"\n\n 2. Search record: ";
            cout<<"\n\n 3. Modify record: ";
            cout<<"\n\n 4. Delete record: ";
            cout<<"\n\n 5. EXIT : ";
            cout<<"\n\n\tSelect Your Option (1-5): ";
            cin>>ch;
            switch(ch)
            {
            case '1':
                telephone_record();
                break;
            case '2':
                cout<<"Enter name : ";
                cin>>name;
                display_sp(name);
                break;
            case '3':
                cout<<"Enter name : ";
                cin>>name;
                modify_record(name);
                break;
            case '4':
                cout<<"Enter name : ";
                cin>>name;
                delete_record(name);
                break;
            case '5':
                cout<<"\n\n\tThanks for using telephone directary";
                break;
            default : cout<<"\a";
            }cin.ignore();
            cin.get();
    }while(ch!='5');
    return 0;
}
////////////////////////////////////////////////////////////////////
/////// CREATE RECORD /////////
/////////////////////////////////////////////////////////////////////
void telephone_record()
{
    telephone tp;
    ofstream outFile;
	outFile.open("contact.dat",ios::binary|ios::app);
	tp.creat_record();
	outFile.write(reinterpret_cast<char *> (&tp), sizeof(telephone));
	outFile.close();
}
/////////////////////////////////////////////////////////////////////
///// SHOW RECORD ////////////
/////////////////////////////////////////////////////////////////////
void display_sp(char na)
{
	telephone tp;
	bool flag=false;
	ifstream inFile;
	inFile.open("contact.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nCONTACT DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&tp), sizeof(telephone)))
	{
		if(tp.retacna()==na)
		{
			tp.show_record();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\ncontact name does not exist";
}
//////////////////////////////////////////////////////////////////////////////////////
///// MODIFY RECORD//////
//////////////////////////////////////////////////////////////////////////////////////
void modify_record(char na)
{
	bool found=false;
	telephone tp;
	fstream File;
	File.open("contact.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&tp), sizeof(telephone));
		if(tp.retacna()==na)
		{
			tp.show_record();
			cout<<"\n\nEnter The New Details of account"<<endl;
			tp.reset_record();
			int pos=(-1)*static_cast<int>(sizeof(telephone));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&tp), sizeof(telephone));
			cout<<"\n\n\t Contact Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Contact Not Found ";
}
///////////////////////////////////////////////////////////////////////////////
//// DELETE RECORD/////////////
///////////////////////////////////////////////////////////////////////////////
void delete_record(char na)
{
	telephone tp;
	ifstream inFile;
	ofstream outFile;
	inFile.open("contact.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&tp), sizeof(telephone)))
	{
		if(tp.retacna()!=na)
		{
			outFile.write(reinterpret_cast<char *> (&tp), sizeof(telephone));
		}
	}
	inFile.close();
	outFile.close();
	remove("contact.dat");
	rename("Temp.dat","contact.dat");
	cout<<"\n\n\tRecord Deleted ..";
}
////////////////////////////////////////////////////////////////////////////////////
//// INTRODUCTION /////////
////////////////////////////////////////////////////////////////////////////////////
void intro()
{
    cout<<"\t\t****************************";
	cout<<"\n\t\t*\t Telephone         *";
	cout<<"\n\t\t*\t Directary         *";
	cout<<"\n\t\t*\t(PHONE BOOK)       *";
	cout<<"\n\t\t****************************";
	cout<<"\n\n";
	cout<<"\n\t\t#############################";
	cout<<"\n\t\t##  MADE BY :- Utsav Darji ##";
	cout<<"\n\t\t##  ID NO   :-  19IT029    ##";
	cout<<"\n\t\t#############################";
	cin.get();
}
