#include <iostream>
#include <pqxx/pqxx>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;
using namespace pqxx;

class Task {
public:
    int id;
    string description;
    string priority;
    bool completed;
    
    Task(int i, string desc, string pri, bool comp)
        : id(i), description(desc), priority(pri), completed(comp) {}
};

class TaskManager {
private:
    string connectionString;
    
public:
    TaskManager(const string& connStr) : connectionString(connStr) {
        testConnection();
    }
    
    // Test database connection
    bool testConnection() {
        try {
            connection C(connectionString);
            if (C.is_open()) {
                cout << "Successfully connected to database!" << endl;
                return true;
            }
        } catch (const exception &e) {
            cerr << "Connection failed: " << e.what() << endl;
            cerr << "Make sure PostgreSQL is running and credentials are correct." << endl;
            return false;
        }
        return false;
    }
    
    // Add a new task
    void addTask(const string& desc, const string& priority = "medium") {
        try {
            connection C(connectionString);
            work W(C);
            
            string sql = "INSERT INTO tasks (description, priority) VALUES (" 
                        + W.quote(desc) + ", " + W.quote(priority) + ")";
            
            W.exec(sql);
            W.commit();
            
            cout << "Task added successfully!" << endl;
        } catch (const exception &e) {
            cerr << "Error adding task: " << e.what() << endl;
        }
    }
    
    // Display all tasks
    void displayTasks() {
        try {
            connection C(connectionString);
            nontransaction N(C);
            
            result R(N.exec("SELECT id, description, priority, completed FROM tasks ORDER BY id"));
            
            if (R.empty()) {
                cout << "\nNo tasks available." << endl;
                return;
            }
            
            cout << "\n" << string(80, '=') << endl;
            cout << left << setw(5) << "ID" 
                 << setw(45) << "Description" 
                 << setw(12) << "Priority"
                 << setw(12) << "Status" << endl;
            cout << string(80, '=') << endl;
            
            for (auto row : R) {
                string desc = row[1].as<string>();
                if (desc.length() > 42) {
                    desc = desc.substr(0, 39) + "...";
                }
                
                cout << left << setw(5) << row[0].as<int>()
                     << setw(45) << desc
                     << setw(12) << row[2].as<string>()
                     << setw(12) << (row[3].as<bool>() ? "[DONE]" : "[PENDING]") << endl;
            }
            cout << string(80, '=') << "\n" << endl;
            
        } catch (const exception &e) {
            cerr << "Error displaying tasks: " << e.what() << endl;
        }
    }
    
    // Display only pending tasks
    void displayPendingTasks() {
        try {
            connection C(connectionString);
            nontransaction N(C);
            
            result R(N.exec("SELECT id, description, priority FROM tasks "
                          "WHERE completed = FALSE ORDER BY id"));
            
            if (R.empty()) {
                cout << "\nNo pending tasks!" << endl;
                return;
            }
            
            cout << "\n=== PENDING TASKS ===" << endl;
            cout << string(80, '=') << endl;
            
            for (auto row : R) {
                cout << "ID " << row[0].as<int>() << ": "
                     << row[1].as<string>() 
                     << " [" << row[2].as<string>() << "]" << endl;
            }
            cout << string(80, '=') << "\n" << endl;
            
        } catch (const exception &e) {
            cerr << "Error displaying pending tasks: " << e.what() << endl;
        }
    }
    
    // Mark task as complete
    void completeTask(int id) {
        try {
            connection C(connectionString);
            work W(C);
            
            string sql = "UPDATE tasks SET completed = TRUE WHERE id = " + to_string(id);
            result R = W.exec(sql);
            W.commit();
            
            if (R.affected_rows() > 0) {
                cout << "Task " << id << " marked as completed!" << endl;
            } else {
                cout << "Task with ID " << id << " not found." << endl;
            }
            
        } catch (const exception &e) {
            cerr << "Error completing task: " << e.what() << endl;
        }
    }
    
    // Delete a task
    void deleteTask(int id) {
        try {
            connection C(connectionString);
            work W(C);
            
            string sql = "DELETE FROM tasks WHERE id = " + to_string(id);
            result R = W.exec(sql);
            W.commit();
            
            if (R.affected_rows() > 0) {
                cout << "Task " << id << " deleted!" << endl;
            } else {
                cout << "Task with ID " << id << " not found." << endl;
            }
            
        } catch (const exception &e) {
            cerr << "Error deleting task: " << e.what() << endl;
        }
    }
    
    // Search tasks by keyword
    void searchTasks(const string& keyword) {
        try {
            connection C(connectionString);
            nontransaction N(C);
            
            string sql = "SELECT id, description, priority, completed FROM tasks "
                        "WHERE description ILIKE " + N.quote("%" + keyword + "%") 
                        + " ORDER BY id";
            result R(N.exec(sql));
            
            if (R.empty()) {
                cout << "No tasks found matching: " << keyword << endl;
                return;
            }
            
            cout << "\nSearch Results for '" << keyword << "':" << endl;
            cout << string(80, '=') << endl;
            
            for (auto row : R) {
                cout << "ID " << row[0].as<int>() << ": "
                     << row[1].as<string>()
                     << " [" << row[2].as<string>() << "] "
                     << (row[3].as<bool>() ? "[DONE]" : "[PENDING]") << endl;
            }
            cout << string(80, '=') << "\n" << endl;
            
        } catch (const exception &e) {
            cerr << "Error searching tasks: " << e.what() << endl;
        }
    }
    
    // Get task statistics
    void displayStats() {
        try {
            connection C(connectionString);
            nontransaction N(C);
            
            result total = N.exec("SELECT COUNT(*) FROM tasks");
            result completed = N.exec("SELECT COUNT(*) FROM tasks WHERE completed = TRUE");
            result pending = N.exec("SELECT COUNT(*) FROM tasks WHERE completed = FALSE");
            result highPriority = N.exec("SELECT COUNT(*) FROM tasks WHERE priority = 'high' AND completed = FALSE");
            
            cout << "\n=== TASK STATISTICS ===" << endl;
            cout << "Total Tasks: " << total[0][0].as<int>() << endl;
            cout << "Completed: " << completed[0][0].as<int>() << endl;
            cout << "Pending: " << pending[0][0].as<int>() << endl;
            cout << "High Priority Pending: " << highPriority[0][0].as<int>() << endl;
            cout << "========================\n" << endl;
            
        } catch (const exception &e) {
            cerr << "Error getting statistics: " << e.what() << endl;
        }
    }
};

// Display menu
void displayMenu() {
    cout << "\n=== Task Manager (PostgreSQL) ===" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View All Tasks" << endl;
    cout << "3. View Pending Tasks" << endl;
    cout << "4. Complete Task" << endl;
    cout << "5. Delete Task" << endl;
    cout << "6. Search Tasks" << endl;
    cout << "7. View Statistics" << endl;
    cout << "8. Exit" << endl;
    cout << "Choice: ";
}

int main() {
    // Connection string format: "dbname=taskdb user=taskuser password=taskpass123 host=localhost"
    string connStr = "dbname=taskdb user=taskuser password=taskpass123 host=localhost";
    
    TaskManager manager(connStr);
    int choice;
    
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
            
            if (priority.empty()) priority = "medium";
            manager.addTask(desc, priority);
            
        } else if (choice == 2) {
            manager.displayTasks();
            
        } else if (choice == 3) {
            manager.displayPendingTasks();
            
        } else if (choice == 4) {
            int id;
            cout << "Enter task ID to complete: ";
            cin >> id;
            manager.completeTask(id);
            
        } else if (choice == 5) {
            int id;
            cout << "Enter task ID to delete: ";
            cin >> id;
            manager.deleteTask(id);
            
        } else if (choice == 6) {
            string keyword;
            cout << "Enter search keyword: ";
            getline(cin, keyword);
            manager.searchTasks(keyword);
            
        } else if (choice == 7) {
            manager.displayStats();
            
        } else if (choice == 8) {
            cout << "Goodbye!" << endl;
            break;
            
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
    
    return 0;
}
