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
        return Select(db, maxCount, QueryType.ALL_USERS).toJson();
    }

    public void StartXqrp(object[] args)
    {
        DBAccess db = Connect(args[0]);
        var listener = eventListener(args[1], EventType.ALL);
        var app = new ExtraQueueingResponsePromotion(db);
        Register(app, listener);
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

    private static DBResult Select(DBAccess db, int maxCount, QueryType allUsers)
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
    public string toJson()
    {
        throw new NotImplementedException();
    }
}

public class DBAccess
{
}

internal enum QueryType
{
    ALL_USERS
}