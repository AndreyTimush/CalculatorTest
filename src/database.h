#include <libpq-fe.h>
#include <memory>
#include "logger.h"

class Database 
{
    static void customDeleter(PGconn* conn);
    using PgConnPtr = std::unique_ptr<PGconn, decltype(&Database::customDeleter)>;
    const char* connInfo = "dbname=calculator user=andrey password=1111 host=localhost";
    PgConnPtr conn{nullptr, &Database::customDeleter};
    Logger &logger = Logger::getLogger();
    public:
        Database();
        bool connectToDb();
        static Database &getDb() {
            static Database db;
            return db;
        }
        bool createTable(); 
        bool addRecord(int firstNumber, char operation, int secondNumber, float result, int status);
        bool loadCache();
        

    
};