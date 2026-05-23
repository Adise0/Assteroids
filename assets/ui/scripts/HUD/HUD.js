"use strict";
const points = document.querySelector("#points");
const UpdatePoints = (newPoints) => {
    points.textContent = newPoints;
};
window.bridge.on("Points", UpdatePoints);
