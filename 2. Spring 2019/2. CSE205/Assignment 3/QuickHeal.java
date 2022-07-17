public class QuickHeal extends Heal
{
    public QuickHeal(Actor t, Actor o)
    {
        super(t, o);
        damage = -10;
        priority = -1;
    }
}
