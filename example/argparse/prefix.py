import argparse

parser = argparse.ArgumentParser(prefix_chars='+')
parser.add_argument('+UVM_TESTNAME')
parser.add_argument('+UVM_TIMEOUT')

args = parser.parse_args()
print(args)