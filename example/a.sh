set -e
g++ a.cpp -o a.out

echo "Help output ---------"
./a.out -h | bat --show-all


echo "Giving -b"
./a.out -b