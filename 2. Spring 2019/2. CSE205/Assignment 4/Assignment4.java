import java.util.Scanner;
import java.util.EmptyStackException;

public class Assignment4
{

    public static void main(String[] args)
    {
        String[] splitInput;
        Scanner scan = new Scanner(System.in);
        ExpressionTree tree = new ExpressionTree();
        System.out.println("Please type your expressions with a space between numbers and operators.");
        System.out.println("Please use postfix notation. As in, 1 + 1 will instead be 1 1 +");
        System.out.println("Please do not use any ( ).");
        System.out.println("Type nothing and just hit enter to quit.");
        System.out.println("Enter an expression.");
        String input = scan.nextLine().trim();
        
        
        while(!input.equals(""))
        {
            splitInput = input.split(" ");

            // TODO: Try to parse the expression and catch any exceptions.
            // For step 17.
            Utilities util = new Utilities();
            if(splitInput.length > 2 && util.isNumber(splitInput[0]) && util.isOperator(splitInput[1]) && util.isNumber(splitInput[2]))
            {
                System.out.println("Error! Infix notation. \nYou used infix notation. Try again.");
            }
            else
            {
                try
                {
                    tree.parseExpression(splitInput);
                    System.out.println("The infix notation of that expression is: " + tree.inFix(tree.getRoot()));
                }
                catch(OperatorOnlyException e)
                {
                    System.out.println(e.getMessage());
                }
                catch(InvalidExpressionException e)
                {
                    System.out.println(e.getMessage());
                }
            }
            System.out.println("Enter an expression.");
            input = scan.nextLine().trim();
        }
        
        System.out.println("Exiting");
        
        scan.close();
    }

}