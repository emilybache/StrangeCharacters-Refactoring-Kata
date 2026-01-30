#include "BadExample.h"
#include <stdexcept>

std::string DBResult::toCsv() {
    throw std::runtime_error("NotImplementedException");
}

ExtraQueueingResponsePromotion::ExtraQueueingResponsePromotion(DBAccess& db) {
    throw std::runtime_error("NotImplementedException");
}

std::string Example::updatedCostumers(DBAccess& db, int maxCount) {
    return select(db, maxCount, QueryType::CUSTOMERS).toCsv();
}

void Example::startXqrp(std::vector<std::any> args) {
    DBAccess& db = connect(args[0]);
    ExtraQueueingResponsePromotion app(db);
    registerApp(app, eventListener(args[1], EventType::ALL));
}

void Example::doit() {
    Example ex;
    DBAccess db;
    auto q = ex.updatedCostumers(db, 4);
    ex.startXqrp({std::string("a"), std::string("b")});
}

void Example::registerApp(ExtraQueueingResponsePromotion& app, EventListener* listener) {
    throw std::runtime_error("NotImplementedException");
}

DBAccess& Example::connect(std::any arg) {
    throw std::runtime_error("NotImplementedException");
}

EventListener* Example::eventListener(std::any eventId, EventType type) {
    throw std::runtime_error("NotImplementedException");
}

DBResult Example::select(DBAccess& db, int maxCount, QueryType queryType) {
    throw std::runtime_error("NotImplementedException");
}