######## ====== Call Overflow - Python bridge Script ====== ########

import requests
import json
from pythonosc import osc_message_builder, udp_client, osc_bundle_builder
import sys
import getopt

reqUrl = 'http://nyuad.im/call-overflow/api/data' # URL to server
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
    message = osc_message_builder.OscMessageBuilder(address = add)
    message.add_arg(dataStr, arg_type = 's')
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
        return True
    except ValueError:
        print count
        return False

# Where the magic happens: get data, if data, send data
def updateOF():
    global count
    req = requests.get(url)    
    data = req.text

    if checkData(data):
        sendData('localhost', data)
    count += 1

# Repeat ad infinitum (or until count == max)
try:
    while True and checkMax():
        updateOF()
except KeyboardInterrupt:
    pass

print 'bye!'