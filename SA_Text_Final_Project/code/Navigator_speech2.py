from textblob import TextBlob
import random

source = "Turn right and look in front of you. Watch out for the wales and stop being so dreamy. Stay precautious and do not forget to dream truthfully. Watch out fort the unknown and stop confusing your surroundings. Watch out for big waves and stop being so dreamy. Sometimes dream every day. Sometimes dream clearly. Turn wherever you feel like going and look around. Stay safe and sometimes dream every day. Do not forget to expect the best clearly. Do not forget to expect the best every day. Stay precautious and always expect the best every day. Sometimes dream truthfully. Turn in the opposite direction and look at me. Stay careful and always expect the best every day. Turn in my direction and look behind. Turn left and look at me. Watch out for trouble and stop wandering. Sometimes focus unconditionally. Watch out for big waves and stop confusing your surroundings. Turn in my direction and look behind. Stay safe and sometimes think unconditionally. Watch out for the ocean and stop being so dreamy. Stay safe and do not forget to think every day. Watch out for the ocean and stop confusing your surroundings. Turn left and look at me. Stay careful and always expect the best unconditionally. Always dream clearly. Turn around your axis and look in the distance. Sometimes dream every day. Stay safe and sometimes expect the best unconditionally. Sometimes expect the best every day."
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