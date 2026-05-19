#include <iostream>
#include "database.h"
#include "logger.h"
#include <libpq-fe.h>
#include "cache.h"


Database::Database()
    : conn(PQconnectdb(connInfo), &Database::customDeleter)
{
}

void Database::customDeleter(PGconn* conn)
{
    if (conn) {
        PQfinish(conn);
    }
}

bool Database::connectToDb()
{
    if (!conn || PQstatus(conn.get()) != CONNECTION_OK) {
        std::string msg = "Connection failed: ";
        if (conn) {
            logger.error(msg + PQerrorMessage(conn.get()));
        } else {
            logger.error(msg);
        }
        conn.reset();
        return false;
    } 
    logger.info("connect to db");

    createTable();

    return true;
}

bool Database::createTable()
{
    PGresult *createTableRes = PQexec(
        conn.get(),
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
        logger.error(std::string("create table failed: ") + PQerrorMessage(conn.get()));
        PQclear(createTableRes);
        return false;
    }

    PQclear(createTableRes);

    logger.info("table was created");
    
    return true;
}

bool Database::addRecord(int firstNumber, char operation, int secondNumber, float result, int status) 
{
    PGresult *prepareRes = PQprepare(
        conn.get(),
        "insert_record",
        "INSERT INTO calculator"
        "(firstNumber, operation, secondNumber, result, status) "
        "VALUES($1, $2, $3, $4, $5)",
        5,
        nullptr
    );

    if (PQresultStatus(prepareRes) != PGRES_COMMAND_OK) {
        logger.error(std::string("failed prepare: ") + PQerrorMessage(conn.get()));
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
        conn.get(),
        "insert_record",
        5,
        record,
        nullptr,
        nullptr,
        0
    );

    if (PQresultStatus(execRes) != PGRES_COMMAND_OK)
    {
        logger.error(std::string("insert failed: ") + PQerrorMessage(conn.get()));
        PQclear(execRes);
        return false;
    }

    PQclear(execRes);

    return true;
}

bool Database::loadCache() 
{
    logger.info("load_cahce function");
    PGresult* res = PQexec(
        conn.get(),
        "SELECT * FROM calculator;"
    );

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);

        return false;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        std::string firstVal = PQgetvalue(res, i, 1);
        std::string operation = PQgetvalue(res, i, 2);
        std::string secondVal = PQgetvalue(res, i, 3);
        std::string result = PQgetvalue(res, i, 4);
        std::string status = PQgetvalue(res, i, 5);

        std::string keyForCache = Cache::getCache().makeKey(firstVal, operation, secondVal);

        Cache::getCache().addRecordToCache(keyForCache, std::make_pair(result, status));

    }

    PQclear(res);
    return true;
}