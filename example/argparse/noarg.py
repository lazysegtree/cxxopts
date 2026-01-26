import argparse

parser = argparse.ArgumentParser('test program')
parser.add_argument('-v', action='store_true')
parser.add_argument('-x')

args = parser.parse_args()
print(args)