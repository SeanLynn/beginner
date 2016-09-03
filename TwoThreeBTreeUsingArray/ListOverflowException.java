package TwoThreeBTree;

/**
 * Created by syk on 2016/4/6.
 */
public class ListOverflowException extends RuntimeException {
    public ListOverflowException() {
        System.out.println("list overflow exception.");
    }

    public ListOverflowException(String message) {
        System.out.printf(message);
    }
}
