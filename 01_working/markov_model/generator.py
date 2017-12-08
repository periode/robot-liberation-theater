import markov
from textblob import TextBlob
import random

def buildAndGenerate(quality):
    model = markov.build_model(text, quality)
    markoved = ''.join(markov.generate(model, quality, max_iterations=500))
    return markoved

probabilityThresholds = [0, 15, 20, 40, 60, 30, 0]


quality = 12

text = open("./savio.txt").read()
model = markov.build_model(text, quality)

print "here is the original: "
print "----------"
print text


for i in range(12, 0, -2):
    print "now printing markov quality %r" % i
    print "----------"
    quality = i
    # buildAndGenerate(i)
    print buildAndGenerate(i)

    ## works up to this point


# finally do it with quality = 1
quality = 1
print "and number 1"
print "------------"
print buildAndGenerate(1)
