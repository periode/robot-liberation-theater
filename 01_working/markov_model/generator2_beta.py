import markov                           # import Allison Parish's markov script
from textblob import TextBlob           # import TextBlob text analyzer
import random                           # import random
import sys                              # import sys - and do some shit, to allow unicode / string conversion
reload(sys)                             #   basically I need this, so that the markov can be read in TextBlob
sys.setdefaultencoding('utf8')

def buildAndGenerate(quality):
    model = markov.build_model(text, quality)                                   # build markov model of quality=n
    markoved = ''.join(markov.generate(model, quality, max_iterations=500))     # generate text from that model, at equal quality, 500 iterations until it stops trying
    return markoved                                                             # return the markov generated text

probabilityThresholds = [60, 20, 80, 60, 50, 30, 20, 20, 10]


# quality = 12

text = open("./savio.txt").read()                   # open source text
# model = markov.build_model(text, quality)

print "here is the original: "
print "----------"
print text

x = 0
for i in range(9, 0, -1):
    markovModel = buildAndGenerate(i)
    markovModel = str(markovModel)              #convert it to string just in case
    print ""
    # print markovModel
    analyzedModel = TextBlob(markovModel)       #TextBlob analysis on the text
    custom_dictionary = []                      # make this dictionary for storing antonyms/homonyms/hypernyms


    for word, tag in analyzedModel.tags:
        if tag == 'NN':

            entry = {               # each of our entries in our dictionary
                'word': word,       # has the initial word
                'others': []        # as well as a list of other possibilities
            }

            for synset in word.get_synsets(pos="n"):
                for syn in synset.lemmas():                                                 # here we loop through the list of lemmas that are related to the current noun
                    entry['others'].append(syn.name().replace('_', ' '))                    # we also replace any possible '_' character with a ' ' space character when we add it to our list of other possibilities
                    if syn.hyponyms():
                        entry['others'].append(syn.hyponyms()[0].name().replace('_', ' '))

            custom_dictionary.append(entry)                                                 # then we add the entry to our dictionary

    # this the part where we actually replace the source text
    for token in analyzedModel.tokenize():                                                  # we need to tokenize it in order to make sure we get each part of the sentences
        for entry in custom_dictionary:                                                     # then for each token, we go through our custom dictionary
            if token == entry['word']:                                                      # if we match the word

                chance = random.randint(0,100)
                if len(entry['others']) != 0 and chance < probabilityThresholds[x]:                               # and if we actually do have a word to replace it with!
                    other = random.choice(entry['others'])                                  # then we pick a random alternative
                    markovModel = markovModel.replace(token, other)                         # and we replace it in the source text


    print markovModel
    print "---------"
    x += 1

# markovModel = str(buildAndGenerate(2))
# print markovModel
print "========="




print "done, works"
