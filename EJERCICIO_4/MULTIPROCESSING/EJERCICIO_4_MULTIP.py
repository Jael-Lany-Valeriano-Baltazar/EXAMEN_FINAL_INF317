import multiprocessing
from decimal import Decimal, getcontext

def calcular_termino(i):
    getcontext().prec += 100
    termino = (Decimal(1)/(16**i)) * ((Decimal(4)/(8*i+1)) - (Decimal(2)/(8*i+4)) - (Decimal(1)/(8*i+5)) - (Decimal(1)/(8*i+6)))
    return termino

def calcular_pi(num_terminos):
    getcontext().prec = num_terminos + 10
    num_procesos = multiprocessing.cpu_count()
    pool = multiprocessing.Pool(processes=num_procesos)
    resultados = pool.map(calcular_termino, range(num_terminos))
    pi = sum(resultados)
    return pi

if __name__ == '__main__':
    num_terminos = 1000
    pi = calcular_pi(num_terminos)
    print(f"Pi: {pi}")