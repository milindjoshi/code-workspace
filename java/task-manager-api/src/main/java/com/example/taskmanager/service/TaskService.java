package com.example.taskmanager.service;

import com.example.taskmanager.model.Task;
import com.example.taskmanager.repository.TaskRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

@Service
public class TaskService {
    
    @Autowired
    private TaskRepository taskRepository;
    
    // Get all tasks
    public List<Task> getAllTasks() {
        return taskRepository.findAll();
    }
    
    // Get task by ID
    public Optional<Task> getTaskById(Long id) {
        return taskRepository.findById(id);
    }
    
    // Create new task
    public Task createTask(Task task) {
        // Set defaults if not provided
        if (task.getPriority() == null || task.getPriority().isEmpty()) {
            task.setPriority("medium");
        }
        if (task.getCompleted() == null) {
            task.setCompleted(false);
        }
        return taskRepository.save(task);
    }
    
    // Update existing task
    public Task updateTask(Long id, Task taskDetails) {
        Task task = taskRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Task not found with id: " + id));
        
        task.setDescription(taskDetails.getDescription());
        task.setPriority(taskDetails.getPriority());
        task.setCompleted(taskDetails.getCompleted());
        
        return taskRepository.save(task);
    }
    
    // Mark task as completed
    public Task completeTask(Long id) {
        Task task = taskRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Task not found with id: " + id));
        
        task.setCompleted(true);
        return taskRepository.save(task);
    }
    
    // Delete task
    public void deleteTask(Long id) {
        Task task = taskRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Task not found with id: " + id));
        
        taskRepository.delete(task);
    }
    
    // Get pending tasks
    public List<Task> getPendingTasks() {
        return taskRepository.findByCompleted(false);
    }
    
    // Get completed tasks
    public List<Task> getCompletedTasks() {
        return taskRepository.findByCompleted(true);
    }
    
    // Get tasks by priority
    public List<Task> getTasksByPriority(String priority) {
        return taskRepository.findByPriority(priority);
    }
    
    // Search tasks
    public List<Task> searchTasks(String keyword) {
        return taskRepository.searchByDescription(keyword);
    }
    
    // Get statistics
    public Map<String, Object> getStatistics() {
        Map<String, Object> stats = new HashMap<>();
        
        long totalTasks = taskRepository.count();
        long completedTasks = taskRepository.countByCompleted(true);
        long pendingTasks = taskRepository.countByCompleted(false);
        long highPriorityTasks = taskRepository.countByPriority("high");
        long mediumPriorityTasks = taskRepository.countByPriority("medium");
        long lowPriorityTasks = taskRepository.countByPriority("low");
        
        stats.put("total", totalTasks);
        stats.put("completed", completedTasks);
        stats.put("pending", pendingTasks);
        stats.put("highPriority", highPriorityTasks);
        stats.put("mediumPriority", mediumPriorityTasks);
        stats.put("lowPriority", lowPriorityTasks);
        
        if (totalTasks > 0) {
            stats.put("completionRate", (completedTasks * 100.0) / totalTasks);
        } else {
            stats.put("completionRate", 0.0);
        }
        
        return stats;
    }
    
    // Get pending high priority tasks
    public List<Task> getPendingHighPriorityTasks() {
        return taskRepository.findPendingHighPriorityTasks();
    }
}