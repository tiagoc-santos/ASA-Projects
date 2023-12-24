from pulp import *

info_inicial = input().split(" ")
num_brinquedos = int(info_inicial[0])
num_pacotes = int(info_inicial[1])
maximo = int(info_inicial[2])

lucro_brinquedos = {}
lucro_pacotes = {}
capacidade_max = {}
pacotes = []
pacotes_brinquedos = {}

for i in range(1,  num_brinquedos + 1):
    lucro, capacidade = map(int, input().split(" "))
    lucro_brinquedos[i] = lucro
    capacidade_max[i] = capacidade

for l in range(1, num_pacotes+1):
    i, j ,k, lucro_pacote = map(int, input().split(" "))
    lucro_pacotes[l] = lucro_pacote
    if i in pacotes_brinquedos:
        pacotes_brinquedos[i].append(l)
    else:
        pacotes_brinquedos[i] = [l]
    
    if j in pacotes_brinquedos:
        pacotes_brinquedos[j].append(l)
    else:
        pacotes_brinquedos[j] = [l]

    if k in pacotes_brinquedos:
        pacotes_brinquedos[k].append(l)
    else:
        pacotes_brinquedos[k] = [l]

prob = LpProblem("Projeto3", LpMaximize)

vars_brinquedo = LpVariable.dicts("Brinquedos", range(1, num_brinquedos+1), 0, None, LpInteger)

vars_pacotes = LpVariable.dicts("Pacotes", range(1, num_pacotes+1), 0, None, LpInteger)

# objective function
prob += (
    lpSum(vars_brinquedo[i] * lucro_brinquedos[i] for i in range(1, num_brinquedos + 1)) + 
    lpSum(vars_pacotes[j] * lucro_pacotes[j] for j in range(1, num_pacotes + 1))
)

# constraints
prob += (
    (lpSum(vars_brinquedo[i] for i in range(1, num_brinquedos + 1)) + 
        lpSum(3 * vars_pacotes[j] for j in range(1, num_pacotes+1))) <= maximo
)

for i in range(1, num_brinquedos+1):
    prob += (
        lpSum(vars_brinquedo[i] + vars_pacotes[j] for j in pacotes_brinquedos[i]) <= capacidade_max[i]
    )
    
prob.solve()

print(value(prob.objective))
