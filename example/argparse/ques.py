import argparse

parser = argparse.ArgumentParser('test program')
parser.add_argument('-?', required=False, action="store_true")
parser.add_argument('--?dsfsd', required=False, action="store_true")
parser.add_argument('--ds?fsd', required=False, action="store_true")
parser.add_argument('-df??', required=False, action="store_true")
parser.add_argument('--???_', required=False, action="store_true")

args = parser.parse_args()
print(args)