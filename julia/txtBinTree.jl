function criaArquivoBinTree()

    dir = pwd()
    arqDest = open("BinTree.txt", "w")
    dir_stats = "../estatisticas/BinTree"
    qntd = [100, 1000, 10000, 100000, 1000000]
    ord  = [1, 2, 3]

    mediaFwriteC = 0
    mediaFwriteP = 0
    mediaFreadC  = 0
    mediaFreadP  = 0
    mediaFseekC  = 0
    mediaFseekP  = 0
    mediaCompC   = 0
    mediaCompP   = 0
    mediaTempoC  = 0
    mediaTempoP  = 0

    for i in qntd
        
        for j in ord

            fwriteC    = []
            fwriteP    = []
            freadC     = []
            freadP     = []
            fseekC     = []
            fseekP     = []
            compC      = []
            compP      = []
            tempoC     = []
            tempoP     = []
            acessos    = []
            tempoTotal = []
            compTotal  = []

            for k = 1:10

                aux = 0
                sum_time = 0
                sum_comp = 0
                open("$(dir_stats)/binTree_$(i)_$(j)_key$(k).txt") do f  
                    
                    # read till end of file 
                    while ! eof(f)   
                    
                        # read a new / next line for every iteration            
                        s = readline(f)
                        s = split(s, " ")

                        if (s[1] == "FwriteC")
                            push!(fwriteC, s[2])
                            mediaFwriteC += parse(Int, s[2])
                            aux += parse(Int, s[2])
                        elseif (s[1] == "FwriteP")
                            push!(fwriteP, s[2])
                            mediaFwriteP += parse(Int, s[2])
                            aux += parse(Int, s[2])
                        elseif (s[1] == "FreadC")
                            push!(freadC, s[2])
                            mediaFreadC += parse(Int, s[2])
                            aux += parse(Int, s[2])
                        elseif (s[1] == "FreadP")
                            push!(freadP, s[2])
                            mediaFreadP += parse(Int, s[2])
                            aux += parse(Int, s[2])
                        elseif (s[1] == "FseekC")
                            push!(fseekC, s[2])
                            mediaFseekC += parse(Int, s[2])
                            aux += parse(Int, s[2])
                        elseif (s[1] == "FseekP")
                            push!(fseekP, s[2])
                            mediaFseekP += parse(Int, s[2])
                            aux += parse(Int, s[2])
                        elseif (s[1] == "ComparacoesC")
                            push!(compC, s[2])
                            mediaCompC += parse(Int, s[2])
                            sum_comp += parse(Int, s[2])
                        elseif (s[1] == "ComparacoesP")
                            push!(compP, s[2])
                            mediaCompP += parse(Int, s[2])
                            sum_comp += parse(Int, s[2])
                        elseif (s[1] == "TempoC")
                            push!(tempoC, s[2])
                            mediaTempoC += parse(Float64, s[2])
                            sum_time += parse(Float64, s[2])
                        elseif (s[1] == "TempoP")
                            push!(tempoP, s[2])
                            mediaTempoP += parse(Float64, s[2])
                            sum_time += parse(Float64, s[2])
                        else
                        end
                    end 
                end
                push!(compTotal, sum_comp)
                push!(tempoTotal, sum_time)
                push!(acessos, aux)
            end

            write(arqDest, "fwriteC_$(i)_$(j) = [")
            for k = 1:length(fwriteC)
                if (k == length(fwriteC))
                    write(arqDest, "$(fwriteC[k])")
                else
                    write(arqDest, "$(fwriteC[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "fwriteP_$(i)_$(j) = [")
            for k = 1:length(fwriteP)
                if (k == length(fwriteP))
                    write(arqDest, "$(fwriteP[k])")
                else
                    write(arqDest, "$(fwriteP[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "freadC_$(i)_$(j) = [")
            for k = 1:length(freadC)
                if (k == length(freadC))
                    write(arqDest, "$(freadC[k])")
                else
                    write(arqDest, "$(freadC[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "freadP_$(i)_$(j) = [")
            for k = 1:length(freadP)
                if (k == length(freadP))
                    write(arqDest, "$(freadP[k])")
                else
                    write(arqDest, "$(freadP[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "fseekC_$(i)_$(j) = [")
            for k = 1:length(fseekC)
                if (k == length(fseekC))
                    write(arqDest, "$(fseekC[k])")
                else
                    write(arqDest, "$(fseekC[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "fseekP_$(i)_$(j) = [")
            for k = 1:length(fseekP)
                if (k == length(fseekP))
                    write(arqDest, "$(fseekP[k])")
                else
                    write(arqDest, "$(fseekP[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "compC_$(i)_$(j) = [")
            for k = 1:length(compC)
                if (k == length(compC))
                    write(arqDest, "$(compC[k])")
                else
                    write(arqDest, "$(compC[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "compP_$(i)_$(j) = [")
            for k = 1:length(compP)
                if (k == length(compP))
                    write(arqDest, "$(compP[k])")
                else
                    write(arqDest, "$(compP[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "tempoC_$(i)_$(j) = [")
            for k = 1:length(tempoC)
                if (k == length(tempoC))
                    write(arqDest, "$(tempoC[k])")
                else
                    write(arqDest, "$(tempoC[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "tempoP_$(i)_$(j) = [")
            for k = 1:length(tempoP)
                if (k == length(tempoP))
                    write(arqDest, "$(tempoP[k])")
                else
                    write(arqDest, "$(tempoP[k]), ")
                end
            end
            write(arqDest, "]\n")
            
            write(arqDest, "acessos_$(i)_$(j) = [")
            for k = 1:length(acessos)
                if (k == length(acessos))
                    write(arqDest, "$(acessos[k])")
                else
                    write(arqDest, "$(acessos[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "tempoTotal_$(i)_$(j) = [")
            for k = 1:length(tempoTotal)
                if (k == length(tempoTotal))
                    write(arqDest, "$(tempoTotal[k])")
                else
                    write(arqDest, "$(tempoTotal[k]), ")
                end
            end
            write(arqDest, "]\n")

            write(arqDest, "compTotal$(i)_$(j) = [")
            for k = 1:length(compTotal)
                if (k == length(compTotal))
                    write(arqDest, "$(compTotal[k])")
                else
                    write(arqDest, "$(compTotal[k]), ")
                end
            end
            write(arqDest, "]\n\n")

        end
    end

    
    mediaFwriteC /= 150
    mediaFwriteP /= 150
    mediaFreadC  /= 150
    mediaFreadP  /= 150
    mediaFseekC  /= 150
    mediaFseekP  /= 150
    mediaCompC   /= 150
    mediaCompP   /= 150
    mediaTempoC  /= 150
    mediaTempoP  /= 150

    write(arqDest, "----------------------------------------------------------\n\n")
    write(arqDest, "AcessosC    : $(mediaFreadC + mediaFseekC + mediaFwriteC)\n")
    write(arqDest, "AcessosP    : $(mediaFreadP + mediaFseekP + mediaFwriteP)\n")
    write(arqDest, "Acessos     : $(mediaFreadC + mediaFseekC + mediaFwriteC + mediaFreadP + mediaFseekP + mediaFwriteP)\n")
    write(arqDest, "ComparacoesC: $(mediaCompC)\n")
    write(arqDest, "ComparacoesP: $(mediaCompP)\n")
    write(arqDest, "Comparacoes : $(mediaCompP + mediaCompC)\n")
    write(arqDest, "TempoC      : $(mediaTempoC)\n")
    write(arqDest, "TempoP      : $(mediaTempoP)\n")
    write(arqDest, "Tempo       : $(mediaTempoP + mediaTempoC)\n")

    close(arqDest)

end

criaArquivoBinTree()