package badnames;

public class Example {

    enum QueryType {
        CUSTOMERS
    }

    enum EventType {
        ALL
    }

    private DBAccess db;

    public String UpdatedCostumers(DBAccess db, int maxCount)
    {
        return select(db, maxCount, QueryType.CUSTOMERS).toCsv();
    }

    public void StartXqrp(Object[] args)
    {
        DBAccess db = DBAccess.connect(args[0]);
        var app = new ExtraQueueingResponsePromotion(db);
        register(app, eventListener(args[1], EventType.ALL));
    }

    private void register(ExtraQueueingResponsePromotion app, EventListener eventListener) {

    }

    private EventListener eventListener(Object a, EventType type) {
        return new EventListener() {};
    }

    private DBResult select(DBAccess db, int maxCount, QueryType queryType) {
        return new DBResult();
    }

}
