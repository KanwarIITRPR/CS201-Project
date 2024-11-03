import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

# File paths for input data
house_location_file = "Data/house_location.txt"
hospital_location_file = "Data/hospital_location.txt"
parameters_file = "Data/map_parameters.txt"
KD_results_file = "Data/results_KD.txt"
BT_results_file = "Data/results_BT.txt"
divisions_file = "Data/KD_divisions.txt"
balls_file = "Data/BT_balls.txt"

# Function to extract parameters from the parameters file
def extractParameters():
    parameters_list = []
    with open(parameters_file, "r") as file:
        # Read each line, remove newline, and convert to int
        parameters_list = list(map(lambda x: int(x.removesuffix("\n")), file.readlines()))
    
    return parameters_list

# Function to extract house locations from the file
def extractHouses():
    contents = []
    with open(house_location_file, "r") as file:
        # Convert each line to a list of floats representing house coordinates
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))
    
    return contents

# Function to extract hospital locations from the file
def extractHospitals():
    contents = []
    with open(hospital_location_file, "r") as file:
        # Convert each line to a list of floats representing hospital coordinates
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))
    
    return contents

# Function to extract results from the K-Dimensional Tree algorithm
def extractKDResults():
    contents = []
    with open(KD_results_file, "r") as file:
        # Convert each line to a list of floats representing results
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))
    
    return contents

# Function to extract results from the Ball Tree algorithm
def extractBTResults():
    contents = []
    with open(BT_results_file, "r") as file:
        # Convert each line to a list of floats representing results
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))
    
    return contents

# Function to extract hospital division data from the divisions file
def extractDivisions(dimensions):
    contents = []
    with open(divisions_file, "r") as file:
        # Convert each line to a list of floats representing divisions
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))

    points, lower_constraints, upper_constraints, depths = [], [], [], []
    for hospital in contents:
        # Split the hospital data into points, constraints, and depth
        points.append(hospital[:dimensions])
        lower_constraints.append(hospital[dimensions:2 * dimensions])
        upper_constraints.append(hospital[2 * dimensions:3 * dimensions])
        depths.append(hospital[-1])
    
    return points, lower_constraints, upper_constraints, depths

# Function to extract balls data from the balls file
def extractBalls():
    contents = []
    with open(balls_file, "r") as file:
        # Convert each line to a list of floats representing ball data
        contents = list(map(lambda x: list(map(lambda y: float(y), x.removesuffix("\n").strip().split(" "))), file.readlines()))

    points, radius, depths = [], [], []
    for hospital in contents:
        # Split the hospital data into points, radius, and depth
        points.append(hospital[:-2])
        radius.append(hospital[-2])
        depths.append(hospital[-1])

    return points, radius, depths

# Extract data from files
houses = extractHouses()
hospitals = extractHospitals()
results_KD = extractKDResults()
results_BT = extractBTResults()

# Extract division and ball data
nodes, lower_constraints, upper_constraints, node_depths = extractDivisions(len(hospitals[0]))
balls, radius, ball_depths = extractBalls()

# Get the size of the map
map_size = extractParameters()[0]
offset = 2  # Offset for visualizing the map

# Function to create the basic location map of houses and hospitals
def location_map():
    plt.figure(figsize=(10, 10))
    # Plot houses as blue circles
    plt.scatter(list(map(lambda x: x[0], houses)), list(map(lambda x: x[1], houses)), c="blue", marker="o", s=30, label="Houses")
    # Plot hospitals as red triangles
    plt.scatter(list(map(lambda x: x[0], hospitals)), list(map(lambda x: x[1], hospitals)), c="red", marker="^", s=100, label="Hospitals")
    # Draw a bounding box around the map area
    plt.plot([0, 0, map_size, map_size, 0], [0, map_size, map_size, 0, 0], c="black", linestyle="--", linewidth=2, alpha=0.2)

    # Set labels and limits for the axes
    plt.xlabel("x coordinate (km)")
    plt.ylabel("y Coordinate (km)")
    plt.xlim(-offset, map_size + offset)
    plt.ylim(-offset, map_size + offset)
    plt.grid(False)
    plt.legend()

# Function to save the basic location map as an image
def plot_map():
    location_map()
    plt.title(f"Hospital and House Locations on a ${map_size}\\times{map_size}\;km$ Map")

    plt.savefig("Plots/map.png", dpi=300)  # Save the figure as a PNG
    print("Plotted Map")

    plt.close()  # Close the current figure

# Function to plot the K-Dimensional Tree results
def plot_KD_map():
    location_map()
    plt.title(f"Mapping Houses to nearest hospitals using K-Dimensional Trees")
    for house_idx in range(len(houses)):
        # Draw dashed lines from houses to their nearest hospitals
        plt.plot([houses[house_idx][0], results_KD[house_idx][0]], [houses[house_idx][1], results_KD[house_idx][1]], c="orange", linestyle="--")

    plt.savefig("Plots/KD_map.png", dpi=300)  # Save the figure as a PNG
    print("Plotted K-Dimensional Tree's results")

    plt.close()  # Close the current figure

# Function to plot the Ball Tree results
def plot_BT_map():
    location_map()
    plt.title(f"Mapping Houses to nearest hospitals using Ball Trees")
    for house_idx in range(len(houses)):
        # Draw dotted lines from houses to their nearest hospitals
        plt.plot([houses[house_idx][0], results_BT[house_idx][0]], [houses[house_idx][1], results_BT[house_idx][1]], c="magenta", linestyle=":")

    plt.savefig("Plots/BT_map.png", dpi=300)  # Save the figure as a PNG
    print("Plotted Ball Tree's results")

    plt.close()  # Close the current figure

# Function to compare K-Dimensional Tree and Ball Tree results
def plot_comparison_map():
    location_map()
    plt.title(f"Comparing results of K-Dimensional Trees and Ball Trees")
    plt.plot([houses[0][0], results_KD[0][0]], [houses[0][1], results_KD[0][1]], c="purple", linestyle="--", label="Same")
    for house_idx in range(1, len(houses)):
        # Draw lines for houses to K-D results
        plt.plot([houses[house_idx][0], results_KD[house_idx][0]], [houses[house_idx][1], results_KD[house_idx][1]], c="purple", linestyle="--")

    common_indices = []
    for house_idx in range(len(houses)):
        # Identify common indices where the results differ
        if (not(results_KD[house_idx][0] == results_BT[house_idx][0] and results_KD[house_idx][1] == results_BT[house_idx][1])):
            common_indices.append(house_idx)

    if len(common_indices) > 0:
        plt.plot([houses[0][0], results_KD[0][0]], [houses[0][1], results_KD[0][1]], c="green", linestyle="-.", label="Different")
    for common_idx in common_indices:
        # Draw lines for different results
        plt.plot([houses[common_idx][0], results_KD[common_idx][0]], [houses[common_idx][1], results_KD[common_idx][1]], c="green", linestyle="-.")
        plt.plot([houses[common_idx][0], results_BT[common_idx][0]], [houses[common_idx][1], results_BT[common_idx][1]], c="green", linestyle="-.")

    plt.legend()
    plt.savefig("Plots/comparison_map.png", dpi=300)  # Save the figure as a PNG
    print("Plotted K-Dimensional Tree's and Ball Tree's comparison")
        
    plt.close()  # Close the current figure

# Function to plot divisions made by the K-Dimensional Tree
def plot_divisions():
    location_map()
    plt.title(f"Plotting divisions made in K-Dimensional Trees")
    for idx in range(len(nodes)):
        # Plot lines for divisions
        plt.plot([nodes[idx][0] - 0.5, nodes[idx][0] + 0.5], [lower_constraints[idx][1], lower_constraints[idx][1]], c="black", linestyle="--")
        plt.plot([nodes[idx][0] - 0.5, nodes[idx][0] + 0.5], [upper_constraints[idx][1], upper_constraints[idx][1]], c="black", linestyle="--")
    
    plt.savefig("Plots/KD_divisions.png", dpi=300)  # Save the figure as a PNG
    print("Plotted K-D divisions made by K-D Trees")

    plt.close()  # Close the current figure

# Function to plot balls made by the Ball Tree
def plot_balls():
    location_map()
    plt.title(f"Plotting balls made in Ball Trees")
    for idx in range(len(balls)):
        # Create a circle for each ball
        ball = patches.Circle(balls[idx], radius[idx], alpha=0.1, color='green', label='Balls')
        plt.gca().add_patch(ball)
    
    plt.savefig("Plots/BT_balls.png", dpi=300)  # Save the figure as a PNG
    print("Plotted balls made by Ball Trees")
    
    plt.close()  # Close the current figure

# Call the plotting functions to generate the maps
plot_map()  # Plot the basic map
plot_KD_map()  # Plot the K-Dimensional Tree results
plot_BT_map()  # Plot the Ball Tree results
plot_comparison_map()  # Compare K-Dimensional Tree and Ball Tree results
plot_divisions()  # Plot K-D divisions
plot_balls()  # Plot balls made by Ball Trees
