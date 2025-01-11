import csv
import re

# Define the input and output file paths
input_file = 'simulation_output.txt'
output_file = 'output_data.csv'

# Define the header for the CSV file
header = [
    'Year', 'Month', 'Temperature (°C)', 'Precipitation (cm)',
    'Grain Height (cm)', 'Number of Deer', 'Number of Predators'
]

# Open input file for reading and output file for writing
with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
    # Initialize a CSV writer with the defined header
    writer = csv.writer(outfile)
    writer.writerow(header)  # Write the header row to the CSV file

    # Regular expression patterns to extract numerical values
    patterns = {
        'Year': r'Year:\s+(\d+)',
        'Month': r'Month:\s+(\d+)',
        'Temperature': r'Temperature:\s+([\d.-]+)°C',
        'Precipitation': r'Precipitation:\s+([\d.]+)\s+cm',
        'Grain Height': r'Grain Height:\s+([\d.]+)\s+cm',
        'Number of Deer': r'Number of Deer:\s+(\d+)',
        'Number of Predators': r'Number of Predators:\s+(\d+)'
    }

    # Initialize variables to hold monthly data
    month_data = {}

    # Iterate through each line in the input file
    for line in infile:
        line = line.strip()  # Remove leading/trailing whitespace

        # Process each attribute using regular expressions
        for key, pattern in patterns.items():
            match = re.search(pattern, line)
            if match:
                month_data[key] = match.group(1)

        # Check if we have collected data for a full month
        if len(month_data) == len(patterns):  # All attributes collected
            # Convert necessary values to appropriate types
            month_data['Year'] = int(month_data['Year'])
            month_data['Month'] = int(month_data['Month'])
            month_data['Temperature (°C)'] = float(month_data['Temperature'])
            month_data['Precipitation (cm)'] = float(month_data['Precipitation'])
            month_data['Grain Height (cm)'] = float(month_data['Grain Height'])
            month_data['Number of Deer'] = int(month_data['Number of Deer'])
            month_data['Number of Predators'] = int(month_data['Number of Predators'])

            # Write data to CSV file
            writer.writerow([
                month_data['Year'], month_data['Month'],
                month_data['Temperature (°C)'], month_data['Precipitation (cm)'],
                month_data['Grain Height (cm)'], month_data['Number of Deer'],
                month_data['Number of Predators']
            ])

            # Clear the month data for the next iteration
            month_data.clear()

print(f"Conversion completed. CSV file saved to: {output_file}")
