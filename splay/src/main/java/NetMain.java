import structure.LazySplayNet;
import structure.SplayNet;

import java.util.Scanner;

public class NetMain {
    public static void main(String[] args) {
        /* Input Type
        Line 1--> number of nodes in the input tree (eg. m)
        Line 2--> list keys of all nodes present in the tree (m integers)
        Line 3--> alpha value -- single integer
        Line 4--> number of search queries (eg, n)
        Line 5 to line (n+5)--> n pairs of integers in next n lines
        Eg of input :-
        7
        5 2 3 7 1 10 0
        5
        4
        0 3
        1 2
        2 5
        1 7
        Corresponding output:
        original Tree:
        5 2 1 0 3 7 10
        Final tree:
        2 0 1 5 3 7 10
        total_routing_cost=9
        epoch_routing_cost=4
        adjustment_cost=5
         */
        Scanner s = new Scanner(System.in);
        int totNodes = s.nextInt();
        SplayNet input_net = new SplayNet();
        for (int i = 0; i < totNodes; i++) {
            int in = s.nextInt();
            input_net.insert(in);
        }

        int alpha = s.nextInt();
        LazySplayNet lazy_net = new LazySplayNet(input_net, alpha);

        int tot_comm_req = s.nextInt();
        for (int i = 0; i < tot_comm_req; i++) {
            int u = s.nextInt();
            int v = s.nextInt();

            lazy_net.request(u, v);
            System.out.println(lazy_net.total_routing_cost);
        }
    }
}
