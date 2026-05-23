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
          <p class="statName">${stat.name}</p>
          <p class="statValue">${stat.value * 10}</p>
        </div>`;
        statsHolder.innerHTML += value;
    });
};
window.bridge.on("Points", UpdatePoints);
window.bridge.on("Stats", DisplayStats);
