import matplotlib.pyplot as plt
import numpy as np

house_location_file = "Data/house_location.txt"
hospital_location_file = "Data/hospital_location.txt"
parameters_file = "Data/map_parameters.txt"
KD_results_file = "Data/results_KD.txt"
BT_results_file = "Data/results_BT.txt"

def extractParameters():
    parameters_list = []
    with open(parameters_file, "r") as file:
        parameters_list = list(map(lambda x: int(x.removesuffix("\n")), file.readlines()))
    
    return parameters_list

def extractHouses():
    contents = []
    with open(house_location_file, "r") as file:
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))
    
    return contents

def extractHospitals():
    contents = []
    with open(hospital_location_file, "r") as file:
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))
    
    return contents

def extractKDResults():
    contents = []
    with open(KD_results_file, "r") as file:
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))
    
    return contents

def extractBTResults():
    contents = []
    with open(BT_results_file, "r") as file:
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))
    
    return contents

houses = extractHouses()
hospitals = extractHospitals()

results_KD = extractKDResults()
results_BT = extractBTResults()

# Plotting the map - only possible for 2D Map
if (len(hospitals[0]) == 2):
    plt.figure(figsize = (10, 10))
    plt.scatter(list(map(lambda x: x[0], houses)), list(map(lambda x: x[1], houses)), c = "blue", marker = "o", s = 30, label = "Houses")

    for house_idx in range(len(houses)):
        plt.plot([houses[house_idx][0], results_KD[house_idx][0]], [houses[house_idx][1], results_KD[house_idx][1]], c = "orange", linestyle = "--")
        plt.plot([houses[house_idx][0], results_BT[house_idx][0]], [houses[house_idx][1], results_BT[house_idx][1]], c = "pink", linestyle = ":")

    plt.scatter(list(map(lambda x: x[0], hospitals)), list(map(lambda x: x[1], hospitals)), c = "red", marker = "^", s = 100, label = "Hospitals")

# Map details
map_size = extractParameters()[0]
offset = 2

plt.title(f"Hospital and House Locations on a ${map_size}\\times{map_size}\;km$ Map")
plt.xlabel("x coordinate(km)")
plt.ylabel("y Coordinate(km)")
plt.xlim(-offset, map_size + offset)
plt.ylim(-offset, map_size + offset)
plt.grid(True)
plt.legend()

plt.savefig("Data/map.png", dpi = 300)
print("Plotted Map!")