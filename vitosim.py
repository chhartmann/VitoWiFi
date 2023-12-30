import serial
ser = serial.Serial("/dev/ttyUSB0", baudrate=4800, parity=serial.PARITY_EVEN, stopbits=serial.STOPBITS_TWO)

# protocol is described here: https://gist.github.com/artekw/1edd5efd02afb8b061a9c4089d9d2bc3

ret_vals = {}

# ret_vals["7507"] = bytes([0x20, 20, 22, 12, 28, 0, 9, 40, 10]) # error code, year, year, month, day, day of week, hour, minute, second
# ret_vals["0800"] = int(25*10).to_bytes(2, 'little')
# ret_vals["088A"] = int(100).to_bytes(4, 'little')
# ret_vals["08A2"] = int(1).to_bytes(1, 'little')
# ret_vals["088E"] = bytes([20, 22, 12, 28, 0, 9, 40, 10])
# ret_vals["2000"] = bytes.fromhex("2BB0FFFFFFFFFFFF")

ret_vals["0800"] = bytes.fromhex("CDFF") # Aussentemperatur -5.1 
ret_vals["0812"] = bytes.fromhex("B901") # Wassertemperatur 44.1
ret_vals["2544"] = bytes.fromhex("CDFF") # Soll Vorlauftemperatur
ret_vals["0808"] = bytes.fromhex("B901") # Ist Ruecklauftempteratur
ret_vals["555A"] = bytes.fromhex("B901") # Soll Kesseltempteratur

ret_vals["088A"] = bytes.fromhex("043A0300") # Brennerstarts 211460 
ret_vals["08A7"] = bytes.fromhex("4B2A3B05") # LaufzeitBrenner 24378.76

ret_vals["0A82"] = bytes.fromhex("00") # StatusStoerung kein Fehler
ret_vals["088E"] = bytes.fromhex("2023010403071537") # Systemzeit  Mi 04.01.2023 07:15:37

ret_vals["7507"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["7510"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["7519"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["7522"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["752B"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["7534"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["753D"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["7546"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["754F"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden
ret_vals["7558"] = bytes.fromhex("F42022091901130504") # Stoerung-History1 Mo 19.09.2022 13:05:04 Flammensigal nicht vorhanden

ret_vals["2000"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerMoHeizen 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2008"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerDiHeizen 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2010"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerMiHeizen 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2018"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerDoHeizen 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2020"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerFrHeizen 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2028"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerSaHeizen 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2030"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerSoHeizen 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--

ret_vals["2100"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerMoWarmwasser 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2108"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerDiWarmwasser 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2110"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerMiWarmwasser 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2118"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerDoWarmwasser 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2120"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerFrWarmwasser 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2128"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerSaWarmwasser 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--
ret_vals["2130"] = bytes.fromhex("2BB0FFFFFFFFFFFF") # TimerSoWarmwasser 05:30 22:00 --:-- --:-- --:-- --:-- --:-- --:--

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
  elif (x == b'\x06'):
    print("ack")
  elif (x == b'\x41'):
    ser.read(2)      # length of user data, request/response
    c = ser.read(1)  # 01 read, 02 write
    a = ser.read(2)  # address
    l = ser.read(1)  # number of bytes expected in the response
    print("cmd " + c.hex())
    print("addr " + a.hex())
    print("len " + l.hex())
    ser.write(b'\x06')
    if (c == b'\x01'): # read
      ser.read(1) # ignore crc
      if (b2s(a)) in received_vals:
        ret_val = received_vals[b2s(a)]
        print("returning received value")
      else:
        ret_val = ret_vals[b2s(a)]
      print("ret val " + b2s(ret_val))
      resp = bytes([0x41, len(ret_val) + 5, 0x01])
      resp += bytes([0, 0, 0, 0]) # is ignored by VitoFiFi
      resp += ret_val
      resp += bytes([sum(resp[1:]) & 0xFF])
      print("response " + b2s(resp))
      ser.write(resp)
    else: # write
      data = ser.read(int.from_bytes(l, 'little'))
      ser.read(1) # ignore crc
      received_vals[b2s(a)] = data
      print("stored " + b2s(data))
      resp = bytes([0x41, 5, 0x01])
      resp += bytes([0, 0, 0, 0]) # is ignored by VitoFiFi
      resp += bytes([sum(resp[1:]) & 0xFF])
      print("response " + b2s(resp))
      ser.write(resp)
  else:
    print("received unexpected value: " + b2s(x))
      
      
