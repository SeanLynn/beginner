package TwoThreeBTree;

public class testDLL {

    public static void main(String[] args) {
        testDLL test = new testDLL(100);
        try {
            test.insertInOrder(10);
            test.insertInOrder(32);
            test.insertInOrder(23);
            test.insertInOrder(80);
            test.insertInOrder(76);
            test.insertInOrder(27);
            test.insertInOrder(76);
            test.insertInOrder(56);
            test.insertInOrder(45);
        }catch (ListOverflowException e){
            e.printStackTrace();
        }
        System.out.println(test.toString());
    }

    private DLLNode[] DLL;
    private int head;
    private int tail;
    private int firstFreeDLLNode;//the index of first free DLLNode in array
    testDLL(int size){
        DLL = new DLLNode[size];
        head = 0;
        tail = 0;
        firstFreeDLLNode = 0;
    }

    public void insertInOrder(int data) {
        try {
            DLL[firstFreeDLLNode] = new DLLNode(data);

            if (firstFreeDLLNode > 0) {
                if (DLL[head].getData() > data) {
                    // if the data is less than the node of head
                    DLL[firstFreeDLLNode].setNext(head);
                    DLL[head].setPrevious(firstFreeDLLNode);
                    head = firstFreeDLLNode;
                } else if (DLL[tail].getData() <= data) {
                    // if the data is larger than the node of head
                    DLL[firstFreeDLLNode].setPrevious(tail);
                    DLL[tail].setNext(firstFreeDLLNode);
                    tail = firstFreeDLLNode;
                } else {
                    int tempIndex = head;
                    while (DLL[tempIndex].getData() < data) {
                        //end until temp.getData >= data
                        tempIndex = DLL[tempIndex].getNext();
                    }
                    //adjust indices of temp, temp.previous and the new inserted node
                    DLL[firstFreeDLLNode].setNext(tempIndex);
                    DLL[firstFreeDLLNode].setPrevious(DLL[tempIndex].getPrevious());
                    DLL[DLL[tempIndex].getPrevious()].setNext(firstFreeDLLNode);
                    DLL[tempIndex].setPrevious(firstFreeDLLNode);
                }
            }
            ++firstFreeDLLNode;
        }catch (ListOverflowException e){
            e.printStackTrace();
        }
    }
    @Override
    public String toString() {
        try {
            StringBuilder builder = new StringBuilder();
            //if the DLL is not empty
            if (firstFreeDLLNode != 0)
                for (int i = 0; DLL[i] != null; i++)
                    builder.append(DLL[i]).append("\n");
            return builder.toString();
        }catch (ListOverflowException e){
            e.printStackTrace();
        }
        return "";
    }
}
