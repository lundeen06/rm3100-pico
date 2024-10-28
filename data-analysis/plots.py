import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def plot_magnetic_fields(csv_file):
    # Read the CSV file
    df = pd.read_csv(csv_file)
    
    # Convert timestamp to seconds for better readability
    df['Time(s)'] = (df['Timestamp(ms)'] - df['Timestamp(ms)'].iloc[0]) / 1000.0
    
    # Create a figure with subplots
    fig, axs = plt.subplots(4, 1, figsize=(12, 10), sharex=True)
    fig.suptitle('Magnetic Field Components vs Time', fontsize=16)
    
    # Plot M_x
    axs[0].plot(df['Time(s)'], df['M_x(µT)'], 'b-', label='M_x')
    axs[0].set_ylabel('M_x (µT)')
    axs[0].grid(True)
    axs[0].legend()
    
    # Plot M_y
    axs[1].plot(df['Time(s)'], df['M_y(µT)'], 'g-', label='M_y')
    axs[1].set_ylabel('M_y (µT)')
    axs[1].grid(True)
    axs[1].legend()
    
    # Plot M_z
    axs[2].plot(df['Time(s)'], df['M_z(µT)'], 'r-', label='M_z')
    axs[2].set_ylabel('M_z (µT)')
    axs[2].grid(True)
    axs[2].legend()
    
    # Plot Magnitude
    axs[3].plot(df['Time(s)'], df['M(µT)'], 'k-', label='M')
    axs[3].set_xlabel('Time (s)')
    axs[3].set_ylabel('M (µT)')
    axs[3].grid(True)
    axs[3].legend()
    
    # Adjust layout to prevent overlap
    plt.tight_layout()
    
    # Save the plot
    plt.savefig('magnetic_field_plots.png', dpi=300, bbox_inches='tight')
    
    # Show the plot
    plt.show()
    
    # Print some basic statistics
    print("\nBasic Statistics:")
    print("-----------------")
    for column in ['M_x(µT)', 'M_y(µT)', 'M_z(µT)', 'M(µT)']:
        print(f"\n{column}:")
        print(f"Mean: {df[column].mean():.2f} µT")
        print(f"Min: {df[column].min():.2f} µT")
        print(f"Max: {df[column].max():.2f} µT")
        print(f"Std Dev: {df[column].std():.2f} µT")

# Example usage
if __name__ == "__main__":
    # Replace 'your_data.csv' with your actual CSV file name
    plot_magnetic_fields('./output/magnetometer_data.csv')