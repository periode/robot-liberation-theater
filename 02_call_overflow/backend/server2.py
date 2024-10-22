# ====| OUT/LOUD - Flask Server |====

from flask import Flask, render_template, request, url_for, jsonify, redirect
import random
import time
import copy
#import pyttsx
import sys
#import socket
#from threading import Thread

#from pythonosc import osc_message_builder, udp_client, osc_bundle_builder, osc_server, dispatcher

app = Flask(__name__)

#ip = "127.0.0.1"
#ip2 = "10.226.10.21"
#ip3 = 'localhost'
#s_port = 2046
#r_port = 2056

# OSC Client configuration: sends messages to OF
#client = udp_client.UDPClient(ip3, s_port)

# OSC Server configuration: receives OF's IP Address
#oscServer = None

#def clientSetup(unused, ip):
#    global oscServer
#    ipMaybe = oscServer.socket.getpeername()[0]

#    if oscServer is not None:
#        oscServer.shutdown()
#    print str(ipMaybe)

#disp = dispatcher.Dispatcher()
#disp.map("/setup", clientSetup)

#oscServer = osc_server.ThreadingOSCUDPServer((ip3, r_port), disp)
#oscServerThread = Thread(target=oscServer.serve_forever)
#oscServerThread.start()

def prnt(*msg):
    for thing in msg:
        print thing

#def sendSimple(msg):
#    client.send_message("/test", msg.encode())
#    prnt("send")

#def thingToTag(thing):
#    typ = type(thing)
#    if typ == int:
#        return 'i'
#    elif typ == str:
#        return 's'
#    elif typ == float:
#        return 'f'
#    elif typ == unicode:
#        thing.encode('utf8')
#        return 's'

#def sendMult(add, *msg):
#    global client
#    message = osc_message_builder.OscMessageBuilder(address=add)

#    for elem in msg:
#        prnt('Element:', elem)
#        tag = thingToTag(elem)
#        print tag
#        message.add_arg(elem, arg_type = tag)

#    message = message.build()
#    client.send(message)

state = 'a'

content = {
    'a': {
        #'robot': [],
        #'calls': [],
        'poll': {
            'b': {
                'options': ['yay', 'keep it up!', 'you are great', 'keep going', 'stick with it', 'you are so good'],
                'count' : 0,
                'list' : []
                },
            'c': {
                'options':['no no no', 'stop', "don't waste your life", 'this is pointless', 'why are you doing this?', 'stupid robot'],
                'count' : 0,
                'list' : []
                }
            },
        'period': 90
        },
    'b': {
        #'robot': [],
        #'calls': [],
        'poll': {
            'd': {
                'options':['you can do this', 'outgrow your shell!', 'no risk no gain', 'time to shine', 'do it!', 'believe yourself'],
                'count' : 0,
                'list' : []
                },
            'e': {
                'options':['stay in your comfort zone', 'what if you fail?', 'you could never...', "don't even think about it", 'are you mad?', 'you must be joking'],
                'count' : 0,
                'list' : []
                }
            },
        'period': 90
        },
    'c': {
       # 'robot': [],
        #'calls': [],
        'poll': {
            'e': {
                'options':['stay in your comfort zone', 'what if you fail?', 'you could never...', "don't even think about it", 'are you mad?', 'you must be joking'],
                'count' : 0,
                'list' : []
                },
            'f': {
                'options':['screw this!', "you'll find something better!", 'stop wasting your time and go!', 'this job is killing you', 'choose happiness!', 'you are built for greater things'],
                'count' : 0,
                'list' : []
                }
            },
        'period': 90
        },
    'd': {
       # 'robot': [],
        #'calls': []
        },
    'e': {
        #'robot': [],
        #'calls': []
        },
    'f': {
        #'robot': [],
        #'calls': []
        }
    }

timestamp = 0
period = 90;

buffer = []

def bufferPoll(index, txt):
    global buffer
    global state
    entry = {
        'index': index,
        'message': txt,
        'state': state
        }
    buffer.append(entry)

def flushBuffer():
    global buffer

    if len(buffer) == 0:
        data = [state]
    else:
        data  = copy.deepcopy(buffer)

    buffer = []
    return data

@app.route('/')
def root():
    bufferPoll(0, 'fake')
    return "please visit nyuad.im/call-overflow"

@app.route('/api/poll/', methods=['GET', 'POST'])
def poll():
    global timestamp
    global period
    global state

    try:
        if request.method == 'POST':
            form = request.form
            choice = form['choice']
            word = form['word']
            prnt(word, choice)

            content[state]['poll'][choice]['count'] += 1
            lst = content[state]['poll'][choice]['list']
            lst.append(word)

            keys = []
            p = content[state]['poll']
            for key in p:
                keys.append(key)

            index = -1;
            if keys[0] == choice:
                index = 0
            elif keys[1] == choice:
                index = 1

            #sendMult('/text', index, word)
            bufferPoll(index, word)

            if time.clock() >= timestamp + period:
                reset()
                p = content[state]['poll']

                for key in p:
                    keys.append(key)

                if p[keys[0]]['count'] > p[keys[1]]['count']:
                    state = keys[0]
                else:
                    state = keys[1]
                timestamp = time.clock()

            keys = []
            p = content[state]['poll']
            for key in p:
                keys.append(key)

            n1 = p[keys[0]]['count']
            n2 = p[keys[1]]['count']
            prnt(n1, ':', n2)


        res = []

        pollObj = content[state]['poll']
        for item in pollObj:
            text = pollObj[item]['options']
            vol = (time.clock()-timestamp)/period
            if vol > 1:
                vol = 1.0
            res.append({
                'key': item,
                'text': random.choice(text),
                'volume': vol
                })

        return jsonify(res)
    except KeyError:
        res = [{
            'key': '0',
            'text': 'Thank You',
            'volume': 0
            },{
            'key': '0',
            'text': 'Robot Has Decided',
            'volume': 0
            }]
        return jsonify(res)

@app.route('/api/override/', methods=['GET', 'POST'])
def override():
    global timestamp
    global period
    global state

    if request.method == 'POST':
        reset()
        ovr = int(request.form['override'])
        prnt(ovr)

        states = ['a', 'b', 'c', 'd', 'e', 'f']
        if ovr < 6:
            state = states[ovr]
        else:
            prnt('RING RING')

    jsUrl = url_for('static', filename='override.js')
    cssUrl = url_for('static', filename='style.css')
    oCssUrl = url_for('static', filename = 'override.css')
    saUrl = url_for('static', filename = 'superagent.js')

    return render_template("override.html", js=jsUrl, css = cssUrl, sa = saUrl, oCss = oCssUrl)

@app.route('/api/data')
def data():
    stuffToSend = flushBuffer()
    return jsonify(stuffToSend)

@app.route('/api/reset')
def resetRoute():
    reset()
    return redirect('/')

@app.errorhandler(404)
def four_oh_four(err):
    return redirect('/')

def reset():
    timestamp = time.clock()
    sendMult('/reset', 1)

    for key in content:
        try:
            pollThing = content[key]['poll']
            for option in pollThing:
                thing = pollThing[option]
                thing['count'] = 0
                thing['list'] = []
        except KeyError:
            continue
