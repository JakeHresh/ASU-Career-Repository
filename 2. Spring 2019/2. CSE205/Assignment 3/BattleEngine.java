public class BattleEngine
{
    private static Node head;
    private static Node tail;
    
    public BattleEngine()
    {
        head = null;
        tail = null;
    }
    
    public static Node getHead()
    {
        return head;
    }
    
    public static boolean isEmpty()
    {
        return head == null;
    }
    
    public static int length()
    {
        int count = 0;
        
        Node current = head;
        while(current != null)
        {
            count++;
            current = current.getNext();
        }
        
        return count;
    }
    
    public static void printContents()
    {
        String out = "";
        
        if(isEmpty())
        {
            out += "Nothing happened.";
        }
        else
        {
            Node current = head;
            while(current != null)
            {
                out = current.getEvent() + "";
                System.out.println(out);
                current = current.getNext();
            }
        }
        
        //System.out.println(out);
    }
    
    public static Actor executeNext()
    {
        Actor target = null;
        //Node current = head;
        if(!isEmpty())
        {
            if(head != null)
            {
                head.getEvent().doEvent();
                target = head.getEvent().getTarget();
                if(head.getNext() != null)
                {
                    head = head.getNext();
                }
            }
        }
        
        return target;
    }
    
    public static void remove(Actor a)
    {
        Node current = head;
        Node last = null;
        for(int i = 0; i < BattleEngine.length(); i++)
        {
            while(current != null && current.getEvent().getOwner().getName() != a.getName() && current.getEvent().getTarget().getName() != a.getName())
            {
                last = current;
                current = current.getNext();
            }
            if(last != null && current != null)
            {
                last.setNext(current.getNext());
            }
            else if(current != null)
            {
                head = current.getNext();
            }
        }
    }
    
    public static void add(Node n)
    {
        Node current = head;
        Node last = null;
        Node temp = null;
        if(isEmpty())
        {
            head = n;
        }
        else
        {
            while(true)
            {
                if(n.getEvent().getPriority() < current.getEvent().getPriority() && current.getPrevious() == null)
                {
                    n.setNext(head);
                    head = n;
                    break;
                }
                else if(n.getEvent().getPriority() < current.getEvent().getPriority())
                {
                    last.setNext(n);
                    n.setNext(current);
                    break;
                }
                else if(n.getEvent().getPriority() >= current.getEvent().getPriority() && current.getNext() == null)
                {
                    current.setNext(n);
                    break;
                }
                else if(n.getEvent().getPriority() >= current.getEvent().getPriority())
                {
                    temp = current;
                    current = current.getNext();
                    current.setPrevious(temp);
                    last = temp;
                }
            }
        }
    }
}
