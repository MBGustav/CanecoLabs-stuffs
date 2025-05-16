
#Image used -- ubuntu
FROM ubuntu:20.04

# Not verbose 
ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y python3 pip sqlite3 vim mc wget curl && apt-get clean

# install python packages
RUN pip install --no-cache-dir --upgrade "fastapi[standard]" sqlmodel 

#set app folder
ENV FOLDER_PROJECT=/app


# expose port
EXPOSE 80

# Copy .env file
RUN mkdir -p $FOLDER_PROJECT
RUN mkdir -p logs
#Copy files and grant execution
COPY app $FOLDER_PROJECT
COPY .env $FOLDER_PROJECT/.env
RUN chmod +x $FOLDER_PROJECT/docker_run_mysql.sh

# Run.. =)

#CMD ["fastapi", "dev", "app/CanecoServer.py",  "--host", "0.0.0.0", "--port", "80"]
# fastapi dev app/CanecoServer.py --host 0.0.0.0 --port 80
CMD ["bash", "/app/docker_run_mysql.sh"]
