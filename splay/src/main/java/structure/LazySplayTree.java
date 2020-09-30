package structure;

import java.util.Scanner;

public class LazySplayTree {
    private SplayTree lazySplayTree;
    private final int alpha;
    private final SplayTree splayTree;

    public LazySplayTree(SplayTree splayTree, int alpha) {
        this.alpha = alpha;
        this.splayTree = splayTree;
        this.lazySplayTree = splayTree.copy();
    }

    public int total_routing_cost = 0;
    public int epoch_routing_cost = 0;
    public int adjustment_cost = 0;

    public void search(int u) {
        int cost = lazySplayTree.search_cost(u);

        splayTree.root = splayTree.splay(splayTree.root, u);

        total_routing_cost = total_routing_cost + cost;
        epoch_routing_cost = epoch_routing_cost + cost;

        if (epoch_routing_cost >= alpha) {
            adjustment_cost += alpha;
            epoch_routing_cost = 0;

            lazySplayTree = splayTree.copy();
        }
    }
}