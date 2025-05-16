from fastapi import APIRouter, Depends, HTTPException
from sqlmodel import Session, select
from db.db_handler import get_session
from models.models import *
from datetime import datetime, timedelta

router = APIRouter()

def access_log(student: Student, session: Session):
    try:
        if student is None or session is None:
            raise ValueError("Objects cannot be None.")
        
        log_access = AccessHistory(student_id=student.id)

        session.add(log_access)
        session.commit()
        session.refresh(log_access)

    except Exception as e:
        session.rollback()
        print(f"[ERROR] Access Log Commit Failed: {e}")
        raise HTTPException(status_code=500, detail=f"Access logging failed: {str(e)}")


# Query for the last users
@router.get("/access")
async def access(session: Session = Depends(get_session)):
    try:
        query = select(AccessHistory)
        time_end = datetime.now() 
        time_beg = time_end - timedelta(minutes=30)
        query = query.where(time_beg <= AccessHistory.datetime_stamp, 
                            time_end >= AccessHistory.datetime_stamp)
        query = query.limit(10).order_by(AccessHistory.id.desc())

        results = session.exec(query).all()
        return results

    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Failed to fetch access history: {str(e)}")
    

