public abstract class BattleEvent
{
    protected Actor owner;
    protected Actor target;
    protected int damage;
    protected int priority;
    
    public Actor getOwner()
    {
        return owner;
    }
    
    public Actor getTarget()
    {
        return target;
    }
    
    public int getDamage()
    {
        return damage;
    }
    
    public int getPriority()
    {
        return priority;
    }
    
    public abstract void doEvent();
}
