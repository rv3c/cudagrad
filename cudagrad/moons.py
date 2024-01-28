from os import getenv

PROFILING = int(getenv("PROFILING", "0"))

if not PROFILING:
    import matplotlib.pyplot as plt
    import numpy as np

###############################################################################


from random import choice, random

from sklearn.datasets import make_moons

from cudagrad.nn import Module, mse, sgd
from cudagrad.tensor import Tensor

class MLP(Module):
    def __init__(self):
        self.w0 = Tensor(
            [16, 2], [choice([-1 * random(), random()]) for _ in range(2 * 16)]
        )
        self.b0 = Tensor([16, 1], [choice([-1 * random(), random()]) for _ in range(16)])
        self.w1 = Tensor(
            [1, 16], [choice([-1 * random(), random()]) for _ in range(1 * 16)]
        )
        self.b1 = Tensor([1], [choice([-1 * random(), random()]) for _ in range(1)])

    def __call__(self, x: Tensor) -> Tensor:
        return Tensor.sigmoid(
            self.w1 @ Tensor.sigmoid((self.w0 @ x + self.b0)) + self.b1
        )

if __name__ == "__main__":
    moons = make_moons()  # two moons

    inputs = moons[0]
    targets = moons[1]

    EPOCHS = 500
    lr = 0.05
    epochs = []
    losses = []
    model = MLP()
    for epoch in range(EPOCHS + 1):
        for i, input in enumerate(inputs):
            model.zero_grad()
            loss = mse(Tensor([1], [targets[i]]), model(Tensor([2, 1], input)))
            loss.backward()
            sgd(model, lr)
        if epoch % (EPOCHS // 10) == 0:
            print(f"{epoch=}", f"{loss.item()=}")
            epochs.append(epoch)
            losses.append(loss.item())
            accuracy = []
            for i, target in enumerate(targets):
                accuracy.append(round(model(Tensor([2, 1], inputs[i])).item()) == target.item())
            print(f"{round(sum(accuracy) / len(accuracy), 2) * 100}%")
            print("".join(["🔥" if x == True else " " for x in accuracy]))

    if not PROFILING:
        plt.scatter(epochs, losses)
        plt.title("MLP trained on two moons")
        plt.xlabel("Epoch")
        plt.ylabel("Loss")
        plt.savefig("./cudagrad/plots/moons.jpg")

        x = np.linspace(-2.5, 2.5, 50)
        y = np.linspace(-1.5, 1.5, 50)
        X, Y = np.meshgrid(x, y)
        Z = np.zeros(X.shape)

        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                input_data = Tensor([2, 1], [X[i, j], Y[i, j]])
                Z[i, j] = model(input_data).item()

        plt.figure()
        plt.contourf(X, Y, Z, cmap="viridis")
        plt.colorbar()  # colors Z value

        # plotting scatter plot over contour plot
        plt.scatter(inputs[targets == 0, 0], inputs[targets == 0, 1], c='red', label='Class 0')
        plt.scatter(inputs[targets == 1, 0], inputs[targets == 1, 1], c='blue', label='Class 1')

        plt.title("Two Moons MLP Visualization (2D)")
        plt.xlabel("X")
        plt.ylabel("Y")
        plt.legend()
        plt.savefig("./cudagrad/plots/moons-2d.jpg")
