cd ../src/
gcc *.c -o main -Wall
cd ../scripts/
cd julia/
julia --color=yes ASI.jl -sh
julia --color=yes BinTree.jl -sh
julia --color=yes BTree.jl -sh
julia --color=yes BStarTree.jl -sh
cd ../../src