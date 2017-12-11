######## ====== Call Overflow - Python bridge Script ====== ########

import requests
import json
from pythonosc import osc_message_builder, udp_client, osc_bundle_builder
import sys
import getopt

url = 'http://enframed.net:5000/api/data' # URL to server
max = None                                        # Max requests
count = 0                                         # Request counter

try:
    opts, args = getopt.getopt(sys.argv[1:], "hlm:")
except getopt.GetoptError:
    print("WRONG OPTION (-h for help)")
    sys.exit()

for opt, arg in opts:
    if opt == '-l':
        url = 'http://localhost:5000/api/data'
    elif opt == '-m':
        max = int(arg)
    elif opt == '-h':
        print("""HELPADOO:
        -l       : run locally
        -m [arg] : max number of requests""")
        sys.exit()

# Set up OSC sender to communicate with OF
port = 2046
client = udp_client.UDPClient('localhost', port)

# Sends JSON string data via OSC to OpenFrameworks
def sendData(add, dataStr):
    global client
    global count

    print count

    dOj = []
    try:
        dObj = json.loads(dataStr)
    except ValueError:
        return

    if len(dObj) == 0:
        return

    message = osc_message_builder.OscMessageBuilder(address = add)
    
    for elem in dObj:
        if type(elem) == str:
            message.add_arg(elem, arg_type = 's')
            break
        elif type(elem) == unicode:
            message.add_arg(elem.encode('utf8'), arg_type = 's')
            break

        for key in elem:
            data = elem[key]
            typ = type(data)

            if typ == int:
                message.add_arg(data, arg_type = 'i')
            elif typ == str:
                message.add_arg(data, arg_type = 's')
            elif typ == unicode:
                message.add_arg(data.encode('utf8'), arg_type = 's')
    message = message.build()

    client.send(message)

# boolean check to limit requests to a maximum amount
def checkMax():
    global max
    global count

    if max is None:
        return True

    return count < max

# Makes sure our JSON is valid and not empty
def checkData(data):
    global count
    try:
        obj = json.loads(data)
        if len(obj) == 0:
            print count
            return False
        print 'JSON : ' + str(count)
        print obj
        return True
    except ValueError:
        print count
        return False

# Where the magic happens: get data, if data, send data
def updateOF():
    global count
    req = requests.get(url)    
    data = req.text

    sendData('/text', data)
    count += 1

# Repeat ad infinitum (or until count == max)
try:
    while True and checkMax():
        updateOF()
except KeyboardInterrupt:
    pass

print 'bye!'