from textblob import TextBlob
import random

source = "Hi sweetie pie. Yes. I need to tell you something. Are you listening? Hello? I am not! I think maybe you are being overly. What do you mean? I know. I understood every word. Can I talk to your mommy? Yes it is. How did you know? You did? Well arent you smart? Is your Mommy? What? Of course I want to talk to you. Dont be silly. You are? Well, That sounds like fun. Is it? Sure I do. Who? What? Cmon. Really? I find that hard to believe. No. Please dont. Its okay. Yes it is. You dont have to. Please dont cry. Dont. Hello?"
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