cd ../src/
gcc *.c -o main.exe -Wall
cd ../scripts/
cd julia/
julia --color=yes ASI.jl -bat
julia --color=yes BinTree.jl -bat
julia --color=yes BTree.jl -bat
julia --color=yes BStarTree.jl -bat
cd ../../src/