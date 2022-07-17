
public class Utilities implements UtilInterface
{
    public Utilities() { /* Intentionally blank */ }
    
    // Returns true if s is a number
    // From: https://stackoverflow.com/questions/1102891/how-to-check-if-a-string-is-numeric-in-java
    @Override
    public boolean isNumber(String s)
    {
        return s.matches("-?\\d+(\\.\\d+)?");
    }

    // Returns true if s is one on the five basic operators
    // TODO: Implement this for step 2.
    @Override
    public boolean isOperator(String s)
    {
        if(s.equals("+") || s.equals("*") || s.equals("-") || s.equals("/") || s.equals("%"))
        {
            return true;
        }
        return false;
    }

    
    // Returns true if every element in the array is either a number or operator
    // TODO: Implement this for step 3.

    @Override
    public boolean allValidTerms(String[] arr)
    {
        for(int i = 0; i < arr.length; i++)
        {
            if(!isNumber(arr[0]))
            {
                return false;
            }
            if(!isNumber(arr[i]) && !arr[i].equals("*") && !arr[i].equals("/") && !arr[i].equals("%") && !arr[i].equals("+") && !arr[i].equals("-"))
            {
                return false;
            }
        }
        return true;
    }

    // Returns the number of operators in the expression
    @Override
    public int countOps(String[] arr)
    {
        int ops = 0;
        
        for(int i = 0; i < arr.length; i++)
        {
            if(isOperator(arr[i]))
            {
                ops++;
            }
        }
        
        return ops;
    }
    
}