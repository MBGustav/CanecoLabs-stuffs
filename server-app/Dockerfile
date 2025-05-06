
#Image used -- ubuntu
FROM ubuntu:20.04

# Not verbose 
ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y python3 pip mysql-server vim mc wget curl && apt-get clean

# install python packages
RUN pip install mysql-connector-python "fastapi[standard]"

# expose port
EXPOSE 5000

#set app folder
ENV FOLDER_PROJECT=/app
RUN mkdir -p $FOLDER_PROJECT
RUN mkdir -p logs
#Copy files and grant execution
COPY app $FOLDER_PROJECT
RUN chmod +x $FOLDER_PROJECT/docker_run_mysql.sh

# Run.. =)
CMD ["/app/docker_run_mysql.sh"]