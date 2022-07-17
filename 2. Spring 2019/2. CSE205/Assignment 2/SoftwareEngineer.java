public class SoftwareEngineer extends Employee
{
    
    public SoftwareEngineer(String nme, double slry)
    {
        name = nme;
        salary = slry;
        cash = 0;
    }
    
    public void giveRaise(double percentRaise)
    {
        salary = (salary * (percentRaise/100)) + salary;
    }
}
