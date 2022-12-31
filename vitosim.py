import serial
ser = serial.Serial("/dev/ttyUSB0", baudrate=4800, parity=serial.PARITY_EVEN, stopbits=serial.STOPBITS_TWO)

ret_vals = {}
ret_vals["7507"] = bytes([0x20, 20, 22, 12, 28, 0, 9, 40, 10]) # error code, year, year, month, day, day of week, hour, minute, second
ret_vals["0800"] = int(25*10).to_bytes(2, 'little')
ret_vals["088A"] = int(100).to_bytes(4, 'little')
ret_vals["08A2"] = int(1).to_bytes(1, 'little')

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
      ser.write(resp)
    else: # write
      ser.read(ser.in_wating)
      ser.write(b'x06')
