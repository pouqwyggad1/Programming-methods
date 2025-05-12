import matplotlib.pyplot as plt
import pandas as pd

n_signals = 3

fig, axes = plt.subplots(4, n_signals, figsize=(16, 10))
fig.suptitle("ДПФ: Сигналы и спектры (с шумом и без)", fontsize=16)

for i in range(n_signals):
    idx = i + 1

    signal = pd.read_csv(f"signal_{idx}.csv", header=None, names=["t", "ampl"])
    signal_noisy = pd.read_csv(f"signal_noisy_{idx}.csv", header=None, names=["t", "ampl"])
    spectrum = pd.read_csv(f"spectrum_{idx}.csv", header=None, names=["freq", "ampl"])
    spectrum_noisy = pd.read_csv(f"spectrum_noisy_{idx}.csv", header=None, names=["freq", "ampl"])

    axes[0, i].plot(signal["t"], signal["ampl"])
    axes[0, i].set_title(f"Сигнал {idx} (без шума)")
    axes[0, i].set_ylabel("Амплитуда")

    axes[2, i].plot(signal_noisy["t"], signal_noisy["ampl"], color='orange')
    axes[2, i].set_title(f"Сигнал {idx} (с шумом)")
    axes[2, i].set_ylabel("Амплитуда")

    axes[1, i].bar(spectrum["freq"], spectrum["ampl"], width=10)
    axes[1, i].set_title(f"Спектр {idx} (без шума)")
    axes[1, i].set_ylabel("Амплитуда")

    axes[3, i].bar(spectrum_noisy["freq"], spectrum_noisy["ampl"], width=10, color='red')
    axes[3, i].set_title(f"Спектр {idx} (с шумом)")
    axes[3, i].set_xlabel("Частота (Гц)")
    axes[3, i].set_ylabel("Амплитуда")

plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.show()
