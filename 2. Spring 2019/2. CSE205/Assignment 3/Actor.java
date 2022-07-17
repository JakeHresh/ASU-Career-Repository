public class Actor
{
    private String name;
    private int currentHealth;
    private final int STARTINGHEALTH = 100;
    
    public Actor(String n)
    {
        name = n;
        currentHealth = STARTINGHEALTH;
    }
    
    public String getName()
    {
        return name;
    }
    
    public int getHealth()
    {
        return currentHealth;
    }
    
    public boolean isDead()
    {
        boolean isDead = false;
        if(currentHealth <= 0)
        {
            isDead = true;
        }
        return isDead;
    }
    
    public void changeHealth(int difference)
    {
        if(currentHealth - difference > STARTINGHEALTH)
        {
            currentHealth = STARTINGHEALTH;
        }
        else if(currentHealth <= STARTINGHEALTH)
        {
            currentHealth -= difference;
        }
    }
}
