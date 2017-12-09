function sendOverride(index) {
    $.post('http://enframed.net:7777/api/override/', { override: index }, function(){
      console.log(index);
    }
}

document.addEventListener('DOMContentLoaded', () => {
    let cont = document.getElementById("control");
    console.log(cont);
    classes = ['dummy', 'smol', 'smol', 'smoler', 'smoler', 'smoler', 'dummy'];
    text = ['CALLING', 'MOTIVATION', 'CRISIS', 'SUPPORT', 'STASIS', 'DECLINE', 'RING RING']

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
