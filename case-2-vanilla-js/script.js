const decrementBtn = document.getElementById("decrementBtn");
const incrementBtn = document.getElementById("incrementBtn");
const result = document.getElementById("result");
const message = document.getElementById("message");

let counter = 0;

function updateView() {
    result.textContent = counter;
    result.classList.remove("result-positive", "result-negative", "result-zero");

    if (counter > 0) {
        result.classList.add("result-positive");
    } else if (counter < 0) {
        result.classList.add("result-negative");
    } else {
        result.classList.add("result-zero");
    }

    incrementBtn.disabled = counter >= 10;
    decrementBtn.disabled = counter <= -10;

    if (counter === 10 || counter === -10) {
        message.textContent = "Вы достигли экстремального значения";
    } else {
        message.textContent = "";
    }
}

incrementBtn.addEventListener("click", () => {
    if (counter < 10) {
        counter += 1;
        updateView();
    }
});

decrementBtn.addEventListener("click", () => {
    if (counter > -10) {
        counter -= 1;
        updateView();
    }
});

updateView();
