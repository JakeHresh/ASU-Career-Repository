public class OperatorOnlyException extends RuntimeException
{
    public OperatorOnlyException()
    {
        super("\nError! Expression is only operators. \nYou only typed operators. Try again.");
    }
}
