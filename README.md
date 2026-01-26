# Code workspace repository

code-workspace/
├── cpp/
│   ├── task-manager/          # File-based task manager
│   └── task-manager-db/       # PostgreSQL-based task manager
├── java/
│   └── task-manager-api/      # Spring Boot REST API
└── frontend/
    └── (coming soon)          # React frontend

1. C++ Task Manager (File-based)
Location: cpp/task-manager/
Command-line task management application that persists data to a local text file.
Features:

Create, read, update, delete tasks
Priority levels (high, medium, low)
Task completion tracking
File I/O for persistence

Technologies: C++11, STL, File I/O

2. C++ Task Manager (PostgreSQL)
Location: cpp/task-manager-db/
Enhanced version using PostgreSQL database for robust data management.
Features:

Full CRUD operations with PostgreSQL
Search functionality
Task statistics
Transaction support
Concurrent access support

Technologies: C++17, PostgreSQL, libpqxx

3. Spring Boot Task Manager REST API
Location: java/task-manager-api/
Production-ready REST API built with Spring Boot and PostgreSQL.
Features:

RESTful API endpoints for task management
Spring Data JPA for database operations
Automatic table creation with Hibernate
JSON request/response handling
CRUD operations with proper HTTP methods
Search and filtering capabilities
Task statistics endpoint

Technologies: Java 17, Spring Boot 3.x, Spring Data JPA, PostgreSQL, Maven
API Endpoints:

GET /api/tasks - Get all tasks
POST /api/tasks - Create new task
PUT /api/tasks/{id} - Update task
DELETE /api/tasks/{id} - Delete task
GET /api/tasks/stats - Get statistics
GET /api/tasks/search?keyword=xxx - Search tasks

🛠 Technology Stack
Languages

C++: 11/17
Java: 17
JavaScript: ES6+ (planned)

Frameworks & Libraries

Spring Boot 3.x
Spring Data JPA
libpqxx (PostgreSQL C++ connector)
React (planned)

Database

PostgreSQL 14+

Build Tools

Maven (Java)
Make/g++ (C++)

Development Tools

Git for version control
VS Code as primary IDE
curl/Postman for API testing
GDB for C++ debugging
Valgrind for memory leak detection

📊 Project Evolution
This repository demonstrates progressive learning and skill development:

Phase 1: Basic C++ with file I/O → Understanding fundamental programming concepts
Phase 2: C++ with PostgreSQL → Database integration and SQL
Phase 3: Spring Boot REST API → Enterprise-level Java development, RESTful design
Phase 4: React Frontend (planned) → Full-stack development

👤 Author
Active developer committed to continuous learning and building production-quality applications.
Focus Areas: Backend Development, Database Systems, Full-Stack Engineering


📄 License
This is a personal learning repository. Feel free to explore and learn from the code.
