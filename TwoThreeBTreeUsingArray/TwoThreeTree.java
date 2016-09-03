package TwoThreeBTree;


/**
 * Created by syk on 2016/4/7.
 */
public class TwoThreeTree {
    private static final int DEFAULT_MAXIMUM = 500;
    private TreeNode[] TreeNodeArray;
    private DLLNode[] DLLNodeArray;
    private int root;                       // root is the index of Tree's root(its value is the index of TreeNodeArray)
    private int firstFreeTreeNode;
    private int firstFreeDLLNode;

    public static void main(String[] args) {
        try {
            TwoThreeTree test = new TwoThreeTree(5);
            test.insert(23);
            test.insert(32);
            test.insert(17);
            test.insert(15);
            test.insert(39);
            test.insert(9);
            test.insert(16);
            test.insert(29);
            test.insert(35);
            test.insert(34);
            test.insert(27);
            test.insert(31);
            test.insert(33);
            test.insert(6);
            test.insert(10);
            test.insert(8);
            test.insert(7);
            test.inOrder(test.getRoot());
            //System.out.println(test.toString());
        }catch (TreeOverflowException e){
            System.out.println(e);
        }
    }
    public TwoThreeTree(){
        this(DEFAULT_MAXIMUM);
    }
    public TwoThreeTree(int size){
        TreeNodeArray = new TreeNode[size];
        DLLNodeArray = new DLLNode[size*5];
        root = 0;
        firstFreeDLLNode = 0;
        firstFreeTreeNode = 0;
    }
//my data structure assignment
    public void inOrder(int currentTreeNodeIndex){
        // inorder traversal
        try {
            if (TreeNodeArray[currentTreeNodeIndex].getChildListHead() != -1) {
                //for two condition, the TreeNode has One key and two key
                inOrder(DLLNodeArray[TreeNodeArray[currentTreeNodeIndex].getChildListHead()].getData());
                System.out.print(DLLNodeArray[TreeNodeArray[currentTreeNodeIndex].getKeyListHead()].getData());
                System.out.print(",");
                if (TreeNodeArray[currentTreeNodeIndex].getNumKeys() != 1) {
                    inOrder(DLLNodeArray[DLLNodeArray[TreeNodeArray[currentTreeNodeIndex].getChildListHead()].getNext()].getData());
                    System.out.print(DLLNodeArray[TreeNodeArray[currentTreeNodeIndex].getKeyListTail()].getData());
                    System.out.print(",");
                }
                inOrder(DLLNodeArray[TreeNodeArray[currentTreeNodeIndex].getChildListTail()].getData());
            } else {
                System.out.print(DLLNodeArray[TreeNodeArray[currentTreeNodeIndex].getKeyListHead()].getData());
                System.out.print(",");
                if (TreeNodeArray[currentTreeNodeIndex].getNumKeys() != 1) {
                    System.out.print(DLLNodeArray[TreeNodeArray[currentTreeNodeIndex].getKeyListTail()].getData());
                    System.out.print(",");
                }
            }
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in inOrder method.");
        }
    }

    int getRoot(){
        return root;
    }

    void insert(int data){
        try {
            if (firstFreeTreeNode > 0) {
                int currentTreeIndex = root;
                while (true) {
                    // find the index of leaf which I need insert
                    int temp = currentTreeIndex;
                    currentTreeIndex = getNextIndex(currentTreeIndex, data);

                    if (temp == currentTreeIndex)
                        break;
                }
                // I split two main condition
                if (TreeNodeArray[currentTreeIndex].getNumKeys() == 1) {
                    DLLNode NodeData = new DLLNode(data);
                    insertConditionOne(currentTreeIndex, NodeData, -1);
                } else {
                    DLLNode NodeData = new DLLNode(data);
                    insertConditionTwo(currentTreeIndex, NodeData, -1);
                }
            } else {
                DLLNodeArray[0] = new DLLNode(data, -1, -1);
                DLLNodeArray[1] = new DLLNode(-1, -1, 2);
                DLLNodeArray[2] = new DLLNode(-1, 1, 4);
                DLLNodeArray[3] = new DLLNode(Integer.MIN_VALUE, -1, -1);
                DLLNodeArray[4] = new DLLNode(-1, 2, -1);
                TreeNodeArray[0] = new TreeNode(0, -1, -1);
                firstFreeDLLNode += 5;
                ++firstFreeTreeNode;
            }
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in insert method.");
        }
    }

    private int createNewBrotherTreeNode(int tempTreeNode) {
        //in condition two
        try {
            if (tempTreeNode != -1)  //judge if the currentTreeNode has child
                TreeNodeArray[firstFreeTreeNode] = new TreeNode(firstFreeDLLNode,
                        firstFreeDLLNode + 1, firstFreeDLLNode + 2);
            else
                TreeNodeArray[firstFreeTreeNode] = new TreeNode(firstFreeDLLNode, -1, -1);
            //the right key will be divided
            return firstFreeTreeNode;
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException occurs in createNewBrotherTreeNode method");
        }
    }

    private int createNewParentTreeNode(){
        //in condition two and currentTreeNode has no parent
        try {
            // the parent Tree Node will be created after brother TreeNode
            TreeNodeArray[firstFreeTreeNode] = new TreeNode(firstFreeDLLNode + 5,
                    firstFreeDLLNode + 6, firstFreeDLLNode + 7);
            TreeNodeArray[firstFreeTreeNode - 1].setParent(firstFreeTreeNode);
            root = firstFreeTreeNode;
            return firstFreeTreeNode;
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in createNewParentTreeNode method");
        }
    }

    private void createBrotherDLLNodeBlock(
            int keyIndexHead, int leftChild, int rightChild){
        try {
            //create two new DLLNode block
            DLLNodeArray[firstFreeDLLNode] = new DLLNode(DLLNodeArray[keyIndexHead + 3].getData(),
                    DLLNodeArray[keyIndexHead + 3].getPrevious(), DLLNodeArray[keyIndexHead + 3].getNext());
            //if(DLLNodeArray[keyIndexHead+3].getPrevious()!=-1) {
            DLLNodeArray[DLLNodeArray[keyIndexHead + 3].getPrevious()].setNext(firstFreeDLLNode);
            //}
            if (DLLNodeArray[keyIndexHead + 3].getNext() != -1) {
                DLLNodeArray[DLLNodeArray[keyIndexHead + 3].getNext()].setPrevious(firstFreeDLLNode);
            }
            //the left child is the index of its brothers's middle child
            DLLNodeArray[firstFreeDLLNode + 1] = new DLLNode(
                    leftChild, -1, firstFreeDLLNode + 2);
            //the right child is the index of its brother's right child
            DLLNodeArray[firstFreeDLLNode + 2] = new DLLNode(
                    rightChild, firstFreeDLLNode + 1, firstFreeDLLNode + 4);
            //empty
            DLLNodeArray[firstFreeDLLNode + 3] = new DLLNode(
                    Integer.MIN_VALUE, -1, -1);
            //empty
            DLLNodeArray[firstFreeDLLNode + 4] = new DLLNode(
                    -1, firstFreeDLLNode + 2, -1);
            firstFreeDLLNode += 5;
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in createBrotherDLLNodeBlock method");
        }
    }
    private void createParentDLLNodeBlock(
            DLLNode overflowNode, int keyIndexHead, int currentTreeIndex, int brotherTreeNode){
        try {
            DLLNodeArray[firstFreeDLLNode] = new DLLNode(overflowNode.getData(),
                    overflowNode.getPrevious(), overflowNode.getNext());
            DLLNodeArray[overflowNode.getPrevious()].setNext(firstFreeDLLNode);
            DLLNodeArray[overflowNode.getNext()].setPrevious(firstFreeDLLNode);
            //the left child is currentTreeIndex
            DLLNodeArray[firstFreeDLLNode + 1] = new DLLNode(
                    currentTreeIndex, -1, firstFreeDLLNode + 2);
            //the right child is brotherTreeNode
            DLLNodeArray[firstFreeDLLNode + 2] = new DLLNode(
                    brotherTreeNode, firstFreeDLLNode + 1, firstFreeDLLNode + 4);
            //empyt
            DLLNodeArray[firstFreeDLLNode + 3] = new DLLNode(
                    Integer.MIN_VALUE, -1, -1);
            //empty
            DLLNodeArray[firstFreeDLLNode + 4] = new DLLNode(
                    -1, firstFreeDLLNode + 2, -1);
            firstFreeDLLNode += 5;
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in createBrotherDLLNodeBlock method");
        }
    }

    private void resetSingleTreeNode(int keyIndexHead, int currentTreeIndex, int tempTreeNode){
        //this method is to reset the tree to the status of having one key
        try {
            DLLNodeArray[keyIndexHead + 3].setData(Integer.MIN_VALUE);
            DLLNodeArray[keyIndexHead + 4].setData(-1);
            //reset the currentTreeIndex
            TreeNodeArray[currentTreeIndex].setKeyListTail(-1);
            TreeNodeArray[currentTreeIndex].setNumKeys(1);
            if (tempTreeNode != -1) {
                TreeNodeArray[currentTreeIndex].setChildListTail(keyIndexHead + 2);
            }
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in resetSingleTreeNode method");
        }
    }

    private void setChildrenParent(int parent, int leftChild, int rightChild){
        //as the name of method
        try {
            if (leftChild != -1) {
                TreeNodeArray[leftChild].setParent(parent);
                TreeNodeArray[rightChild].setParent(parent);
            }
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in setChildrenParent method");
        }
    }

    public void insertConditionTwo(int currentTreeIndex, DLLNode NodeData, int tempTreeNode){

        /*
        the leaf has two key.
        currentTreeIndex is an index of TreeNodeArray.
        data is what you want to insert.
        tempTreeNode is the new Created TreeNode, which maybe have many offspring.
        */
        try {
            int keyIndexhead = TreeNodeArray[currentTreeIndex].getKeyListHead();
            int keyIndexTail = TreeNodeArray[currentTreeIndex].getKeyListTail();
            DLLNode overflowNode;
            if (TreeNodeArray[currentTreeIndex].getParent() == -1) {
                //currentTreeIndex == root
                //create two new TreeNodes, brother and parent
                int brotherTreeNode = createNewBrotherTreeNode(tempTreeNode);
                ++firstFreeTreeNode;

                int parentTreeNode = createNewParentTreeNode();
                ++firstFreeTreeNode;

                if (NodeData.getData() <= DLLNodeArray[keyIndexhead].getData()) {
                    //overflow from leftChild
                    //when the data is inserted into the TreeNode, the middle one will be the overflow
                    overflowNode = new DLLNode(DLLNodeArray[keyIndexhead].getData(),
                            DLLNodeArray[keyIndexhead].getPrevious(), DLLNodeArray[keyIndexhead].getNext());
                    DLLNodeArray[keyIndexhead].setData(NodeData.getData());
                    //reset DLLNodes' previous and next
                    if (tempTreeNode != -1) {
                        DLLNodeArray[keyIndexhead].setNext(NodeData.getNext());
                        DLLNodeArray[keyIndexhead].setPrevious(NodeData.getPrevious());
                        DLLNodeArray[NodeData.getNext()].setPrevious(keyIndexhead);
                        DLLNodeArray[NodeData.getPrevious()].setNext(keyIndexhead);
                    } else {
                        overflowNode.setPrevious(keyIndexhead);
                        overflowNode.setNext(firstFreeDLLNode);
                    }
                    //int brotherDLLNode = firstFreeDLLNode;
                    createBrotherDLLNodeBlock(keyIndexhead,
                            DLLNodeArray[keyIndexhead + 2].getData(), DLLNodeArray[keyIndexhead + 4].getData());

                    setChildrenParent(brotherTreeNode,
                            DLLNodeArray[keyIndexhead + 2].getData(), DLLNodeArray[keyIndexhead + 4].getData());
                    //overflow is the parent's data
                    createParentDLLNodeBlock(overflowNode, keyIndexhead, currentTreeIndex, brotherTreeNode);

                    //left child doesn't change, right child become tempTreeNode
                    DLLNodeArray[keyIndexhead + 2].setData(tempTreeNode);
                } else if (NodeData.getData() <= DLLNodeArray[keyIndexTail].getData()) {
                    //overflow from center Child
                    overflowNode = new DLLNode(NodeData.getData(), NodeData.getPrevious(), NodeData.getNext());
                    //create two new DLLNode block
                    //int brotherDLLNode = firstFreeDLLNode;

                    if (tempTreeNode == -1) {
                        overflowNode.setPrevious(keyIndexhead);
                        overflowNode.setNext(firstFreeDLLNode);
                    }

                    createBrotherDLLNodeBlock(keyIndexhead, tempTreeNode, DLLNodeArray[keyIndexhead + 4].getData());
                    setChildrenParent(brotherTreeNode,
                            tempTreeNode, DLLNodeArray[keyIndexhead + 4].getData());
                    //int parentDLLNode = firstFreeDLLNode;
                    createParentDLLNodeBlock(overflowNode, keyIndexhead, currentTreeIndex, brotherTreeNode);
                } else {
                    //overflow from right child
                    overflowNode = new DLLNode(DLLNodeArray[keyIndexhead + 3].getData(),
                            DLLNodeArray[keyIndexhead + 3].getPrevious(), DLLNodeArray[keyIndexhead + 3].getNext());
                    DLLNodeArray[keyIndexhead + 3].setData(NodeData.getData());

                    if (tempTreeNode != -1) {
                        //set the relation of
                        DLLNodeArray[keyIndexhead + 3].setNext(NodeData.getNext());
                        DLLNodeArray[keyIndexhead + 3].setPrevious(NodeData.getPrevious());
                        DLLNodeArray[NodeData.getNext()].setPrevious(keyIndexhead + 3);
                        DLLNodeArray[NodeData.getPrevious()].setNext(keyIndexhead + 3);
                    } else {
                        overflowNode.setPrevious(keyIndexhead);
                        overflowNode.setNext(firstFreeDLLNode);
                    }
                    //create two new DLLNode block
                    createBrotherDLLNodeBlock(keyIndexhead, DLLNodeArray[keyIndexhead + 4].getData(), tempTreeNode);
                    setChildrenParent(brotherTreeNode,
                            DLLNodeArray[keyIndexhead + 4].getData(), tempTreeNode);
                    createParentDLLNodeBlock(overflowNode, keyIndexhead, currentTreeIndex, brotherTreeNode);
                }
                resetSingleTreeNode(keyIndexhead, currentTreeIndex, tempTreeNode);
                TreeNodeArray[currentTreeIndex].setParent(parentTreeNode);
            } else {
                int brotherTreeNode = createNewBrotherTreeNode(tempTreeNode);
                ++firstFreeTreeNode;
                TreeNodeArray[brotherTreeNode].setParent(TreeNodeArray[currentTreeIndex].getParent());
                if (NodeData.getData() <= DLLNodeArray[keyIndexhead].getData()) {
                    //overflow from left child
                    overflowNode = new DLLNode(DLLNodeArray[keyIndexhead].getData(),
                            DLLNodeArray[keyIndexhead].getPrevious(), DLLNodeArray[keyIndexhead].getNext());
                    //overflow = DLLNodeArray[keyIndexhead].getData();
                    DLLNodeArray[keyIndexhead].setData(NodeData.getData());

                    if (tempTreeNode != -1) {
                        DLLNodeArray[keyIndexhead].setNext(NodeData.getNext());
                        DLLNodeArray[keyIndexhead].setPrevious(NodeData.getPrevious());
                        if (NodeData.getNext() != -1) {
                            DLLNodeArray[NodeData.getNext()].setPrevious(keyIndexhead);
                        }
                        if (NodeData.getPrevious() != -1) {
                            DLLNodeArray[NodeData.getPrevious()].setNext(keyIndexhead);
                        }
                    } else {
                        overflowNode.setPrevious(keyIndexhead);
                        overflowNode.setNext(firstFreeDLLNode);
                    }
                    //create a new DLLNode block
                    createBrotherDLLNodeBlock(keyIndexhead,
                            DLLNodeArray[keyIndexhead + 2].getData(), DLLNodeArray[keyIndexhead + 4].getData());
                    setChildrenParent(brotherTreeNode,
                            DLLNodeArray[keyIndexhead + 2].getData(), DLLNodeArray[keyIndexhead + 4].getData());
                    //rest the keyIndexHead ~ keyIndexHead+4
                    DLLNodeArray[keyIndexhead + 2].setData(tempTreeNode);
                } else if (NodeData.getData() <= DLLNodeArray[keyIndexTail].getData()) {
                    overflowNode = new DLLNode(NodeData.getData(), NodeData.getPrevious(), NodeData.getNext());

                    if (tempTreeNode == -1) {
                        overflowNode.setPrevious(keyIndexhead);
                        overflowNode.setNext(firstFreeDLLNode);
                    }
                    //create two new DLLNode block
                    createBrotherDLLNodeBlock(keyIndexhead, tempTreeNode, DLLNodeArray[keyIndexhead + 4].getData());
                    setChildrenParent(brotherTreeNode,
                            tempTreeNode, DLLNodeArray[keyIndexhead + 4].getData());
                } else {
                    overflowNode = new DLLNode(DLLNodeArray[keyIndexhead + 3].getData(),
                            DLLNodeArray[keyIndexhead + 3].getPrevious(), DLLNodeArray[keyIndexhead + 3].getNext());
                    DLLNodeArray[keyIndexhead + 3].setData(NodeData.getData());
                    // reset the relation of the origin DLLNode and new DLLNode
                    if (tempTreeNode != -1) {
                        DLLNodeArray[keyIndexhead + 3].setNext(NodeData.getNext());
                        DLLNodeArray[keyIndexhead + 3].setPrevious(NodeData.getPrevious());
                        DLLNodeArray[NodeData.getNext()].setPrevious(keyIndexhead + 3);
                        DLLNodeArray[NodeData.getPrevious()].setNext(keyIndexhead + 3);
                    } else {
                        overflowNode.setNext(firstFreeDLLNode);
                        overflowNode.setPrevious(keyIndexhead);
                    }
                    //create one new DLLNode block
                    createBrotherDLLNodeBlock(keyIndexhead, DLLNodeArray[keyIndexhead + 4].getData(), tempTreeNode);
                    setChildrenParent(brotherTreeNode,
                            DLLNodeArray[keyIndexhead + 4].getData(), tempTreeNode);
                }
                resetSingleTreeNode(keyIndexhead, currentTreeIndex, tempTreeNode);
                //like the insert() method
                if (TreeNodeArray[TreeNodeArray[currentTreeIndex].getParent()].getNumKeys() == 1) {
                    insertConditionOne(TreeNodeArray[currentTreeIndex].getParent(), overflowNode, brotherTreeNode);
                } else {
                    insertConditionTwo(TreeNodeArray[currentTreeIndex].getParent(), overflowNode, brotherTreeNode);
                }
            }
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in insertConditionTwo method");
        }
    }

    private void insertConditionOne(int currentTreeIndex, DLLNode NodeData, int tempTreeNode) {
        // the leaf has only one key
        try {
            int keyIndexhead = TreeNodeArray[currentTreeIndex].getKeyListHead(); // the index of exist data of the leaf
            if (DLLNodeArray[keyIndexhead].getData() <= NodeData.getData()) {
                //overflow from right child
                //set the order of DLLNode
                DLLNodeArray[keyIndexhead + 3].setData(NodeData.getData());
                //reset the relation of DLLNodes
                if (tempTreeNode != -1) {
                    DLLNodeArray[keyIndexhead + 3].setNext(NodeData.getNext());
                    DLLNodeArray[DLLNodeArray[keyIndexhead + 3].getNext()].setPrevious(keyIndexhead + 3);
                    DLLNodeArray[keyIndexhead + 3].setPrevious(NodeData.getPrevious());
                    DLLNodeArray[DLLNodeArray[keyIndexhead + 3].getPrevious()].setNext(keyIndexhead + 3);
                } else {
                    DLLNodeArray[keyIndexhead + 3].setNext(DLLNodeArray[keyIndexhead].getNext());
                    if (DLLNodeArray[keyIndexhead + 3].getNext() != -1) {
                        DLLNodeArray[DLLNodeArray[keyIndexhead + 3].getNext()].setPrevious(keyIndexhead + 3);
                    }
                    DLLNodeArray[keyIndexhead + 3].setPrevious(keyIndexhead);
                    DLLNodeArray[keyIndexhead].setNext(keyIndexhead + 3);
                }
                DLLNodeArray[keyIndexhead + 4].setData(tempTreeNode);
                //reset the currentTreeNode
                TreeNodeArray[currentTreeIndex].setKeyListTail(keyIndexhead + 3);
                TreeNodeArray[currentTreeIndex].setNumKeys(2);
                if (tempTreeNode != -1) {
                    TreeNodeArray[currentTreeIndex].setChildListTail(keyIndexhead + 4);
                }
            } else {
                //overflow from left child
                DLLNodeArray[keyIndexhead + 3].
                        setData(DLLNodeArray[keyIndexhead].getData());
                DLLNodeArray[keyIndexhead].setData(NodeData.getData());
                //reset the relation of DLLNodes
                DLLNodeArray[keyIndexhead + 3].setNext(DLLNodeArray[keyIndexhead].getNext());
                if (DLLNodeArray[keyIndexhead].getNext() != -1) {
                    DLLNodeArray[DLLNodeArray[keyIndexhead].getNext()].setPrevious(keyIndexhead + 3);
                }
                if (tempTreeNode != -1) {
                    DLLNodeArray[keyIndexhead + 3].setPrevious(DLLNodeArray[keyIndexhead].getPrevious());
                    DLLNodeArray[DLLNodeArray[keyIndexhead].getPrevious()].setNext(keyIndexhead + 3);
                    DLLNodeArray[keyIndexhead].setPrevious(NodeData.getPrevious());
                    DLLNodeArray[NodeData.getPrevious()].setNext(keyIndexhead);
                    DLLNodeArray[keyIndexhead].setNext(NodeData.getNext());
                    DLLNodeArray[NodeData.getNext()].setPrevious(keyIndexhead);
                } else {
                    //is leaf
                    DLLNodeArray[keyIndexhead].setNext(keyIndexhead + 3);
                    DLLNodeArray[keyIndexhead + 3].setPrevious(keyIndexhead);
                }
                //rest the currentDLLNode block
                DLLNodeArray[keyIndexhead + 4].setData(DLLNodeArray[keyIndexhead + 2].getData());
                DLLNodeArray[keyIndexhead + 2].setData(tempTreeNode);
                //reset the currentTreeNode
                TreeNodeArray[currentTreeIndex].setKeyListTail(keyIndexhead + 3);
                TreeNodeArray[currentTreeIndex].setNumKeys(2);
                if (tempTreeNode != -1) {
                    TreeNodeArray[currentTreeIndex].setChildListTail(keyIndexhead + 4);
                }
            }
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in insertConditionOne method");
        }
    }

    private int getNextIndex(int currentTreeIndex, int data) {
        TreeNode temp = TreeNodeArray[currentTreeIndex];
        //judge if this TreeNode is a leaf
        try {
            if (temp.getChildListHead() == -1) {
                return currentTreeIndex;
            }
            if (temp.getNumKeys() == 1) {
                //if the TreeNode has one key
                if (DLLNodeArray[temp.getKeyListHead()].getData() >= data) {
                    currentTreeIndex = DLLNodeArray[temp.getChildListHead()].getData();
                } else {
                    currentTreeIndex = DLLNodeArray[temp.getChildListTail()].getData();
                }
            } else {
                //if the TreeNode has two key
                if (DLLNodeArray[temp.getKeyListHead()].getData() >= data) {
                    currentTreeIndex = DLLNodeArray[temp.getChildListHead()].getData();
                } else if (DLLNodeArray[temp.getKeyListTail()].getData() >= data) {
                    currentTreeIndex = DLLNodeArray[temp.getChildListHead() + 1].getData();
                } else {
                    currentTreeIndex = DLLNodeArray[temp.getChildListTail()].getData();
                }
            }
            return currentTreeIndex;
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in getNextIndex method");
        }
    }

    @Override
    public String toString() {
        try {
            // this line is just for the assignment just
            StringBuilder builder = new StringBuilder("insert in this order:\n23, 32, 17, 15, 39, 9, 16, 29, 35, 34, 27, 31, 33, 6, 10, 8, 7.\n");
            builder.append("root = ").append(root);
            builder.append("\nTreeNodeArray:\n");
            for (int i = 0; i < firstFreeTreeNode; i++) {
                builder.append(i).append(": ");
                builder.append(TreeNodeArray[i]).append("\n");
            }
            builder.append("DLLNodeArray\n");
            for (int i = 0; i < firstFreeDLLNode; i++) {
                builder.append(i).append(": ");
                builder.append(DLLNodeArray[i]).append("\n");
                if (i % 5 == 4) {
                    builder.append("\n");
                }
            }
            return builder.toString();
        }catch (RuntimeException e){
            throw new TreeOverflowException("TreeOverflowException Exception occurs in toString method");
        }
    }

    class TreeNode {
        private int parent;
        private int numKeys;
        private int keyListHead;
        private int keyListTail;
        private int childListHead;
        private int childListTail;

        public TreeNode() {
            numKeys=0;
            childListTail = childListHead = keyListTail = keyListHead = parent = -1;
        }

        TreeNode(int data, int leftChild, int rightChild) {
            //data is the index of the new TreeNode's element;
            //leftChild is the index of the new TreeNode's leftChild(if any)
            //rightChild is the index of the new TreeNode's rightChild(if any)
            parent=-1;
            numKeys=1;
            keyListHead=data;
            keyListTail=-1;
            childListHead=leftChild;
            childListTail=rightChild;
        }

        @Override
        public String toString() {
            return "TreeNode{" +
                    "parent=" + parent +
                    ", numKeys=" + numKeys +
                    ", keyListHead=" + keyListHead +
                    ", keyListTail=" + keyListTail +
                    ", childListHead=" + childListHead +
                    ", childListTail=" + childListTail +
                    '}';
        }
        int getParent() {
            return parent;
        }
        void setParent(int parent) {
            this.parent = parent;
        }

        int getNumKeys() {
            return numKeys;
        }

        void setNumKeys(int numKeys) {
            this.numKeys = numKeys;
        }

        int getKeyListHead() {
            return keyListHead;
        }

        void setKeyListHead(int keyListHead) {
            this.keyListHead = keyListHead;
        }

        int getKeyListTail() {
            return keyListTail;
        }

        void setKeyListTail(int keyListTail) {
            this.keyListTail = keyListTail;
        }

        int getChildListHead() {
            return childListHead;
        }

        void setChildListHead(int childListHead) {
            this.childListHead = childListHead;
        }

        int getChildListTail() {
            return childListTail;
        }

        void setChildListTail(int childListTail) {
            this.childListTail = childListTail;
        }
    }
}
