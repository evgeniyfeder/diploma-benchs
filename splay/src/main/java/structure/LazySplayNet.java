package structure;

import java.util.Scanner;

public class LazySplayNet {
    public SplayNet lazySplayNet;          // original BST
    private final int alpha;                // synchronization cost
    public final SplayNet splayNet;

    public LazySplayNet(SplayNet splayNet, int alpha) {
        this.alpha = alpha;
        this.splayNet = splayNet;
        this.lazySplayNet = splayNet.copy();
    }

    /* Statistics */
    public int adjustment_cost = 0;              // stores cost taken for adjusting
    public int total_routing_cost = 0;           // stores cost taken to route all pairs of queries given in input
    public int epoch_routing_cost = 0;           // cost inside one epoch

    public void request(int u, int v) {
        // calculates cost to travel from u to v in LazyNet
        int cost = lazySplayNet.cost(u, v);

        // makes changes in the splayNet
        splayNet.commute(u, v);

        // changes statistics
        total_routing_cost = total_routing_cost + cost;
        epoch_routing_cost = epoch_routing_cost + cost;

        // if epoch_cost exceeds 'a' changed tree is used for next query
        if (epoch_routing_cost >= alpha)
        {
            adjustment_cost += alpha;
            epoch_routing_cost = 0;
            lazySplayNet = splayNet.copy();
        }
    }
}