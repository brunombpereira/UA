# This program should find the phase of a fictional substance
# for given temperature and pressure conditions, but it has several bugs.
# 
# a) Try to run the program with Python3 and see what happens.
#    There's a syntax error near the end.  Fix it.
# b) Try again.  It'll crash with a runtime error.  Find the cause and fix it.
# c) There is also a semantic error: for T=300 and P=100,
#    the phase should be SOLID.
#    Fix it to agree with the phase diagram.  Test in several conditions.
# d) Adjust the format string to output the temperature with 1 decimal place
#    and the pressure with 3. 

print("Kryptonite phase classifier")

# Input.  (You can fix the runtime error by changing something here.)
T = int(input("Temperature (K)? "))
P = int(input("Pressure (kPa)? "))
m = 50 / 400

# Determine the phase. (This is wrong. Fix to match the phase diagram.)
if((P < (m * T) and T < 400) or (T > 400 and P < 50)):
    phase = "GAS"
elif(T > 400.0 and P > 50):
    phase = "LIQUID"
else:
    phase = "SOLID"

print(f"At {T} K and {P} kPa, Kryptonite is in the {phase} phase.".format(T, P, phase))
