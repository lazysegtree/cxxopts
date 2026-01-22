import argparse

parser = argparse.ArgumentParser('test program')
parser.add_argument('-a', required=False)
parser.add_argument('-2', required=False)
parser.add_argument('numbers', nargs='*')

args = parser.parse_args()
print(args)