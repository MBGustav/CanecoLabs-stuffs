from fastapi import FastAPI
from sqlmodel import Field, Session, SQLModel, create_engine, select, Relationship
from datetime import date, time
import models.models

from routes import student, access_history, reservation
from db.db_handler import create_db_and_tables, populate_tables
import models 
app = FastAPI()

#Initialize Logger
#LOG = logging.getLogger(__name__)
#LOG.info("API is starting up")

#Initialize db
@app.router.on_startup.append
def on_startup():
    create_db_and_tables()
    populate_tables(10)

# Include student Route
app.include_router(student.router)

# Include access_history Route
app.include_router(access_history.router)

# include Reserve History Route
app.include_router(reservation.router)

