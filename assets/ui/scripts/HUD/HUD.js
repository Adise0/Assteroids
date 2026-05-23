"use strict";
const points = document.querySelector("#points");
const statsHolder = document.querySelector(".statHolder");
let stats;
const UpdatePoints = (newPoints) => {
    points.textContent = newPoints;
};
const DisplayStats = (statValues) => {
    stats = JSON.parse(statValues);
    stats.forEach((stat) => {
        const value = `<div class="stat" id="${stat.name}">
          <p class="statName">${stat.name} - (1)</p>
          <p class="statValue">${stat.value} ${GetUnits(stat.name)}</p>
        </div>`;
        statsHolder.innerHTML += value;
    });
};
const GetUnits = (name) => {
    switch (name) {
        case "Acceleration":
            return "km/s";
        case "Deceleration":
            return "km/s";
        case "Turn speed":
            return "deg/s";
        case "Max speed":
            return "km/s";
        case "Fire rate":
            return "bullets/s";
        default:
            return "";
    }
};
window.bridge.on("Points", UpdatePoints);
window.bridge.on("Stats", DisplayStats);
