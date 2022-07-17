import java.util.*;
public class Assignment5
{
    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        Stack<String> stack = new Stack<String>();
        Queue<String> q = new LinkedList<String>();
        Stack<String> reverse = new Stack<String>();
        System.out.println("Please input the cars, one at a time in the order they enter the yard.");
        System.out.println("Type DONE when finished.");
        String input = scan.nextLine();
        while(!input.equals("DONE"))
        {
            stack.push(input);
            input = scan.nextLine();
        }
        System.out.println("Now, provide the desired output order. You must type as many as you said entered the yard.");
        for(int i = 0; i < stack.size(); i++)
        {
            q.add(scan.nextLine());
        }
        boolean allLeft = true;
        int size1 = stack.size();
        for(int j = 0; j < size1; j++)
        {
            if(stack.peek().equals(q.peek()))
            {
                stack.pop();
                q.remove();
            }
            else
            {
                allLeft = false;
            }
        }
        if(allLeft)
        {
            System.out.println("The cars were able to leave in that order!");
        }
        else
        {
            int size = stack.size();
            String out = "";
            for(int j = 0; j < size; j++)
            {
                reverse.push(stack.pop());
            }
            for(int i = 0; i < size; i++)
            {
                out += reverse.pop();
            }
            System.out.println("The cars could not leave in that order...");
            System.out.println("Input:");
            System.out.println("Holding Line: " + out);
        }
    }
}
