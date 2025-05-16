#!/bin/bash

cd app
source .env


fastapi dev app/main.py --host 0.0.0.0 --port 80

#docker Hanging
while true; do
    sleep 30;
done