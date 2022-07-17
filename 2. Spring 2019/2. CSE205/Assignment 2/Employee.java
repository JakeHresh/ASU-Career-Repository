public abstract class Employee
{
    
    protected String name;
    protected double salary;
    protected double cash;
    
    public String getName()
    {
        return name;
    }
    
    public double getCash()
    {
        return cash;
    }
    
    public double getSalary()
    {
        return salary;
    }
    
    public void getPaid()
    {
        double biweekly = salary/26;
        cash = biweekly + cash;
    }
    
    public abstract void giveRaise(double percentRaise);
}
