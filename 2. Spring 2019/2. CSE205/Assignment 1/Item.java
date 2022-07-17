public class Item
{
    private String name;
    private double value;
    
    public Item()
    {
        name = "";
        value = 0;
    }
    
    public Item(String n, double v)
    {
        name = n;
        value = v;
    }
    
    public String getName()
    {
        return name;
    }
    
    public double getValue()
    {
        return value;
    }
}
