package TwoThreeBTree;

/**
 * Created by syk on 2016/4/6.
 */
public class DLLNode {
    private int data;
    private int previous;
    private int next;
    public DLLNode(int data){
        this(data, -1,-1);
    }
    public DLLNode(int data, int previous, int next){
        this.data = data;
        this.previous = previous;
        this.next = next;
    }

    @Override
    public String toString() {
        return "DLLNode{" +
                "data=" + data +
                ", previous=" + previous +
                ", next=" + next +
                '}';
    }

    public void setData(int data){
        this.data = data;
    }

    public int getData(){
        return data;
    }

    public int getPrevious() {
        return previous;
    }

    public void setPrevious(int previous) {
        this.previous = previous;
    }

    public int getNext() {
        return next;
    }

    public void setNext(int next) {
        this.next = next;
    }
}

