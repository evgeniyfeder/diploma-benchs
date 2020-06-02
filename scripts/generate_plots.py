import argparse
import pandas
import matplotlib.pyplot as plt


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("-i", "--input", help="path to input csv file")
    parser.add_argument("-o", "--output", help="path to output plot 'png' picture")

    args = parser.parse_args()

    plt.title('Ratio of algorithm cost to static optimal cost depends of alpha')
    plt.xlabel('alpha')
    plt.ylabel('ratio of ALG to OPT')
    plt.grid(True)

    ax = plt.gca()

    df = pandas.read_csv(args.input, header=0, names=["alpha", "standard", "lazy"])
    df.plot(kind='line', x='alpha', y='standard', color='red', ax=ax)
    df.plot(kind='line', x='alpha', y='lazy', color='blue', ax=ax)
    plt.savefig(args.output)


if __name__ == '__main__':
    main()
