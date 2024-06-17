using System.Diagnostics.Tracing;

namespace BadNamesExamples;

/**
 * Example method names for discussion
 */
public class Example
{
    private DBAccess db;
    
    public string UpdatedCostumers(DBAccess db, int maxCount)
    {
        return Select(db, maxCount, QueryType.CUSTOMERS).ToCsv();
    }

    public void StartXqrp(object[] args)
    {
        DBAccess db = Connect(args[0]);
        var app = new ExtraQueueingResponsePromotion(db);
        Register(app, eventListener(args[1], EventType.ALL));
    }

    private void Register(ExtraQueueingResponsePromotion app, EventListener listener)
    {
        throw new NotImplementedException();
    }

    private DBAccess Connect(object arg)
    {
        throw new NotImplementedException();
    }

    private EventListener eventListener(object eventId, EventType type)
    {
        throw new NotImplementedException();
    }

    private static DBResult Select(DBAccess db, int maxCount, QueryType queryType)
    {
        throw new NotImplementedException();
    }   
}

public class ExtraQueueingResponsePromotion
{
    public ExtraQueueingResponsePromotion(DBAccess db)
    {
        throw new NotImplementedException();
    }
}

public enum EventType
{
    ALL
}

internal class DBResult
{
    public string ToCsv()
    {
        throw new NotImplementedException();
    }
}

public class DBAccess
{
}

internal enum QueryType
{
    CUSTOMERS
}