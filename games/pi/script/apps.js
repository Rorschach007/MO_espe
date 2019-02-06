var PI = "14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282925409171536436789259036001133053054882046652138414695194151160943305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912983367336244065664308602139494639522473719070217986094370277053921717629317675238467481846766940513200056812714526356082778577134275778960917363717872146844090122495343014654958537105079227968925892354201995611212902196086403441815981362977477130996051870721134999999837297804995105973173281609631859 50244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989";

var buttons = [], blocks = [3, '.'];
var canvas, g, size, fontSize, max = 11, index = 0, x = 0, y, speed, width, height, running = false, ai;

onload = function() {
    canvas = document.getElementsByTagName("canvas")[0];
    canvas.width  = window.innerWidth;
    canvas.height = window.innerHeight *  0.7;
    g = canvas.getContext("2d");
    size = canvas.width / max;
    g.strokeStyle = "#C81E14";
    g.lineWidth   = canvas.height / 40;

    width = size / 3 * 2;
    height = size * 1.2;

    fontSize = canvas.height / 10;
    g.font = fontSize + "px Arial";

    y = canvas.height / 2 - size / 2 + size;

    canvas.onclick = bot;

    speed = canvas.width / 400;

    for(var i = 0; i < 10; i++) {
    buttons.push(document.getElementById("b" + i));
    buttons[i].type = i;
    buttons[i].onclick = function() {
        click(this.type);
    }
  }

  draw();
}

function update() {
    if(!running)
        return;

    x += speed;

    draw();

    if(x > blocks.length * size) {
        y += speed * 3;
        if(y - fontSize * 4 > canvas.height) {
            alert("Game Over!\n\nHas conseguido " + index + " decimales!");
            gameOver();
            return;
        }
    } else
        y = canvas.height / 2 - size / 2 + size;

    requestAnimationFrame(update);
}

function gameOver() {
    running = false;
    index = 0;
    x = 0;
    y = canvas.height / 2 - size / 2 + size;
    blocks = [3, '.'];
    draw();
}

function draw() {
    g.clearRect(0, 0, canvas.width, canvas.height);

    for(var b = 0; b < blocks.length; b++) {
        g.fillStyle = "#FF3C28";
        g.fillRect(b * size + 4, canvas.height / 2 - size / 2 + size, size, size);
        g.strokeRect(b * size + 4, canvas.height / 2 - size / 2 + size, size, size);

        g.fillStyle = "#FFF";
        g.font = fontSize + "px Arial";
        g.fillText(blocks[b], b * size + 4 + size / 2 - fontSize / 3, canvas.height / 2 + fontSize / 3 + size);
    }

    g.fillStyle = "#00F";
    g.font = fontSize * 4 + "px Times New Roman";
    g.fillText("π", x, y);
}

function bot() {
    if(ai)
        return;

    ai = setInterval(function() {
        addBlock(PI[index]);
    }, 500);
}

function click(type) {
    if(ai) {
        clearInterval(ai);
        gameOver();
        ai = null;
        return;
    }

    addBlock(type);
}

function addBlock(type) {
    if(!running) {
        running = true;
        requestAnimationFrame(update);
    }

    if(PI[index] == type) {
        index++;
        blocks.push(type);
        if(blocks.length > max - 2) {
            blocks.shift();
            if(x > size)
                x -= size;
        }
    }
}
