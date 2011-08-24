//#ifndef _C_H_
//    #define _C_H_
//
//#include <stdlib.h>
//#include <iostream>
//#include <sstream>
//#include <stdexcept>
//	
//
//#include "mysql_driver.h" 
//#include "mysql_connection.h"
//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>
//	
//#define EXAMPLE_HOST "localhost"
//#define EXAMPLE_USER "root"
//#define EXAMPLE_PASS ""
//#define EXAMPLE_DB "world"
//
//using namespace std;
//using namespace sql::mysql; 
//
//class asdMySQL
//{
//	public:
//		asdMySQL(){}
//		~asdMySQL() {}
//
//	void start()
//	{
//		  sql::Driver *driver;
//		  sql::Connection *con;
//		  sql::Statement *stmt;
//		  sql::ResultSet *res;
//	
//		  /* Create a connection */
//		  driver = sql::mysql::get_driver_instance();
//		  con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
//		  /* Connect to the MySQL test database */
//		  con->setSchema("test");
//	
//		  stmt = con->createStatement();
//		  res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
//		  while (res->next()) {
//			cout << "\t... MySQL replies: ";
//			/* Access column data by alias or column name */
//			cout << res->getString("_message") << endl;
//			cout << "\t... MySQL says it again: ";
//			/* Access column fata by numeric offset, 1 is the first column */
//			cout << res->getString(1) << endl;
//		  }
//		  delete res;
//		  delete stmt;
//		  delete con;
//	}
//};
//
//
//#endif