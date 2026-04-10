#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --- TOPIC: COMPOSITION ("Has-a" Relationship) ---
// A Robot is composed of a Controller. This is better than inheritance 
// because we might switch from a PID to a MPC controller at runtime.
class FlightController {
public:
    string firmware_version;
    FlightController(string v) : firmware_version(v) {}
};

class RobotInterface {
public:
    virtual void executeMission() = 0; // Pure Virtual - The "Contract"
    virtual void emergencyStop() = 0;
    virtual ~RobotInterface() {}
};

class BaseRobot : public RobotInterface {
protected:
    string callsign;
    int* telemetry_freq; // Pointer to demonstrate DEEP COPY for dynamic sensor data
    FlightController* fc; // COMPOSITION: The "Brain" of the robot

public:
    // --- TOPIC: PARAMETERIZED CONSTRUCTOR ---
    BaseRobot(string name, string firmware) {
        this->callsign = name;
        this->telemetry_freq = new int(50); // Default 50Hz for IMU sampling
        this->fc = new FlightController(firmware);
        cout << "[System]: Hardware Abstraction Layer (HAL) initialized for " << name << endl;
    }

    // --- TOPIC: DEEP COPY CONSTRUCTOR (Placement Gold! 🏆) ---
    // In Robotics, if you copy a Robot object, you must copy the SENSOR DATA 
    // to a new memory address. If you share the pointer (Shallow Copy), 
    // deleting one robot will break the telemetry of the other!
    BaseRobot(const BaseRobot &source) {
        this->callsign = source.callsign + "_BACKUP";
        this->telemetry_freq = new int(*source.telemetry_freq); // Deep Copy
        this->fc = new FlightController(source.fc->firmware_version); // Deep Copy
        cout << "[System]: Redundant Backup System Created: " << this->callsign << endl;
    }

    // --- TOPIC: FRIEND CLASS ---
    // In Robotics, 'CalibrationUnit' needs access to private Motor/IMU offsets 
    // without exposing them to the general user.
    friend class CalibrationUnit;

    virtual ~BaseRobot() {
        delete telemetry_freq; 
        delete fc;
        cout << "[System]: Resources released for " << callsign << endl;
    }
};

// --- TOPIC: FRIEND CLASS IMPLEMENTATION ---
class CalibrationUnit {
public:
    void calibrateSensors(BaseRobot &r) {
        cout << "[Calibration]: Tuning IMU for " << r.callsign << ". Setting sample rate to 100Hz." << endl;
        *r.telemetry_freq = 100; // Accessing protected members directly
    }
};

// --- TOPIC: INHERITANCE ---
class Quadcopter : public BaseRobot {
public:
    Quadcopter(string id) : BaseRobot(id, "ArduPilot-v4.5") {}

    // --- TOPIC: POLYMORPHISM (Function Overriding) ---
    void executeMission() override {
        cout << "[UAV " << callsign << "]: Mission Start. Arming 4 Brushless DC Motors." << endl;
    }

    void emergencyStop() override {
        cout << "[UAV " << callsign << "]: KILLED. Disarming all ESCs immediately." << endl;
    }

    ~Quadcopter() { cout << "Quadcopter Class Destructed. "; }
};

int main() {
    // --- TOPIC: DYNAMIC ALLOCATION (Heap) ---
    // Professional Robotics uses the Heap for large objects that persist throughout a mission.
    Quadcopter* mainDrone = new Quadcopter("Alpha-1");
    
    // Triggering DEEP COPY for a Redundant Backup system
    Quadcopter backupDrone = *mainDrone; 

    // Calibration using FRIEND access
    CalibrationUnit cal;
    cal.calibrateSensors(*mainDrone);

    mainDrone->executeMission();

    cout << "\n--- End of Mission ---" << endl;
    delete mainDrone; // Triggers Child -> Parent destructor chain

    return 0;
}