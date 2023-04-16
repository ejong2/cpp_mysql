#include <iostream>
#include <memory>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "jdbc/mysql_connection.h"
#include "jdbc/cppconn/driver.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/prepared_statement.h"

#pragma comment(lib,"mysqlcppconn.lib")
#pragma comment(lib, "WS2_32.lib")

using namespace std;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "1234";

int main()
{
    try
    {
        sql::Driver* driver = get_driver_instance();
        std::shared_ptr<sql::Connection> con(driver->connect(server, username, password));
        // 데이터베이스 선택
        con->setSchema("ue_db");

        std::shared_ptr<sql::Statement> stmt(con->createStatement());
        std::shared_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT email, password FROM ueuser"));
        // 데이터 조회
        while (res->next())
        {
            cout << "email: " << res->getString("email") << ", password: " << res->getString("password") << endl;
            // 조회 결과 출력
        }
    }
    catch (const sql::SQLException& e)
    {
        cerr << "MySQL 오류: " << e.what() << endl;
        cerr << "SQLState: " << e.getSQLState() << " 에러 코드: " << e.getErrorCode() << endl;
    }
    catch (const std::exception& e)
    {
        cerr << "예외 발생: " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "알 수 없는 예외 발생" << endl;
    }

    return 0;
}