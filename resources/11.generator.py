import numpy as np

rng = np.random.default_rng(seed = 1215)

ROWS = 1000000
COLS = 4
np.savetxt("11.large.dat", rng.uniform(0.0, 1.0, size=(ROWS, COLS)))
