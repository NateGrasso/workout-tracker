//
//  main.cpp
//  WorkoutTracker.cpp
//
//  Created by Nathan Grasso on 3/27/21.
//  Purpose: To record workout information. Program will access, save, and calculate data using user inputs and past inputs.
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>   // vector arrays because my array size is dynamic
#include <numeric> // for summation of vectors
using namespace :: std;


int setTotal = 0, exerciseTotal = 0, totalWeight= 0, reps=0, weight=0, exerciseCount = 1,  set = 1, start = 0; //#4
string date, exerciseName, line; //#4
char nextSet, nextExercise; //#4
const char SENTINEL = 'q'; //#4 #9

vector <int> setTotalArray; //#5
vector <int> exerciseTotalArray; //#5

ofstream out_workouts; //#4
ifstream in_workouts; //#4

int main()
{   // main menu, prompt for options, specify start values
    cout << "Welcome to your Workout Tracker!" << endl;
    cout << '\n' << "To start a new workout, enter a 1." << endl;
    cout << "To view a previous workout, enter a 2." << endl;
    cout << '\n' <<"Option: ";
    cin >> start;
    cout << '\n';
    
    switch(start) // main structure of program #9 #8
    {
        case 1: //collects user input, opens and appends calculated input to a file, outputs weight totals #3,#5,#8,#9
            out_workouts.open ("workouts.txt", fstream :: app);                                       // open file and append so the file is not overwritten #6
            cout << '\n' << "Please enter the date: ";
            cin >> date;
            cout << "\n";
            out_workouts << "Date: " << date << endl;
           
            while (nextExercise != SENTINEL)
            {
                cout << "Exercise " << exerciseCount << ": ";
                cin.ignore (1, '\n');                                                                // remove new line character from input stream
                getline(cin, exerciseName);                                                          // read string
                out_workouts << "Exercise: " << exerciseName << endl;
                exerciseCount += 1;
                
                
                while (nextSet != SENTINEL)
                {
                    cout << "Set " << set << "\n";
                    out_workouts << "Set " << set << endl;
                    cout << "Reps: ";
                    cin >> reps;
                    out_workouts << "Reps: " << reps << endl;
                    cout << "Weight: ";
                    cin >> weight;
                    out_workouts << "Weight: " << weight << " lbs" << endl;
                    cout << "\n";
                        setTotal = (reps * weight);                                                  // calculate set total
                        setTotalArray.push_back(setTotal);                                           //ADD to vector
                        cout << "You moved " << setTotal << " lbs this set!" <<  "\n";
                    setTotal = 0;
                    cout << "\n" << "n for next set or q to finish: ";
                    cin >> nextSet;
                        set += 1;                                                                    // increment set value
                    cout << "\n";
                    if (nextSet == SENTINEL)
                    {
                        exerciseTotal = accumulate(setTotalArray.begin(), setTotalArray.end(),0);   //sum elements in vector
                        exerciseTotalArray.push_back(exerciseTotal);                                // ADD to total to vector
                        exerciseTotal = 0;
                        setTotalArray.clear();                                                      //clear vector for next exercise
                    }
                }
                nextSet = ' ';
                set = 1;
                cout << "n for next exercise or q to finish workout: ";
                cin >> nextExercise;
                cout << "\n";
                if (nextExercise == SENTINEL)
                {
                    totalWeight = accumulate(exerciseTotalArray.begin(), exerciseTotalArray.end(), 0); // sum elements in vector
                    cout << "You moved " << totalWeight << "lbs this workout! Great Job!" << endl;
                    out_workouts << "Total weight moved: " << totalWeight << " lbs" << endl;
                    out_workouts.close();                                                              // close file
                }
            }
            break;
        
        case 2: //Opens and read txt file and outputs read data to screen #9,#6,#3
            in_workouts.open("workouts.txt");
                
            if (in_workouts.is_open())
            {
                while (getline(in_workouts,line))
                {
                cout << line << endl;
                }
                in_workouts.close();
            }
            else
            {
                cout << "file not found.";
            }
                break;
        default: // Gives an error code if non-valid input is entered #9
            cout << "Not a valid option." << '\n';
                break;
    }
return 0;
}

