g++ ../ei/heuristic.cpp -o heuristic -std=c++14
g++ chk.cpp -o chk -std=c++14

for ((i = 1; i <= 7; ++i))
do
    time ./heuristic < $i.in > $i.out
    ./chk $i.in $i.out $i.out
done
