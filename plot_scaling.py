#!/usr/bin/env python3

import re
import numpy as np
import matplotlib.pyplot as plt

# --- 1) Parse measured total times
cores_meas = [64, 128]
times_meas = []
with open('total_times.txt') as f:
    for line in f:
        m = re.search(r'=\s*([0-9.eE+-]+)', line)
        if m:
            times_meas.append(float(m.group(1)))

if len(times_meas) != 2:
    raise RuntimeError("Expected exactly 2 measured points in total_times.txt")

# --- 2) Fit a linear model: T(p) = m*p + b
m, b = np.polyfit(cores_meas, times_meas, 1)

# --- 3) Extrapolate to 256 & 512 cores
cores_extra = [256, 512]
times_extra = [m*p + b for p in cores_extra]

# --- 4) Plot
plt.figure()
plt.plot(cores_meas, times_meas, 'o-', label='Measured')
plt.plot(cores_extra, times_extra, 'x--', label='Extrapolated')
plt.xlabel('Total cores')
plt.ylabel('Total time (s)')
plt.title('Weak Scaling: Measured & Extrapolated')
plt.legend()
plt.grid(True)
plt.savefig('weak_scaling_plot.png')
plt.show()

