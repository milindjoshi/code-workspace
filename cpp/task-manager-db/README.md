# C++ Task Manager (PostgreSQL)

Command-line task manager using PostgreSQL database.

## Prerequisites
```bash
sudo apt install postgresql postgresql-contrib libpqxx-dev
```

## Database Setup
```bash
sudo -u postgres psql
```
```sql
CREATE DATABASE taskdb;
CREATE USER taskuser WITH PASSWORD 'taskpass123';
GRANT ALL PRIVILEGES ON DATABASE taskdb TO taskuser;
\c taskdb
CREATE TABLE tasks (
    id SERIAL PRIMARY KEY,
    description TEXT NOT NULL,
    priority VARCHAR(20) DEFAULT 'medium',
    completed BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
\q
```

## Compilation
```bash
make
# or
g++ -o task_manager_db task_manager_db.cpp -lpqxx -lpq -std=c++17
```

## Usage
```bash
./task_manager_db
```

## Technologies

- C++17
- PostgreSQL
- libpqxx library
