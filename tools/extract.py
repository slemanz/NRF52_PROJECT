import numpy as np
import matplotlib.pyplot as plt
from serial_app import serialApp

ser = serialApp()

matriz_dados = [
        [1, 2, 3, 4],        
        [5, 6, 7, 8, 9, 10], 
        [11, 12, 13]         
    ]

def show_conjuntos(matriz):
    """
    Mostra quantos conjuntos de dados existem e suas características
    """
    print(f"\nExistem {len(matriz)} conjuntos de dados disponíveis:")
    for i, conjunto in enumerate(matriz):
        minutos = (len(conjunto) - 1)*10
        print(f"{i+1}: {minutos/60:.2f} horas")

def plot_conjunto(matriz, indice):
    """
    Plota o conjunto de dados selecionado com marcação temporal
    """
    conjunto = matriz[indice]
    
    # Criar array de tempo (intervalos de 10 minutos)
    tempo = np.arange(len(conjunto)) * 10
    
    plt.figure(figsize=(10, 6))
    plt.plot(tempo, conjunto, 'bo-', linewidth=2, markersize=8)
    plt.grid(True)
    plt.title(f'Conjunto de Dados {indice+1}')
    plt.xlabel('Tempo (minutos)')
    plt.ylabel('Temperatura')
    plt.xticks(tempo)
    plt.ylim(0,30)
    plt.show()

def main():
    #ser.update_port()
    ser.serial_port.port = '/dev/ttyUSB0'
    ser.serial_port.baudrate = 115200
    ser.connect_serial()
    exit()
    show_conjuntos(matriz_dados)
    
    # User choice
    while True:
        try:
            escolha = int(input("\nEscolha um conjunto para visualizar (0 para sair): "))
            if escolha == 0:
                break
            elif 1 <= escolha <= len(matriz_dados):
                plot_conjunto(matriz_dados, escolha-1)
            else:
                print("Escolha inválida!")
        except ValueError:
            print("Por favor, digite um número válido!")

if __name__ == "__main__":
    main()