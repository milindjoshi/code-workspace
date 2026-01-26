#!/bin/bash

echo "=== Testing Task Manager API ==="

echo -e "\n1. Creating tasks..."
curl -X POST http://localhost:8080/api/tasks -H "Content-Type: application/json" -d '{"description":"Buy groceries","priority":"high"}'
echo
curl -X POST http://localhost:8080/api/tasks -H "Content-Type: application/json" -d '{"description":"Finish homework","priority":"medium"}'
echo
curl -X POST http://localhost:8080/api/tasks -H "Content-Type: application/json" -d '{"description":"Call dentist","priority":"low"}'
echo

echo -e "\n2. Getting all tasks..."
curl http://localhost:8080/api/tasks
echo

echo -e "\n3. Getting pending tasks..."
curl http://localhost:8080/api/tasks/pending
echo

echo -e "\n4. Completing task 1..."
curl -X PATCH http://localhost:8080/api/tasks/1/complete
echo

echo -e "\n5. Getting statistics..."
curl http://localhost:8080/api/tasks/stats
echo

echo -e "\n=== Test Complete ==="
