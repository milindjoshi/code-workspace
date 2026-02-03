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

---

## 🐳 Running with Docker (Recommended)

### Quick Start
```bash
# Build and start containers
docker compose up -d --build

# Check status
docker compose ps

# View logs
docker compose logs -f app
```

The API will be available at `http://localhost:8080`

### Docker Commands
```bash
# Start containers
docker compose up -d

# Stop containers
docker compose down

# View logs
docker compose logs -f

# Rebuild after code changes
docker compose up -d --build

# Stop and remove all data
docker compose down -v
```

### What's Included

The Docker setup includes:
- **PostgreSQL container** - Database server (port 5432)
- **Spring Boot container** - REST API (port 8080)
- **Docker network** - Connects the containers
- **Persistent volume** - Database data survives container restarts

### Architecture
```
┌─────────────────────────────────┐
│   Docker Network                │
│                                 │
│  ┌──────────────────────────┐  │
│  │  PostgreSQL Container    │  │
│  │  Port: 5432              │  │
│  │  Volume: postgres-data   │  │
│  └──────────────────────────┘  │
│              ↕                  │
│  ┌──────────────────────────┐  │
│  │  Spring Boot Container   │  │
│  │  Port: 8080              │  │
│  └──────────────────────────┘  │
└─────────────────────────────────┘
            ↕
    http://localhost:8080
```

---
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

# Mark task as complete
curl -X PATCH http://localhost:8080/api/tasks/1/complete

# Search tasks
curl "http://localhost:8080/api/tasks/search?keyword=spring"
```

### Using Postman

Import these endpoints into Postman for easier testing.

## Technologies

- Spring Boot 3.x
- Spring Data JPA
- PostgreSQL
- Maven
- Java 17
- Docker & Docker Compose

## Project Structure
```
task-manager-api/
├── src/
│   ├── main/
│   │   ├── java/com/example/taskmanager/
│   │   │   ├── model/
│   │   │   │   └── Task.java
│   │   │   ├── repository/
│   │   │   │   └── TaskRepository.java
│   │   │   ├── service/
│   │   │   │   └── TaskService.java
│   │   │   ├── controller/
│   │   │   │   └── TaskController.java
│   │   │   └── TaskmanagerApplication.java
│   │   └── resources/
│   │       └── application.properties
│   └── test/
├── Dockerfile
├── docker-compose.yml
├── .dockerignore
├── pom.xml
└── README.md
```

## Development

### Local Development (without Docker)
```bash
# Install dependencies
./mvnw clean install

# Run with auto-reload
./mvnw spring-boot:run
```

### Docker Development
```bash
# Make code changes

# Rebuild and restart
docker compose down
docker compose up -d --build

# View logs
docker compose logs -f app
```

## Troubleshooting

### Port Already in Use
```bash
# Check what's using the port
sudo lsof -i :8080

# Stop local PostgreSQL if using Docker
sudo service postgresql stop
```

### Database Connection Issues
```bash
# Check if PostgreSQL container is running
docker compose ps

# Check PostgreSQL logs
docker compose logs postgres

# Restart containers
docker compose restart
```

### View Application Logs
```bash
# All logs
docker compose logs

# Follow logs in real-time
docker compose logs -f app

# Last 50 lines
docker compose logs --tail=50 app
```

## Future Enhancements

- [ ] Add input validation (@Valid annotations)
- [ ] Implement exception handling (@ControllerAdvice)
- [ ] Add pagination for large datasets
- [ ] Implement JWT authentication
- [ ] Add unit and integration tests
- [ ] Create Swagger/OpenAPI documentation
- [ ] Set up CI/CD pipeline
- [ ] Deploy to cloud (AWS/Azure/GCP)
