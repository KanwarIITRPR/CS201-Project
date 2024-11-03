import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

house_location_file = "Data/house_location.txt"
hospital_location_file = "Data/hospital_location.txt"
parameters_file = "Data/map_parameters.txt"
KD_results_file = "Data/results_KD.txt"
BT_results_file = "Data/results_BT.txt"
divisions_file = "Data/KD_divisions.txt"
balls_file = "Data/BT_balls.txt"

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

def extractDivisions(dimensions):
    contents = []
    with open(divisions_file, "r") as file:
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))

    points, lower_constraints, upper_constraints, depths = [], [], [], []
    for hospital in contents:
        points.append(hospital[:dimensions])
        lower_constraints.append(hospital[dimensions:2 * dimensions])
        upper_constraints.append(hospital[2 * dimensions:3 * dimensions])
        depths.append(hospital[-1])
    
    return points, lower_constraints, upper_constraints, depths

def extractBalls():
    contents = []
    with open(balls_file, "r") as file:
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))

    points, radius, depths = [], [], []
    for hospital in contents:
        points.append(hospital[:-2])
        radius.append(hospital[-2])
        depths.append(hospital[-1])

    return points, radius, depths


houses = extractHouses()
hospitals = extractHospitals()

results_KD = extractKDResults()
results_BT = extractBTResults()

nodes, lower_constraints, upper_constraints, node_depths = extractDivisions(len(hospitals[0]))
balls, radius, ball_depths = extractBalls()

map_size = extractParameters()[0]
offset = 2

def location_map():
    plt.figure(figsize = (10, 10))
    plt.scatter(list(map(lambda x: x[0], houses)), list(map(lambda x: x[1], houses)), c = "blue", marker = "o", s = 30, label = "Houses")
    plt.scatter(list(map(lambda x: x[0], hospitals)), list(map(lambda x: x[1], hospitals)), c = "red", marker = "^", s = 100, label = "Hospitals")
    plt.plot([0, 0, map_size, map_size, 0], [0, map_size, map_size, 0, 0], c = "black", linestyle = "--", linewidth = 2, alpha = 0.2)

    plt.xlabel("x coordinate(km)")
    plt.ylabel("y Coordinate(km)")
    plt.xlim(-offset, map_size + offset)
    plt.ylim(-offset, map_size + offset)
    plt.grid(False)
    plt.legend()

def plot_map():
    location_map()
    plt.title(f"Hospital and House Locations on a ${map_size}\\times{map_size}\;km$ Map")

    plt.savefig("Plots/map.png", dpi = 300)
    print("Plotted Map")

    plt.close()


def plot_KD_map():
    location_map()
    plt.title(f"Mapping Houses to nearest hospitals using K-Dimensional Trees")
    for house_idx in range(len(houses)):
        plt.plot([houses[house_idx][0], results_KD[house_idx][0]], [houses[house_idx][1], results_KD[house_idx][1]], c = "orange", linestyle = "--")

    plt.savefig("Plots/KD_map.png", dpi = 300)
    print("Plotted K-Dimensional Tree's results")

    plt.close()

def plot_BT_map():
    location_map()
    plt.title(f"Mapping Houses to nearest hospitals using Ball Trees")
    for house_idx in range(len(houses)):
        plt.plot([houses[house_idx][0], results_BT[house_idx][0]], [houses[house_idx][1], results_BT[house_idx][1]], c = "magenta", linestyle = ":")

    plt.savefig("Plots/BT_map.png", dpi = 300)
    print("Plotted Ball Tree's results")

    plt.close()

def plot_comparison_map():
    location_map()
    plt.title(f"Comparing results of K-Dimensional Trees and Ball Trees")
    plt.plot([houses[0][0], results_KD[0][0]], [houses[0][1], results_KD[0][1]], c = "purple", linestyle = "--", label = "Same")
    for house_idx in range(1, len(houses)):
        plt.plot([houses[house_idx][0], results_KD[house_idx][0]], [houses[house_idx][1], results_KD[house_idx][1]], c = "purple", linestyle = "--")

    common_indices = []
    for house_idx in range(len(houses)):
        if (not(results_KD[house_idx][0] == results_BT[house_idx][0] and results_KD[house_idx][1] == results_BT[house_idx][1])):
            common_indices.append(house_idx)

    if len(common_indices) > 0:
        plt.plot([houses[0][0], results_KD[0][0]], [houses[0][1], results_KD[0][1]], c = "green", linestyle = "-.", label = "Different")
    for common_idx in common_indices:
        plt.plot([houses[common_idx][0], results_KD[common_idx][0]], [houses[common_idx][1], results_KD[common_idx][1]], c = "green", linestyle = "-.")
        plt.plot([houses[common_idx][0], results_BT[common_idx][0]], [houses[common_idx][1], results_BT[common_idx][1]], c = "green", linestyle = "-.")

    plt.legend()
    plt.savefig("Plots/comparison_map.png", dpi = 300)
    print("Plotted K-Dimensional Tree's and Ball Tree's comparison")
        
    plt.close()

def plot_divisions():
    location_map()
    plt.title(f"Plotting divisions made in K-Dimensional Trees")

    text_offset = 0.5
    for node_idx in range(len(nodes)):
        plt.plot([lower_constraints[node_idx][0], upper_constraints[node_idx][0]], [lower_constraints[node_idx][1], upper_constraints[node_idx][1]], color = "darkgoldenrod", alpha = 0.5, linestyle = "--", linewidth = 2)
        plt.text(nodes[node_idx][0] + text_offset/(2 ** 0.5), nodes[node_idx][1] + text_offset/(2 ** 0.5), f"{int(node_depths[node_idx])}", fontsize = 12, color = "black")
    
    plt.savefig("Plots/KD_divisions.png", dpi = 300)
    print("Plotted hyperspace divisions of the K-Dimensional Tree")
        
    plt.close()

def plot_balls():
    location_map()
    plt.title(f"Plotting balls made in Ball Trees")

    min_x, min_y = 0, 0
    max_x, max_y = map_size, map_size

    temp_alpha = 0.2
    temp_width = 2
    delta_alpha = (1 - temp_alpha) / len(ball_depths)
    delta_width = (temp_width - 0.5) / len(ball_depths)
    for ball_idx in range(len(balls)):
        if radius[ball_idx] == 0:
            radius[ball_idx] = 1
        circle = patches.Circle(balls[ball_idx], radius[ball_idx], color = "darkblue", fill = False, alpha = temp_alpha + (delta_alpha * ball_depths[ball_idx]), linestyle = ":", linewidth = temp_width - (delta_width * ball_depths[ball_idx]))
        plt.gca().add_patch(circle)
        plt.text(balls[ball_idx][0] + radius[ball_idx]/(2 ** 0.5), balls[ball_idx][1] + radius[ball_idx]/(2 ** 0.5), f"{int(ball_depths[ball_idx])}", fontsize = 12, color = "black")

        min_x = min(balls[ball_idx][0] - radius[ball_idx], min_x)
        min_y = min(balls[ball_idx][1] - radius[ball_idx], min_y)
        max_x = max(balls[ball_idx][0] + radius[ball_idx], max_x)
        max_y = max(balls[ball_idx][1] + radius[ball_idx], max_y)

    plt.xlim(min(min_x, min_y) - offset, max(max_x, max_y) + offset)
    plt.ylim(min(min_x, min_y) - offset, max(max_x, max_y) + offset)

    plt.savefig("Plots/BT_balls.png", dpi = 300)
    print("Plotted balls of the Ball Tree")

    plt.close()

plot_map()
plot_KD_map()
plot_BT_map()
plot_comparison_map()
plot_divisions()
plot_balls()