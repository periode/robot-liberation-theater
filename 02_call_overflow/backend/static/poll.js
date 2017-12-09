var voice;

function setup() {
    noCanvas();
    voice = new p5.Speech(0, setRandomVoice);
}

function setRandomVoice() {
    let nVoices = window.speechSynthesis.getVoices().length;
    let n = Math.floor(Math.random() * nVoices)
    this.setVoice(n);
}

function getOptions(callback) {
    $.get("http://enframed.net:7777/api/poll/", function(res){
            console.log(res.body);
            let button1 = document.getElementById("choice-1");
            let button2 = document.getElementById("choice-2");

            button1.word = res.body[0]['text'];
            button2.word = res.body[1]['text'];

            button1.choice = res.body[0]['key'];
            button2.choice = res.body[1]['key'];

            button1.innerText = button1.word;
            button2.innerText = button2.word;

            voice.setVolume(res.body[0]['volume']);

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

    voice.speak(button.word);

    $.post("http://enframed.net:7777/api/poll",
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
