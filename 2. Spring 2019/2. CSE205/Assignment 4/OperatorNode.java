public class OperatorNode implements Node
{
    private String data;
    public Node left;
    public Node right;
    
    public OperatorNode(String o)
    {
        data = o;
        left = null;
        right = null;
    }
    
    public void setValue(String o)
    {
        data = o;
    }
    //ARBITRARY METHOD
    public String getValue()
    {
        return data;
    }
    
    public Node getLeft()
    {
        return left;
    }
    
    public Node getRight()
    {
        return right;
    }
    
    public String toString()
    {
        return data;
    }
    
}
