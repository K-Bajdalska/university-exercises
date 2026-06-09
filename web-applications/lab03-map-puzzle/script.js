let map = L.map('map').setView([53.436376, 14.518474], 17);
L.tileLayer.provider('Esri.WorldImagery').addTo(map);
const userLocationEl = document.getElementById("user-location");

document.getElementById("getLocation").addEventListener("click", function() {
    if (!navigator.geolocation) {
        alert("Twoja przeglądarka nie obsługuje geolokalizacji.");
        return;
    }

    navigator.geolocation.getCurrentPosition(
        position => {
            const lat = position.coords.latitude;
            const lon = position.coords.longitude;
            map.setView([lat, lon], 17);
            userLocationEl.innerHTML = `<p class="usrLoc">${lat.toFixed(4)}, ${lon.toFixed(4)}</p>`;
        },
        error => {
            console.error(error);
            alert("Nie udało się pobrać lokalizacji.");
        }
    );
})

document.getElementById("save").addEventListener("click", function() {
    if ("Notification" in window && Notification.permission === "default") {
    Notification.requestPermission().then(permission => {
        if (permission === "granted") {
            console.log("Użytkownik zezwolił na powiadomienia");
        }
    });
}
    map.closePopup();
    leafletImage(map, function(err, canvas) {
        if (err) {
            console.error(err);
            return;
        }

        const imgMap = canvas.toDataURL("image/png");
        const img = new Image();
        img.src = imgMap;

        img.onload = function() {
            const srcWidth = img.width; 
            const srcHeight = img.height; 
            const splitCols = 4;
            const splitRows = 4;
            const tileWidth = srcWidth / splitCols;  
            const tileHeight = srcHeight / splitRows; 
            const tiles = [];

            for (let row = 0; row < splitRows; row++) {
                for (let col = 0; col < splitCols; col++) {
                    const tempCanvas = document.createElement("canvas");
                    const tempCtx = tempCanvas.getContext("2d");
                    tempCanvas.width = tileWidth;
                    tempCanvas.height = tileHeight;
                    tempCtx.drawImage(
                        img,
                        col * tileWidth, row * tileHeight, tileWidth, tileHeight,
                        0, 0, tileWidth, tileHeight
                    );
                    tiles.push({
                        id: `${row}-${col}`,
                        canvas: tempCanvas,
                        correctRow: row,
                        correctCol: col
                    });
                }
            }
            shuffle(tiles);

            const container = document.getElementById("raster-map");
            container.innerHTML = "";
            container.style.display = "grid";
            container.style.gridTemplateColumns = `repeat(8, ${tileWidth}px)`;
            container.style.gridTemplateRows = `repeat(2, ${tileHeight}px)`;
            container.style.gap = "0px";
            container.style.width = `${8 * tileWidth}px`;
            container.style.height = `${2 * tileHeight}px`;

            tiles.forEach(tile => {
                const tileDiv = document.createElement("div");
                tileDiv.classList.add("tile");
                tileDiv.draggable = true;
                tileDiv.dataset.id = tile.id;
                tileDiv.appendChild(tile.canvas);
                container.appendChild(tileDiv);
            });

            const board = document.getElementById("place-to-match");
            board.innerHTML = "";
    board.style.display = "grid";
    board.style.gridTemplateColumns = `repeat(4, ${tileWidth}px)`;
    board.style.gridTemplateRows = `repeat(4, ${tileHeight}px)`;
    board.style.gap = "0px";
    board.style.width = `${4 * tileWidth}px`;
    board.style.height = `${4 * tileHeight}px`;
    const rasterMap = document.getElementById("raster-map");


    rasterMap.addEventListener("dragover", e => e.preventDefault());
    rasterMap.addEventListener("drop", e => {
        e.preventDefault();
        if (!draggedTile) return;
        rasterMap.appendChild(draggedTile);
        checkPuzzleCompletion();
    });
            for (let row = 0; row < splitRows; row++) {
                for (let col = 0; col < splitCols; col++) {
                    const slot = document.createElement("div");
                    slot.classList.add("slot");
                    slot.dataset.correctId = `${row}-${col}`;
                    slot.addEventListener("dragover", handleDragOver);
                    slot.addEventListener("drop", handleDrop);
                    board.appendChild(slot);
                }
            }
            enableDragDrop();
        };
    });
});


let draggedTile = null;

function enableDragDrop() {
    document.querySelectorAll(".tile").forEach(tile => {
        tile.addEventListener("dragstart", e => {
            draggedTile = e.target;
            setTimeout(() => tile.classList.add("hidden"), 0);
        });

        tile.addEventListener("dragend", e => {
            e.target.classList.remove("hidden");
            draggedTile = null;
        });
    });
}

function handleDragOver(e) {
    e.preventDefault();
}

function handleDrop(e) {
    e.preventDefault();
    if (!draggedTile) return;
    const target = e.currentTarget;
    if (target.children.length > 0) return;
    target.appendChild(draggedTile);
    checkPuzzleCompletion();
}

function checkPuzzleCompletion() {
    const slots = document.querySelectorAll("#place-to-match .slot");
    let allCorrect = true;

    slots.forEach(slot => {
        const tile = slot.querySelector(".tile");
        if (!tile || tile.dataset.id !== slot.dataset.correctId) {
            allCorrect = false;
        }
    });

    if (allCorrect) {
        slots.forEach(slot => {
            const tile = slot.querySelector(".tile");
            if (tile) {
                tile.classList.add("correct");
            }
        });
        console.log("Gratulacje! Ułożyłeś wszystkie puzzle!")

        if ("Notification" in window && Notification.permission === "granted") {
            new Notification("Gratulacje!", {
                body: "Ułożyłeś wszystkie puzzle!",
            });
        }
    }
}

function shuffle(array) {
    for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
    }
}

function updateMapCenter() {
    const center = map.getCenter();
    userLocationEl.innerHTML = `
        <p class="usrLoc">${center.lat.toFixed(4)}, ${center.lng.toFixed(4)}</p>
    `;
}

map.on('moveend', updateMapCenter);
updateMapCenter();
