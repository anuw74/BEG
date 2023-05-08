#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>

using namespace std;

const char* hostname    = "localhost";
const char* username    = "root";
const char* password    = "";
const char* database    = "cppdb";
unsigned int port       = 3306;
const char* unixsocket  = NULL;
unsigned long clientflag = 0;

MYSQL* connectdatabase(){
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);
    if(conn){
        cout<<"connected to database "<<endl;
        return conn;
    }
    else{
        cout<<"Failed to connect to database"<<endl;
        return conn;
    }
}

insertion(MYSQL* conn){
    int qstate = 0;
    stringstream  ss;
    string usernamedb,emaildb,passworddb;
    cout<<"enter username "<<endl;
    cin>>usernamedb;
    cout<<"Enter email id "<<endl;
    cin>>emaildb;
    cout<<"Enter password "<<endl;
    cin>>passworddb;
    ss << "INSERT INTO users (username, email, password) VALUES ('"+usernamedb+"', '"+emaildb+"', '"+passworddb+"')";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout<<"Record inserted...~~~ \n";
    }
    else{
        cout<<"failed to insert...~~~ \n";
    }

}

display(MYSQL* conn){
    MYSQL_ROW row;
    MYSQL_RES* res;
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM users");
        if(!qstate){
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            while(row = mysql_fetch_row(res)){
                    for(int i=0;i<count;i++){
                        cout<<"\t"<<row[i];
                    }
                    cout<<endl;

            }
        }

    }
    else{
        cout<<"Failed to fetch ";


    }




}
deletedb(MYSQL* conn)
{
    string username;
    stringstream ss;
    cout<<"Enter username of record ";
    cin>>username;

    /*ss  << "DELETE FROM users WHERE username = '"+username+"' ";
    string query = ss.str();
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout<<"~~~~~Record deleted...~~~ \n";
    }
    else{
        cout<<"~~~~~failed to delete...~~~ \n";
    }*/


}

int main()
{
    int c;
    MYSQL* conn = connectdatabase();
    op:
    if(conn){
        cout<<"Enter numbers for operations "<<endl;
        cout<<"1 for insertion \n2 for displaying \n3 for deletion\n4 for exit ";
        cin>>c;
        switch(c){
            case 1:
            insertion(conn);
            goto op;
            break;
            case 2:
            display(conn);
            goto op;
            break;
            case 3:
            cout<<deletedb(conn);
            goto op;
            break;
            case 4:
            exit(0);
            break;
            default:
                cout<<"Wrong input   ......exiting.....\n\n";
               goto op;
        }

    }
    else{
        exit(0);
    }

    return 0;
}
