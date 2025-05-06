# Helped by:
# https://dev.to/jamesbmour/part-3-pydantic-data-models-4gnb

from pydantic import BaseModel, model_validator
from typing import Optional

class StudentRequest(BaseModel): 
    cardId: Optional[str] =None
    id: Optional[str] =None

# Class for simple messages reception/send
class MessageResponse(BaseModel):
    message: str

#TODO
# class Student(BaseModel):
#     id: str
#     cardId: str
#     hierarchy: str
#     name: str
#     course: str

# class TimeRequest(BaseModel):
#     date: str
#     time: str