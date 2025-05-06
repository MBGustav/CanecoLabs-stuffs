from fastapi import FastAPI, HTTPException
from models import *
from DataBaseHandler import DataBaseHandler
from dotenv import load_dotenv
import os, json

load_dotenv()

env = dict() 
env['DB_PASSWORD'] = os.getenv('DB_PASSWORD')
env['DB_USER']     = os.getenv('DB_USER')
env['DB_NAME']     = os.getenv('DB_NAME')



# instantiate the app
app = FastAPI()

# serializing the queries stufs
def get_db():
    db = DataBaseHandler(
        database=env['DB_NAME'],
        user=env['DB_USER'],
        password=env['DB_PASSWORD']
        )
    try:
        yield db
    finally:
        db.close()


# Hello Everybody !
@app.get("/")
async def home():
    return {"message": "Welcome to CanecoLabs-API!"}


# checking if the user exists(cardId or id (RA))
@app.post("/usr_check", response_model=MessageResponse)
async def usr_check(user_request: StudentRequest):

    values = user_request.model_dump()  # returns a dict of the validated fields
    try:
        if not values['id'] and not values['cardId'] :
            raise HTTPException(status_code=400, detail="User field is required")
        
        if values['id'] :
            return {"message": values['id']}
    
        return {"message": values['cardId']}
    

    except Exception as e:
        raise HTTPException(status_code=500, detail=f"An error occurred: {str(e)}")

    

    #db = get_db()

    # try:
    #     result = db.get_student_by_id(user_id)
    #     db.close()

    #     if result:
    #         return {"message": f"User exists: {result['student_name']}"}
    #     else:
    #         return {"message": "User not found"}

    # except Exception as e:
    #     db.close()
    #     raise HTTPException(status_code=500, detail=f"Database error: {str(e)}")

