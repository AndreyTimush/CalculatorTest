#include <iostream>
#include "database.h"
#include "logger.h"
#include <libpq-fe.h>


Database::Database() {
    conn = PQconnectdb(connInfo);
};

bool Database::connectToDb()
{
    if (PQstatus(conn) != CONNECTION_OK) {
        std::string msg = "Connection failed: ";
        logger.error(msg + PQerrorMessage(conn));
        PQfinish(conn);
        return false;
    } 
    logger.info("connect to db");

    createTable();

    return true;
}

bool Database::createTable()
{
    PGresult *createTableRes = PQexec(
        conn,
        "CREATE TABLE IF NOT EXISTS calculator ("
        "id SERIAL PRIMARY KEY,"
        "firstNumber INT,"
        "operation CHAR(1),"
        "secondNumber INT,"
        "result REAL,"
        "status INT"
        ");"
    );

    if (PQresultStatus(createTableRes) != PGRES_COMMAND_OK) {
        logger.error(std::string("create table failed: ") + PQerrorMessage(conn));

        PQclear(createTableRes);

        return false;
    }

    logger.info("table was created");
    
    return true;
}

bool Database::addRecord(int firstNumber, char operation, int secondNumber, float result, int status) 
{
    PGresult *prepareRes = PQprepare(
        conn,
        "insert_record",
        "INSERT INTO calculator"
        "(firstNumber, operation, secondNumber, result, status) "
        "VALUES($1, $2, $3, $4, $5)",
        5,
        nullptr
    );

    if (PQresultStatus(prepareRes) != PGRES_COMMAND_OK) {
        logger.error(std::string("failed prepare: ") + PQerrorMessage(conn));
        PQclear(prepareRes);

        return false;
    }

    PQclear(prepareRes);

    logger.info("statement prepared");

    std::string firstVal = std::to_string(firstNumber);
    std::string op{operation};
    std::string secondVal = std::to_string(secondNumber);
    std::string res = std::to_string(result);
    std::string stat = std::to_string(status);

    const char* record[5] = 
    {
        firstVal.c_str(),
        op.c_str(),
        secondVal.c_str(),
        res.c_str(),
        stat.c_str()
    };

    PGresult *execRes = PQexecPrepared(
        conn,
        "insert_record",
        5,
        record,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(execRes) != PGRES_COMMAND_OK)
    {
        logger.error(std::string("insert failed: ") + PQerrorMessage(conn));
        PQclear(execRes);
        return false;
    }

    PQclear(execRes);

    return true;
}