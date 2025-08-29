# Drone Flight Controller Monitor

A Qt6/QML-based single-page dashboard for drone flight controller monitoring, PID tuning, and real-time telemetry visualization.

## Overview

This application provides a comprehensive yet simple drone monitoring interface designed for ease of use. Everything is accessible from a single page dashboard, making it perfect for real-time flight monitoring, PID parameter adjustment, and telemetry analysis.

## Key Features

### 🚁 Real-Time Drone Monitoring
- **Flight Status Dashboard**: Live connection status, battery level, altitude, and speed
- **Flight Instruments**: Essential flight parameters display
- **3D Orientation Viewer**: Real-time drone attitude visualization
- **Status Indicators**: Visual feedback for all critical systems

### 📈 Telemetry & Data Visualization
- **Real-Time Oscilloscope**: Large format chart for monitoring multiple telemetry channels
- **Multi-channel Support**: Simultaneous visualization of flight data streams
- **Adjustable Time Scales**: 0.1s to 10s per division for detailed analysis
- **Variable Amplitude Scaling**: Customizable range from 0.1 to 10 units per division

### ⚙️ PID Tuning Interface
- **Live PID Adjustment**: Real-time tuning of flight controller parameters
- **Parameter Monitoring**: Visual feedback of PID adjustments
- **Easy Controls**: Simple interface for precise parameter modification

### 🎮 Manual Flight Control
- **Dual Joystick Interface**: 
  - Left stick: Throttle and Yaw control
  - Right stick: Pitch and Roll control
- **Emergency Controls**: Quick access emergency stop button
- **Auto-Land Function**: One-click automatic landing

### 📡 Communication
- **Protocol Console**: Direct communication with flight controller
- **Telemetry Stream**: Real-time data reception and display
- **Command Interface**: Send commands to drone systems

## Design Philosophy

### Simple Single-Page Layout
- **Everything Visible**: All functions accessible without navigation
- **Optimized Grid Layout**: Professional 4x3 grid organization
- **Minimal Learning Curve**: Intuitive interface design
- **Quick Access**: All controls within immediate reach

### Professional Flight Operations
- **Dark Theme**: Reduced eye strain during extended monitoring
- **Clear Status Indicators**: Immediate system status awareness
- **Organized Layout**: Logical grouping of related functions
- **Responsive Design**: Works on various screen sizes (minimum 1200x800)

## Technical Specifications

### System Requirements
- **Qt Framework**: Qt 6.8 or higher
- **Graphics**: OpenGL support recommended
- **Platform**: Windows, macOS, Linux
- **Screen**: Minimum 1200x800 resolution

### Core Dependencies
- Qt6 Core, Widgets, Gui
- Qt6 Qml, Quick, QuickControls2
- Qt6 Charts (for oscilloscope)

## Quick Start

### Building the Application
```bash
# Clone the repository
git clone https://github.com/muvx2531/FlightTools.git
cd FlightTools/Flight

# Build with CMake
mkdir build && cd build
cmake ..
cmake --build .

# Run the application
./appFlight
```

### For Optimal Performance
Set OpenGL backend (recommended):
```bash
export QSG_RHI_BACKEND=opengl
```

## Dashboard Layout

```
┌─────────────────────────────────────────────────────────┐
│ STATUS BAR: Flight Status | Battery | Altitude | Time   │
├─────────────┬──────────────┬─────────────┬──────────────┤
│ Flight      │ Flight       │ 3D          │ Manual       │
│ Instruments │ Instruments  │ Orientation │ Controls     │
│             │              │             │ (Joysticks)  │
├─────────────┼──────────────┴─────────────┴──────────────┤
│ PID         │ Real-Time Oscilloscope                    │
│ Adjustment  │ (Telemetry Visualization)                 │
│ Panel       │                                           │
├─────────────┴───────────────────────────────────────────┤
│ Protocol Console (Communication Interface)               │
└─────────────────────────────────────────────────────────┘
```

## Component Overview

- **`Main.qml`**: Single-page dashboard layout and coordination
- **`FlightInstument.qml`**: Flight parameter display component
- **`Plot3DOrientation.qml`**: 3D drone attitude visualization  
- **`Joystick.qml`**: Manual flight control interface
- **`PIDadjustmentPanel.qml`**: Real-time PID tuning controls
- **`RealtimeOscilloscope.qml`**: Multi-channel telemetry display
- **`ProtocolConsole.qml`**: Communication and command interface

## Usage

1. **Launch Application**: Start the dashboard to see all monitoring tools
2. **Monitor Flight**: Watch real-time telemetry in the oscilloscope
3. **Adjust PID**: Fine-tune controller parameters using the left panel
4. **Manual Control**: Use joysticks for direct flight control when needed
5. **Emergency**: Access emergency controls in the top-right section

## Target Users

- **Drone Pilots**: Real-time flight monitoring and control
- **Engineers**: PID tuning and system analysis
- **Researchers**: Telemetry analysis and data collection
- **Hobbyists**: Easy-to-use flight monitoring interface

## Development Status

This is an active Qt6/QML project focused on providing a simple, effective drone monitoring solution. The single-page design ensures all critical functions are immediately accessible without complex navigation.

---

**Repository**: https://github.com/muvx2531/FlightTools.git  
**License**: See repository for details