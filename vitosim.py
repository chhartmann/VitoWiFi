import serial
ser = serial.Serial("/dev/ttyUSB0", baudrate=4800, parity=serial.PARITY_EVEN, stopbits=serial.STOPBITS_TWO)

ret_vals = {}

# ret_vals["7507"] = bytes([0x20, 20, 22, 12, 28, 0, 9, 40, 10]) # error code, year, year, month, day, day of week, hour, minute, second
# ret_vals["0800"] = int(25*10).to_bytes(2, 'little')
# ret_vals["088A"] = int(100).to_bytes(4, 'little')
# ret_vals["08A2"] = int(1).to_bytes(1, 'little')
# ret_vals["088E"] = bytes([20, 22, 12, 28, 0, 9, 40, 10])
# ret_vals["2000"] = bytes.fromhex("2BB0FFFFFFFFFFFF")

#TODO neg. außentemperatur testen
ret_vals["0800"] = bytes.fromhex("3300") # Aussentemperatur 5.1 
ret_vals["0812"] = bytes.fromhex("B901") # Wassertemperatur 44.1
ret_vals["088A"] = bytes.fromhex("043A0300") # Brennerstarts 211460 
ret_vals["08A7"] = bytes.fromhex("4B2A3B05") # LaufzeitBrenner 24378.76
ret_vals["08A2"] = bytes.fromhex("00") # StatusStoerung kein Fehler
ret_vals["7507"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["088E"] = bytes.fromhex("2023010403071537") # Systemzeit  Mi 04.01.2023 07:15:37
ret_vals["2000"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerMoHeizen 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--

#TODO store written values to be read back
received_vals = {}

def b2s(b):
  return ''.join(format(x, '02X') for x in b)

while (True):
  x = ser.read()
  print("received " + x.hex())
  if (x == b'\x04'):
    print("reset")
    ser.write(b'\x05')
  elif (x == b'\x16'):
    print("init")
    ser.read(2)
    ser.write(b'\x06')
  elif (x == b'\x41'):
    ser.read(2)      # length of user data, request/response
    c = ser.read(1)  # 01 read, 02 write
    a = ser.read(2)  # address
    l = ser.read(1)  # number of bytes expected in the response
    ser.read(1)      # crc
    print("cmd " + c.hex())
    print("addr " + a.hex())
    print("len " + l.hex())
    ser.write(b'\x06')
    if (c == b'\x01'): # read
      ret_val = ret_vals[b2s(a)]
      print("ret val " + b2s(ret_val))
      resp = bytes([0x41, len(ret_val) + 5, 0x01])
      resp += bytes([0, 0, 0, 0]) # is idnored by VitoFiFi
      resp += ret_val
      resp += bytes([sum(resp[1:]) & 0xFF])
      print("response " + b2s(resp))
      ser.write(resp)
    else: # write
      ser.read(ser.in_wating)
      ser.write(b'x06')
