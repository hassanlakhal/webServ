#!/bin/bash

for ((i=1; i<=4; i++)); do
#   curl http://127.0.0.1:8081/home/1228087.jpg   --output image$i.jpg # replace with your actual URL
  curl -X POST -H "Content-Type: image/jpeg" --data-binary "@./www/home/1228087.jpg" http://127.0.0.1:8081/home
#   curl -X POST -H "Content-Type: image/jpeg" http://127.0.0.1:8080/home/1228087.jpg --output image$i.jpg
  echo "Request $i sent"
done
