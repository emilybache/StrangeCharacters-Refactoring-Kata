#ifndef STRANGECHARACTERS_REFACTORING_KATA_BADEXAMPLE_H
#define STRANGECHARACTERS_REFACTORING_KATA_BADEXAMPLE_H

#include <string>
#include <vector>
#include <any>

class DBAccess {
};

enum class EventType {
    ALL
};

enum class QueryType {
    CUSTOMERS
};

class DBResult {
public:
    std::string toCsv();
};

class ExtraQueueingResponsePromotion {
public:
    ExtraQueueingResponsePromotion(DBAccess& db);
};

class EventListener {
};

class Example {
private:
    DBAccess* db;

    void registerApp(ExtraQueueingResponsePromotion& app, EventListener* listener);
    DBAccess& connect(std::any arg);
    EventListener* eventListener(std::any eventId, EventType type);
    static DBResult select(DBAccess& db, int maxCount, QueryType queryType);

public:
    std::string updatedCostumers(DBAccess& db, int maxCount);
    void startXqrp(std::vector<std::any> args);
    static void doit();
};

#endif //STRANGECHARACTERS_REFACTORING_KATA_BADEXAMPLE_H