from pulp import *

num_brinquedos, num_pacotes, maximo = map(int, input().split())

brinquedos = {}
pacotes = {}
lucro_brinquedos = {}
lucro_pacotes = {}
capacidade_max = {}
pacotes_brinquedos = {}

for i in range(1,  num_brinquedos + 1):
    lucro, capacidade = map(int, input().split(" "))
    if(lucro == 0 or capacidade == 0):
        continue
    i = str(i)
    brinquedos[i] = 0
    lucro_brinquedos[i] = lucro
    capacidade_max[i] = capacidade
    pacotes_brinquedos[i] = []

for l in range(1, num_pacotes+1):
    i, j ,k, lucro_pacote = map(int, input().split(" "))
    if(i > num_brinquedos or j > num_brinquedos or k > num_brinquedos or lucro_pacote == 0):
        continue
    l = str(l)
    i = str(i)
    j = str(j)
    k = str(k)
    if(lucro_pacote <= (lucro_brinquedos[i] + lucro_brinquedos[j] + lucro_brinquedos[k])):
        continue
    pacotes[l] = 0
    lucro_pacotes[l] = lucro_pacote
    pacotes_brinquedos[i].append(l)
    pacotes_brinquedos[j].append(l)
    pacotes_brinquedos[k].append(l)

prob = LpProblem("Projeto3", LpMaximize)

vars_brinquedo = LpVariable.dicts("Brinquedos", brinquedos, 0, None, LpInteger)

vars_pacotes = LpVariable.dicts("Pacotes", pacotes, 0, None, LpInteger)

# objective function
prob += (
    lpSum([vars_brinquedo[i] * lucro_brinquedos[i] for i in brinquedos.keys()]) 
        + lpSum([vars_pacotes[j] * lucro_pacotes[j] for j in pacotes.keys()])
)

# constraints
for i in brinquedos:
    prob += (
       (lpSum([vars_pacotes[j] for j in pacotes_brinquedos[i]]) + vars_brinquedo[i]) <= capacidade_max[i], "Toy maximum capacity" + i
    )
    
prob += (
    (lpSum([vars_brinquedo[i] for i in brinquedos.keys()]) + 3 * lpSum([vars_pacotes[j] for j in pacotes.keys()])) <= maximo, "Total toys constraints"
)

prob.solve(PULP_CBC_CMD(msg = False, timeLimit = 0.05))

print(int(pulp.value(prob.objective)))
