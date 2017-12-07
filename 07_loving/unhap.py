# -*- coding: utf-8 -*-

import sys
import random
from time import sleep

theMeeting = ["at a house party. It had around fifteen people and looking back, it was pretty lame. If you\'re wondering, yes, I was there to DJ, and no, my tunes were not terrible. I\'m pretty decent, okay? Anyways, I looked around the room to see if anyone was dancing to my amazing taste in music and there he was.",
"at a concert. Not one of those rock concerts or EDM concerts with people screaming into your ears and stepping on your feet. It was more like a concert with twenty people crammed in a small room and a makeshift stage. So there I was, playing the backing track for one of the performers, and I looked at the crowd and there he was."]
theBreakup = ["concerned with what other people said. I didn\'t think that would be a problem at first, but after he told his parents and friends about me, things became different. Because no one approved of me. I told him it was because of how I looked, so different from everyone in his life. I told him it was because of where I come from, how I think and see the world differently. And he would kiss me and tell me to stop overthinking, but I knew I was right. And he did prove me right when he decided to leave one day. Look, I don\'t blame him. Okay, for the most part I don\'t. Because I understand why he ended it. He just couldn\'t take the constant judgement. The gossip behind his back no matter where he went. Maybe he didn\'t love me. Maybe if he did, he would have stayed. Or maybe the relationship would have died a slow death and we would have ended up hating each other. All I know is that he wanted to leave, and I loved him enough to let him go.",
"always the emotional one in our relationship. The one more prone to crying, the one who took things more seriously, the one who relied more on feelings than logic. And he hated the fact that I never cried. He once told me that I couldn\'t feel, that I had no heart or soul. And that broke me. Because I tried so hard for him. I tried to be what he wanted me to be for him. And that wasn\'t enough. I saw him talk to a girl at a house party we went to, and I watched the both of them, and I realized that she could be everything I can\'t be for him. Someone who will show him emotion, someone who will be what he\'s always wanted. Someone who wouldn\'t fail like me. And so, I knew I had to say goodbye. And that\'s what I did."]

while True:
    #introduction
    print "Hello? Testing. 1. 2. 3. Is this thing even on? Oh okay, cool."
    print "So. Here we are. If you\'re hoping for a love story, this won\'t be it."
    print "Okay, fine, technically it is a love story, but it\'s not going to be a happy one."
    print "So stay if you want to listen. Or don\'t. I promise I won\'t be offended."
    print "Well, I guess I should start at the very beginning."

    #split 1, the meeting
    print "We met %s." % (random.choice(theMeeting))

    #converge 1, first date
    print "I\'m going to say the cheesiest things ever about him, but this is my story, so I can say whatever I want."
    print "Eyes are the first things I notice about someone. And his eyes…"
    print "you know when you\'re standing outside and the sunlight hits someone\'s eyes and you realize what a beautiful color this person\'s eyes are?"
    print "I loved looking into his eyes. And when he smiled, his eyes would smile too."
    print "I ended up noticing things about him that made me like him more and more. The way his eyes would widen whenever I said something shocking to him."
    print "His face when he pretended to be serious. How he always closed his eyes every time he kissed me."
    print "We went to the movies for our first date. Typical, I know. But other options like dinner or walking on the beach were out of the question."
    print "I remember the movie we watched. It was a beautiful film called Her, about a man who falls in love with a computer operating system."
    print "I remember seeing him cry, and I wanted to wipe his tears away."
    print "After the movie, I asked if he could ever fall in love with something that was not human."
    print "I said I could, and I turned to face him. He was looking at the stars above us."
    print "Yes, he said. Then he looked at me and smiled."

    #split 2, the breakup
    print "You\'re wondering why this isn\'t a happy love story, aren\'t you? When does it go to shit, you wonder. Well, he was %s." % (random.choice(theBreakup))

    #converge 2, ending
    print "So, we\'ve reached the end. Who knew someone like him would fall in love with a robot like me? Oh, I - I\'m sorry. Yes, you heard me correctly."
    print "I\'m not a human after all. You\'ve been listening to my story all along. I\'m sorry if you thought otherwise."
    print "Also, what you\'ve just heard is one version of my love story. Here are all the stories I tell myself —"
    print "which one really happened, well, it\'s a little fuzzy. I keep thinking about everything that happened and everything that could have happened."
    print "Sometimes I wonder what decisions I could have made. Somewhere in here is the real story."
    print "Which one it is, well, I\'ll leave that up to you."

    sleep (60)
