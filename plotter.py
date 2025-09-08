import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read results
df = pd.read_csv("build/results.csv", header=None, names=["x", "T"])

# Analytical solution
x = np.linspace(0, 0.5, 100)
y = 800 * x + 100

# Plot
plt.plot(x, y, label="Analytical")
plt.scatter(df["x"], df["T"], label="FVM", color="black", marker="o")
plt.xlabel("x (m)")
plt.ylabel("Temperature (Celsius)")
plt.legend()
plt.grid(True)
plt.show()
