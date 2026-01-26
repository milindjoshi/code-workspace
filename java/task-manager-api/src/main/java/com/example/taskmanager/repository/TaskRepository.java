package com.example.taskmanager.repository;

import com.example.taskmanager.model.Task;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface TaskRepository extends JpaRepository<Task, Long> {
    
    // Find all tasks by completion status
    List<Task> findByCompleted(Boolean completed);
    
    // Find all tasks by priority
    List<Task> findByPriority(String priority);
    
    // Find tasks by priority and completion status
    List<Task> findByPriorityAndCompleted(String priority, Boolean completed);
    
    // Search tasks by description (case-insensitive)
    @Query("SELECT t FROM Task t WHERE LOWER(t.description) LIKE LOWER(CONCAT('%', :keyword, '%'))")
    List<Task> searchByDescription(@Param("keyword") String keyword);
    
    // Count tasks by completion status
    long countByCompleted(Boolean completed);
    
    // Count tasks by priority
    long countByPriority(String priority);
    
    // Get pending high priority tasks
    @Query("SELECT t FROM Task t WHERE t.priority = 'high' AND t.completed = false ORDER BY t.createdAt DESC")
    List<Task> findPendingHighPriorityTasks();
}