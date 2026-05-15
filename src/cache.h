#include <memory>
#include <string>
#include <unordered_map>
#include <string>

class Cache
{
    std::unordered_map<std::string, std::pair<std::string, std::string>> cashMap;
    public:
        static Cache& getCache();
        std::string makeKey(std::string firstNumber, std::string operation, std::string secondNumber);
        void addRecordToCache(std::string key, std::pair<std::string, std::string> resStat);
        std::pair<std::string, std::string> findRec(std::string findRecord);
};