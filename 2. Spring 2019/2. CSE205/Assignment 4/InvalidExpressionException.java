public class InvalidExpressionException extends RuntimeException
{
    public InvalidExpressionException()
    {
        super("\nError! Expression cannot have an even number of terms, start with an operator, or include \nnon-math terms.\nYour expression was invalid. Try again.");
    }
}
