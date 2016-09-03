package TwoThreeBTree;

/**
 * Created by syk on 2016/4/10.
 */
public class TreeOverflowException extends RuntimeException {
    TreeOverflowException(){
        System.out.println("Tree overflow exception");
    }

    TreeOverflowException(String message){
        System.out.println(message);
    }
}
