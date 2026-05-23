"use strict";
const points = document.querySelector("#points");
const stats = document.querySelector("#stats");
const UpdatePoints = (newPoints) => {
    points.textContent = newPoints;
};
const DisplayStats = (statValues) => {
    console.log("Got stats!");
    stats.textContent = statValues;
};
window.bridge.on("Points", UpdatePoints);
window.bridge.on("Stats", DisplayStats);
