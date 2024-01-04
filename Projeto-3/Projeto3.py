from pulp import *

info_inicial = input().split(" ")
num_brinquedos = int(info_inicial[0])
num_pacotes = int(info_inicial[1])
maximo = int(info_inicial[2])

brinquedos = []
pacotes = []
lucro_brinquedos = {}
lucro_pacotes = {}
capacidade_max = {}
pacotes_brinquedos = {}

for i in range(1,  num_brinquedos + 1):
    lucro, capacidade = map(int, input().split(" "))
    i = str(i)
    brinquedos.append(i)
    lucro_brinquedos[i] = lucro
    capacidade_max[i] = capacidade
    pacotes_brinquedos[i] = []

for l in range(1, num_pacotes+1):
    i, j ,k, lucro_pacote = map(int, input().split(" "))
    l = str(l)
    i = str(i)
    j = str(j)
    k = str(k)
    pacotes.append(l)
    lucro_pacotes[l] = lucro_pacote
    pacotes_brinquedos[i].append(l)
    pacotes_brinquedos[j].append(l)
    pacotes_brinquedos[k].append(l)

prob = LpProblem("Projeto3", LpMaximize)

vars_brinquedo = LpVariable.dicts("Brinquedos", brinquedos, 0, None, LpInteger)

vars_pacotes = LpVariable.dicts("Pacotes", pacotes, 0, None, LpInteger)

# objective function
prob += (
    lpSum([vars_brinquedo[i] * lucro_brinquedos[i] for i in brinquedos]) 
        + lpSum([vars_pacotes[j] * lucro_pacotes[j] for j in pacotes])
)

# constraints
prob += (
    (lpSum([vars_brinquedo[i] for i in brinquedos]) + lpSum(3*[vars_pacotes[j] for j in pacotes])) <= maximo, "Total toys constraints"
)

for i in brinquedos:
    prob += (
       (lpSum([vars_pacotes[j] for j in pacotes_brinquedos[i]]) + vars_brinquedo[i]) <= capacidade_max[i], "Toy maximum capacity" + i
    )
    
prob.solve(GLPK(msg=0))

print(int(pulp.value(prob.objective)))
