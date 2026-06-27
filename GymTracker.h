//
//  GymTracker.h
//  SmartGymTracker
//
//  Created by Sebastian Alvarez on 6/27/25.
//

#ifndef GYMTRACKER_H
#define GYMTRACKER_H


#include <vector>
#include <utility>
#include <map>
#include <memory> // this has unique_ptr
#include "Workout.h"// most of the time only inlude the base class
using namespace std;

class GymTracker {
public:
    void deleteWorkout(int id) {
        auto it = history.find(id);//find by id in map if not found return maps end iterator
        if (it != history.end()) {
            history.erase(it);
            std::cout << "Workout with ID " << id << " deleted from memory.\n"; //delete workout from map if found
        } else {
            std::cout << "Workout ID not found.\n";//this if it isn't found
            return;
        }
        std::ofstream file("workout.txt", std::ios::trunc);
        if(!file.is_open()) return; //do this to avoid writing to a bad stream aka crash
        for(const auto& pair : history) {
            pair.second->logWorkoutToStream(file); //the object is a strengthWorkout which makes it able to use the method logWorkoutToStream.
        }
        file.close();
    }
    void addWorkout(unique_ptr<Workout> w) {
        w->logWorkout(); //logs the workout object
        history[nextId++] = std::move(w); //unique ptr has to get moved because it cannot be copied. history map increments the current nextId ex/ history[2] = std::move(w) now the pair is {2, w}
    }
    void displayAllWorkouts() const {
        for(const auto& pair : history) {
            std::cout << "Workout ID: " << pair.first << "\n";
            pair.second->displayWorkout(); //second is the strengthWorkout object so it has access to displayWorkout.
            std::cout << "\n";
        }
    }
    void loadFromFile() {
        ifstream file("workout.txt"); //open file workout.txt
        if(!file.is_open()) {
            return;               // if it doesn't open then skip everything
        }
        
        string line;
        
        while(getline(file, line)){ // getline takes in cin or ifstream and saves text to line. (optional delimeter so that it stops at a character instead of \n which is getline(cin, name, ',');
            if(line.empty()) continue; // continue to next iteration if empty
            if(line.find("Workout ID:") == 0) continue; // if it shows workout id move to next iteration
            
            string date, type, name;
            vector<int> reps;
            vector<float> weight;
            
            size_t firstComma = line.find(','); // size_t is an unsigned int used for indexes mostly
            size_t secondComma = line.find(',', firstComma + 1);
            size_t thirdComma = line.find(',', secondComma + 1);
            size_t setsPos = line.find(", Sets: ");
            if (firstComma == std::string::npos || secondComma == std::string::npos || thirdComma == std::string::npos) {
                continue;
            }
            
            date = line.substr(0, firstComma);
            type = line.substr(secondComma + 2, thirdComma - secondComma - 2); //reason for this is that the second argument is the length of the substring not an index.
            name = line.substr(thirdComma + 2, setsPos - thirdComma - 2); // this one just goes from third comma + 2 to the end of the string
            
             // returns the index of the first letter in the word.
            int numSets = stoi(line.substr(setsPos + 8)); //string to integer the sets
            
            for(int i = 0; i < numSets; ++i) {
                if (!getline(file, line)) break;  //if getline doesn't get a line then break the for loop.
                
                size_t colonPos = line.find(":");
                size_t repsPos = line.find(" reps of ");
                size_t lbsPos = line.find(" lbs");
                size_t ofPos = line.find("of");
                
                int r = stoi(line.substr(colonPos + 2, repsPos - colonPos - 2));
                float w = stof(line.substr(ofPos + 3, lbsPos - ofPos - 3 ));
                
                reps.push_back(r);
                weight.push_back(w);
            }
            auto w = make_unique<StrengthWorkout>(name, date, type, numSets, reps, weight);
            history[nextId++] = std::move(w);//only starts at 1 because of post-increment
        }
        file.close();
    }
    
    ~GymTracker() = default;
    
private:
    map<int,unique_ptr<Workout>> history; //map that takes in ints as the key and a unique pointer to a Workout object as the value, which gives fast access to each workout by ID its named history.
    int nextId = 1; // ID counter starting at 1
    
};
#endif
