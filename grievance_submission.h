#ifndef GRIEVANCE_SUBMISSION_H
#define GRIEVANCE_SUBMISSION_H   //This is a header guard. 
//It prevents the file from being included more than once during compilation, avoiding "redefinition" errors.

#include <string>

int generateComplaintID(); //This function will generate a unique integer ID for each complaint.
std::string getCurrentTimestamp(); //Returns the current time as a string, formatted like "2025-07-12 19:14:03" (for example).
void submitComplaint(const std::string& username);  // Must match definition

#endif //ends the header guard
