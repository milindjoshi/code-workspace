# Spring Boot Task Manager API

REST API for task management built with Spring Boot and PostgreSQL.

## Prerequisites
```bash
# Java 17
sudo apt install openjdk-17-jdk maven

# PostgreSQL (if not already installed)
sudo apt install postgresql
```

## Database Setup

Use the same `taskdb` database from C++ project, or create fresh:
```sql
CREATE DATABASE taskdb;
CREATE USER taskuser WITH PASSWORD 'taskpass123';
GRANT ALL PRIVILEGES ON DATABASE taskdb TO taskuser;
```

Spring Boot will auto-create the `tasks` table.

## Running
```bash
# Make sure PostgreSQL is running
sudo service postgresql start

# Run the application
./mvnw spring-boot:run
```

The API will start at `http://localhost:8080`

## API Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/api/tasks` | Get all tasks |
| GET | `/api/tasks/{id}` | Get task by ID |
| POST | `/api/tasks` | Create new task |
| PUT | `/api/tasks/{id}` | Update task |
| PATCH | `/api/tasks/{id}/complete` | Mark complete |
| DELETE | `/api/tasks/{id}` | Delete task |
| GET | `/api/tasks/pending` | Get pending tasks |
| GET | `/api/tasks/stats` | Get statistics |

## Testing
```bash
# Create a task
curl -X POST http://localhost:8080/api/tasks \
  -H "Content-Type: application/json" \
  -d '{"description":"Learn Spring Boot","priority":"high"}'

# Get all tasks
curl http://localhost:8080/api/tasks

# Get statistics
curl http://localhost:8080/api/tasks/stats
```

## Technologies

- Spring Boot 3.x
- Spring Data JPA
- PostgreSQL
- Maven
- Java 17
