import csv
import re

# Input data in the specified format
data = [
    "1024    N     362.04    S    1776.27    (  4.91)        N     362.52    S    1787.82    (  4.93)",
    "2048    N     308.12    S    2088.34    (  6.78)        N     320.79    S    2122.61    (  6.62)",
    "4096    N     358.99    S    1942.60    (  5.41)        N     363.99    S    1795.12    (  4.93)",
    "8192    N     357.96    S    1967.81    (  5.50)        N     364.73    S    2070.64    (  5.68)",
    "16384    N     355.80    S    1724.22    (  4.85)        N     365.04    S    2030.73    (  5.56)",
    "32768    N     358.47    S    1717.57    (  4.79)        N     365.29    S    1880.61    (  5.15)",
    "65536    N     356.61    S    1930.13    (  5.41)        N     365.39    S    2044.47    (  5.60)",
    "131072    N     356.45    S    1751.95    (  4.91)        N     364.98    S    2021.92    (  5.54)",
    "262144    N     350.14    S    1741.38    (  4.97)        N     364.99    S    1810.27    (  4.96)",
    "524288    N     350.75    S    1736.92    (  4.95)        N     363.00    S    1835.04    (  5.06)",
    "1048576    N     333.28    S    1270.86    (  3.81)        N     352.06    S    1653.52    (  4.70)",
    "2097152    N     336.55    S     856.51    (  2.54)        N     354.78    S    1206.14    (  3.40)",
    "4194304    N     337.12    S     791.12    (  2.35)        N     350.96    S    1031.10    (  2.94)",
    "8000000    N     329.61    S     766.53    (  2.33)        N     351.92    S     935.06    (  2.66)"
]

# Output CSV file
output_csv = "output.csv"

# Open CSV file for writing
with open(output_csv, 'w', newline='') as csvfile:
    # Initialize CSV writer
    writer = csv.writer(csvfile)

    # Write header row
    writer.writerow(['ARRAYSIZE', 'NTime', 'NPerformance', 'Speedup', 'STime', 'SPerformance', 'Speedup'])

    # Regular expression pattern to match numbers and decimal points
    num_pattern = r'[-+]?\d*\.\d+|\d+'

    # Process each line of input data
    for line in data:
        # Use regex to find all numeric values in the line
        values = re.findall(num_pattern, line)

        try:
            # Extract relevant numeric values based on their position in the line
            array_size = int(values[0])
            n_time = float(values[1])
            n_performance = float(values[2])
            s_time = float(values[3])
            s_performance = float(values[4])
            speedup = float(values[5])  # Speedup is the same for both N and S

            # Write row to CSV file with the desired column order
            writer.writerow([array_size, n_time, n_performance, speedup, s_time, s_performance, speedup])

        except (IndexError, ValueError) as e:
            # Handle errors gracefully (e.g., missing or invalid data)
            print(f"Error processing line: {line}")
            print(e)

print(f"CSV file '{output_csv}' created successfully.")