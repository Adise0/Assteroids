const points = document.querySelector("#points");
const statsHolder = document.querySelector(".statHolder");
const shopHolder = document.querySelector(".shopHolder");

interface Stat {
  name: string;
  value: number;
  level: number;
}

interface ShopStat {
  name: string;
  level: number;
  currentValue: number;
  newValue: number;
}

let stats: Stat[];

const ToId = (name: string) => name.replace(/\s+/g, "-");
const ToRound = (num: number) => Math.round(num * 10) / 10;

const UpdatePoints = (newPoints?: string | undefined) => {
  points!.textContent = newPoints!;
};

const UpdateStat = (newStat?: string | undefined) => {
  const stat: Stat = JSON.parse(newStat!);

  const statElm = document.querySelector(`#${ToId(stat.name)}`);
  statElm!.querySelector(".statName")!.textContent =
    `${stat.name} - (${stat.level})`;

  statElm!.querySelector(".statValue")!.textContent =
    `${ToRound(stat.value)} ${GetUnits(stat.name)}`;
};

const DisplayStats = (statValues?: string | undefined) => {
  stats = JSON.parse(statValues!);
  stats.forEach((stat) => {
    const value = `<div class="stat" id="${ToId(stat.name)}">
          <p class="statName">${stat.name} - (1)</p>
          <p class="statValue">${ToRound(stat.value)} ${GetUnits(stat.name)}</p>
        </div>`;

    statsHolder!.innerHTML += value;
  });
};

const OpenShop = (shopValue?: string | undefined) => {
  const shop: ShopStat[] = JSON.parse(shopValue!);
  (shopHolder as HTMLDivElement).style.display = "flex";
  let value = "";
  shop.forEach((shopStat) => {
    value += `
          <div class="statCard" onclick="PickOption('${shopStat.name}')">
          <p class="statCardName">${shopStat.name}</p>
          <img src="../icons/${shopStat.name}.png" alt="" class="statIcon" />
          <p class="statChange">${ToRound(shopStat.currentValue)} -> ${ToRound(shopStat.newValue)}</p>
          <p class="level">${shopStat.level}</p>
          </div>
    `;
  });

  shopHolder!.innerHTML = value;
};

const PickOption = (option: string) => {
  Send("PickUpgrade", option);
  (shopHolder as HTMLDivElement).style.display = "none";
};

const GetUnits = (name: string): string => {
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
