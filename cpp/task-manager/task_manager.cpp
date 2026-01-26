#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

// Task structure
struct Task {
    int id;
    string description;
    bool completed;
    string priority; // high, medium, low
    
    Task(int i, string desc, string pri = "medium") 
        : id(i), description(desc), completed(false), priority(pri) {}
};

class TaskManager {
private:
    vector<Task> tasks;
    int nextId;
    
public:
    TaskManager() : nextId(1) {}
    
    // Add a new task
    void addTask(const string& desc, const string& priority = "medium") {
        tasks.push_back(Task(nextId++, desc, priority));
        cout << "Task added successfully! (ID: " << nextId - 1 << ")" << endl;
    }
    
    // Display all tasks
    void displayTasks() const {
        if (tasks.empty()) {
            cout << "No tasks available." << endl;
            return;
        }
        
        cout << "\n" << string(70, '=') << endl;
        cout << left << setw(5) << "ID" 
             << setw(35) << "Description" 
             << setw(12) << "Priority"
             << setw(10) << "Status" << endl;
        cout << string(70, '=') << endl;
        
        for (const auto& task : tasks) {
            cout << left << setw(5) << task.id
                 << setw(35) << task.description.substr(0, 32)
                 << setw(12) << task.priority
                 << setw(10) << (task.completed ? "[DONE]" : "[PENDING]") << endl;
        }
        cout << string(70, '=') << "\n" << endl;
    }
    
    // Mark task as complete
    void completeTask(int id) {
        for (auto& task : tasks) {
            if (task.id == id) {
                task.completed = true;
                cout << "Task " << id << " marked as completed!" << endl;
                return;
            }
        }
        cout << "Task with ID " << id << " not found." << endl;
    }
    
    // Delete a task
    void deleteTask(int id) {
        auto it = remove_if(tasks.begin(), tasks.end(), 
                           [id](const Task& t) { return t.id == id; });
        
        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            cout << "Task " << id << " deleted!" << endl;
        } else {
            cout << "Task with ID " << id << " not found." << endl;
        }
    }
    
    // Save tasks to file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing." << endl;
            return;
        }
        
        for (const auto& task : tasks) {
            file << task.id << "|" 
                 << task.description << "|" 
                 << task.priority << "|"
                 << task.completed << endl;
        }
        
        cout << "Tasks saved to " << filename << endl;
    }
    
    // Load tasks from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "No saved tasks found." << endl;
            return;
        }
        
        tasks.clear();
        string line;
        int maxId = 0;
        
        while (getline(file, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);
            
            int id = stoi(line.substr(0, pos1));
            string desc = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string priority = line.substr(pos2 + 1, pos3 - pos2 - 1);
            bool completed = stoi(line.substr(pos3 + 1));
            
            Task task(id, desc, priority);
            task.completed = completed;
            tasks.push_back(task);
            
            if (id > maxId) maxId = id;
        }
        
        nextId = maxId + 1;
        cout << "Tasks loaded from " << filename << endl;
    }
};

// Display menu
void displayMenu() {
    cout << "\n=== Task Manager ===" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View All Tasks" << endl;
    cout << "3. Complete Task" << endl;
    cout << "4. Delete Task" << endl;
    cout << "5. Save Tasks" << endl;
    cout << "6. Load Tasks" << endl;
    cout << "7. Exit" << endl;
    cout << "Choice: ";
}

int main() {
    TaskManager manager;
    int choice;
    
    // Try to load existing tasks
    manager.loadFromFile("tasks.txt");
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer
        
        if (choice == 1) {
            string desc, priority;
            cout << "Enter task description: ";
            getline(cin, desc);
            cout << "Enter priority (high/medium/low): ";
            getline(cin, priority);
            manager.addTask(desc, priority);
            
        } else if (choice == 2) {
            manager.displayTasks();
            
        } else if (choice == 3) {
            int id;
            cout << "Enter task ID to complete: ";
            cin >> id;
            manager.completeTask(id);
            
        } else if (choice == 4) {
            int id;
            cout << "Enter task ID to delete: ";
            cin >> id;
            manager.deleteTask(id);
            
        } else if (choice == 5) {
            manager.saveToFile("tasks.txt");
            
        } else if (choice == 6) {
            manager.loadFromFile("tasks.txt");
            
        } else if (choice == 7) {
            cout << "Save before exiting? (y/n): ";
            char save;
            cin >> save;
            if (save == 'y' || save == 'Y') {
                manager.saveToFile("tasks.txt");
            }
            cout << "Goodbye!" << endl;
            break;
            
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
    
    return 0;
}
