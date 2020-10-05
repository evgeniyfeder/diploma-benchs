import structure.LazySplayTree;
import structure.SplayTree;

import java.util.Scanner;

public class TreeMain {
    public static void main(String[] args) {
        /* Input Type
        Line 1--> number of nodes in the input tree (eg. m)
        Line 2--> list keys of all nodes present in the tree (m integers)
        Line 3--> alpha
        Line 4--> number of search queries (eg, n)
        Line 5--> n integers (keys that are to be queried)
        Eg of input :-
        7
        5 2 3 7 1 10 0
        5
        6
        0 3 1 2 5 2
        Corresponding output:
        10
         */
        Scanner s = new Scanner(System.in);
        int totNodes = s.nextInt();

        SplayTree input_tree = new SplayTree();
        for (int i = 0; i < totNodes; i++) {
            int in = s.nextInt();
            input_tree.insert(in);
        }

        int alpha = s.nextInt();
        LazySplayTree lazy_tree = new LazySplayTree(input_tree, alpha);

        int tot_comm_req = s.nextInt();
        for (int i = 0; i < tot_comm_req; i++) {
            int u = s.nextInt();
            lazy_tree.search(u);
            System.out.println(lazy_tree.total_routing_cost);
        }
    }
}
