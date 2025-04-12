from serial_app import serialApp
from coletas import *

ser = serialApp()

matriz_dados = [[]]


def main():
    #ser.update_port()
    ser.serial_port.port = '/dev/ttyUSB0'
    ser.serial_port.baudrate = 115200
    ser.connect_serial()

    matriz_dados = ser.get_coletas()

    coletas_show(matriz_dados)
    
    # User choice
    while True:
        try:
            escolha = int(input("\nEscolha um conjunto para visualizar (0 para sair): "))
            if escolha == 0:
                ser.close_serial()
                break
            elif 1 <= escolha <= len(matriz_dados):
                coletas_plot(matriz_dados, escolha-1)
            else:
                print("Escolha inválida!")
        except ValueError:
            print("Por favor, digite um número válido!")

if __name__ == "__main__":
    main()