var voice;

function setup() {
    noCanvas();
    voice = new p5.Speech(0, setRandomVoice);
}

function setRandomVoice() {
    let daVoices = window.speechSynthesis.getVoices();
    let nVoices = daVoices.length;
    let valid = false;
    let attempt = 0;
    do {
        let n = Math.floor(Math.random() * nVoices)
        let curVoice = daVoices[n];

        if (!curVoice.name.includes('Google')) {
            valid = true;
            this.setVoice(n);
            return;
        }

        ++attempt;
    } while (!valid && attempt < 200);
    this.setVoice(n);
}

function getOptions(callback) {
    $.get("http://enframed.net:5000/api/poll/", function(res){
            let button1 = document.getElementById("choice-1");
            let button2 = document.getElementById("choice-2");

            button1.word = res[0]['text'];
            button2.word = res[1]['text'];

            button1.choice = res[0]['key'];
            button2.choice = res[1]['key'];

            button1.innerText = button1.word;
            button2.innerText = button2.word;

            let mappedVolume = 0.9 * res.body[0]['volume'] + 0.1;

            voice.setVolume(mappedVolume);

            if (callback) {
                callback(button1, button2);
            }
        });
}

function sendVote(i) {
    let button = document.getElementById('choice-' + (i + 1));
    if (!button) {
        console.error('NO BUTTON OOP');
        return;
    }

    voice.cancel();
    voice.speak(button.word);

    $.post("http://enframed.net:5000/api/poll/",
      {word: button.word, choice: button.choice}
    ).done(getOptions());
}

document.addEventListener('DOMContentLoaded', () => {
    getOptions((b1, b2) => {
        b1.addEventListener('click', () => { sendVote(0); });
        b2.addEventListener('click', () => { sendVote(1); });

        //b1.addEventListener('touchstart', () => { sendVote(0); });
        //b2.addEventListener('touchstart', () => { sendVote(1); });
    })
}, false);
