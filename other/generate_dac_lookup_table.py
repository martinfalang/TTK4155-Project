"""
Generate a lookup table for duty cycles for modulating a 
sine wave with a PWM signal. 

Creates `resolution` number of entries, each spaced at
2pi / resolution intervals. These are then converted into 
sine amplitude. 
"""
from math import sin, pi
from matplotlib import pyplot as plt


show_plots = input("Show plots? (y/n)   ").lower().strip()

resolution = 32
step = 2 * pi / resolution

# create list of amplitudes
T = []
A = []
for i in range(0, resolution):
    ts = step * i
    ampl = (1 + sin(ts)) / 2

    T.append(ts)
    A.append(ampl)
print(A)

# plot amplitudes against time steps
if show_plots == "y":
    fig1 = plt.figure(1)
    plt.title("Amplitude values")
    plt.scatter(T, A)
    plt.show()


# generate list of OCR values for PWM timer
OCR_MAX = 0xFF
OCR = []
for a in A:
    OCR.append( int(a * OCR_MAX) )

print(OCR)

# plot OCR values
if show_plots == "y":
    fig2 = plt.figure(2)
    plt.title("OCR values")
    plt.scatter(T, OCR)
    plt.show()
