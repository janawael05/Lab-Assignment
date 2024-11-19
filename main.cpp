#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <queue>
#include <vector>
using namespace std;

class Patient {
public:
    string id;
    char gender;
    string arrivalTime;
    bool isUrgent;
    int waitTime = 0;

    Patient(const string& id, char gender, const string& arrivalTime, bool isUrgent);

    bool operator<(const Patient& other) const;
};
Patient::Patient(const std::string& id, char gender, const std::string& arrivalTime, bool isUrgent)
        : id(id), gender(gender), arrivalTime(arrivalTime), isUrgent(isUrgent) {}

bool Patient::operator<(const Patient& other) const {
    if (isUrgent != other.isUrgent) {
        return !isUrgent;
    }
    return waitTime > other.waitTime;
}
class PatientScheduler {
private:
    priority_queue<Patient> urgentQueue;
    queue<Patient> normalQueue;
    vector<Patient> inService;
    vector<Patient> completedPatients;
    int maxServiceTime = 10;

public:
    void addPatient(const Patient& patient);
    void advanceTime(int timeStep);
    void servePatients();
    void displayQueues() const;
    void displayStatistics() const;
    int getUrgentQueueSize() const;
    int getNormalQueueSize() const;
    int
    () const;
};
void PatientScheduler::addPatient(const Patient& patient) {
    if (patient.isUrgent) {
        urgentQueue.push(patient);
    } else {
        normalQueue.push(patient);
    }
}

void PatientScheduler::advanceTime(int timeStep) {

    priority_queue<Patient> updatedUrgentQueue;
    while (!urgentQueue.empty()) {
        Patient patient = urgentQueue.top();
        urgentQueue.pop();
        patient.waitTime += timeStep;
        updatedUrgentQueue.push(patient);
    }
    urgentQueue = std::move(updatedUrgentQueue);

    queue<Patient> updatedNormalQueue;
    while (!normalQueue.empty()) {
        Patient patient = normalQueue.front();
        normalQueue.pop();
        patient.waitTime += timeStep;
        updatedNormalQueue.push(patient);
    }
    normalQueue = std::move(updatedNormalQueue);


    for (auto it = inService.begin(); it != inService.end();) {
        it->waitTime -= timeStep;
        if (it->waitTime <= 0) {
            completedPatients.push_back(*it);
            it = inService.erase(it);
        } else {
            ++it;
        }
    }
}

void PatientScheduler::servePatients() {
    try {
        if (inService.empty()) {
            if (!urgentQueue.empty()) {
                Patient patient = urgentQueue.top();
                urgentQueue.pop();
                patient.waitTime = maxServiceTime;
                inService.push_back(patient);
            } else if (!normalQueue.empty()) {
                Patient patient = normalQueue.front();
                normalQueue.pop();
                patient.waitTime = maxServiceTime;
                inService.push_back(patient);
            } else {
                throw underflow_error("No patients available to serve! Both queues are empty.");
            }
        }
    } catch (const underflow_error &e) {
        cout << "Underflow Error in servePatients: " << e.what() << endl;
    } catch (const exception &e) {
        cout << "Unexpected Error in servePatients: " << e.what() << endl;
    }
}


    void PatientScheduler::displayQueues() const {
        cout << "Waiting Urgent Patients: ";
        priority_queue<Patient> tempUrgentQueue = urgentQueue;
        while (!tempUrgentQueue.empty()) {
            cout << tempUrgentQueue.top().id << " ";
            tempUrgentQueue.pop();
        }
        cout << "\n";

        cout << "Waiting Normal Patients: ";
        queue<Patient> tempNormalQueue = normalQueue;
        while (!tempNormalQueue.empty()) {
            cout << tempNormalQueue.front().id << " ";
            tempNormalQueue.pop();
        }
        cout << "\n";

        cout << "In-Service Patients: ";
        for (const auto &patient: inService) {
            cout << patient.id << " ";
        }
        cout << "\n";

        cout << "Completed Patients: ";
        for (const auto &patient: completedPatients) {
            cout << patient.id << " ";
        }
        cout << "\n";
    }


void PatientScheduler::displayStatistics() const {
    cout << "Simulation Statistics:\n";
    cout << "Total Patients Served: " << completedPatients.size() << "\n";
    cout << "Total Urgent Patients: "
         << count_if(completedPatients.begin(), completedPatients.end(),
                     [](const Patient& p) { return p.isUrgent; })
         << "\n";
    cout << "Total Normal Patients: "
         << count_if(completedPatients.begin(), completedPatients.end(),
                     [](const Patient& p) { return !p.isUrgent; })
         << "\n";
}
int PatientScheduler::getUrgentQueueSize() const {
    return urgentQueue.size();
}

int PatientScheduler::getNormalQueueSize() const {
    return normalQueue.size();
}

int PatientScheduler::getInServiceSize() const {
    return inService.size();
}
