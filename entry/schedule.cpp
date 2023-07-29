#include <iostream>
#include "schedule.h"

int main() {
    //std::cout << "Hello, mp_schedule!" << std::endl;

    //Graph myGraph("rosterList.txt", "studentList.txt");

    //V2D roster = file_to_V2D("../rosterList.txt");
    // V2D roster = file_to_V2D("../data/c5_s10_3_roster_errors.csv");

    // /*
    // for (int i = 0; i < (int) roster.size(); ++i){
    //     std::cout << "{ ";
    //     for(int j = 0; j < (int) roster[i].size()-1; ++j){
    //     std::cout << roster[i][j] << ", ";
    //     }
    //     std::cout << roster[i][roster[i].size()-1] << "}, \\" << std::endl;
    // }
    // */

    // //V2D student = file_to_V2D("../studentList.txt");
    // V2D student = file_to_V2D("../data/c5_s10_3_students_errors.csv");

    // /*
    // for (int i = 0; i < (int) student.size(); ++i){
    //     std::cout << "{ ";
    //     for(int j = 0; j < (int) student[i].size()-1; ++j){
    //     std::cout << student[i][j] << ", ";
    //     }
    //     std::cout << student[i][student[i].size()-1] << "}, \\" << std::endl;
    // }
    // */

    
    // V2D out = clean(roster, student);

    // for (int i = 0; i < (int) out.size(); ++i){
    //     std::cout << "{ ";
    //     for(int j = 0; j < (int) out[i].size()-1; ++j){
    //     std::cout << "\"" << out[i][j] << "\", ";
    //     }
    //     std::cout << "\"" << out[i][out[i].size()-1] << "\"}, \\" << std::endl;
    // }

    // V2D student_test = {{"CS101", "a", "b", "c"},\
    //                     {"CS102", "a", "b"},\
    //                     {"CS103", "c"}};

    // std::vector<std::string> timeSlots;
    // timeSlots.push_back("0");
    // timeSlots.push_back("1");
    // timeSlots.push_back("2");
    // timeSlots.push_back("3");
    // //Graph(out, timeSlots);

    // schedule(student_test, timeSlots);

    // V2D outSched = schedule(out, timeSlots);

    // std::cout << "Coloring:" << std::endl;
    // std::cout << "{ ";
    // for (int i = 0; i < (int) outSched.size(); ++i){
    //     std::cout << "{ ";
    //     for(int j = 0; j < (int) outSched[i].size()-1; ++j){
    //     std::cout << outSched[i][j] << ", ";
    //     }
    //     std::cout << outSched[i][outSched[i].size()-1] << "}, \\" << std::endl;
    // }
    // std::cout << "}" << std::endl;

    unordered_map<string, vector<string>> private_test_1;
    private_test_1["CS449"] = {"CS192", "CS106", "CS464", "CS194", "CS135", "CS526", "CS471", "CS593", "CS129", "CS355", "CS433", "CS366", "CS503"};
    private_test_1["CS503"] = {"CS192", "CS464", "CS194", "CS135", "CS526", "CS471", "CS593", "CS129", "CS355", "CS366", "CS449"};
    private_test_1["CS106"] = {"CS192", "CS194", "CS526", "CS545", "CS593", "CS129", "CS433", "CS366", "CS449"};
    private_test_1["CS464"] = {"CS192", "CS194", "CS135", "CS545", "CS593", "CS129", "CS355", "CS433", "CS503", "CS449"};
    private_test_1["CS192"] = {"CS106", "CS464", "CS194", "CS135", "CS526", "CS545", "CS593", "CS129", "CS355", "CS433", "CS366", "CS503", "CS449"};
    private_test_1["CS194"] = {"CS192", "CS106", "CS464", "CS526", "CS593", "CS433", "CS366", "CS503", "CS449"};
    private_test_1["CS135"] = {"CS192", "CS464", "CS545", "CS471", "CS593", "CS129", "CS355", "CS366", "CS503", "CS449"};
    private_test_1["CS545"] = {"CS192", "CS106", "CS464", "CS135", "CS593", "CS355", "CS433", "CS366"};
    private_test_1["CS366"] = {"CS192", "CS106", "CS194", "CS135", "CS526", "CS545", "CS471", "CS593", "CS129", "CS355", "CS433", "CS503", "CS449"};
    private_test_1["CS593"] = {"CS192", "CS106", "CS464", "CS194", "CS135", "CS526", "CS545", "CS471", "CS129", "CS355", "CS433", "CS366", "CS503", "CS449"};
    private_test_1["CS471"] = {"CS135", "CS526", "CS593", "CS129", "CS355", "CS366", "CS503", "CS449"};
    private_test_1["CS355"] = {"CS192", "CS464", "CS135", "CS545", "CS471", "CS593", "CS129", "CS433", "CS366", "CS503", "CS449"};
    private_test_1["CS526"] = {"CS192", "CS106", "CS194", "CS471", "CS593", "CS366", "CS503", "CS449"};
    private_test_1["CS129"] = {"CS192", "CS106", "CS464", "CS135", "CS471", "CS593", "CS355", "CS433", "CS366", "CS503", "CS449"};
    private_test_1["CS433"] = {"CS192", "CS106", "CS464", "CS194", "CS545", "CS593", "CS129", "CS355", "CS366", "CS449"};

    vector<size_t> colors;
    for (size_t i = 0; i < 8; i++) {
        colors.push_back(i);
    }

    unordered_map<string, size_t> color_labels;
    int counter = 0;
    for (auto it = private_test_1.begin(); it != private_test_1.end(); it++) {
        color_labels = color(it->first, private_test_1, colors.size());
        printColors(color_labels);
        cout << counter << endl;
        counter++;
    }
}