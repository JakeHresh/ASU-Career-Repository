public class Heal extends BattleEvent
{
    public Heal(Actor t, Actor o)
    {
        target = t;
        owner = o;
        damage = -30;
        priority = 0;
    }
    
    public void doEvent()
    {
        System.out.println(owner.getName() + " heals " + target.getName() + " for " + -damage + " health!");
        target.changeHealth(damage);
    }
    
    public String toString()
    {
        String display = "Target: " + target.getName() + " Damage: " + damage + " Priority: " + priority;
        return display;
    }
}
