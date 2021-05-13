function BinTree(ARGS)

    dir_inicio = pwd()
    dir_src = mkpath("../../src")
    cd(dir_src)
    
    qntd = [100, 1000, 10000, 100000, 1000000]

    printstyled("ÁRVORE B\n", color = :yellow)
    for i in qntd
        
        vetRand = []
        for j = 1:10
            
            randNum = rand(1:i)
            while (randNum in vetRand)
                randNum = rand(1:i)
            end
            push!(vetRand, randNum)
            
            printstyled("| QNTD: $(i) KEY: $(randNum)\n", color = :green)
            
            if (ARGS[1] == "-sh") 
                run(`./main 3 $i 1 $randNum key$j`)
                run(`./main 3 $i 2 $randNum key$j`)
                run(`./main 3 $i 3 $randNum key$j`)
            elseif (ARGS[1] == "-bat")
                run(`main.exe 3 $i 1 $randNum key$j`)
                run(`main.exe 3 $i 2 $randNum key$j`)
                run(`main.exe 3 $i 3 $randNum key$j`)
            else
                printstyled("Parâmetro errado!\n", color = :red)
                printstyled("Esperado: '-sh' ou '-bat'\n", color = :red)
                printstyled("Recebido: $(ARGS[1])\n", color = :red)
                return
            end
            
        end
        
    end
    
    cd("../scripts/julia")
end

BinTree(ARGS)