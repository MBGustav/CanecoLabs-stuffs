from pydantic import BaseModel
from typing import Optional
from sqlmodel import Field, Session, SQLModel, create_engine, select, Relationship
from datetime import datetime, date, time, timezone
import sqlmodel


# schema Definitions
class AccessHistory(SQLModel, table=True):
    id:             Optional[int]   = Field(default=None, primary_key=True) #access id
    student_id:     str             = Field(default=None, foreign_key="student.id") 
    datetime_stamp: datetime        = Field(default_factory=datetime.now)
    student:    Optional["Student"] = Relationship(back_populates="access_history")


class ReserveHistory(SQLModel, table=True):
    id:         str  = Field(default=None, primary_key=True) #access id
    student_id: str  = Field(default=None, foreign_key="student.card_id") 
    date_stamp: date = Field(default=None)
    hour_stamp: time = Field(default=None)
    student : Optional["Student"] = Relationship(back_populates="reserve_history") #FKEY


class Student(SQLModel, table=True):
    id:            int = Field(default=None, primary_key=True)
    card_id:       str = Field(default=None, index=True, unique=True)
    registration:  str = Field(default=None, index=True, unique=True) # RA do aluno
    name:          str = Field(default=None)
    course:        str = Field(default=None)
    hierarchy:     int = Field(default=2) #President(0), Monitor(1), Visitor(2)
    access_history: list["AccessHistory"] = Relationship(back_populates='student') #FKEY
    reserve_history: list["ReserveHistory"] = Relationship(back_populates='student') #FKEY



#Queries structure
class StudentQuery(BaseModel):
    id:         Optional[str] = None
    card_id:    Optional[str] = None







#(1) https://medium.com/@jtgraham38/how-to-make-auto-updating-timestamp-fields-in-sqlmodel-03c1d674fa99