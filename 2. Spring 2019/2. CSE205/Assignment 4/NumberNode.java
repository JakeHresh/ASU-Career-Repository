
/**
 * Write a description of class NumberNode here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class NumberNode implements Node
{
    private String data;
    
    public NumberNode(String d)
    {
        data = d;
    }
    
    /*public int getValue()
    {
        return data;
    }*/
    
    public String getValue()
    {
        return data;
    }
    
    public Node getLeft()
    {
        return null;
    }
    
    public Node getRight()
    {
        return null;
    }
    
    public String toString()
    {
        return data;
    }
    
}
