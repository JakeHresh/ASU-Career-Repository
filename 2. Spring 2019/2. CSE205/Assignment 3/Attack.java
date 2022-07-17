public class Attack extends BattleEvent
{
    public Attack(Actor t, Actor o)
    {
        target = t;
        owner = o;
        damage = 30;
        priority = 0;
    }
    
    public int getPriority()
    {
        return priority;
    }
    
    public void doEvent()
    {
        System.out.println(owner.getName() + " attacks " + target.getName() + " for " + damage + " damage!");
        target.changeHealth(damage);
        if(target.isDead())
        {
            System.out.println(target.getName() + " is defeated!");
            //BattleEngine.remove(target);
        }
    }
    
    public String toString()
    {
        String display = "Target: " + target.getName() + " Damage: " + damage + " Priority: " + priority;
        return display;
    }
}
