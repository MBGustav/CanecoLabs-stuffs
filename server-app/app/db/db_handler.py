from fastapi import APIRouter, Depends, HTTPException

from sqlmodel import Field, Session, SQLModel, create_engine, select, Relationship
from sqlmodel.pool import StaticPool
from models.models import Student, AccessHistory

#To populate the table
from faker import Faker
from random import randint, randrange
import datetime

router = APIRouter()

sqlite_file_name = "db/database.db"
sqlite_url = f"sqlite:///{sqlite_file_name}"
connect_args = {"check_same_thread": False}
engine = create_engine(sqlite_url, 
                       echo=True,
                       
                       connect_args=connect_args,
                       poolclass=StaticPool
                       )

def create_db_and_tables():
    SQLModel.metadata.create_all(engine)

# sync port to db connection
def get_session():
    with Session(engine) as session:
        yield session

#just a debug function


def random_datetime(start_date, end_date):
    time_between_dates = end_date - start_date
    days_between_dates = time_between_dates.days
    random_number_of_days = randrange(days_between_dates)
    random_date = start_date + datetime.timedelta(days=random_number_of_days)
    random_time = datetime.time(randint(0, 23), randint(0, 59), randint(0, 59))
    return datetime.datetime.combine(random_date, random_time)


def populate_tables(num_regs=250):
    course_list = ["ENC", "BCC", "BSI"]
    beg_date = datetime.datetime(2025,1, 10)
    end_date = datetime.datetime(2025,4, 15)
    student_list = []
    access_list = []

    for i in range(num_regs):
        my_name = Faker().name()
        my_cardID = ''.join([hex(randint(0, 15))[2:] for _ in range(6)])
        my_reg    = ''.join([str(randint(0, 9)) for _ in range(6)])
        my_course = course_list[randint(0, len(course_list) - 1)]
        my_hierarchy = randint(0, 2)

        student_list.append(Student(
            card_id=my_cardID,
            name=my_name,
            registration=my_reg,
            hierarchy=my_hierarchy,
            course=my_course))
        
    for i in range(num_regs):
        my_id = randint(0, len(student_list))
        datetime_stamp = random_datetime(beg_date, end_date)
        access_list.append(AccessHistory(
            student_id=my_id,
            datetime_stamp=datetime_stamp
        ))

    with Session(engine) as session:
        for student in student_list:
            session.add(student)
        for access in access_list:
            session.add(access)
        session.commit()