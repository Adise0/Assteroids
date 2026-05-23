const points = document.querySelector("#points");
const stats = document.querySelector("#stats");

const UpdatePoints = (newPoints?: string | undefined) => {
  points!.textContent = newPoints!;
};

const DisplayStats = (statValues?: string | undefined) => {
  console.log("Got stats!");
  stats!.textContent = statValues!;
};

window.bridge.on("Points", UpdatePoints);
window.bridge.on("Stats", DisplayStats);
