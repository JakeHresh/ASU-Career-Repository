public class QuickAttack extends Attack
{
    public QuickAttack(Actor t, Actor o)
    {
        super(t, o);
        damage = 10;
        priority = -1;
    }
}
