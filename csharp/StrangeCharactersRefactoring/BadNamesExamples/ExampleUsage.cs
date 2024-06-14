namespace BadNamesExamples;

public class ExampleUsage
{
    public void doit()
    {
        var q = new Example().CustomerQuery(new DBAccess(), 4);
        new Example().StartXqrp(new object[] { "a", "b" });
    }
}