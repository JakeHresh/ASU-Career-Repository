import java.util.Stack;
import java.util.EmptyStackException;

public class ExpressionTree extends RuntimeException
{
    private Node root;
    private Utilities util;
    public Stack<Node> stack = new Stack<Node>();
    
    public ExpressionTree()
    {
        root = null;
        util = new Utilities();
    }
    
    public Node getRoot()
    {
        return root;
    }
    
    
    // TODO: Implement the public method parseExpression.
    // This is for steps 12, 13, 14, and 15.
    public void parseExpression(String[] arr) throws InvalidExpressionException, OperatorOnlyException
    {
        Stack<OperatorNode> ostack = new Stack<OperatorNode>();
        Stack<NumberNode> nstack = new Stack<NumberNode>();
        OperatorNode op = null;
        NumberNode nu = null;
        if(util.countOps(arr) == arr.length)
        {
            throw new OperatorOnlyException();
        }
        else if(!util.allValidTerms(arr))
        {
            throw new InvalidExpressionException();
        }
        else if(arr.length%2 == 0)
        {
            throw new InvalidExpressionException();
        }
        else if(arr.length == 1)
        {
            root = new NumberNode(arr[0]);
        }
        else
        {
            for(int i = 0; i < arr.length; i++)
            {
                if(util.isNumber(arr[i]))
                {
                    nu = new NumberNode(arr[i]);
                    stack.push(nu);
                }
                else if(util.isOperator(arr[i]))
                {
                    op = new OperatorNode(arr[i]);
                    op.right = stack.pop();
                    op.left = stack.pop();
                    stack.push(op);
                }
            }
            root = stack.pop();
        }
    }
    // Possible TODO: Implement to do an in-order traversal.
    
    public String inFix(Node n)
    {
        String out = "";
        if(n != null)
        {
            out = inFix(n.getLeft()) + n.toString() + inFix(n.getRight());
        }
        return out;
    }
}