#include <iostream>
 
int main() {
    double speed;
 
    std::cout << "Enter the robot's speed (m/s): ";
    std::cin >> speed;

    // Check if the input operation failed
    // !std::cin checks the failbit of the input stream
    // It returns true if the previous cin operation failed (e.g., non-numeric input)
    // std::cin has an overloaded operator! that checks the stream's state
    std::cout << "Stream state: " << std::cin.rdstate() << std::endl;
    std::cout << "NOT of Stream state: " << !std::cin.rdstate() << std::endl;

    // 🛡️ What !std::cin Actually Does
    // When you write if (!std::cin), you are using an Overloaded Operator. Internally, it is programmed to work like this:
    // "Return TRUE if the stream has FAILED (failbit or badbit is set). Return FALSE if the stream is HEALTHY."
    // If input is valid (e.g., 5.5): rdstate() is 0. !std::cin returns false. The if block is skipped.
    // If input is invalid (e.g., "fast"): rdstate() becomes 2 or 4. !std::cin returns true. The error message triggers.
    

    if (!std::cin) {
        // std::cerr is the standard error stream
        // It outputs error messages to stderr instead of stdout
        // Useful for separating error output from regular output
        std::cerr << "Error: Please enter a valid number for speed." << std::endl;
        return 1; // Exit with error code
    }
    
    // Alternative approach using Exception Handling:
    // try {
    //     double speed;
    //     if (!(std::cin >> speed)) {
    //         // Manually throw an exception
    //         throw std::invalid_argument("Invalid speed input");
    //     }
    // }
    // catch (const std::invalid_argument& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    //     return 1;
    // }
    // 
    // Or enable exceptions on cin:
    // std::cin.exceptions(std::ios::failbit);
    // try {
    //     std::cin >> speed;
    // }
    // catch (const std::ios_base::failure& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    //     return 1;
    // }
 
    std::cout << "Setting robot speed to " << speed << " m/s." << std::endl;
 
    // Code to set the robot speed would go here
 
    return 0;
}