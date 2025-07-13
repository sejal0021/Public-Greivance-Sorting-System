#ifndef GRIEVANCE_H
#define GRIEVANCE_H

#include <string>

class Grievance {
private:
    int id;
    std::string username;
    std::string title;
    std::string description;
    std::string category;
    int priority;
    std::string location;
    std::string timestamp;
    std::string status;

public:
    Grievance();  // Default constructor
    Grievance(int id, const std::string& username, const std::string& title,
              const std::string& description, const std::string& category,
              int priority, const std::string& location,
              const std::string& timestamp, const std::string& status);

    // Getters
    int getId() const;
    std::string getUsername() const;
    std::string getTitle() const;
    std::string getDescription() const;
    std::string getCategory() const;
    int getPriority() const;
    std::string getLocation() const;
    std::string getTimestamp() const;
    std::string getStatus() const;

    // Setters
    void setId(int id);
    void setUsername(const std::string& username);
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setCategory(const std::string& category);
    void setPriority(int priority);
    void setLocation(const std::string& location);
    void setTimestamp(const std::string& timestamp);
    void setStatus(const std::string& status);

    void display() const;
};

#endif
