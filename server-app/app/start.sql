
-- create DATABASE
CREATE DATABASE IF NOT EXISTS db_server;

-- enter database
USE db_server;


CREATE TABLE STUDENT_DATA(
    student_id CHAR(10) PRIMARY KEY,     -- unique id RA
    student_cardId INT NOT NULL,         -- card Id from Uni
    student_hierarchy INT NOT NULL,      -- hierarchy: admin, visitor or another
    student_name CHAR(60) NOT NULL,      -- Student Name
    student_course INT                   -- Course Type
);
--https://www.spdi.ufscar.br/arquivos/desenvolvimento-institucional/avaliacao-institucional/informacoes-cursos-de-graduacao.pdf


-- each insertion is an access to the lab
CREATE TABLE HISTORIC_ACCESS (
    id INT AUTO_INCREMENT PRIMARY KEY,      -- unique identifier for each access(is it necessary?)
    student_id CHAR(10) NOT NULL,           -- comes from STUDENT_DATA
    date_timestamp DATE NOT NULL,           -- date (y/m/d) access
    hour_timestamp TIME NOT NULL,           -- access time

    FOREIGN KEY (student_id) REFERENCES STUDENT_DATA(student_id)
);

-- reserved dates (to-do)
CREATE TABLE RESERVE_ACCESS (
    reserve_id INT AUTO_INCREMENT PRIMARY KEY, -- unique identifier for reservation
    student_id CHAR(10) NOT NULL,              -- comes from STUDENT_DATA
    reserve_date DATE NOT NULL,                -- date of the reservation
    reserve_time TIME NOT NULL,                -- time of the reservation
    
    FOREIGN KEY (student_id) REFERENCES STUDENT_DATA(student_id)
);

-- Insert data into STUDENT_DATA
INSERT INTO STUDENT_DATA (student_id, student_hierarchy, student_name, student_course)
VALUES 
(1, 1, 'Gustavo Barreto', 101),
(2, 2, 'Rafael Banin', 102),
(3, 3, 'Duda', 103);

-- Insert data into HISTORIC_ACCESS
INSERT INTO HISTORIC_ACCESS (student_id, date_timestamp, hour_timestamp)
VALUES 
(1, '2023-01-01', '08:30:00'),
(2, '2023-01-02', '09:00:00'),
(3, '2023-01-03', '10:15:00');

-- Insert data into RESERVE_ACCESS
INSERT INTO RESERVE_ACCESS (student_id, reserve_date, reserve_time)
VALUES 
(1, '2023-02-01', '14:00:00'),
(2, '2023-02-02', '15:30:00'),
(3, '2023-02-03', '16:45:00');