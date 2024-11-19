Patient Scheduling Simulation System
This project simulates a healthcare scheduling system that prioritizes and processes patients based on urgency. It employs a queue-based model to manage urgent and normal patients, simulating real-world scenarios in patient management and healthcare workflows.
System Requirements:
Operating System: Windows, macOS, or Linux
Compiler: A C++ compiler supporting C++11 or later (e.g., GCC, Clang, or MSVC)
Development Environment: Any IDE with C++ support (e.g., Visual Studio, CLion, or Code::Blocks)
Additional Tools:
make (for Linux/macOS systems)
Project Structure
Files and Classes:
main: Contains the implementation of the simulation system.
Patient: Represents a patient with attributes like ID, gender, arrival time, and urgency.
PatientScheduler: Manages the queues and patient servicing.
Simulation: Simulates the entire patient scheduling system.
Functional Highlights:
Urgent Queue Management: Handles patients requiring immediate attention.
Normal Queue Management: Manages non-urgent patients in a first-come, first-served manner.
In-Service Tracking: Tracks patients currently being served.
Statistics Generation: Displays simulation statistics, such as the total number of patients served.
Usage:
Start the Program: Run the compiled binary, which automatically populates 100 patients for simulation.
Simulation Flow:
Press Enter to advance the simulation by 10 minutes.
Observe patient queue updates and service completions.
At the end of the simulation, view detailed statistics including:
Total patients served.
Breakdown of urgent and normal patients.
