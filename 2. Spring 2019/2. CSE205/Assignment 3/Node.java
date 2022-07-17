public class Node
{
    private Node next;
    private BattleEvent event;
    private Node previous;
    
    public Node(BattleEvent e)
    {
        event = e;
        next = null;
        previous = null;
    }
    
    public BattleEvent getEvent()
    {
        return event;
    }
    
    public void setEvent(BattleEvent e)
    {
        event = e;
    }
    
    public void setNext(Node n)
    {
        next = n;
    }
    
    public Node getNext()
    {
        return next;
    }
    
    public void setPrevious(Node n)
    {
        previous = n;
    }
    
    public Node getPrevious()
    {
        return previous;
    }
}
