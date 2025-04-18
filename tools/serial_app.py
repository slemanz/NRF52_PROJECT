import serial
import serial.tools.list_ports

def byte_to_hex(byte_str):       
        return ''.join( [ "%02X" % ord( x ) for x in byte_str ] ).strip()

def HexToByte(hexStr):
    bytes = []
    hexStr = ''.join( hexStr.split(" ") )

    for i in range(0, len(hexStr), 2):
        bytes.append( chr( int (hexStr[i:i+2], 16 ) ) )
    return ''.join( bytes )

class serialApp ():
    def __init__(self):
        self.serial_port = serial.Serial()
        self.baudrate = [9600,115200]
        self.portlist = []
        self.serial_port.timeout = 1

    def update_port(self): #updates de portas seriais
        self.portlist =[port.device for port in serial.tools.list_ports.comports()]
        print (self.portlist)

    def connect_serial(self):
        try:
            self.serial_port.open()
            print("CONECTADO",self.serial_port.port)
            return True
        except:
            print("Houve um erro")
            return False

    def close_serial(self):
        self.serial_port.close()
        print("DESCONECTADO", self.serial_port.port)
    
    def read_serial(self):
            data = self.serial_port.readline()
            return data

    def send_serial (self,data):
        if(self.serial_port.isOpen()):
            message = str(data) + "\r\n"
            self.serial_port.write(message.encode())
            
    def clear_serial(self):
        self.serial_port.reset_input_buffer()
        self.serial_port.reset_output_buffer()

    def get_count(self):
        self.clear_serial()
        self.send_serial("count")
        message = self.read_serial()
        message = self.read_serial()

        count = int(((message.decode()).replace("Count: ", "")).replace("\n", ""))
        return count

    def get_coletas(self):
        self.send_serial("storage extract")

        values = [[]]

        message = self.read_serial()
        message = self.read_serial()
        message = self.read_serial()
        message = self.read_serial()
        idx = 0
        while(message != b''):
            if(b'=' in message):
                idx += 1
                values.append([])
            else:
                value = float((message.decode()).replace(" C\n", ""))
                values[idx].append(value)

            message = self.read_serial()

        return values