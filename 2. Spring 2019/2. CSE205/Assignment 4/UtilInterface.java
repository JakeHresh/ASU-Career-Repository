/**
 * An interface for several utility methods used in this program.
 * 
 * @author Tyler Baron
 *
 */

public interface UtilInterface
{
    public boolean isNumber(String s);
    
    public boolean isOperator(String s);
    
    public boolean allValidTerms(String[] arr);
    
    public int countOps(String[] arr);
}