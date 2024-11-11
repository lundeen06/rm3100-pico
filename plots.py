import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def plot_magnetic_fields(csv_file):
    # Read the CSV file
    df = pd.read_csv(csv_file)
    
    # Convert timestamp to seconds for better readability
    df['Time(s)'] = (df['Timestamp(ms)'] - df['Timestamp(ms)'].iloc[0]) / 1000.0
    
    # Calculate means and store them
    means = {}
    for column in ['M(µT)', 'M_x(µT)', 'M_y(µT)', 'M_z(µT)']:
        means[column] = df[column].mean()
    
    # Save means to text file
    filename = csv_file.split('/')[-1].replace('.csv', '_means.txt')
    output_path = f'./analysis/means/{filename}'
    
    with open(output_path, 'w') as f:
        f.write("Mean Values for Magnetic Field Components\n")
        f.write("=======================================\n\n")
        for component, mean_value in means.items():
            f.write(f"{component}: {mean_value:.2f} µT\n")
    
    # Print some basic statistics
    print("\nStatistics:")
    print("-----------------")
    for column in ['M(µT)', 'M_x(µT)', 'M_y(µT)', 'M_z(µT)']:
        print(f"\n{column}:")
        print(f"Mean: {df[column].mean():.2f} µT")
        print(f"Min: {df[column].min():.2f} µT")
        print(f"Max: {df[column].max():.2f} µT")
        print(f"Std Dev: {df[column].std():.2f} µT")
    
    # Create a figure with subplots
    fig, axs = plt.subplots(4, 1, figsize=(12, 10), sharex=True)
    fig.suptitle('Magnetic Field Components vs Time', fontsize=16)
    
    # Plot Magnitude
    axs[0].plot(df['Time(s)'], df['M(µT)'], 'k-', label='M')
    axs[0].set_xlabel('Time (s)')
    axs[0].set_ylabel('M (µT)')
    axs[0].grid(True)
    axs[0].legend()
    
    # Plot M_x
    axs[1].plot(df['Time(s)'], df['M_x(µT)'], 'b-', label='M_x')
    axs[1].set_ylabel('M_x (µT)')
    axs[1].grid(True)
    axs[1].legend()
    
    # Plot M_y
    axs[2].plot(df['Time(s)'], df['M_y(µT)'], 'g-', label='M_y')
    axs[2].set_ylabel('M_y (µT)')
    axs[2].grid(True)
    axs[2].legend()
    
    # Plot M_z
    axs[3].plot(df['Time(s)'], df['M_z(µT)'], 'r-', label='M_z')
    axs[3].set_ylabel('M_z (µT)')
    axs[3].grid(True)
    axs[3].legend()
    
    # Adjust layout to prevent overlap
    plt.tight_layout()
    
    # Save the plot
    # plt.savefig('./output/plot.png', dpi=500, bbox_inches='tight')
    
    # Show the plot
    plt.show()

# Example usage
if __name__ == "__main__":
    # Replace 'your_data.csv' with your actual CSV file name
    plot_magnetic_fields('./output/A-1.csv')
    plot_magnetic_fields('./output/A-2.csv')
    plot_magnetic_fields('./output/O5-1.csv')
    plot_magnetic_fields('./output/O10-1.csv')
    plot_magnetic_fields('./output/I5-1.csv')
    plot_magnetic_fields('./output/I10-1.csv')
    plot_magnetic_fields('./output/O5-2.csv')
    plot_magnetic_fields('./output/O10-2.csv')
    plot_magnetic_fields('./output/I5-2.csv')
    plot_magnetic_fields('./output/I10-2.csv')