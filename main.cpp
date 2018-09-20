#include <iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<mysql.h>
#include<windows.h>
using namespace std;

MYSQL* conn;//connection object
MYSQL_ROW row;
MYSQL_RES* res;
int qstate;//for query
char* ip="localhost";
char* usr="root";   //connection descriptions
char* pass="";
char* db="student records";
string name,dob,reg;
    int phy,chem,maths,comp,elec,total,roll;
    double percent;
    char sec,grade;
class db
{
public:
    static void connect()//for creating connection with sql
    {

        conn=mysql_init(0); //object initialization
        if(conn)
        {
            cout<<"Database connected"<<endl;

        }
        else
        {
           cout<<"connection failed"<<mysql_error(conn)<<endl;
        }
        conn = mysql_real_connect(conn, "localhost", "root", "", "student records", 0, NULL, 0);
        if(conn)
        {
            cout<<"connected database to mysql "<<conn<<endl;
        }
        else
        {
            cout<<"connection failed "<<mysql_error(conn)<<endl;
        }
    }

};

void main2();//controls setup choice
void query();//for query regarding single records
void enter();//for entering values in table
void del();//for deleting the table or records
void  display();//for displaying the table
void arrange();//for sorting
void update();//to update
void main2()
{
    system("cls");
    system("title NIT STUDENTS RECORDS");
    system("color 0f");//white
    db::connect();
    int menu;//to store menu choice
    cout<<"1. enter"<<endl;
    cout<<"2. query"<<endl;
    cout<<"3. delete"<<endl;
    cout<<"4. display"<<endl;
    cout<<"5. sort"<<endl;
    cout<<"6. update"<<endl;
    cout<<"7. exit"<<endl;
    cout<<"Enter your choice"<<endl;
    cin>>menu;

    switch(menu)
    {
    case 1:
        enter();
        main2();
        break;
    case 2:
        query();
        main2();
        break;
    case 3:
        del();
        main2();
        break;
    case 4:
        display();
        main2();
        break;
    case 5:
        arrange();
        main2();
        break;
    case  6:
        update();
        main2();
        break;
    case 7:
        exit(0);
        break;
    default:
        cout<<"enter valid choice"<<endl;
        main2();
    }

}
void enter()//function declaration
{
    int n,i;   //no of entries and loop control

    cout<<"enter the number of students"<<endl;
    cin>>n;
    for( i=0;i<n;i++)
    {
        cout<<"enter the name"<<endl;
        cin>>name;
        cout<<"enter date of birth"<<endl;
        cin>>dob;
        cout<<"Enter reg"<<endl;
        cin>>reg;
        cout<<"Enter roll"<<endl;
        cin>>roll;
        cout<<"enter marks of physics chemistry maths computer electronics"<<endl;
        cin>>phy>>chem>>maths>>comp>>elec;
        total=phy+chem+maths+comp+elec;
        percent=total/5;
        if(percent<40)
            grade='f';
        else
            grade='p';
        string insert_query="insert into database(NAME,SEC,ROLL,REG,DOB,PHY,CHEM,MATHS,COMP,ELEC,TOTAL,PERCENT,GRADE) values('"+name+"','"+sec+"',roll,'"+reg+"','"+dob+"',phy,chem,maths,comp,elec,total,percent,'"+grade+"')";
        const char* q=insert_query.c_str(); //string to char explicit conversion
        qstate=mysql_query(conn,q);

        if(!qstate)
        {
            cout<<"Successfully added to database"<<endl;

        }
        else
        {
            cout<<"insertion problem"<<endl;

        }
    }
}
void display()
{
    qstate=mysql_query(conn,"select * from database");
    if(!qstate)//nonzero results
    {
        res=mysql_store_result(conn);
        //reading and displaying records;
        while(row=mysql_fetch_row(res))
        {
            cout<<"name: "<<row[0]<<" "
            <<"sec: "<<row[1]<<" "
            <<"roll: "<<row[2]<<" "
            <<"reg: "<<row[3]<<" "
            <<"dob: "<<row[4]<<" "
            <<"physics: "<<row[5]<<" "
            <<"chemistry: "<<row[6]<<" "
            <<"maths: "<<row[7]<<" "
            <<"computer: "<<row[8]<<" "
            <<"electronics: "<<row[9]<<" "
            <<"total: "<<row[10]<<" "
            <<"percentage: "<<row[11]<<" "
            <<"grade: "<<row[12]<<endl;
        }

    }
    else
    {
        cout<<"query execution problem"<<mysql_error(conn)<<endl;
    }
}
void del()
{
    int k;//choice for deletion
    const char* qd;
    cout<<"1.for deletion of whole table"<<endl;
    cout<<"2.for deletion of particular rows"<<endl;
    cout<<"enter your choice"<<endl;
    cin>>k;

    if(k==1)
       {
        string delete_query="delete * from database";
        qd=delete_query.c_str();
        qstate=mysql_query(conn,qd);
         if(!qstate)
        {
            cout<<"Successfully deleted database"<<endl;

        }
        else
        {
            cout<<"deletion problem"<<endl;

        }
       }
    else if(k==2)
    {
        char p;//for choice of deletion
        string field;
        string delete_query2;
        cout<<"enter the field of query"<<endl;
        cin>>field;
        cout<<"enter a if u have a specified query field"<<endl;
        cout<<"enter b have range to check"<<endl;
        cout<<"Enter your choice"<<endl;
        cin>>p;

        if(p=='a')
            {string cndtns;//cndtns for deletions
            cout<<"Enter the conditions"<<endl;
            cin>>cndtns;
            int c;
             if((field=="ROLL")||(field=="PHYSICS")||(field=="CHEMISTRY")||(field=="MATHS")||(field=="COMPUTER")||(field=="ELECTRONICS")||(field=="TOTAL"))
            {   c=atoi(cndtns.c_str());
                delete_query2="delete from database where field= c";
                qd=delete_query2.c_str();
                qstate=mysql_query(conn,qd);
            }
            else
            {
                delete_query2="delete from database where field= '"+cndtns+"'";
                qd=delete_query2.c_str();
                qstate=mysql_query(conn,qd);
            }
            if(!qstate)
            {
                cout<<"Successfully deleted database"<<endl;

            }
            else
            {
                cout<<"deletion problem"<<endl;

            }
        }
        if(p=='b')
        {
                int ul,ll;//upper and lower limit of the input field
                cout<<"Enter the uppper and lower limit of the field respectively"<<endl;
                cin>>ul>>ll;
                delete_query2="delete from database where field <= ul and field >=ll";
                qd=delete_query2.c_str();
                qstate=mysql_query(conn,qd);
                if(!qstate)
                {
                    cout<<"Successfully deleted database"<<endl;

                }
                else
                {
                    cout<<"deletion problem"<<endl;

                }
        }

        }

    else {
        cout<<"Enter correct option"<<endl;
        del();
    }
}

void query()
{
    char q;//for choice of query
        string field;

        cout<<"enter the field of query"<<endl;
        cin>>field;
        cout<<"enter s if u have a specified query field"<<endl;
        cout<<"enter br have range to check"<<endl;
        cout<<"Enter your choice"<<endl;
        cin>>q;

        if(q =='s')
           {

            string cndtns2;//cndtns for query
            cout<<"Enter the conditions"<<endl;
            cin>>cndtns2;
            int a;

            if((field=="ROLL")||(field=="PHYSICS")||(field=="CHEMISTRY")||(field=="MATHS")||(field=="COMPUTER")||(field=="ELECTRONICS")||(field=="TOTAL"))
            {   a=atoi(cndtns2.c_str());
                qstate=mysql_query(conn,"select * from database where field=a ");

            }
            else
            {
                qstate=mysql_query(conn,"select * from database where field= cndtns2");

            }
            if(!qstate)
            {
                res=mysql_store_result(conn);
        //reading and displaying records;
                while(row=mysql_fetch_row(res))
                {
                    cout<<"name: "<<row[0]<<" "
                        <<"sec: "<<row[1]<<" "
                        <<"roll: "<<row[2]<<" "
                        <<"reg: "<<row[3]<<" "
                        <<"dob: "<<row[4]<<" "
                        <<"physics: "<<row[5]<<" "
                        <<"chemistry: "<<row[6]<<" "
                        <<"maths: "<<row[7]<<" "
                        <<"computer: "<<row[8]<<" "
                        <<"electronics: "<<row[9]<<" "
                        <<"total: "<<row[10]<<" "
                        <<"percentage: "<<row[11]<<" "
                        <<"grade: "<<row[12]<<endl;
                }


            }
            else
            {
                cout<<"query problem"<<endl;

            }
           }
            else if(q=='r')
            {


                int ul,ll;//upper and lower limit of the input field
                cout<<"Enter the uppper and lower limit of the field respectively"<<endl;
                cin>>ul>>ll;
                 qstate=mysql_query(conn,"select * from database where field <=ul and field >=ll");

                if(!qstate)
                {
                    res=mysql_store_result(conn);
        //reading and displaying records;
                    while(row=mysql_fetch_row(res))
                    {
                        cout<<"name: "<<row[0]<<" "
                            <<"sec: "<<row[1]<<" "
                            <<"roll: "<<row[2]<<" "
                            <<"reg: "<<row[3]<<" "
                            <<"dob: "<<row[4]<<" "
                            <<"physics: "<<row[5]<<" "
                            <<"chemistry: "<<row[6]<<" "
                            <<"maths: "<<row[7]<<" "
                            <<"computer: "<<row[8]<<" "
                            <<"electronics: "<<row[9]<<" "
                            <<"total: "<<row[10]<<" "
                            <<"percentage: "<<row[11]<<" "
                            <<"grade: "<<row[12]<<endl;
                    }


                }
                else
                {
                    cout<<"query problem"<<endl;

                }
            }
            else
                {cout<<"Enter correct option"<<endl;
                query();
        }

}
void arrange()
{
  string field;
  cout<<"Enter the field on the basis of which you want to sort" <<endl;
  cin>>field;
  qstate=mysql_query(conn,"select * from database order by field");
    if(!qstate)//nonzero results
    {
        res=mysql_store_result(conn);
        //reading and displaying records;
        while(row=mysql_fetch_row(res))
        {
            cout<<"name: "<<row[0]<<" "
            <<"sec: "<<row[1]<<" "
            <<"roll: "<<row[2]<<" "
            <<"reg: "<<row[3]<<" "
            <<"dob: "<<row[4]<<" "
            <<"physics: "<<row[5]<<" "
            <<"chemistry: "<<row[6]<<" "
            <<"maths: "<<row[7]<<" "
            <<"computer: "<<row[8]<<" "
            <<"electronics: "<<row[9]<<" "
            <<"total: "<<row[10]<<" "
            <<"percentage: "<<row[11]<<" "
            <<"grade: "<<row[12]<<endl;
        }

    }
    else
    {
        cout<<"query execution problem"<<mysql_error(conn)<<endl;
    }
}
void update()
{
    string field,field2;
    cout<<"Enter the field you want to update and the field to specify condition of update on"<<endl;
    cin>>field2>>field;
    int updt,cndn;//constant for integer condition
    string updt2,cndn2;//constant for string condition
    if((field=="ROLL")||(field=="PHYSICS")||(field=="CHEMISTRY")||(field=="MATHS")||(field=="COMPUTER")||(field=="ELECTRONICS")||(field=="TOTAL"))
    {
        cout<<"Enter the value to set and the condition respectively"<<endl;
        cin>>updt>>cndn;
        qstate=mysql_query(conn,"update database set field2= updt where field=cndn");

    }
    else
    {

        cout<<"Enter the value to set and the condition respectively"<<endl;
        cin>>updt2>>cndn2;
        qstate=mysql_query(conn,"update database set field2= updt2 where field=cndn2");


    }

        if(!qstate)
        {
            cout<<"Successfully update database"<<endl;

        }
        else
        {
            cout<<"update problem"<<endl;

        }
}

