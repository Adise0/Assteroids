const points = document.querySelector("#points");
const statsHolder = document.querySelector(".statHolder");

interface Stat {
  name: string;
  value: number;
  level: number;
}

let stats: Stat[];

const UpdatePoints = (newPoints?: string | undefined) => {
  points!.textContent = newPoints!;
};

const DisplayStats = (statValues?: string | undefined) => {
  stats = JSON.parse(statValues!);
  stats.forEach((stat) => {
    const value = `<div class="stat" id="${stat.name}">
          <p class="statName">${stat.name}</p>
          <p class="statValue">${stat.value * 10}</p>
        </div>`;

    statsHolder!.innerHTML += value;
  });
};

window.bridge.on("Points", UpdatePoints);
window.bridge.on("Stats", DisplayStats);
