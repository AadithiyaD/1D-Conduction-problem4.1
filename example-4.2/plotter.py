import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read results
df = pd.read_csv("build/results.csv", header=None, names=["x", "T"])

# Analytical solution
x = np.linspace(0, 0.02, 100)
Ta = 100
Tb = 200
l = 0.02
k = 0.5
q = 1e6
y = ((Tb - Ta)/l + (q/(2*k))*(l - x))*x + Ta

# Plot
plt.plot(x, y, label="Analytical")
plt.scatter(df["x"], df["T"], label="FVM", color="black", marker="o")
plt.xlabel("x (m)")
plt.ylabel("Temperature (Celsius)")
plt.legend()
plt.grid(True)
plt.show()
