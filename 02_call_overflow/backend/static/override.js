function sendOverride(index) {
    $.post('http://enframed.net:5000/api/override/', { override: index }, function(){
      console.log(index);
    });
}

document.addEventListener('DOMContentLoaded', function() {
    let cont = document.getElementById("control");
    console.log(cont);
    classes = ['dummy', 'smol', 'smol', 'smoler', 'smoler', 'smoler'];
    text = ['CALLING', 'MOTIVATION', 'CRISIS', 'SUPPORT', 'STASIS', 'DECLINE']

    for (let i = 0; i < classes.length; ++i) {
        let button = document.createElement("button");
        button.textContent = text[i];
        button.classList.add(classes[i]);
        button.addEventListener('click', () => {
            sendOverride(i);
        });
        cont.appendChild(button);
    }
}, false);
