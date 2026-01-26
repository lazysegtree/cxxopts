import argparse

parser = argparse.ArgumentParser('test program')
parser.add_argument('-?', required=False, action="store_true")

args = parser.parse_args()
print(args)