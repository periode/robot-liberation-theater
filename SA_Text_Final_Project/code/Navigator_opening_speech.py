from textblob import TextBlob
import random

source = "Hell is empty and all the devils are here. Cowards die many times before their deaths, the valiant never taste of death but once. How far that little candle throws its beams. So shines a good deed in a naughty world. Listen to many, speak to a few. All the world is a stage, and all the men and women merely players, they have their exits and their entrances, and one man in his time plays many parts, his acts being seven ages. Life every man holds dear, but the dear man holds honour far more precious dear than life. What is done cannot be undone. When we are born we cry that we are come to this great stage of fools. As soon go kindle fire with snow, as seek to quench the fire of love with words. Uneasy lies the head that wears a crown. Virtue is bold, and goodness never fearful."
processed = TextBlob(source)
print source
custom_dictionary = []


for word, tag in processed.tags:
    if tag == 'NN':

        entry = {               
            'word': word,       
            'others': []        
        }

        for synset in word.get_synsets(pos="n"):
            for syn in synset.lemmas():                                 
                entry['others'].append(syn.name().replace('_', ' '))   
                if syn.antonyms():
                    entry['others'].append(syn.antonyms()[0].name().replace('_', ' '))

        custom_dictionary.append(entry)


for token in processed.tokenize():                      # we need to tokenize it in order to make sure we get each part of the sentences
    for entry in custom_dictionary:                     # then for each token, we go through our custom dictionary
        if token == entry['word']:                      # if we match the word

            if len(entry['others']) != 0:               # and if we actually do have a word to replace it with!
                other = random.choice(entry['others'])  # then we pick a random alternative
                source = source.replace(token, other)   # and we replace it in the source text

print source