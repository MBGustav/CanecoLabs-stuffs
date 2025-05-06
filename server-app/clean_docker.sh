#!/bin/bash


tag_docker_name='database_ubuntu'
sudo docker stop ${tag_docker_name}
sudo docker rm ${tag_docker_name}

docker ps
