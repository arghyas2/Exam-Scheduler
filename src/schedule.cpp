/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    vector<vector<string>> to_return;
    string to_parse = file_to_string(filename);
    string line;
    // cout << to_parse << endl;
    stringstream s(to_parse);
    int index = 0;
    while (getline(s, line)) {
        vector<string> split_line;
        split_string(line, ',', split_line);
        for (auto& word : split_line) {
            word = trim(word);
        }
        to_return.push_back(split_line);
    } 
    // for (size_t i = 0; i < to_return.size(); i++) {
    //     for (size_t j = 0; j < to_return[i].size(); j++) {
    //         cout << to_return[i][j] << endl;
    //     }
    // }
    return to_return;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & sv){

    // student in roster but not registered privately
    vector<vector<string>> to_return(cv);
    for (size_t i = 0; i < to_return.size(); i++) {
        vector<string> line = to_return[i];
        for(size_t j = 1; j < to_return[i].size(); j++) {
            string course = line[0];
            string student  = line[j];
            if (studentEnrolled(student, sv, course) == false) {
                to_return[i][j] = "removeThis";
            }
        }
        to_return[i].erase(remove(to_return[i].begin(), to_return[i].end(), "removeThis"), to_return[i].end());
    }
    vector<vector<string>> return_correct;
    for (size_t i = 0; i < to_return.size(); i++) {
        if (to_return[i].size() > 1) {
            return_correct.push_back(to_return[i]);
        }
    }
    return return_correct;

    // // student registered privately but not on roster

    // for (size_t i = 0; i < sv.size(); i++) {
    //     for (size_t j = 1; j < sv[i].size(); j++) {
    //         vector<string> line = sv[i];
    //         string student = line[0];
    //         string course = line[j];
    //         if (inRoster(student, cv, course) == false) {
    //             line.erase(line.begin() + j); 
    //         }
    //     }
    // }

}

bool studentEnrolled(const string& student, const V2D & sv, const string& course) {
    // checks for student existing and being enrolled in the class 
    for (size_t i = 0; i < sv.size(); i++) {
        if (sv[i][0] == student) {
            auto result = find(sv[i].begin(), sv[i].end(), course);
            return result != sv[i].end(); 
        }
    }
    return false;
}

// bool inRoster(const string& student, const V2D & cv, const string& course) {
//     for (size_t i = 0; i < cv.size(); i++) {
//         if (cv[i][0] == course) {
//             auto result = find(cv[i].begin(), cv[i].end(), student);
//             return result != cv[i].end();
//         }
//     }
//     return false;
// }

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    unordered_map<string, vector<string>> graph = constructGraph(courses);
    printGraph(graph);
    unordered_map<string, size_t> color_labels;
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        color_labels = color(it->first, graph, timeslots.size());
        if (!color_labels.empty()) {
            break;
        }
    }
    if (color_labels.empty()) {
        V2D to_return = {{"-1"}};
        return to_return;
    }
    V2D to_return(timeslots.size());
    for (size_t i = 0; i < to_return.size(); i++) {
        to_return[i].push_back(timeslots[i]);
    }
    for (auto it = color_labels.begin(); it != color_labels.end(); ++it) {
        cout << "Node: " << it->first << ": ";
        cout << "Color: " << it->second << endl;
        to_return[it->second].push_back(it->first);
    }
    return to_return;
}

unordered_map<string, vector<string>> constructGraph(const V2D &courses) {
    unordered_map<string, vector<string>> graph;
    for (size_t i = 0; i < courses.size(); i++) {
        graph[courses[i][0]] = vector<string>(0);
    }
    for (size_t i = 0; i < courses.size(); i++) {
        for (size_t j = i + 1; j < courses.size(); j++) {
            if (common_element(courses[i], courses[j])) {
                graph[courses[i][0]].push_back(courses[j][0]);
                graph[courses[j][0]].push_back(courses[i][0]);
            }
        }
    }
    return graph;
}

// the function below is directly from the C++ std library documentation 

bool common_element(vector<string> first, vector<string> second) {
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());
    vector<string> checker;
    set_intersection(first.begin(), first.end(), second.begin(), second.end(), back_inserter(checker));
    return !checker.empty();
}

void printGraph(unordered_map<string, vector<string>> graph) {
    cout << "START" << endl;
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        cout << "Node: " << it->first << ": ";
        cout << "Adjacency List: {";
        for (auto s : it->second) {
            cout << s << " ";
        }
        cout << "}" << endl;
    }
    cout << "END" << endl;
}

void printColors(unordered_map<string, size_t> color_labels) {
    if (color_labels.empty()) {
        cout << "empty" << endl;
        return;
    }
    for (auto it = color_labels.begin(); it != color_labels.end(); ++it) {
        cout << "Node: " << it->first << ": ";
        cout << "Color: " << it->second << endl;
    }
}

unordered_map<string, size_t> color(string start_node, unordered_map<string, vector<string>> graph, size_t colors) {
    unordered_map<string, size_t> color_labels;
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        color_labels[it->first] = -1;
    }
    // BFS to color graph
    queue<string> q;
    q.push(start_node);
    unordered_set<string> visited;
    while (!q.empty()) {
        string curr = q.front();
        visited.insert(curr);
        q.pop();
        vector<string> neighbors = graph[curr];
        unordered_set<int> taken;
        // add neighbors to queue, take note of taken colors 
        for (auto neighbor : neighbors) {
            if (visited.count(neighbor) == 0) {
                q.push(neighbor);
            }
            taken.insert(color_labels[neighbor]);
        }
        for (size_t color = 0; color < colors; color++) {
            if (taken.count(color) == 0) {
                color_labels[curr] = color;
                break;
            }
        }
        if (color_labels[curr] == static_cast<size_t>(-1)) {
            unordered_map<string, size_t> empty;
            return empty;
        }
    }
    // Coloring the graph
    // for (auto it = graph.begin(); it != graph.end(); ++it) {
    //     vector<string> neighbors = it->second;
    //     auto node = it->first;
    //     unordered_set<int> taken;
    //     for (size_t i = 0; i < neighbors.size(); i++) {
    //         taken.insert(color_labels[neighbors[i]]);
    //     }
    //     for (size_t color = 0; color < colors; color++) {
    //         if (taken.count(color) == 0) {
    //             color_labels[node] = color;
    //             break;
    //         }
    //     }
    //     if (color_labels[node] == static_cast<size_t>(-1)) {
    //         unordered_map<string, size_t> empty;
    //         return empty;
    //     }
    // }
    return color_labels;
}