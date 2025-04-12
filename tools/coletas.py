import numpy as np
import matplotlib.pyplot as plt

def coletas_show(matriz):
    """
    Mostra quantos coletas de dados existem e suas características
    """
    print(f"\nExistem {len(matriz)} coletas de dados disponíveis:")
    for i, conjunto in enumerate(matriz):
        minutos = (len(conjunto) - 1)*10
        print(f"{i+1}: {minutos/60:.2f} horas")

def coletas_plot(matriz, indice):
    """
    Plota a coleta de dados selecionado com marcação temporal
    """
    conjunto = matriz[indice]
    
    # Criar array de tempo (intervalos de 10 minutos)
    tempo = np.arange(len(conjunto)) * (10/60)
    
    plt.figure(figsize=(10, 6))
    plt.plot(tempo, conjunto, 'b', linewidth=2)
    plt.grid(True)
    plt.title(f'Coleta de Dados {indice+1}')
    plt.xlabel('Tempo (horas)')
    plt.ylabel('Temperatura (°C)')
    plt.ylim(0,40)
    plt.xlim(0, tempo[-1])
    plt.show()