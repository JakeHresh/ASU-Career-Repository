import java.util.Scanner;
import java.util.ArrayList;
public class Assignment3
{
    static Scanner scan = new Scanner(System.in);
    static ArrayList<Actor> actors = new ArrayList<Actor>();
    static Actor player = null;
    static Actor goblin = null;
    static Actor imp = null;
    static boolean ongoing = true;
    static boolean notAdded = true;
    static int turns = 0;
    public static void main(String[] args)
    {
        player = new Actor("Player");
        goblin = new Actor("Goblin");
        actors.add(player);
        actors.add(goblin);
        String input = "";
        while(!input.equals("H") && ongoing && player.getHealth() > 0)
        {
            input = mainMenu();
            if(input.equals("A"))
            {
                for(Actor actor : actors)
                {
                    System.out.println(actor.getName() + " has " + actor.getHealth() + " health left.");
                }
            }
            else if(input.equals("B"))
            {
                System.out.println("Which enemy do you want to attack? (Type their name)");
                String choose = scan.nextLine();
                Actor target = actorSearch(choose);
                while(target == null)
                {
                    System.out.println("No enemy by that name!");
                    choose = scan.nextLine();
                    target = actorSearch(choose);
                }
                BattleEngine.add(new Node(new QuickAttack(target, player)));
                runTurn();
                if(!ongoing)
                {
                    break;
                }
            }
            else if(input.equals("C"))
            {
                System.out.println("Which enemy do you want to attack? (Type their name)");
                String choose = scan.nextLine();
                Actor target = actorSearch(choose);
                while(target == null)
                {
                    System.out.println("No enemy by that name!");
                    choose = scan.nextLine();
                    target = actorSearch(choose);
                }
                BattleEngine.add(new Node(new Attack(target, player)));
                runTurn();
                if(!ongoing)
                {
                    break;
                }
            }
            else if(input.equals("D"))
            {
                System.out.println("Which enemy do you want to attack? (Type their name)");
                String choose = scan.nextLine();
                Actor target = actorSearch(choose);
                while(target == null)
                {
                    System.out.println("No enemy by that name!");
                    choose = scan.nextLine();
                    target = actorSearch(choose);
                }
                BattleEngine.add(new Node(new PreciseAttack(target, player)));
                runTurn();
                if(!ongoing)
                {
                    break;
                }
            }
            else if(input.equals("E"))
            {
                BattleEngine.add(new Node(new QuickHeal(player, player)));
                runTurn();
                if(!ongoing)
                {
                    break;
                }
            }
            else if(input.equals("F"))
            {
                BattleEngine.add(new Node(new Heal(player, player)));
                runTurn();
                if(!ongoing)
                {
                    break;
                }
            }
            else if(input.equals("G"))
            {
                BattleEngine.add(new Node(new LongHeal(player, player)));
                runTurn();
                if(!ongoing)
                {
                    break;
                }
            }
            //input = mainMenu();
        }
    }
    
    public static Actor actorSearch(String n)
    {
        Actor searched = null;
        for(Actor actor : actors)
        {
            if(n.equals(actor.getName()))
            {
                searched = actor;
                break;
            }
        }
        return searched;
    }
    
    public static void runTurn()
    {
        turns++;
        if(notAdded)
        {
            imp = null;
        }
        if(notAdded && turns >= 3)
        {
            imp = new Actor("Imp");
            actors.add(imp);
            System.out.println("A wandering Imp sneaks up on you and joins the battle against you!");
            notAdded = false;
        }
        if(goblin != null && player != null)
        {
            BattleEngine.add(new Node(new Attack(player, goblin)));
        }
        if(imp != null && player != null)
        {
            BattleEngine.add(new Node(new QuickAttack(player, imp)));
        }
        System.out.println("Battle Event queue is:");
        BattleEngine.printContents();
        for(Actor actor : actors)
        {
            Actor target = BattleEngine.executeNext();
            /*if(target.isDead())
            {
                actors.remove(target);
                target = null;
                break;
            }*/
            if(imp != null && imp.isDead())
            {
                BattleEngine.remove(imp);
                //break;
            }
            if(goblin != null && goblin.isDead())
            {
                BattleEngine.remove(goblin);
                //break;
            }
            if(player != null && player.isDead())
            {
                BattleEngine.remove(player);
                //break;
            }
        }
        for(Actor actor2 : actors)
        {
            BattleEngine.remove(actor2);
        }
        if(goblin != null && goblin.isDead())
        {
            actors.remove(goblin);
            goblin = null;
        }
        if(imp != null && imp.isDead())
        {
            actors.remove(imp);
            imp = null;
        }
        if(actors.size() == 1 || player == null)
        {
            ongoing = false;
        }
    }
    
    public static String mainMenu()
    {
        System.out.println("What do you want to do?");
        System.out.println("A. Check Status of the Combatants");
        System.out.println("B. Quick Attack");
        System.out.println("C. Normal Attack");
        System.out.println("D. Precise Attack");
        System.out.println("E. Quick Heal");
        System.out.println("F. Normal Heal");
        System.out.println("G. Long Heal");
        System.out.println("H. Quit");
        String input = scan.nextLine();
        input = input.toUpperCase();
        while(!input.equals("A") && !input.equals("B") && !input.equals("C") && !input.equals("D") && !input.equals("E") && !input.equals("F") && !input.equals("G") && !input.equals("H"))
        {
            System.out.println("Invalid input");
            input = scan.nextLine();
            input = input.toUpperCase();
        }
        return input;
    }
}
