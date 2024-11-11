import numpy as np
import re
import glob
import os

def read_means_from_file(filename):
    """
    Read magnetic field means from the formatted txt file.
    Returns dictionary of components in µT.
    """
    means = {}
    with open(filename, 'r') as f:
        lines = f.readlines()
        for line in lines:
            match = re.match(r'(M(?:_[xyz])?\(µT\)): ([-\d.]+) µT', line)
            if match:
                component = match.group(1)
                value = float(match.group(2))
                means[component] = value
    return means

def get_distance_from_filename(filename):
    """Extract distance in meters from filename."""
    if '5' in os.path.basename(filename):
        return 0.05
    elif '10' in os.path.basename(filename):
        return 0.10
    else:
        raise ValueError(f"Could not determine distance from filename: {filename}")

def check_sensor_orientation(field_values):
    """
    Check if sensor orientation makes sense:
    - X should be largest for horizontal field
    - Z should be largest for vertical field
    Returns warning message if orientation seems wrong
    """
    warnings = []
    x, y, z = abs(field_values['M_x(µT)']), abs(field_values['M_y(µT)']), abs(field_values['M_z(µT)'])
    
    # Check if X is dominant (horizontal field should be mainly in X)
    if x < y or x < z:
        warnings.append("WARNING: X-component is not dominant. Sensor may not be oriented correctly!")
        warnings.append(f"Field components (µT) - X: {x:.1f}, Y: {y:.1f}, Z: {z:.1f}")
    
    return warnings

def calculate_magnetic_moment(observed_file, ambient_files, distance, output_file):
    """Calculate magnetic moment using averaged ambient field."""
    
    # Read observed field
    observed_means = read_means_from_file(observed_file)
    
    # Read and average ambient fields
    ambient_fields = []
    for amb_file in ambient_files:
        means = read_means_from_file(amb_file)
        field = np.array([means['M_x(µT)'], means['M_y(µT)'], means['M_z(µT)']]) 
        ambient_fields.append(field)
    
    avg_ambient = np.mean(ambient_fields, axis=0)
    ambient_std = np.std(ambient_fields, axis=0)
    
    # Check sensor orientation
    orientation_warnings = check_sensor_orientation(observed_means)
    
    # Extract components and convert from µT to T
    observed_field = np.array([
        observed_means['M_x(µT)'],
        observed_means['M_y(µT)'],
        observed_means['M_z(µT)']
    ]) * 1e-6  # Convert µT to T

    # Calculate net field vector using averaged ambient
    B_net = observed_field - (avg_ambient * 1e-6)
    B_net_magnitude_T = np.linalg.norm(B_net)

    # Calculate magnetic moment
    mu_0 = 4 * np.pi * 1e-7  # Permeability of free space in H/m
    r_cubed = distance**3
    moment_magnitude = (4 * np.pi * r_cubed * B_net_magnitude_T) / mu_0

    # Save results
    with open(output_file, 'w') as f:
        # Write any orientation warnings first
        if orientation_warnings:
            f.write("ORIENTATION WARNINGS\n")
            f.write("===================\n")
            for warning in orientation_warnings:
                f.write(f"{warning}\n")
            f.write("\n")

        f.write(f"Analysis Report\n")
        f.write(f"Distance: {distance*100:.1f} cm\n")
        f.write("="*50 + "\n\n")
        
        f.write("Observed Fields:\n")
        for component, value in observed_means.items():
            f.write(f"{component}: {value:.2f} µT\n")
        
        f.write("\nAmbient Fields (averaged):\n")
        components = ['M_x(µT)', 'M_y(µT)', 'M_z(µT)']
        for i, comp in enumerate(components):
            f.write(f"{comp}: {avg_ambient[i]:.2f} ± {ambient_std[i]:.2f} µT\n")
        
        f.write("\nNet Field\n")
        f.write("=========\n")
        f.write(f"Net field vector (µT): [{B_net[0]*1e6:.2f}, {B_net[1]*1e6:.2f}, {B_net[2]*1e6:.2f}]\n")
        f.write(f"Net field magnitude: {B_net_magnitude_T*1e6:.2f} µT\n\n")
        
        f.write("Calculated Magnetic Moment\n")
        f.write("========================\n")
        f.write(f"Moment magnitude: {moment_magnitude:.2e} A⋅m²\n")

def process_all_files(base_dir='./analysis/means/'):
    """Process all measurement files with averaged ambient field."""
    
    means_files = glob.glob(os.path.join(base_dir, '[!A]*_means.txt'))
    ambient_files = [
        os.path.join(base_dir, 'A-1_means.txt'),
        os.path.join(base_dir, 'A-2_means.txt')
    ]
    
    output_dir = os.path.dirname(os.path.dirname(base_dir))
    
    for observed_file in means_files:
        print(f"\nProcessing {os.path.basename(observed_file)}...")
        
        try:
            distance = get_distance_from_filename(observed_file)
            print(f"  Detected distance: {distance*100:.1f} cm")
        except ValueError as e:
            print(f"Error: {e}")
            continue
        
        # Generate single output file
        output_name = os.path.basename(observed_file).replace('_means.txt', '_analysis.txt')
        output_file = os.path.join(output_dir, output_name)
        
        calculate_magnetic_moment(
            observed_file,
            ambient_files,
            distance,
            output_file
        )
        print(f"  Analysis saved to {output_name}")

if __name__ == "__main__":
    process_all_files()