from fastapi import APIRouter, Depends, HTTPException
from starlette.responses import RedirectResponse
from sqlmodel import Field, Session, SQLModel, create_engine, select, Relationship
from db.db_handler import get_session
from models.models import *
from routes.access_history import access_log



router = APIRouter()

@router.get("/")
async def home():
    return {"message": "Welcome to CanecoLabs-API!"}

#insert student (#TODO Cookie from president)
@router.post("/student/")
def create_student(student : Student, session : Session = Depends(get_session)):
    try:
        session.add(student)
        session.commit()
        session.refresh(student)
        return student
    
    except Exception as e:
        raise HTTPException(status_code=204, detail=f"User not added:\n {str(e)}")
    
#Read Student and add log entry
@router.get("/student/")
def read_student(input_search : StudentQuery, session : Session = Depends(get_session)):
    try:
        query = select(Student) # FROM STUDENT, SELECT ..
        if input_search.card_id is not None: # WHERE CARD_ID  == input
            query = query.where(Student.card_id == input_search.card_id)
        elif input_search.id is not None: # WHERE ID  == input
            query = query.where(Student.id == input_search.id)
        else:
            raise HTTPException(status_code=400, detail=f"Bad Request:\n {str(e)}")    
            #return RedirectResponse(url="https://http.cat/status/400")
        
        result = session.exec(query).first()
        copy = result
        access_log(result, session)
        
        return copy
    
    except Exception as e:
        raise HTTPException(status_code=204, detail=f"User not added:\n {str(e)}")
    


# Returns if usr exists (1. check cardId, 2. check RA, else is out)
# @router.post("/usr")
# async def usr(request: StudentRequest,db: UserQuery = Depends(get_db)):
#     try:
#         if request.cardId:
#             allowed = db.validate_student_by_card(request.cardId)
#         elif request.id:
#             allowed = db.validate_student_by_id(request.cardId)
#         else:
#             raise HTTPException(status_code=400, detail="id or Card ID is required")
#         return {"allowed": True}
#     except Exception as e:
#         raise HTTPException(status_code=500, detail=f"An error occurred: {str(e)}")


# @router.post("/usr/add")
# async def usr_add(request: StudentRequest, db: UserQuery = Depends(get_db)):
#     try:
#         for field in ['id', 'cardId', 'name', 'Hierarchy']:
#             if not getattr(request, field, None):
#                 raise HTTPException(status_code=400, detail=f"{field} must be provided.")
#         success = db.add_student(request.id, request.cardId, request.Hierarchy, request.name)
#         if not success:
#             raise HTTPException(status_code=500, detail="Failed to add the student.")
#         return {"message": f"Student({request.name}) added successfully."}
#     except Exception as e:
#         raise HTTPException(status_code=500, detail=f"An error occurred: {str(e)}")


# @router.delete("/usr/rm")
# async def usr_rm(request: StudentRequest, db: UserQuery = Depends(get_db))  -> MessageResponse:
#     return {"message": f"Deleted student with id: {id}"}


# @router.get("/db-dbg")
# async def db_dbg(db: UserQuery = Depends(get_db)):
#     try:
#         students = db.list_all_students()
#         return {"students": students}
#     except Exception as e:
#         raise HTTPException(status_code=500, detail=f"An error occurred: {str(e)}")
