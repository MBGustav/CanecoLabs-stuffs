
tag_docker_name='database_ubuntu'

sudo docker stop ${tag_docker_name}
sudo docker rm ${tag_docker_name}

# build image
sudo docker build -t ${tag_docker_name} . # --no-cache

# check for errors
i_EXIT_CODE=$?
if [ $i_EXIT_CODE -ne 0 ]; then
    printf "Error during Docker build. Exit code %s\n" ${i_EXIT_CODE}
    exit $i_EXIT_CODE
fi


echo "Debug running Docker:"
#echo "docker exec -it ${tag_docker_name} /bin/bash"


docker run -d -p 80:80 --name ${tag_docker_name} ${tag_docker_name}
echo "Showing running Instances"
docker ps
