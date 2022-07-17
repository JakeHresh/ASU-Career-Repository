public class AdministrativeAssistant extends Employee implements Hourly
{
    
    private int hoursPerWeek;
    
    public AdministrativeAssistant(String nme, double slry, int hrs)
    {
        name = nme;
        salary = slry;//how much they are paid per hour
        hoursPerWeek = hrs;
    }
    
    public void giveRaise(double increase)
    {
        salary += increase;
    }
    
    public void getPaid()
    {
        double weeklyPay = salary*hoursPerWeek;
        cash = (weeklyPay*2) + cash;
    }
    
    public void changeHours(int hours)
    {
        hoursPerWeek = hours;
    }
    
    public int numHours()
    {
        return hoursPerWeek;
    }
}
