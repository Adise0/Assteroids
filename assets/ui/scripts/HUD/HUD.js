"use strict";
const points = document.querySelector("#points");
const statsHolder = document.querySelector(".statHolder");
const shopHolder = document.querySelector(".shopHolder");
let stats;
const ToId = (name) => name.replace(/\s+/g, "-");
const UpdatePoints = (newPoints) => {
    points.textContent = newPoints;
};
const UpdateStat = (newStat) => {
    const stat = JSON.parse(newStat);
    const statElm = document.querySelector(`#${ToId(stat.name)}`);
    statElm.querySelector(".statName").textContent =
        `${stat.name} - (${stat.level})`;
    statElm.querySelector(".statValue").textContent =
        `${stat.value} ${GetUnits(stat.name)}`;
};
const DisplayStats = (statValues) => {
    stats = JSON.parse(statValues);
    stats.forEach((stat) => {
        const value = `<div class="stat" id="${ToId(stat.name)}">
          <p class="statName">${stat.name} - (1)</p>
          <p class="statValue">${stat.value} ${GetUnits(stat.name)}</p>
        </div>`;
        statsHolder.innerHTML += value;
    });
};
const OpenShop = (shopValue) => {
    const shop = JSON.parse(shopValue);
    shopHolder.style.display = "flex";
    let value = "";
    shop.forEach((shopStat) => {
        value += `
          <div class="statCard" onclick="PickOption('${shopStat.name}')">
          <p class="statCardName">${shopStat.name}</p>
          <img src="../icons/${shopStat.name}.png" alt="" class="statIcon" />
          <p class="statChange">${shopStat.currentValue} -> ${shopStat.newValue}</p>
          <p class="level">${shopStat.level}</p>
    `;
    });
    shopHolder.innerHTML = value;
};
const PickOption = (option) => {
    Send("PickUpgrade", option);
    shopHolder.style.display = "none";
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
window.bridge.on("OpenShop", OpenShop);
window.bridge.on("UpdateStat", UpdateStat);
