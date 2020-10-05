import argparse
import pandas
import subprocess
import random
import plotly.express as px
import logging
import pathlib


def get_executable(module):
    return ["/home/evgeniyfeder/jdk/jdk-11.0.8+10/bin/java",
            "-classpath",
            "/home/evgeniyfeder/work-itmo/diplom/diploma-benchs/splay/target/classes",
            module]


def get_queries(reqs: pandas.DataFrame):
    output = ""
    if reqs.columns.size == 3:
        output += f"{reqs.shape[0]}\n"

        for index, row in reqs.iterrows():
            output += f"{row['src']} {row['dst']}\n"
            ex_class = "NetMain"
    else:
        raise NotImplementedError()
    return output, ex_class


def count_cost_of_size_plot(start_tree, req_path, args):
    # input tree
    input = f"{len(start_tree)}\n"

    reqs = pandas.read_csv(req_path)

    for elem in start_tree:
        input = input + f"{elem} "
    input += "\n"

    result = pandas.DataFrame(columns=["x", "y", "color"])
    for alpha in args.alphas:
        alpha_input = input
        alpha_input += f"{alpha}\n"

        qs, ex = get_queries(reqs)
        alpha_input += qs

        java_output = subprocess.check_output(get_executable(ex), universal_newlines=True, input=alpha_input).strip(
            "\n ")

        result = result.append({"y": int(java_output.split("\n")[-1]), "x": reqs.shape[0],
                                "color": alpha}, ignore_index=True)


def count_avg_cost_of_length_plot(start_tree, req_path, args):
    # input tree
    input = f"{len(start_tree)}\n"

    reqs = pandas.read_csv(req_path)

    for elem in start_tree:
        input = input + f"{elem} "
    input += "\n"

    input += f"{args.alpha}\n"

    qs, ex = get_queries(reqs)
    input += qs

    java_output = subprocess.check_output(get_executable(ex), universal_newlines=True, input=alpha_input).strip("\n ")

    result = pandas.DataFrame(columns=["x", "y", "color"])
    for iter, step_cost in enumerate(java_output.split("\n"), start=1):
        result = result.append({"y": int(step_cost) / iter, "x": iter,
                                "color": pathlib.Path(req_path).name}, ignore_index=True)
    return result


def count_cost_of_a_plot(start_tree, req_path, args):
    # input tree
    input = f"{len(start_tree)}\n"

    reqs = pandas.read_csv(req_path)

    for elem in start_tree:
        input = input + f"{elem} "
    input += "\n"

    result = pandas.DataFrame(columns=["x", "y", "color"])
    for alpha in range(args.start, args.end + args.step, args.step):
        alpha_input = input
        alpha_input += f"{alpha}\n"

        qs, ex = get_queries(reqs)
        alpha_input += qs

        java_output = subprocess.check_output(get_executable(ex), universal_newlines=True, input=alpha_input).strip(
            "\n ")

        result = result.append({"y": int(java_output.split("\n")[-1]), "x": alpha,
                                "color": pathlib.Path(req_path).name}, ignore_index=True)

    return result


def print_plots(args):
    res_df = pandas.DataFrame()

    n = int(args.nodes_cnt)
    start_tree = [i for i in range(n)]
    random.shuffle(start_tree)

    for req_path in args.requests:
        plot = args.func(start_tree, req_path, args)
        res_df = res_df.append(plot, ignore_index=True)
    print(res_df)
    fig = px.line(res_df, x="x", y="y", color="color")
    fig.show()


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("--requests", "-r", required=True, nargs="+", help="Path to csv file with requests")
    parser.add_argument("--nodes-cnt", "-n", required=True, help="Number of nodes in tree")
    parser.add_argument("--plot", "-p", required=True, help="Path to output plot")

    subparsers = parser.add_subparsers()

    cost_of_a = subparsers.add_parser("cost_of_a")
    cost_of_a.set_defaults(func=count_cost_of_a_plot)
    cost_of_a.add_argument("--start", required=True, type=int, help="Start value of alpha")
    cost_of_a.add_argument("--step", required=True, type=int, help="Step of alpha")
    cost_of_a.add_argument("--end", required=True, type=int, help="End of alpha")

    avg_cost_of_length = subparsers.add_parser("avg_cost_of_length")
    avg_cost_of_length.set_defaults(func=count_avg_cost_of_length_plot)
    avg_cost_of_length.add_argument("--alpha", required=True, type=int)

    cost_of_size = subparsers.add_parser("cost_of_size")
    cost_of_size.set_defaults(func=count_cost_of_size_plot)
    cost_of_size.add_argument("--alphas", "-a", required=True, nargs="+", help="Alphas ")
    args = parser.parse_args()

    print_plots(args)


if __name__ == '__main__':
    main()
