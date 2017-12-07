import random
from time import sleep

turn = ['right', 'left', 'around your axis', 'in the opposite direction', 'where your noise is pointing at', 'wherever you feel like going', 'in my direction']
look = ['around', 'behind', 'in front of you', 'in the distance', 'at me']
watch_out = ['for trouble', 'for big waves', 'for the ocean', 'for the wales', 'fort the unknown']
stay = ['careful', 'precautious', 'safe']
stop = ['wandering', 'being so dreamy', 'confusing your surroundings']

first = ['do not forget to', 'always', 'sometimes']
second = ['focus', 'think', 'dream', 'expect the best']
third = ['clearly', 'without limits', 'every day', 'unconditionally', 'truthfully']


while True:

	conclusion = random.random()
	if conclusion < 0.25:
		print "Turn %s and look %s." % (random.choice(turn), random.choice(look))
		exit()

	if conclusion < 0.5:
		print "Watch out %s and stop %s." % (random.choice(watch_out), random.choice(stop))
		exit()

	if conclusion < 0.75:
		print "Stay %s and %s %s %s." % (random.choice(stay), random.choice(first), random.choice(second), random.choice(third))
		exit()

	if conclusion < 1:
		print "%s %s %s." % (random.choice(first), random.choice(second), random.choice(third))
		exit()


