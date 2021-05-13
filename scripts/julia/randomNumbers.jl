function randomNumbers()

    vet_aux = [100, 1000, 10000, 100000, 1000000]

    for i in vet_aux

        vetAux2 = []
        for j = 1:i
            push!(vetAux2, j)
        end

        vetRegistros = []
        count = 0
        while (length(vetAux2) > 0)
            x = rand(1:length(vetAux2))
            push!(vetRegistros, vetAux2[x])
            deleteat!(vetAux2, x)
        end

        io = open("../../input/$(i).txt", "w")
        for j = 1:length(vetRegistros)
            write(io, "$(vetRegistros[j])\n")
        end
        close(io)

    end

end

randomNumbers()