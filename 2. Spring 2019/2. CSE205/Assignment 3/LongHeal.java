public class LongHeal extends Heal
{
    public LongHeal(Actor t, Actor o)
    {
        super(t, o);
        damage = -80;
        priority = 1;
    }
}
