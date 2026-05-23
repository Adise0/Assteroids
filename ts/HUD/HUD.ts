const points = document.querySelector("#points");

const UpdatePoints = (newPoints?: string | undefined) => {
  points!.textContent = newPoints!;
};

window.bridge.on("Points", UpdatePoints);
